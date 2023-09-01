/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <thread>


void
test ()
{
  std::cout << "Testing thread id: " << std::this_thread::get_id() << std::endl;
}

int
main ()
{

  std::cout << "Starting" << std::this_thread::get_id() << std::endl;
  test ();
  std::cout << "Finished" << std::this_thread::get_id() << std::endl;

  return 0;
}
