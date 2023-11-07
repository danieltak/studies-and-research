#  Cpp Snippets

<!-- vscode-markdown-toc -->
* 1. [Introduction](#Introduction)
* 2. [Time ellapsed](#Timeellapsed)
* 3. [Minimize and Maximize X11 Window](#MinimizeandMaximizeX11Window)
* 4. [Convert Hex String to Unsigned Int and then convert to ASCII String](#ConvertHexStringtoUnsignedIntandthenconverttoASCIIString)

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

##  3. <a name='MinimizeandMaximizeX11Window'></a>Minimize and Maximize X11 Window

Sometimes Qt default functions won't handle properly the Window, so X11 libraries are needed to handle.

To add to the project, the following CMakeLists configuration:

```Cmake
find_package(X11 REQUIRED)

include_directories(${X11_INCLUDE_DIR})
link_libraries(${X11_LIBRARIES})
```

Includes:

```cpp
#include <X11/Xlib.h>
```

Use `XIconifyWindow()` to minimize the window, on Qt6 the following code:

```cpp
// If there is only one Window
MainWindow * win = (MainWindow *) qApp::activeWindow();
Display *display = nullptr;
xcb_connection_t *connection = nullptr;
bool bIsPlatformX11 = false;
if (auto *x11Application = qGuiApp->nativeInterface<QNativeInterface::QX11Application>())
{
    display = x11Application->display();
    connection = x11Application->connection();
    bIsPlatformX11 = true;
}
XIconifyWindow( display, win->winId(), 0);
```

To maximize:

```cpp
// If there is only one Window
MainWindow * win = (MainWindow *) qApp::activeWindow();
Display *display = nullptr;
xcb_connection_t *connection = nullptr;
bool bIsPlatformX11 = false;
if (auto *x11Application = qGuiApp->nativeInterface<QNativeInterface::QX11Application>())
{
    display = x11Application->display();
    connection = x11Application->connection();
    bIsPlatformX11 = true;
}
// Show
XMapWindow( display, win->winId() );
// Hide
// XUnMapWindow( display, win->winId() );
```

##  4. <a name='ConvertHexStringtoUnsignedIntandthenconverttoASCIIString'></a>Convert Hex String to Unsigned Int and then convert to ASCII String

First a struct of characters of an ASCII table is created and then an array of structs is created for the Special Characters (first 31 items from ASCII table).

A function that converts Hex string to a BYTE (unsigned int) vector using `strtol` STL function was used from the following answer: https://stackoverflow.com/questions/17261798/converting-a-hex-string-to-a-byte-array

Later it recreates the string by replacing special characters with special character symbol between brackets.

```cpp
#include <iostream>

#include <string>
#include <vector>

using namespace std;

// Special Characters ASCII
typedef struct
{
    unsigned int   iDec;
    unsigned int   iOct;
    std::string         strHex;
    std::string         strChar;
} SpecialCharsItemStruct;

const SpecialCharsItemStruct SpecialCharsItems[] =
    {
        // iDec,          iOct,           strHex,       strChar
        {  0,               0,              "00",        "[NUL]" },
        {  1,               1,              "01",        "[SOH]" },
        {  2,               2,              "02",        "[STX]" },
        {  3,               3,              "03",        "[ETX]" },
        {  4,               4,              "04",        "[EOT]" },
        {  5,               5,              "05",        "[ENQ]" },
        {  6,               6,              "06",        "[ACK]" },
        {  7,               7,              "07",        "[BEL]" },
        {  8,              10,              "08",        "[BS]" },
        {  9,              11,              "09",        "[TAB]" },
        { 10,              12,              "0A",        "[LF]" },
        { 11,              13,              "0B",        "[VT]" },
        { 12,              14,              "0C",        "[FF]" },
        { 13,              15,              "0D",        "[CR]" },
        { 14,              16,              "0E",        "[SO]" },
        { 15,              17,              "0F",        "[SI]" },
        { 16,              20,              "10",        "[DLE]" },
        { 17,              21,              "11",        "[DC1]" },
        { 18,              22,              "12",        "[DC2]" },
        { 19,              23,              "13",        "[DC3]" },
        { 20,              24,              "14",        "[DC4]" },
        { 21,              25,              "15",        "[NAK]" },
        { 22,              26,              "16",        "[SYN]" },
        { 23,              27,              "17",        "[ETB]" },
        { 24,              30,              "18",        "[CAN]" },
        { 25,              31,              "19",        "[EM]" },
        { 26,              32,              "1A",        "[SUB]" },
        { 27,              33,              "1B",        "[ESC]" },
        { 28,              34,              "1C",        "[FS]" },
        { 29,              35,              "1D",        "[GS]" },
        { 30,              36,              "1E",        "[RS]" },
        { 31,              37,              "1F",        "[US]" }
    };

std::vector<unsigned int> HexToBytes(const std::string& hex) {
  std::vector<unsigned int> bytes;

  for (unsigned int i = 0; i < hex.length(); i += 2) {
    std::string byteString = hex.substr(i, 2);
    unsigned int byte = (unsigned int) strtol(byteString.c_str(), NULL, 16);
    bytes.push_back(byte);
  }

  return bytes;
}

int main()
{
    std::string strHex = "0148656C6C6F20576F726C0064";
    std::string strText = "";
    std::vector<unsigned int> vRet = HexToBytes( strHex );
    cout << "Numbers: " << endl;
    for( auto i : vRet)
    {
        std::string strCharacterToAppend;
        
        cout << i << endl;
        
        if (i >= 0 && i < 32 )
        {
            strCharacterToAppend = SpecialCharsItems[ i ].strChar;
            //cout << SpecialCharsItems[ i ].strChar << endl;
        }
        else
        {
            strCharacterToAppend = i;
        }
        strText.append( strCharacterToAppend );
    }
    
    
    cout << "String: " << strText << endl;
    return 0;
}

```

The output of this example is:

```
Numbers: 
1
72
101
108
108
111
32
87
111
114
108
0
100
String: [SOH]Hello Worl[NUL]d
```

## Free memory vector of pointers

```cpp
/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

struct myStructure{             // Structure declaration
  int myNum;         // Member (int variable)
  string myString;   // Member (string variable)
} ;       // Structure variable

int main()
{
    std::vector<myStructure*> vStructure;

    cout<<sizeof(myStructure) << " " << sizeof(vStructure) << endl;
    
    for(int i=0; i<10;i++)
    {
        myStructure* pStructure = new myStructure;
        pStructure->myNum = i;
        pStructure->myString = i + 39;
        vStructure.push_back( pStructure );
    }
    myStructure*& pStructureCopy = vStructure[8];
     cout << vStructure.size() << " " << pStructureCopy->myNum << " " << pStructureCopy->myString <<endl;
    for(auto ptrObj : vStructure )
    {
        delete ptrObj;
    }    
    vStructure.clear();
    vStructure = vector<myStructure*>(); 
     
     cout << vStructure.size() << " " << vStructure.capacity() << " " << (pStructureCopy == nullptr) 
     << " " <<endl;
    return 0;
}
```