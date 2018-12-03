/* @Author

* Student Name: Ömer Faruk Davarcı
* Student ID: 150160048
* Date: 03.12.2018        */

#include <iostream>//input output
#include <fstream>//ifstream lib
#include <stdlib.h>//EXIT_SUCCESS
#include <cmath>//absolutevalue

#define MAX_CARDS 1000
#define MAX_VALUE 1000000

using namespace std;
// STRUCTS ************************************************************************************************************
// STRUCTS ************************************************************************************************************
// STRUCTS ************************************************************************************************************

struct Node {
  int number;
  Node *next;
};

struct  Stack {

  Node *head;
  void create();//creates null stack
  void push(int);//pushs data to the top of stack
  int pop();//pops data from the top of stack
  bool isEmpty();//checks that stack is empyt or not

};

struct game_model {
  Stack *player1;
  Stack *player2;
  Stack *bin;
  Stack *table;

  int playerCards;
  int tableCards;
  bool game_end();
  bool player_end();
  void readData (const char *);
  void printData();
};

// STRUCTS ************************************************************************************************************
// STRUCTS ************************************************************************************************************
// STRUCTS ************************************************************************************************************


bool isThereTxt (const char *);//checks arguments file to look that it exists
bool inRange (int);//checks counts of cards to look that it is in range
bool numberinRange (int);//checks number of cards to look that it is in range
int whoseturn (int);//calculates whose turn


struct game_model game;

// MAIN ************************************************************************************************************
// MAIN ************************************************************************************************************
// MAIN ************************************************************************************************************

int main(int argc, char const *argv[]) {
  int firstplayer = 1;
  if (argc > 2) {
    cout << "So many arguments from expected!" << endl;
    return EXIT_SUCCESS;
  }

  if (isThereTxt(argv[1])) {
    game.readData(argv[1]);

    int turnnumber = 1;
    while (!game.game_end()) {
      int card_of_table = (game.table)->pop();
      if (whoseturn(turnnumber) == firstplayer) {//turn of first player
        if (card_of_table < 0) {//if giving cards

          for (; card_of_table < 0; card_of_table++) {// does those card_of_table times
            int top_of_player1 = (game.player1)->pop();
            int top_of_player2 = (game.player2)->pop();
            if (top_of_player1 > top_of_player2) {// if it is greater take it
              (game.player2)->push(top_of_player2);
              (game.player2)->push(top_of_player1);
            }else{                               // if it is lower throw it
              (game.bin)->push(top_of_player1);
              (game.player2)->push(top_of_player2);
            }
            if (game.player_end()) {//if one player out of cards, end it
              game.printData();
              return EXIT_SUCCESS;
            }
          }

        }else{//if taking cards

          for (; card_of_table > 0; card_of_table--) {// does those card_of_table times
            int top_of_player1 = (game.player1)->pop();
            int top_of_player2 = (game.player2)->pop();
            if (top_of_player2 > top_of_player1) {// if it is greater take it
              (game.player1)->push(top_of_player1);
              (game.player1)->push(top_of_player2);
            }else{                               // if it is lower throw it
              (game.bin)->push(top_of_player2);
              (game.player1)->push(top_of_player1);
            }
            if (game.player_end()) {//if one player out of cards, end it
              game.printData();
              return EXIT_SUCCESS;
            }
          }

        }

//second player **********************************************************************
//second player *********************************************************************
//second player *********************************************************************

      }else{//turn of second player
        if (card_of_table < 0) {//if giving cards

          for (; card_of_table < 0; card_of_table++) {// does those card_of_table times
            int top_of_player1 = (game.player1)->pop();
            int top_of_player2 = (game.player2)->pop();
            if (top_of_player2 > top_of_player1) {// if it is greater take it
              (game.player1)->push(top_of_player1);
              (game.player1)->push(top_of_player2);
            }else{                               // if it is lower throw it
              (game.bin)->push(top_of_player2);
              (game.player1)->push(top_of_player1);
            }
            if (game.player_end()) {//if one player out of cards, end it
              game.printData();
              return EXIT_SUCCESS;
            }
          }

        }else{//if taking cards

          for (; card_of_table > 0; card_of_table--) {// does those card_of_table times
            int top_of_player1 = (game.player1)->pop();
            int top_of_player2 = (game.player2)->pop();
            if (top_of_player1 > top_of_player2) {// if it is greater take it
              (game.player2)->push(top_of_player2);
              (game.player2)->push(top_of_player1);
            }else{                               // if it is lower throw it
              (game.bin)->push(top_of_player1);
              (game.player2)->push(top_of_player2);
            }
            if (game.player_end()) {//if one player out of cards, end it
              game.printData();
              return EXIT_SUCCESS;
            }
          }

        }
      }

      turnnumber++;
    }

    game.printData();

  }else{
    cout << "No file named: " << argv[1] << endl;
  }

  return EXIT_SUCCESS;
}

