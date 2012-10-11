#include <cstdlib>
#include <iostream>
#include <csignal>

void handle(int) 
{
   std::signal(SIGSEGV, SIG_DFL);
   std::cout << "Catched segfault !!!" << std::endl;
   std::abort();
}

int main(int argc, char* argv[])
{
   int error = EXIT_SUCCESS;
   std::signal(SIGSEGV, handle);

   char *s = const_cast<char *>("Stupid!"); 
   *s = 'S';

   return error;
}
