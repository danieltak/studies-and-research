# Meetings Notes
<!-- vscode-markdown-toc -->
* 1. [Breaking Dependencies: The Path to High-Quality Software](#BreakingDependencies:ThePathtoHigh-QualitySoftware)
	* 1.1. [Introduction](#Introduction)
	* 1.2. [Graph of a low Quality Software project](#GraphofalowQualitySoftwareproject)
	* 1.3. [Quality Matters](#QualityMatters)
	* 1.4. [Design Patterns](#DesignPatterns)
		* 1.4.1. [The Classic Factory Method Design Pattern](#TheClassicFactoryMethodDesignPattern)
	* 1.5. [The Classic Strategy Design Pattern](#TheClassicStrategyDesignPattern)
	* 1.6. [The Many Choices of Design Patterns](#TheManyChoicesofDesignPatterns)
	* 1.7. [Singleton Pattern](#SingletonPattern)
* 2. [std::function a deep dive behind the curtain](#std::functionadeepdivebehindthecurtain)
	* 2.1. [Intro](#Intro)
		* 2.1.1. [Function signature are types](#Functionsignaturearetypes)
		* 2.1.2. [Variable with pointer to function](#Variablewithpointertofunction)
		* 2.1.3. [constexpr function pointer](#constexprfunctionpointer)
		* 2.1.4. [Summary](#Summary)
	* 2.2. [Why use std::function?](#Whyusestd::function)
		* 2.2.1. [Calback Example](#CalbackExample)
		* 2.2.2. [Task Scheduler example](#TaskSchedulerexample)
		* 2.2.3. [Function template signature](#Functiontemplatesignature)
		* 2.2.4. [Call Interface](#CallInterface)

<!-- vscode-markdown-toc-config
	numbering=true
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->

##  1. <a name='BreakingDependencies:ThePathtoHigh-QualitySoftware'></a>Breaking Dependencies: The Path to High-Quality Software

###  1.1. <a name='Introduction'></a>Introduction

> Klaus Iglberger

Software must change constantly, but It is not easy to design a software to meet those requirements.

Definition of Software Design:

> Software Design is the art of managing interdependencies between software components. It aims at minimizing (technical) dependencies and introduces the necessary abstractions and compromises.

Easy to change, maintain and test, with abstractions to deal with complexity.

###  1.2. <a name='GraphofalowQualitySoftwareproject'></a>Graph of a low Quality Software project

The graph of a Software project for Software Development x Time. In the beginning it starts as a optimal delevopment, without issues and pretty fast, but after some time the quality starts to decrease due to lack of design.

- Things are getting more difficult to change
- New features become more difficult to add
- Less time is left to care about the code

After some more time:

- More and more bugs creep in
- More time is wasted in debugging
- Even less time is left to care about the code

Later more people are hired:

- New devs need training
- Less time for the old devs

Point of maxiumum frustation:

- Difficult to meet deadlines
- Devs leave the company

###  1.3. <a name='QualityMatters'></a>Quality Matters

> The implementation details matters, but the design matters more!

> The design plays a much more central role in the success of a project than any feature could ever do. Good software is not primarily about the proper use of any feature, rather, it is about solid architecture and design.
> Good software design can tolerate some bad implementation decisions, but bad software design cannot be saved by the heroic use of features alone.

###  1.4. <a name='DesignPatterns'></a>Design Patterns

####  1.4.1. <a name='TheClassicFactoryMethodDesignPattern'></a>The Classic Factory Method Design Pattern

Define an interface for creating an object, but let subclasses decide which class to instantiate. Factory Method lets a class defer instantiation to subclasses.

It is often used as synonym for "creating something", std::make_unique() is an example.

We can separate this pattern on High level and Low level, so the application use and implementation details

std::make_unique() is not a Factory Method, because it does not allow customization, does not manage the relationship between entities, does not invert dependencies, does not help to break dependencies and is not a method, it is a function. A virtual function is sometimes called a method in C++.

So it is an example of a factory function.

###  1.5. <a name='TheClassicStrategyDesignPattern'></a>The Classic Strategy Design Pattern

The Context points to the strategy, the strength is delegation and has an architecture boundary between use and implementation details (Low and High level).

The classic OO Strategy is often considered to be the ONE implementation, nothing could be further from the truth. The C++ Standards Library itself has multiple strategies.

```cpp
template<
    class T,
    class Deleter = std::default_delete<T>
> class unique_ptr;
```

The Deleter is a strategy.

```cpp
template<
    class Key,
    class Hash = std::hash<Key>,
    class KeyEqual = std::equal_to<Key>,
    class Allocator = std::allocator<Key>
> class unordered_set;
```

Hash, KeyEqual and Allocator are strategies.

###  1.6. <a name='TheManyChoicesofDesignPatterns'></a>The Many Choices of Design Patterns

> It depends...

As every complex solution, there is no magic formula to solve the problem. It is difficult and complicated, so the designer needs a solid base of knowledge.

List of people to follow:

- Charles Bay
- Tony van Eerd
- Mike Shah

###  1.7. <a name='SingletonPattern'></a>Singleton Pattern

> Ensure that a class has only one instance, while providing a global access point to this instance.

A common form of Singleton is the so-called 'Meyers' Singleton'

```cpp
// Singleton.h
class Singleton
{
public:
  static Singleton& Instance()
  {
    if (!pInstance)
    {
      if (destroyed)  // check for dead reference
      {
        OnDeadReference();
      }
      else            // create on first call
      {
        Create();
      }
    }
    return *pInstance_;
  }

  virtual ~Singleton()
  {
    pInstancce_ = 0;
    destroyed_ = true;
  }

private:
  static void Create()
  {
    static Singleton theInstance;
    pInstance_ = &theInstance;
  }

  static void OnDeadReference()
  {
    throw std::runtime_error("Dead Reference Detected");
  }

  // variables
  static Singleton* pInstance_;
  static bool       destroyed_;

  // disabled - do not implement
  Singleton(const Singleton&)
  Singleton& operator=(const Singleton&);
};

// Singleton.cpp
Singleton * Singleton::pInstance_ = 0;
bool        Singleton::destroyed_ = false;
```

> Anytime you make something accessible to every part of your program, you're asking for trouble.

Global variables are a bad ideia because:

- they represent mutable state;
- read and write operations are difficult to control, especially on multi-threaded environments;
- they are hard to reason about;
- may be subject to the Static Initialization Order Flask (SIOF).

> There are times when manually passing around an object is gratuitous or actively makes code harder to read. Some systems, like logging or memory management, shouldn't be part of a module's public API.

So it seems that sometimes we need Singletons, but Singletons create dependencies.

##  2. <a name='std::functionadeepdivebehindthecurtain'></a>std::function a deep dive behind the curtain

> Andreas Reischuck

###  2.1. <a name='Intro'></a>Intro

```cpp
void basic_function(){}
// is the same as:
auto trailing_basic_function() -> void {}
```

####  2.1.1. <a name='Functionsignaturearetypes'></a>Function signature are types

```cpp
using VoidFunction = void();
// same as:
using TrailingVoidFunction = auto() -> void;
```

####  2.1.2. <a name='Variablewithpointertofunction'></a>Variable with pointer to function

```cpp
using VoidFunction = void();
// same as:
using VoidFunctionPtr = VoidFunction*;

auto basic_function_ptr = VoidFunctionPtr{&basic_function}
```
####  2.1.3. <a name='constexprfunctionpointer'></a>constexpr function pointer

```cpp
constexpr auto consexpr_basic_function_ptr = VoidFunctionPtr{&basic_function};
```

####  2.1.4. <a name='Summary'></a>Summary

- Function signatures are types
- we can store pointers to functions
- Function pointers are known to compile time

###  2.2. <a name='Whyusestd::function'></a>Why use std::function?

####  2.2.1. <a name='CalbackExample'></a>Calback Example

A user clicks a button and you want to trigger an action, but the class doesn't know what to do, how to implement?

```cpp
struct Button
{
  VoidFunctionPtr clicked;
};

struct EditDialog
{
  Button okButton;
  Button cancelButton;
}

void onOkClicked();
void onCancelClicked();
```

How can we call the instance methos of the Dialog on clicked?

You can use a void pointer:

```cpp
using VoidVoidPtrFunction = void(void *);

struct Button
{
  void* clicked_instance;
  VoidVoidPtrFunction clicked;
};

// avoid this C-style approach
```

Oject Oriented approach:

```cpp
struct ClickableInterface
{
  virtual ~ClickavleInterface() = default;
  virtual void onClicked() = 0;
};

struct EditDialog
{
  Button okButton;
  Button cancelButton;
};

// also avoid
```

std::function approach:

```cpp
#include <functional>

using CallbackFunc = std::function<void()>;
struct Button
{
  CallbackFunc clicked;
};

EditDialog::EditDialog()
{
  okButton.clicked = [this]()
  {
    this->onClicked();
  };
}
```

####  2.2.2. <a name='TaskSchedulerexample'></a>Task Scheduler example

You can have multiple object types as inputs to the task scheduler.

```cpp
struct Scheduler
{
  using Task = std::function<void()>;

  void queueUpTask( const Task& );

private:
  std:queue<Task> queue;
};
```

####  2.2.3. <a name='Functiontemplatesignature'></a>Function template signature

```cpp
using IntFunction = Function<void(int)>;

template<class Signature>
struct Function;

// Partial Template Specialization
template <class Ret, class... Args>
struct Function<Ret(Args...)> {};
```
