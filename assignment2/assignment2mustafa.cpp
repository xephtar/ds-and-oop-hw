
/* @Author
* Student Name: Mustafa BOZDO�AN
* Student ID: 150160048
* Date: 08.11.2018		*/

#include <iostream>
#include <stdlib.h>
#include <cstring> //strings
#include <locale.h> //setlocale turkish char
#include <fstream> // fstream
#include <cctype> // tolower

using namespace std;

	struct occur_node {
	char character;
	occur_node *next;
	int occurence;
	};

	struct vocab_node {
	char character;
	vocab_node *next;
	occur_node *list;
	};

	struct vocab_list
	{
	vocab_node *head;
		void create(); // vocab_list olu�turcak
		void print();  // cout yapcak
		void add_char(char );  // bir karakter okuyacak ve alfabetik olarak vocab_list'e yazacak. Zaten yazm��sa ge�ecek.
		void add_occurence(char , char );  // ilkini vocab_list i�inde arayacak. �kinciyi occur_node'lar�nda arayacak. Yoksa occur_node olu�turcak, varsa occurance bir art�rcak.
		int get_occurence(char ); // karakterin toplam bulunmas�n� d�nd�rcek. Sondaki karakter say�lmaz.
		int get_union_occurence (char , char ); // ikisinin toplam birarada bulunmas�n� d�nd�rcek.
	};

	struct language_model {
	vocab_list *vocabularylist;
		void readData (const char *);  // input.txt'den okuyacak. create(), add_char(char ), add_occurence(char , char ) �a�r�lcak. language model doldurulacak.
		double calculateProbability (char, char); // birarada bulunma say�s� b�l� birinin bulunma say�s� d�nd�rcek
	};

	struct language_model modelx;

	void vocab_list::create() {
		head = NULL;
		// int vocabnode_counter;
	}



	void vocab_list::add_char(char input) {
		vocab_node *traverse;
		traverse = head;
		while (traverse) {
			if (input == traverse->character) {       // karakter i�in node varsa fonksiyonu bitir
				return;
			}
			traverse=traverse->next;
		}
		traverse = head;
		vocab_node *new_vocabnode, *behind; // BEH�ND = NULL YAP VE BELK� YEN� VOCAB_NODE OLU�TUR


		behind = new vocab_node;	 // YEN�
	// BUNUN YER�NE ALTTAK�LER	behind = NULL;	 // YEN�
		behind->next = NULL;
		behind->character = '\0';
		behind->list = NULL;

		new_vocabnode = new vocab_node;
		new_vocabnode->next = NULL;
		new_vocabnode->character = input;
		new_vocabnode->list = NULL;
		if (head == NULL) {              // ilk node olu�tur
			head = new_vocabnode;
			return;
		}
		if(isalpha(input)) {
			if (input < head->character || head->character < 64) {         //birinciden de �ndeyse veya birinci nokta virg�lse
				new_vocabnode->next = head;
				head = new_vocabnode;
				return;
			}
			while (traverse && (input > traverse->character) && (traverse->character > 64)) {         // NULL de�ilse ve arkas�nda olmal�ysa (daha b�y�kse) ve !nokta virg�l de�ilse! ilerlet
				behind = traverse;
				traverse = traverse->next;
			}
			if(traverse) {         // aradaysa
				new_vocabnode->next = traverse;
				behind->next = new_vocabnode;
			} else {       	      // sondaysa
				behind->next = new_vocabnode;
			}
		} else {
			while (traverse) {
				behind = traverse;
				traverse = traverse->next;
			}
			behind->next = new_vocabnode;
		}
	}

	// void vocab_list::add_occurence(char before, char now)
	// {
	// 	if (before == 10) {
	// 		return;
	// 	}
	// 	vocab_node *trav;
	// 	trav = head;
	// 	while (trav->character != before) {
	// 		trav = trav->next;
	// 	}
	// 	occur_node *newnode = new occur_node;
	// 	occur_node *occ;
	// 	occur_node *o_behind;
	// 	occ = trav->list;
	// 	newnode->character = now;
	// 	newnode->occurence = 1;
	// 	newnode->next = NULL;
	//
	// 	if (trav->list == NULL) {
	// 		trav->list = newnode;
	// 	}else{
	// 		while (occ) {
	// 			if(occ->character == now){
	// 				occ->occurence = occ->occurence + 1;
	// 				return;
	// 			}
	// 			occ = occ->next;
	// 		}
	// 		occ = trav->list;
	// 		while (occ) {
	// 			o_behind = occ;
	// 			occ = occ->next;
	// 		}
	// 		o_behind->next = newnode;
	// 	}
	// }

	void vocab_list::add_occurence(char first, char second) {
		//tanımlar
		vocab_node *traverse;
		occur_node *new_occurnode;
		occur_node *on;
		// first yeni bir satırsa direk çık ekleme
		if (first == 10) {
			return;
		}else{
			//	vocab_node->character == first bul, occur_node->character == second var m� diye bak. Yoksa olu�tur varsa occurance++
		traverse = head;
		while ((traverse->character != first)) {       // vocab_node->char = first  bul
			traverse= traverse->next;
		}
		new_occurnode = new occur_node;
		new_occurnode->next = NULL;
		new_occurnode->character = second;
		new_occurnode->occurence = 1;
		on = traverse->list;
		if (on == NULL) {
			traverse->list = new_occurnode;
			return;
		}else{
			while (on) {
				if (on->character == second) {
					on->occurence = on->occurence + 1;
					return;
				}
				on = on->next;
			}

			on = traverse->list;
			while (on->next) {
				on = on->next;
			}
			on->next = new_occurnode;
		}
		}

}

