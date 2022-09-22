#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>
#include <vector> 
#include <algorithm> 


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
  std::set<T> intersect; 
  typename std::set<T>::iterator is1; 
  for (is1 = s1.begin(); is1 != s1.end(); ++is1)
  {
    if (s2.find(*is1))
    {
      intersect.insert(*is1); 
    }
  }
  
  return intersect; 
}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
  std::set<T> u;
  u = s2;
  typename std::set<T>::iterator is1;
  for(is1 = s1.begin(); is1 != s1.end(); ++is1)
  {
    if (!s2.find(*is1))
    {
      u.insert(*is1);
    }
  }
  return u; 
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
