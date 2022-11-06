#include <iostream> 
#include <iomanip> 
#include <sstream> 
#include "book.h"
#include "util.h"
#include <string> 
#include <set>
#include <list>
#include <map> 
using namespace std; 

set<string> Book::keywords() const 
{
  set<string> words; 
  set<string> author;
  set<string>::iterator authorIt; 
  words = parseStringToWords(name_); 
  author = parseStringToWords(author_); 
  for (authorIt = author.begin(); authorIt != author.end(); ++authorIt)
  {
    words.insert(*authorIt); 
  }
  words.insert(to_string(price_));
  words.insert(to_string(qty_)); 
  words.insert(isbn_);
  return words; 
}

string Book::displayString() const
{
  stringstream ss; 
  ss << name_ << "\n" << "Author: " << author_ <<" "<< "ISBN: " << isbn_ << "\n" << setprecision(2) << fixed << price_ << " " << qty_ << " " << "left." << "\n" << endl; 
  return ss.str(); 
}

void Book::dump(ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}

Book::Book(const string category, const string name, double price, int qty, string isbn, string author) : Product(category, name, price, qty)
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
  vector<string>::iterator i; 
  return true; 
}