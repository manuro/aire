#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <string>
#include <cstring>

#include "Watch.h"

class MyClass
{
  public:
    //! \brief Count the occurrences of the fixed substring "Ni".
    //! \param szString String to analyze.
    //! \return Number of substring occurrences. 
    template<class T>
    static uint32_t getNICount(const std::basic_string<T>& szString)
    {
      // Counter for the occurrences of the substring
      uint32_t nCount = 0;
      // We love c++11 auto :-)
      auto it = szString.begin();
      // Until iterator is at the end
      while(it != szString.end())
      {
        // Check character i 
        if(*it == 'N')
        {
          // Move to character i+1 or end
          ++it;
          // Check boundary of sliding window
          if(it == szString.end()) 
          {
            // Iterator is at the end of input
            break;
          }
          else
          {
            // Check character i+1
            if(*it == 'i')
            {
              // Found substring increment counter
              nCount++;
              // Go to character i+2
              ++it;
            }
          }
        }
        else
        {
          // Character i is not N so move to i+1
          ++it;
        }
      }
      return nCount;
    }

    //! \brief Replaces substrings "Ni" by "NI" fixed key/value. Not in situ. 
    //         Fast but not maintainable and generic in respect to key/value.
    //! \param szString String to transform.
    //! \return String with substituted substrings.
    template<class T> 
    static std::basic_string<T> replaceNiWithNI(const std::basic_string<T>& szString)
    {
      // Result string
      std::basic_string<T> szResult;
      // Reserve memory for performance
      szResult.reserve(szString.length()); 
      // Create string iterator
      auto it = szString.begin();
      // Until iterator is at the end
      while(it != szString.end())
      {
        // Check character i 
        if(*it == 'N')
        {
          // Move to character i+1 or end
          ++it;
          // Check boundary of sliding window
          if(it == szString.end()) 
          {
            // Iterator is at the end of input
            szResult += 'N';
            break;
          }
          else
          {
            // Check character i+1
            if(*it == 'i')
            {
              // Found substring so replace
              szResult += 'A';
              szResult += 'B';
              //szResult += "AB";
              ++it;
            }
            else
            {
              // Insert the first char of sliding window
              szResult += 'N';
            }
          }
        }
        else
        {
          // Character i is not N so move to i+1
          szResult += *it;
          ++it;
        }
      }
      return szResult;
    }

    //! \brief Substitute all substrings in a string using 
    //         Knuth-Morris-Pratt-Algorithmus in O(n+m). Not insitu.
    //         Slower but variable key/value pairs.
    //! \param szString String to transform.
    //! \param szKey Substring to search for.
    //! \param szValue Substitution string.
    template<class T> 
    static std::basic_string<T> replaceKMP(const std::basic_string<T>& szString,
        const std::basic_string<T>& szKey, const std::basic_string<T>& szValue)
    {
      std::basic_string<T> szResult(szString);
      size_t m = szString.length();
      size_t n = szKey.length();
      uint32_t i = 0;
      int j = -1;
      int pi[n+1];
      
      // Prefix analysis 
      pi[0] = -1;
      while(i < n)
      {
        while(j >= 0 && szKey[j] != szKey[i])
        {
          j = pi[j];
        }
        i++;
        j++;
        pi[i] = j;
      }

      // Search and replace
      i = 0;
      j = 0;
      while(i < m)
      {
        while(j >= 0 && szResult[i] != szKey[j])
        {
          j = pi[j];
        }
        i++;
        j++;
        if(j == n)
        {
          if(szValue.length() > n)
          {
            // String to substitute is larger than key
            szResult.replace(i-n, n, szValue.substr(0,n));
            // Insert additional substitution characters
            szResult.insert(i,szValue.substr(n));
            j = pi[j];
            // Shift next search index by difference
            i += szValue.length()-n;
            // Readjust string length boundary
            m = szResult.length();
          }
          else if (szValue.length() < n)
          {
            // String to substitute is smaller than key
            szResult.replace(i-n, szValue.length(), szValue);
            // Delete superseded characters
            szResult.erase(i-n+szValue.length(), n-szValue.length());
            j = pi[j];
            // Shift next search index by difference
            i -= n-szValue.length();
            // Readjust string length boundary
            m = szResult.length();
          }
          else if (szValue.length() == n)
          {
            // String to substitute equals key size
            szResult.replace(i-n, n, szValue.substr(0,n));
            j = pi[j];
          }
        }
      }
      return szResult;
    }
};

//! \brief Singleton type of the watch.
typedef aire::Singleton<aire::Watch<wchar_t>> StopWatch;

int main()
{
  // Unicode version ----------------------------------------------------------
  const wchar_t *szMyTestString = L"NiNi NI N ni NNi nI Niinii";
  const wchar_t *szTestString2 = L"Ni nI NI nI Ni";
  const char *szTestString1 = "Ni nI NI nI Ni";
  
  uint32_t nCount = 0;
  std::basic_string<wchar_t> szResult;

  // Aufruf getNiCount(...) der Klasse MyClass
  StopWatch::GetInstance()->getTimer(L"Count")->start();
  for(uint32_t k = 0; k < 1e6; k++)
  {
    //nCount = MyClass::getNICount<wchar_t>(szTestString2);
    //nCount = MyClass::getNICount<char>(szTestString1);
    nCount = MyClass::getNICount<wchar_t>(szMyTestString);
  }
  StopWatch::GetInstance()->getTimer(L"Count")->stop();

  // Aufruf replaceNiWithNI(...) der Klasse MyClass
  StopWatch::GetInstance()->getTimer(L"Replace")->start();
  for(uint32_t k = 0; k < 1e7; k++)
  {
    //szResult = MyClass::replaceNiWithNI<wchar_t>(szTestString2);
    //szResult = MyClass::replaceNiWithNI<char>(szTestString1);
    szResult = MyClass::replaceNiWithNI<wchar_t>(szMyTestString);
    //szResult = MyClass::replaceKMP<wchar_t>(szMyTestString, L"Ni", L"AB");
  }
  StopWatch::GetInstance()->getTimer(L"Replace")->stop();

  // Ausgabe: "Ni ist X mal enthalten. Neuer String: Y"
  std::wcout << "Ni ist " << nCount << " ist mal enthalten. " 
             << "Neuer String: " << szResult.c_str() << std::endl; 

  StopWatch::GetInstance()->printTime(std::wcout, false);
  return EXIT_SUCCESS;
}
