#include <string>
#include <set>
#include <vector>
#include <iostream> 
#include "product.h"
#include "user.h"
#include "datastore.h"
#include <map> 


class MyDataStore : public DataStore 
{
  public: 
    MyDataStore(); 
    ~MyDataStore(); 
    void addProduct(Product* p); 
    void addUser(User* u); 
    std::vector<Product*> search(std::vector<std::string>& terms, int type); 
    void dump(std::ostream& ofile);
    void addCart(std::string user, Product* p);
    void viewCart(std::string user);  
    void buyCart(std::string user); 
protected:
    std::map<std::string, User*> userMap; 
    std::vector<Product*> productSet; 
    std::map<std::string, std::vector<Product*>> cartMap; 
    std::map<std::string, std::set<Product*>> keywordToProduct; 
    std::vector<Product*> hits; 
    std::vector<User*> userVector; 
}; 