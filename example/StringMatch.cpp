#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cstring>

class MyClass
{
   public:
      template<class T, class traits>
      static uint32_t getNICount()
      {
         uint32_t count = 0;

         return count;
      }

      template<class T, class traits>
      static std::string replaceNiWithNI(std::string string)
      {
      }
};

int main()
{
   const char *szTestString1 = "Ni nI NI nI Ni";
   const wchar_t *szTestString2 = L"Ni nI NI nI Ni";
   
   // Aufruf getNiCount(...) der Klasse MyClass
   uint32_t count = MyClass::getNICount(std::string(szTestString2));
   
   // Aufruf replaceNiWithNI(...) der Klasse MyClass
   //std::string szString = MyClass::replaceNiWithNI(std::string(szTestString2));
   
   // Ausgabe: "Ni ist X mal enthalten. Neuer String: Y"
   //std::cout << "Ni ist " << count << " ist mal enthalten. " 
   //   << "Neuer String: " << szString << std::endl; 
   
   return EXIT_SUCCESS;
}
