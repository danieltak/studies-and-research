#  Cpp Snippets

<!-- vscode-markdown-toc -->
* 1. [Introduction](#Introduction)
* 2. [Time ellapsed](#Timeellapsed)

<!-- vscode-markdown-toc-config
	numbering=true
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->



##  1. <a name='Introduction'></a>Introduction

On this document there are some code snippets for C++ 17.
For reuse and lesser the research time.

##  2. <a name='Timeellapsed'></a>Time ellapsed

This snippet contains a time counter for measuring elapsed time.

The [following code](https://stackoverflow.com/a/21995693/7690982) has a template `since()` function used for this purpose.

```cpp
// .h
#include <chrono>

std::chrono::steady_clock::time_point m_testTimer;
template <
    class result_t   = std::chrono::milliseconds,
    class clock_t    = std::chrono::steady_clock,
    class duration_t = std::chrono::milliseconds
>
auto since(std::chrono::time_point<clock_t, duration_t> const& start)
{
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}

// .cpp
m_testTimer = std::chrono::steady_clock::now();
// Do something
std::cout << "Time elapsed (ms):" << since(m_testTimer).count() << std::endl;
```

Or when you want to measure the time the code takes to return to this function , you can reset at the end of the task and mease at the beggining and initialize the variable on the constuctor with the following pseudo code on the cpp file:

```cpp
// .cpp
//constructor
m_testTimer = std::chrono::steady_clock::now();
// function
std::cout << "Time elapsed (ms):" << since(m_testTimer).count() << std::endl;
// Do something
m_testTimer = std::chrono::steady_clock::now();
```

A class can be creating for taking snapshots of now and return the elapsed time.