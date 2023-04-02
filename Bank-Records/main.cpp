// Computer Programming, XB_40011, Fall 2018
// Vrije Universiteit, Amsterdam
//
// (GRADED) Assignment 6.2 "Bank Records"
// 
// Submit this assignment to Canvas!
// By doing so you declare to comply to the regulations as stated
// on the page on "Ethical behaviour and fraud" in the course's
// Canvas site.
//
// Student name   : Meroon tesfai keleta sengal
// Student number : 2646691
// VUnet-id       : mel450
//
// Fill in your details above,
// then enter your code below this header.
//
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

class bank_account{
  public:
  void set_name(const string& account_name);
  string get_name() const;

  void set_account_type(bool is_credit);
  bool get_account_type() const;

  void set_balance(double amount);
  double get_balance() const;
  
  private:
  string name;
  bool credit;
  double balance;
};

void bank_account::set_name(const string& account_name){
  name = account_name;
}

void bank_account::set_account_type(bool is_credit){
  credit = is_credit;
}

void bank_account::set_balance(double amount){
  if (amount < 0.0 && !get_account_type()){
   throw runtime_error("account cannot hold negative balance");
  }
  balance += amount; 
}

double bank_account::get_balance()const{
  return balance;
}

string bank_account::get_name() const{
  return name;
}

bool bank_account::get_account_type() const{
  return credit;
}

class registry {
  public:
  void account_creation(const string& name, bool is_credit);
  void account_transaction(const string& name, double amount);
  void account_removal(const string& name);
  bool is_exist(const string& account_name) const;
  void print();

  private:
  bank_account& fetch_account(const string& account_name);
  vector <bank_account> reg;
};

bank_account& registry::fetch_account(const string& account_name){
  for(int i = 0; i < reg.size(); i++){
   if(reg.at(i).get_name() == account_name){
    return reg[i];
   }
  }
  throw runtime_error("account does not exist");
}

bool registry::is_exist(const string& account_name) const{
  for(int i = 0; i < reg.size(); i++){
   if(account_name == reg.at(i).get_name()){
    return true;
   }
  }
  return false;
}

void registry::account_creation(const string& name, bool is_credit){
  if(is_exist(name)){
   throw runtime_error("account already exists");
  }
  bank_account new_account;
  new_account.set_name(name);
  new_account.set_account_type(is_credit);
  new_account.set_balance(0);
  reg.push_back(new_account);
}

void registry::account_transaction(const string& name, double amount){
  fetch_account(name).set_balance(amount);
}

void registry::account_removal(const string& name){
  for(int i = 0; i < reg.size(); i++){
   if(reg.at(i).get_name() == name){
    if(reg.at(i).get_balance() >= 0){
     reg.erase(reg.begin() + i);
      return;
    }
    else{
     throw runtime_error("account holds negative balance");
    }
   }
  }
  throw runtime_error("account does not exist");
}

void registry::print(){
  for(int i = 0; i < reg.size(); i++){
   if(reg.at(i).get_balance() < 0){
    cout << reg.at(i).get_name() << " owes " << - reg.at(i).get_balance() << " euros " << endl;
   }
   else{
    cout << reg.at(i).get_name() << " owns " <<  reg.at(i).get_balance() << " euros " <<endl;
   }
  }
}

int main(){
  ifstream inFS;
  string input;
  
  cout << "Enter the name of the records file: " << endl;
  cin >> input;
   
  inFS.open(input); 
  
  if (!inFS.is_open()) {
   cout << "Could not open file " << input << endl;
  }  

  registry bank;
  int line = 0;
  
  while(inFS){
   try{
    char type;
    string name;
    char is_credit;
    double amount;
    line++;

    inFS >> type >> name;
    if (!inFS) break;

    if (type == 'c') {
        inFS >> is_credit;
        bank.account_creation(name, is_credit == 'y');
    }
    
    else if (type == 't') {
        inFS >> amount;
        bank.account_transaction(name, amount);
    }
    
    else if (type == 'r') {
        bank.account_removal(name);
    }
   }

   catch (const runtime_error &excpt){
   cout << "error on line " << line << ": " << excpt.what() << endl;
   }
  }
  
  bank.print();
  
  inFS.close();
  
  return 0;
}