int vocab_list::get_occurence (char x) {
	x = tolower(x);
	vocab_node *traverse;
	traverse = head;
	int occurence = 0;
	while (traverse && traverse->character != x) {
		traverse = traverse->next;
	}
	if(traverse) {
		occur_node *on;
		on = traverse->list;
		while (on) {
			occurence = occurence + on->occurence;
			on = on->next;
		}
	}
	return occurence;

}

int vocab_list::get_union_occurence(char first,char second) {
	first = tolower(first);
	second = tolower(second);
	int union_occurence = 0;
	vocab_node *traverse;
	traverse = head;
	while (traverse && traverse->character != first) {
		traverse = traverse->next;
	}
	if (traverse) {
		occur_node *on;
		on = traverse->list;
		while(on && on->character != second) {
			on = on->next;
		}
		if(on == NULL) {
			return union_occurence;
		} else {
			union_occurence = on->occurence;
			return union_occurence;
		}
	} else {
		return union_occurence;
	}
}

	void vocab_list::print() {
		vocab_node *traverse;
		occur_node *on;
		traverse = head;
		while (traverse) {
				if(traverse->character == 32){
		      cout << "<SP>"  << ":" << endl;
		    }else if(traverse->character != 10){
		      cout << traverse->character << ":" << endl;
		    }
			on = traverse->list;
		  while (on) {
				if(on->character == 32){
		      cout << "     <" << "<SP>" << "," << on->occurence << ">" << endl;
		    }else if(on->character != 10){
		      cout << "     <" << on->character << "," << on->occurence << ">" << endl;
		    }
		    on = on->next;
		  }
		  traverse = traverse->next;
		}
	}

	void language_model::readData(const char * filename) {
		vocabularylist = new vocab_list;
		vocabularylist->create();

		char letter[5];
		FILE *file;
		file = fopen(filename , "r");  //	fscanf(file, "%c", &x); bu sadece yedek
		fseek(file, 0, SEEK_SET);
		char back = '\0';
		while(!feof(file)) {
			fread(letter,sizeof(char),1,file);
			letter[0] = tolower(letter[0]);
			if (letter[0] == '\0') {
				break;
			}
			vocabularylist->add_char(letter[0]);
			if(back != '\0') {
				vocabularylist->add_occurence(back, letter[0]);
			}
			back = letter[0];
		}
		fclose(file);
	}



	double language_model::calculateProbability(char second, char first) {
		int occurence, union_occurence;
		first = tolower(first);
		second = tolower(second);
		double probability = 0;
		occurence = vocabularylist->get_occurence(first);
		union_occurence = vocabularylist->get_union_occurence(first, second);
		if (occurence == 0) {
			return probability;
		}else{
			probability = (double)union_occurence/(double)occurence;
			return probability;
		}
	}

int main(int argc, char const *argv[]) {
	/*
	setlocale(LC_ALL, "Turkish");
	*/
	modelx.readData(argv[1]);
  	int commands = argc;
	if (commands == 4) {
	    cout << "<" << *argv[2] << " , " << *argv[3] << " , " << modelx.calculateProbability(*argv[3],*argv[2]) << ">" << endl;
  	} else {
  		(modelx.vocabularylist)->print();
 	}
	return 0;

}
