#include <iostream> 
#include <sstream> 
#include "book.h"
#include "util.h"
#include <string> 
#include <set>
#include <list>
#include <map> 
using namespace std; 

set<string> Book::keywords()  
{
  set<string> words; 
  words = parseStringToWords(name_);
  words.insert(to_string(price_));
  words.insert(to_string(qty_)); 
  words.insert(isbn_);
  words.insert(author_);
  return words; 
}

string Book::displayString() const
{
  stringstream ss; 
  ss << name_ << " " <<  price_ << " " << qty_ << " " << isbn_ << " " << author_ << endl; 
  return ss.str(); 
}

void Book::dump(ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}

Book::Book(string category, string name, double price, int qty, string isbn, string author) : Product(category_, name_, price_, qty_)
{
  //category_ = category; 
  //name_ = name; 
  //price_ = price; 
  //qty_ = qty; 
  isbn_ = isbn; 
  author_ = author; 
}

bool Book::isMatch(std::vector<std::string>& searchTerms) const//implement later
{
  return true; 
}