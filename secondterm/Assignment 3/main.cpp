/* @Author
  Name: Ömer Faruk Davarcı
  Number:150160048
  Date: 08.05.2019
*/
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
#define MAX_ITEM 30
#define MAX_IGREDIENTS 6
#define MENU_ITEMS 14

class Item{
protected:
  string name;
  int type;
  int count;
  float price;
public:
  Item(string n, int c, float p){
    name = n;
    count = c;
    price = p;
  }
  virtual ~Item(){
  }
  void set_values(string n, int c, float p){
    name = n;
    count = c;
    price = p;
  }
  virtual float getCount(){
    return count;
  }
  virtual void setCount(float x){
    count = x;
  }
  virtual string getName(){
    return name;
  }
  virtual int getType(){
    return type;
  }
  virtual float getCost(){
    return price*count;
  }
};

class TypeOne: public Item{
protected:
  int type;
  float weight;
  float ppg;
public:
  TypeOne(string n,float w, float p):Item(n,w,p){
    weight = w;
    ppg = p;
    type = 1;
  }
  ~TypeOne(){}

  float getCount(){
    return weight;
  }
  void setCount(float x){
    weight = x;
  }
  string getName(){
    return name;
  }
  int getType(){
    return type;
  }
  float getCost(){
    return ppg;
  }
};

class TypeTwo: public Item{
protected:
  int type;
  int number;
  float ppu;
public:
  TypeTwo(string n,float w, float p):Item(n,w,p){
    number = w;
    ppu = p;
    type = 2;
  }
  ~TypeTwo(){}

  float getCount(){
    return number;
  }
  void setCount(float x){
    number = x;
  }
  string getName(){
    return name;
  }
  int getType(){
    return type;
  }
  float getCost(){
    return ppu;
  }
};

class TypeThree: public Item{
protected:
  int type;
  float milimeter;
  float ppm;
public:
  TypeThree(string n,float w, float p):Item(n,w,p){
    milimeter = w;
    ppm = p;
    type = 3;
  }
  ~TypeThree(){}

  float getCount(){
    return milimeter;
  }
  void setCount(float x){
    milimeter = x;
  }
  string getName(){
    return name;
  }
  int getType(){
    return type;
  }
  float getCost(){
    return ppm;
  }
};

class MenuItems{
  string name;
  string ingredients[MAX_IGREDIENTS];
  int size;
public:
  MenuItems(string n, string arr[MAX_IGREDIENTS], int s){
    size = s;
    name = n;
    for (int i = 0; i < s; i++) {
      ingredients[i] = arr[i];
    }
  }
  ~MenuItems(){}
  string getName(){
    return name;
  }
  float find_ingredient(float c, string s,Item *stock_list[MAX_ITEM], int number){
    int last = 0;
    float cost = 0;

    for (int i = 0; i < size; i++) {
      if (ingredients[0].compare("N/A")){
        float number_ingredient;
        istringstream is(ingredients[i]);
        is >> number_ingredient;
        for (int j = 0; j < number; j++) {
          size_t found = ingredients[i].find(stock_list[j]->getName());
          if (found != string::npos){
            cost += number_ingredient*stock_list[j]->getCost();
          }
        }
      }
    }
    if (s == name) {
      if (ingredients[0].compare("N/A")){
        for (int i = 0; i < size; i++) {
          float number_ingredient;
          istringstream is(ingredients[i]);
          is >> number_ingredient;
          for (int j = 0; j < number; j++) {
            size_t found = ingredients[i].find(stock_list[j]->getName());
            if (found != string::npos){
              for (int k = 1; k <= c; k++) {
                if (number_ingredient*k > stock_list[j]->getCount()){
                  if (last) {
                    cout << last << " " << name << " cost: " << last*cost << endl;
                  }
                  throw "We dont have enough ";
                }else{
                  stock_list[j]->setCount(stock_list[j]->getCount()-number_ingredient);
                  last = k;
                }
              }
            }
          }
        }
        cout << last << " " << name << " cost: " << last*cost << endl;
        return last*cost;
      }else{
        for (int j = 0; j < number; j++) {
          size_t found = name.find(stock_list[j]->getName());
          if (found != string::npos){
            for (int k = 1; k <= c; k++) {
              if (k > stock_list[j]->getCount()) {
                if (last) {
                  cost = last*stock_list[j]->getCost();
                  cout << last << " " << name << " cost: " << cost << endl;
                }
                throw "We dont have enough ";
              }else{
                last = k;
              }
            }
            cost = last*stock_list[j]->getCost();
            stock_list[j]->setCount(stock_list[j]->getCount()-last);
          }
        }
        cout << last << " " << name << " cost: " << cost << endl;
        return cost;
    }
    return 0;
  }
  return 0;
}
  string getIngredients(int n){
    if (n > size) {
      throw "Out Of Ingredients Size!";
    }else{
      return ingredients[n];
    }
  }
  void print(){
     try{
       cout << this->getName();
       for (int i = 0; i < size; i++) {
         cout << " " << this->getIngredients(i);
       }
       cout << "\n";
     }catch(const char* msg){
       cerr << msg << endl;
     }
  }
};


