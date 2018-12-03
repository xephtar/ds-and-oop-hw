/* @Author

* Student Name: Ömer Faruk Davarcı
* Student ID: 150160048
* Date: 08.11.2018        */


using namespace std;

struct occur_node
{
	char character;
	int occurrence;
	occur_node *next;
};

struct vocab_node
{
	char character;
	vocab_node *next;
	occur_node *list;
};

struct vocab_list
{
	vocab_node *head;

	void create();
	void print();
	void add_char(char );
	void add_occurence(char , char );
	int get_occurence(char );
	int get_union_occurence (char , char );
};

struct language_model
{
	vocab_list *vocabularylist;

	void readData (const char *);
	double calculateProbability (char, char);
};

struct language_model lang;

void vocab_list::create()
{
	head = NULL;
}

void vocab_list::add_char(char newchar)
{
	vocab_node *trav;
	trav = head;
	while(trav && trav->character != newchar){
		trav = trav->next;
	}
	if(trav != NULL){
		return;
	}
	trav = head;
	vocab_node *n = new vocab_node;
	vocab_node *n_behind;
	n->character = newchar;
	n->next = NULL;
	n->list = NULL;
	if (head == NULL) {// if there is no node, this is first node
			head = n;
			return;
	}

	if (isalpha(newchar)) {//is char punctation or letter
		if (!isalpha(head->character)) {
			n->next = head;
			head = n;
			return;
		}
		if (newchar < head->character) {//if new char comes before in alphabetical order from head, head is new node
			n->next = head;
			head = n;
			return;
		}
		while (trav && (trav->character < newchar) && isalpha(trav->character)) {//if it is alpha go to end or if letter is lower than other nodes go to end
			n_behind = trav;
			trav = trav->next;
		}
		if (trav) {
			n->next = trav;
			n_behind->next = n;
		}else {
			n_behind->next = n;
		}
	}else{
		while (trav) {
			n_behind = trav;
			trav = trav->next;
		}
		n_behind->next = n;
	}

}

void vocab_list::add_occurence(char before, char now)
{
	if (before == 10) {//to not connect nodes to newline character
		return;
	}
	vocab_node *trav;
	trav = head;
	while (trav->character != before) {//search before character
		trav = trav->next;
	}
	occur_node *newnode = new occur_node;
	occur_node *occ;
	occur_node *o_behind;
	occ = trav->list;
	newnode->character = now;
	newnode->occurrence = 1;
	newnode->next = NULL;

	if (trav->list == NULL) {// if there is no node set the first node
		trav->list = newnode;
	}else{
		while (occ) {
			if(occ->character == now){// if there is same node increase and exit
				occ->occurrence = occ->occurrence + 1;
				return;
			}
			occ = occ->next;
		}
		occ = trav->list;
		while (occ) {//if it is not same any node, add to last
			o_behind = occ;
			occ = occ->next;
		}
		o_behind->next = newnode;
	}
}

int vocab_list::get_occurence(char searching)
{
	vocab_node *trav;
	trav = head;
	int counter = 0;
	while (trav && trav->character != tolower(searching)) {//trav it until find searching letter
		trav = trav->next;
	}
	if (trav == NULL) {
		return counter;
	}
	occur_node *occ;

	occ = trav->list;
	while (occ) {//until NULL count all occurrence
		counter += occ->occurrence;
		occ = occ->next;
	}
	return counter;
}

int vocab_list::get_union_occurence(char main, char after)
{
	vocab_node *trav;
	trav = head;
	int counter = 0;
	while (trav && trav->character != main) {//travel until find main
		trav = trav->next;
	}
	if(trav == NULL){
		return counter;
	}
	occur_node *occ;
	occ = trav->list;
	while (occ) {
		if (occ->character == after) {//if it is same as second character count it
			counter = occ->occurrence;
		}
		occ = occ->next;
	}

	return counter;
}

void vocab_list::print()
{
	vocab_node *trav;
	occur_node *occ;
	trav = head;
	while (trav) {
	  occ = trav->list;
			if(trav->character == 10){
				//do nothing
			}else if(isspace(trav->character)){
	      cout << "<SP>"  << ":" << endl;
	    }else{
	      cout << trav->character << ":" << endl;
	    }
	  while (occ) {
			if(occ->character == 10){
				//do nothing
			}else if(isspace(occ->character)){
	      cout << "  <" << "<SP>" << "," << occ->occurrence << ">" << endl;
	    }else{
	      cout << "  <" << occ->character << "," << occ->occurrence << ">" << endl;
	    }
	    occ = occ->next;
	  }
	  trav = trav->next;
	}
}

double language_model::calculateProbability(char first, char second)
{
	int totaloccur,unionoccur;
	double result = 0;
	totaloccur = vocabularylist->get_occurence(tolower(first));
	unionoccur = vocabularylist->get_union_occurence(tolower(first),tolower(second));
	if (totaloccur == 0) {
		return result;
	}else{
		result = (double)unionoccur/(double)totaloccur;
		return result;
	}
}

void language_model::readData(const char *filename)
{
	string deneme ("ş");
	vocabularylist = new vocab_list;
  vocabularylist->create();
  ifstream infile;
  infile.open(filename);
	char data;
	char prev;
  while (!infile.eof()) {
    infile.get(data);
    if (data >= 32 || data == 10) {//takes newline and letters
      vocabularylist->add_char(tolower(data));
			if(prev){//check for first character
				vocabularylist->add_occurence(tolower(prev),tolower(data));
			}
    }
		prev = data;
  }
  infile.close();
}
