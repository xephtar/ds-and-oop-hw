/* @Author

* Student Name: Ömer Faruk Davarcı
* Student ID: 150160048      */

#include <iostream>//input output
#include <fstream>//ifstream lib
#include <stdlib.h>//EXIT_SUCCESS
#include <string.h>//strcmp
#include "Vector.h"
#include "Polynomial.h"


void printMenu();

int main(int argc, char const *argv[]) {
  if (argc != 3) {
    cout << "Just give two arguments first Vector.txt and second Polynomial.txt !" << endl;
    return EXIT_SUCCESS;
  }
  ifstream infile;
  int data;
  infile.open(argv[2]);//polynomial.txt starts here
  infile >> data;
  int polySize = data;
  Polynomial *polynomials[polySize];
  for (int a = 0; a < polySize; a++) {
    infile >> data;
    int polyDegree = data;
    int arr[polyDegree+1];
    for (int i = polyDegree; i >= 0; i--) {
      infile >> data;
      arr[i] = data;
    }
    polynomials[a] = new Polynomial(polyDegree,arr);
  }
  infile.close();//polynomial.txt ends here

  infile.open(argv[1]);//vector.txt starts here
  infile >> data;
  int vectorSize = data;
  VectorX *vectors[vectorSize];
  for (int a = 0; a < vectorSize; a++) {
    infile >> data;
    int size = data;
    int arr[size];
    for (int i = 0; i < size; i++) {
      infile >> data;
      arr[i] = data;
    }
    vectors[a] = new VectorX(size,arr);
  }
  infile.close();//vector.txt ends here

  printMenu();
  bool isRunning = true;
  while (isRunning) {
    cout << endl;
    int selection;
    cout << "Enter an option: ";
    cin >> selection;
    switch (selection) {
      case 1:
      {
        cout << "Vectors:" << endl;
        for (int i = 0; i < vectorSize; i++) {
          cout << i+1 << ". ";
          cout << *vectors[i];
          cout << endl;
        }
        cout << endl;
        cout << "Polynomials:" << endl;
        for (int i = 0; i < polySize; i++) {
          cout << i+1 << ". ";
          cout << *polynomials[i];
          cout << endl;
        }
        cout << endl;
        break;
      }
      case 2:{
        cout << "Which polynomial operation would you like to do?(+:addition, *:multiplication):" << endl;
        char c[3];
        cin >> c[0] >> c[1] >> c[2];
        int a = c[0] - 49;// -48 for ascii table numbers start from 48, -1 for my array becomes from 0
        int b = c[2] - 49;// -48 for ascii table numbers start from 48, -1 for my array becomes from 0
        if (c[1] == 43) {//43 for ascii number of +
          cout << "(" << *polynomials[a] << ") + (" << *polynomials[b] << ") = (" << *polynomials[a] + *polynomials[b] << ")"  << endl;
        }else if(c[1] == 42){//42 for ascii number of *
          cout << "(" << *polynomials[a] << ") * (" << *polynomials[b] << ") = (" << *polynomials[a] * *polynomials[b] << ")" << endl;;
        }
        break;
      }
      case 3:
      {
        cout << "Which vector operation would you like to do?(+:addition, *:scalar multiplication, .:dot product):" << endl;
        char c[3];
        cin >> c[0] >> c[1] >> c[2];
        int a = c[0] - 49;// -48 for ascii table numbers start from 48, -1 for my array becomes from 0
        if (c[1] == 42) {//42 for ascii number of *
          int b = c[2] - 48;// -48 for ascii table numbers start from 48
          cout << *vectors[a] << " * (" << b << ") = " << *vectors[a] * b << endl;
        }else{
          int b = c[2] - 49;// -48 for ascii table numbers start from 48, -1 for my array becomes from 0
          if (vectors[a]->getSize() == vectors[b]->getSize()) {
            if (c[1] == 43) {//43 for ascii number of +
              cout << *vectors[a] << " + " << *vectors[b] << " = (" << *vectors[a] + *vectors[b] << ")" << endl;
            }else if(c[1] == 46){//46 for ascii number of .
              cout << *vectors[a] << " . " << *vectors[b] << " = " << *vectors[a] * *vectors[b] << endl;
            }
          }else{
            cout << "Sizes are not equal!" << endl;
          }
        }
        break;
      }
      case 4:
        printMenu();
        break;
      case 0:
        isRunning = false;
        break;
      default:
        cout << "Invalid input! Give an input according to menu please!" << endl;
        break;
    };
  }
  return 0;
}
void printMenu(){
  cout << "Polynomial and Vector List Program!" << endl;
  cout << "Polynomials and Vectors are read from text files!" << endl;
  cout << endl;
  cout << "Possible Actions:" << endl;
  cout << "1. Print Polynomial and Vector lists" << endl;
  cout << "2. Do a polynomial operation" << endl;
  cout << "3. Do a vector operation" << endl;
  cout << "4. Help: Print possible actions" << endl;
  cout << "0. Exit the program" << endl;
}
