#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std; 

struct Stack {
	int element[1000];
	int top;
	void create();
	void close();
	bool push(int);
	int pop();
	bool isempty();
	};

void Stack::create(){
top = 0;
}
void Stack::close(){
}

bool Stack::push(int newelement){
if (top < 1000) {
element[top++] = newelement;
return true;
}
return false;
}

int Stack::pop(){
return element[--top];
}

bool Stack::isempty(){
return (top == 0);
}


int main(int argc, char const *argv[]) {
  int arguments = 2;
  if (argc > arguments) {
    return EXIT_SUCCESS;
  }
Stack t, s1, s2;
t.create();
s1.create();
s2.create();
int t_card_number;
int s_card_number;

int trans = 0;
ifstream inFile;
inFile.open(argv[1]);
	inFile>>trans;
	t_card_number = trans;
	inFile>>trans;
	s_card_number = trans;
int i;
	for (i = 0; i < t_card_number; i++) {
		inFile>>trans;
		t.push(trans);
	}
	for (i = 0; i < s_card_number; i++) {
		inFile>>trans;
		s1.push(trans);
	}
	for (i = 0; i < s_card_number; i++) {
		inFile>>trans;
		s2.push(trans);
	}
int selector = 0;
int bin = 0;
	while (!t.isempty()) {
		selector = t.pop();
		if (selector < 0) {
			for (i = 0; i > selector; i--) {     // ilk oyuncu bu kadar kart versin
				if(s1.isempty() || s2.isempty()) {
					cout<<bin;
					return EXIT_SUCCESS;
				}
				if (s1.element[(s1.top-1)] > s2.element[(s2.top-1)]) {
					s2.push(s1.pop());
				} else {
					s1.pop();
					bin++;
				}
			}
		} else {   // ilk oyuncu bu kadar kart alsýn
			for (i = 0; i < selector; i++) {
				if(s1.isempty() || s2.isempty()) {
					cout<<bin;
					return EXIT_SUCCESS;
				}
				if (s2.element[(s2.top-1)] > s1.element[(s1.top-1)]) {
					s1.push(s2.pop());
				} else {
					s2.pop();
					bin++;
				}
			}
		}
		
		if (t.isempty()) {
			cout<<bin;
			return EXIT_SUCCESS;
		}
		selector = t.pop();
		if (selector < 0) {
			for (i = 0; i > selector; i--) {     // ikinci oyuncu bu kadar kart versin
				if(s1.isempty() || s2.isempty()) {
					cout<<bin;
					return EXIT_SUCCESS;
				}
				if (s2.element[(s2.top-1)] > s1.element[(s1.top-1)]) {
					s1.push(s2.pop());
				} else {
					s2.pop();
					bin++;
				}
			}
		} else {   // ikinci oyuncu bu kadar kart alsýn
			for (i = 0; i < selector; i++) {
				if(s1.isempty() || s2.isempty()) {
					cout<<bin;
					return EXIT_SUCCESS;
				}
				if (s1.element[(s1.top-1)] > s2.element[(s2.top-1)]) {
					s2.push(s1.pop());
				} else {
					s1.pop();
					bin++;
				}
			}
		}
		
	}
	cout<<bin;
inFile.close();
t.close();
s1.close();
s2.close();
return EXIT_SUCCESS;
}





