#include <iostream> 
#include <sstream> 
#include "clothing.h"
#include "util.h"
#include <string>
#include <set>
#include <map>

using namespace std; 

set<string> Clothing::keywords()
{
  set<string> words; 
  words = parseStringToWords(name_); 
  words.insert(to_string(price_));
  words.insert(to_string(qty_)); 
  words.insert(size_);
  words.insert(brand_); 

  return words; 
}

string Clothing::displayString() const
{
  stringstream ss; 
  ss << name_ << " " << price_ << " " << qty_ << " " << size_ << " " << brand_ << endl; 
  return ss.str(); 
}

void Clothing::dump(ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}

Clothing::Clothing(string category, string name, double price, int qty, string size, string brand) : Product(category_, name_, price_, qty_)
{
  size_ = size; 
  brand_ = brand; 
}