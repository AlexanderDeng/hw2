#include <iostream> 
#include <iomanip> 
#include <sstream> 
#include "clothing.h"
#include "util.h"
#include <string>
#include <set>
#include <map>

using namespace std; 

set<string> Clothing::keywords() const
{
  set<string> words; 
  set<string> brand;
  set<string>::iterator brandIt; 
  words = parseStringToWords(name_); 
  brand = parseStringToWords(brand_); 
  for (brandIt = brand.begin(); brandIt != brand.end(); ++brandIt)
  {
    words.insert(*brandIt); 
  }
  words.insert(to_string(price_));
  words.insert(to_string(qty_)); 
  words.insert(size_);
  return words; 
}

string Clothing::displayString() const
{
  stringstream ss; 
  ss << name_ << "\n" << "Size: " << size_ <<" "<< "Brand: " << brand_ << "\n" << setprecision(2) << fixed << price_ << " " << qty_ << " " << "left." << "\n" << endl; 
  return ss.str(); 
}

void Clothing::dump(ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}

Clothing::Clothing(const string category, const string name, double price, int qty, string size, string brand) : Product(category, name, price, qty)
{
  size_ = size; 
  brand_ = brand; 
}