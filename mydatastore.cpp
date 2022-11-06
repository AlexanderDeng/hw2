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
  ofile << "<products>" << endl; 
  for (j = productSet.begin(); j != productSet.end(); j++) //iterates through products and dumps them 
  {
    (**j).dump(ofile); 
  }
  ofile << "</products>" << endl; 
  
  ofile << "<users>" << endl; 
  for (k = userMap.begin(); k != userMap.end(); ++k) //iterates through userMap and dumps to the user object pointer
  {
    k->second->dump(ofile);
  }
  ofile << "</users>" << endl; 
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
    cout << "Invalid request" << endl; 
  }
}

void MyDataStore::viewCart(std::string user)
{
  if (cartMap.find(user) != cartMap.end()) //if user is found 
  {
    int x = 1; //to list the item numbers 
    for (vector<Product*>::iterator it = cartMap[user].begin(); it != cartMap[user].end(); ++it) //iterate thru user's cart 
    {
      cout << "Item " << x++ << endl //cout Item x and then the item.displaystring shit
           << (*it)->displayString() << endl;
    }
  }
  else
  {
    cout << "Invalid username" << endl; 
  }
}

void MyDataStore::buyCart(std::string user)
{
  map<string, vector<Product*>>::iterator cartMapIt = cartMap.find(user); 
	if (cartMapIt == cartMap.end()) //checks if user exists 
  {
		cout << "Invalid username" << endl;
		return;
	}
  else 
  {
    for (vector<Product*>::iterator it = cartMap[user].begin(); it != cartMap[user].end();) //iterate thru user's cart 
    {
      if ((*it)->getQty() >= 1 && userMap[user]->getBalance() >= (*it)->getPrice()) //if enough in stock and enough in balance 
      {
        (*it)->subtractQty(1); //reduce quantity 
        userMap[user]->deductAmount((*it)->getPrice()); //deduct price from user's balance 
        cartMap[user].erase(it); //remove pointer to item from their cart if bought successfully 
      }
      else
        ++it; //if too broke to buy the current item advances pointer to see if you can buy the next 
    }
  }
}
