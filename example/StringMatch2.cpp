#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <cstring>

class MyClass
{
   public:
      template<typename T>
      static uint32_t getNICount(const T* string)
      {
         uint32_t count = 0;

         return count;
      }

      template<typename T>
      static T* replaceNiWithNI(const T* string)
      {
         T* szNewString;
         return szNewString;
      }
};

int main()
{
   const char *szTestString1 = "Ni nI NI nI Ni";
   const wchar_t *szTestString2 = L"Ni nI NI nI Ni";
   
   // Aufruf von char ---------------------------------------------------------
   // Aufruf getNiCount(...) der Klasse MyClass
   uint32_t count = MyClass::getNICount<char>(szTestString1);
   
   // Aufruf replaceNiWithNI(...) der Klasse MyClass
   char* szNewString1 = MyClass::replaceNiWithNI<char>(szTestString1);
   
   // Ausgabe: "Ni ist X mal enthalten. Neuer String: Y"
   std::cout << "Ni ist " << count << " ist mal enthalten. " 
      << "Neuer String: " << szNewString1 << std::endl; 
   
   // Aufruf von wide char ----------------------------------------------------
   // Aufruf getNiCount(...) der Klasse MyClass
   count = MyClass::getNICount<wchar_t>(szTestString2);
   
   // Aufruf replaceNiWithNI(...) der Klasse MyClass
   wchar_t* szNewString2 = MyClass::replaceNiWithNI<wchar_t>(szTestString2);
   
   // Ausgabe: "Ni ist X mal enthalten. Neuer String: Y"
   std::cout << "Ni ist " << count << " ist mal enthalten. " 
      << "Neuer String: " << szNewString2 << std::endl; 

   return EXIT_SUCCESS;
}
