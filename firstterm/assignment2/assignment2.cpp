/* @Author

* Student Name: Ömer Faruk Davarcı
* Student ID: 150160048
* Date: 08.11.2018        */

#include <iostream>//input output
#include <fstream>//ifstream lib
#include <stdlib.h>//EXIT_SUCCESS
#include <ctype.h>//tolower
#include <string>//for str compare
#include "header.h"

int main(int argc, char *argv[]) {
  string whitespace ("<SP>");
  if (argv[1]) {
    lang.readData(argv[1]);
  }else{
    cout << "There is no input file" << endl;
    return EXIT_SUCCESS;
  }

  int calculateprob = 4;
  if (argc == calculateprob) {//prints if there are spesific characters to calculate
    if(whitespace.compare(argv[2]) == 0 && whitespace.compare(argv[3]) == 0){
      cout << "<" << argv[2] << " , " << argv[3] << " , " << lang.calculateProbability(' ',' ') << ">" << endl;
    }else if (whitespace.compare(argv[2]) == 0){
      cout << "<" << argv[2] << " , " << argv[3] << " , " << lang.calculateProbability(' ',*argv[3]) << ">" << endl;
    }else if(whitespace.compare(argv[3]) == 0){
      cout << "<" << argv[2] << " , " << argv[3] << " , " << lang.calculateProbability(*argv[2],' ') << ">" << endl;
    }else{
      cout << "<" << argv[2] << " , " << argv[3] << " , " << lang.calculateProbability(*argv[2],*argv[3]) << ">" << endl;
    }
  }else{//prints if there are no spesific characters to calculate
    (lang.vocabularylist)->print();
  }
  return EXIT_SUCCESS;
}
