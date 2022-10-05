#include <iostream> 
#include <sstream> 
#include "book.h"
#include "util.h"
#include <string> 
#include <set>
#include "mydatastore.h"

using namespace std; 

MyDataStore::MyDataStore()
{

}

MyDataStore::~MyDataStore()
{
  vector<Product*>::iterator prodIt; 
  for (prodIt = productSet.begin(); prodIt != productSet.end(); ++prodIt) //delete products in productSet 
  {
    delete *prodIt; 
  }
  userMap.clear(); 
  cartMap.clear();  
  keywordToProduct.clear(); //clearing maps 
  vector<Product*>::iterator userVectorIt; 
  for (unsigned int i = 0; i < userVector.size(); ++i)
  {
    delete userVector[i]; 
  }
}

void MyDataStore::addProduct(Product* p)
{
  productSet.push_back(p); 
  std::set<string> keywordsSet = p->keywords(); //finds keywords for added product and puts them in temp set
  std::set<string>::iterator i; //keywordsSet iterator 
  std::map<string, set<Product*>>::iterator j; //keywordToProduct iterator 
 
  for (i = keywordsSet.begin(); i != keywordsSet.end(); ++i) 
  {
    j = keywordToProduct.find(*i); //attempts to find keyword
    if (j == keywordToProduct.end())//if keyword doesn't exists yet
    {
      std::set<Product*> temp; //temp to push new pairs into keywordToProduct
      temp.insert(p); 
      keywordToProduct.insert({*i, temp}); 
    }
    else
    {
      j->second.insert(p); //create a new pair of keywords and the product
    }
  }
}

void MyDataStore::addUser(User* u)
{
  userVector.push_back(u); 
  string username = u->getName(); 
  userMap.insert({username, u}); //create pairing of string name and pointer to user
  vector<Product* > cart; //init new cart
  cartMap.insert({username, cart}); //create pairing of that user and a cart
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type)
{
  set<Product*> temp; //declare temp vector 

  if (type != 0 && type != 1)
  {
    vector<Product*> empty; 
    cout << "Error, unknown type of search!" << endl; 
    return empty; 
  }
  if (terms.size() == 0)
  {
    cout << "No terms provided!"; 
    vector<Product*> empty; 
    return empty; 
  }

  if (type == 0) //intersection search 
  {
    temp = keywordToProduct[terms[0]]; //sets temp to the first product b.c u can't intersect an empty vector :(
    for (unsigned int q = 0; q < terms.size(); q++)
    {
      temp = setIntersection(temp, keywordToProduct[terms[q]]); //sets temp = to the intersect of each new term 
    } 
    vector<Product*> temp2(temp.begin(), temp.end()); //turns the set returned by setIntersection into a vector 
    hits = temp2;  
  }

  else if (type == 1) //union search 
  {
    temp = keywordToProduct[terms[0]]; 

    for (unsigned int i = 1; i < terms.size(); i++)
    {
      temp = setUnion(temp, keywordToProduct[terms[i]]); //only change is now calling setUnion instead.
    } 
    vector<Product*> temp2(temp.begin(), temp.end());
    hits = temp2;  
  }

  return hits; 
}

void MyDataStore::dump(std::ostream& ofile)
{
  vector<Product*>::iterator j; 
  map<string, User*>::iterator k;
  ofile << "<Products>" << endl; 
  for (j = productSet.begin(); j != productSet.end(); j++) //iterates through products and dumps them 
  {
    (**j).dump(ofile); 
  }
  ofile << "</Product>" << endl; 
  
  ofile << "<Users>" << endl; 
  for (k = userMap.begin(); k != userMap.end(); ++k) //iterates through userMap and dumps to the user object pointer
  {
    k->second->dump(ofile);
  }
  ofile << "</Users>" << endl; 
}

void MyDataStore::addCart(string user, Product* p)
{
  bool found = false; 
  map<string, vector<Product*>>::iterator k = cartMap.find(user); 
  for (k = cartMap.begin(); k != cartMap.end(); ++k) //iterates through cartMap 
  {
    if (k->first == user) //if a valid user 
    {
      (k->second).push_back(p); //add the product to the cart
      cout << "Added to cart successfully" << endl; 
      found = true; 
    }
  }
  if (!found)
  {
    cout << "Invalid Username!" << endl; 
  }
}

void MyDataStore::viewCart(std::string user)
{
  bool found = false; 
  map<string, vector<Product*>>::iterator i; 
  for (i = cartMap.begin(); i != cartMap.end(); ++i) //iterate thru map of users and their carts
  {
    if (i->first == user) //if user is found
    {
      found = true; 
      vector<Product*>::iterator j; //declare new iterator 
      for(j = i->second.begin(); j != i->second.end(); ++j) //iterate through their cart
      {
        cout << (**j).displayString() << endl; //display each product
      }
    }
  }
  if (!found) //if user not found
  {
    cout << "User not found! "; 
  }
}

void MyDataStore::buyCart(std::string user)
{
  map<string, vector<Product*>>::iterator cartMapIt = cartMap.find(user); 
	if (cartMapIt == cartMap.end()) //checks if user exists 
  {
		cout << "Invalid: User not found!" << endl;
		return;
	}
  else 
  {
    vector<Product*> userCart = cartMap.find(user)->second; //create copy of users cart 
    User* referenceUser = userMap.find(user)->second; //get reference to actual user 
    vector<Product*>::iterator cartIt = userCart.begin(); //iterator for user's cart 
    for (unsigned int i = 0; i < userCart.size(); i++) //loop through all elements of the cart vector 
    {
      if ((*cartIt)->getPrice() <= referenceUser->getBalance() && (*cartIt)->getQty() > 0) //if price is lower than bal and in stock 
      {
        userCart.erase(cartIt); //removes item from users cart 
        double bill = (*cartIt)->getPrice(); //calculates amount 
        referenceUser->deductAmount(bill); //deducts amount and buys 
        (*cartIt)->subtractQty(1); //removes 1 from stock 
      }
      if ((referenceUser->getBalance() < (*cartIt)->getPrice()) || (*cartIt)->getQty() == 0 ) //if out of stock now or not enough money
      {
			  ++cartIt; //increment it to try and buy the next item. 
      }
		}
    cartMap.find(user)->second = userCart; //updates cart 
  }	
}