int main(int argc, char const *argv[]) {
  Item *stock[MAX_ITEM];

  ifstream file;
  file.open("stock.txt");
  string str;
  int stock_line_counter = 0;
  int stock_counter = 0;
  while (getline(file,str)){
    if (stock_line_counter){
      istringstream ss(str);
      string substr;
      string name;
      int count;
      float price;
      int type;
      int index = 0;
      while(getline(ss, substr, '\t')){
        if (index == 0) {
          name = substr;
        }else if(index == 1){
          istringstream(substr) >> type;
        }else if(index == 2){
          istringstream(substr) >> count;
        }else if(index == 3){
          istringstream(substr) >> price;
        }
        index++;
      }
      if (type == 1) {
        stock[stock_counter] = new TypeOne(name,count,price);
        stock_counter++;
      }else if(type == 2){
        stock[stock_counter] = new TypeTwo(name,count,price);
        stock_counter++;
      }else if(type == 3){
        stock[stock_counter] = new TypeThree(name,count,price);
        stock_counter++;
      }
    }
    stock_line_counter++;
  }
  file.close();

  MenuItems *menu[MENU_ITEMS];

  file.open("menu.txt");
  int menu_counter = 0;
  int menu_line_counter = 0;
  while (getline(file,str)){
    if (menu_line_counter){
      istringstream ss(str);
      string substr;
      string name;
      string arr[MAX_IGREDIENTS];
      int index = 0;
      int i = 0;
      while(getline(ss, substr, '\t')){
        if (index == 0) {
          name = substr;
        }else if(index == 1){
          istringstream sssub(substr);
          string subsubstr;
          while(getline(sssub, subsubstr, ',')){
            arr[i] = subsubstr;
            i++;
          }
        }
        index++;
      }
      menu[menu_counter] = new MenuItems(name,arr,i);
      menu_counter++;
    }
    menu_line_counter++;
  }
  file.close();
  float tip = 0.15;
  float tax = 0.08;

  file.open("order.txt");
  while (getline(file,str)) {
    string table_name;
    table_name = str;
    cout << table_name << " ordered:" << endl;
    getline(file,str);
    istringstream is(str);
    int n;
    is >> n;
    float total = 0;
    for (int i = 0; i < n; i++) {
      getline(file,str);
      istringstream ss(str);
      string substr;
      string name;
      float number;
      int index = 0;
      while(getline(ss, substr, ' ')){
        if (index == 0) {
          istringstream conv(substr);
          conv >> number;
        }else{
          istringstream sssub(substr);
          string subsubstr;
          while(getline(sssub, subsubstr, ' ')){
            if (name.empty()) {
              name += subsubstr;
            }else{
              name += " " + subsubstr;
            }
          }
        }
        index++;
      }
      for (int i = 0; i < menu_counter; i++) {
        try{
          total += menu[i]->find_ingredient(number,name,stock,stock_counter);
        }catch(const char* msg){
          cerr << msg;
          cout << menu[i]->getName() << endl;
        }
      }
    }
    cout << "Tip is " << total*tip << endl;
    cout << "Total cost: " << total+(total*tip)+(total*tax) << endl;
    string star(20, '*');
    cout << star << endl;
  }
  file.close();

  ofstream myfile;
  myfile.open("stock.txt");
  myfile << "Name\tType\tItemCount\tPrice" << "\n";
   for (int i = 0; i < stock_counter; i++) {
     myfile << stock[i]->getName() << "\t" << stock[i]->getType() << "\t" << stock[i]->getCount() << "\t" << stock[i]->getCost() << "\n";
   }
   myfile.close();


  for (int i = 0; i < menu_counter; i++) {
    delete menu[i];
  }

  for (int i = 0; i < stock_counter; i++) {
    delete stock[i];
  }
  return 0;
}