// MAIN ************************************************************************************************************
// MAIN ************************************************************************************************************
// MAIN ************************************************************************************************************


void Stack::create(){
  head = NULL;
}

void Stack::push(int data){
  Node *newnode = new Node;
  newnode->number = data;
  newnode->next = head;
  head = newnode;
}

int Stack::pop(){
  Node *topnode;
  int temp;
  topnode = head;
  head = head->next;
  temp = topnode->number;
  delete topnode;
  return temp;
}

bool Stack::isEmpty(){
  return (head == NULL);
}

void game_model::readData(const char *filename)
{
  ifstream infile;
  infile.open(filename);
  player1 = new Stack;
  player2 = new Stack;
  bin = new Stack;
  table = new Stack;
  player1->create();
  player2->create();
  bin->create();
  table->create();

  int data;
  infile >> data;
  tableCards = data;
  if (!inRange(tableCards)) {//checks range of tablecards
    cout << "Given card counts are not in range between 0 and 1000!" << endl;
    return;
  }
  infile >> data;
  playerCards = data;
  if (!inRange(playerCards)) {//checks range of playercards
    cout << "Given card counts are not in range between 0 and 1000!" << endl;
    return;
  }

  int counter;
  for (counter = 1; counter <= tableCards; counter++) {
    infile >> data;
    if (numberinRange(data)) {
      table->push(data);
    }else{
      cout << "One input is out of range!" << endl;
      return;
    }
  }

  for (counter = 1; counter <= playerCards; counter++) {
    infile >> data;
    if (numberinRange(data)) {
      player1->push(data);
    }else{
      cout << "One input is out of range!" << endl;
      return;
    }
  }
  for (counter = 1; counter <= playerCards; counter++) {
    infile >> data;
    if (numberinRange(data)) {
      player2->push(data);
    }else{
      cout << "One input is out of range!" << endl;
      return;
    }
  }

  infile.close();
}

void game_model::printData(){
  Stack *temp = new Stack;
  temp->create();
  int datatemp;
  int counter = 0;

  while(!bin->isEmpty()){
    datatemp = bin->pop();
    temp->push(datatemp);
    counter++;
  }
  while (!temp->isEmpty()) {
    datatemp = temp->pop();
    bin->push(datatemp);
  }

  cout << counter << endl;
}

bool game_model::game_end(){
  if (table->isEmpty()) {
    return 1;
  }else if(player1->isEmpty()){
    return 1;
  }else if(player2->isEmpty()){
    return 1;
  }else{
    return 0;
  }
}

bool game_model::player_end(){
  if(player1->isEmpty()){
    return 1;
  }else if(player2->isEmpty()){
    return 1;
  }else{
    return 0;
  }
}

bool isThereTxt(const char *file){
  ifstream infile;
  infile.open(file);
  if (!infile) {
    return 0;
  }
  infile.close();
  return 1;
}

bool inRange(int value){
  if (value < 0 || value > MAX_CARDS) {
    return 0;
  }
  return 1;
}

bool numberinRange(int num){
  if (num == 0 || abs(num) > MAX_VALUE) {
    return 0;
  }
  return 1;
}

int whoseturn(int turn){
  return turn % 2;
}
