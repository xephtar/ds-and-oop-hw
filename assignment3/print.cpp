cout << game.tableCards << endl;
cout << game.playerCards << endl;
cout << "**************" << endl;

cout << (game.table)->pop() << endl;
cout << (game.table)->pop() << endl;
cout << "Empty:" << (game.table)->isEmpty() << endl;
cout << "**************" << endl;

cout << (game.player1)->pop() << endl;
cout << (game.player1)->pop() << endl;
cout <<  "Empty:" << (game.player1)->isEmpty() << endl;
cout << (game.player1)->pop() << endl;
cout <<  "Empty:" << (game.player1)->isEmpty() << endl;
cout << "**************" << endl;

cout << (game.player2)->pop() << endl;
cout << (game.player2)->pop() << endl;
cout << (game.player2)->pop() << endl;
cout <<  "Empty:" << (game.player2)->isEmpty() << endl;
cout << "**************" << endl;



void game_model::printData(){
  Stack *temp = new Stack;
  temp->create();
  int datatemp;
  int counter = 0;

  if (table->isEmpty()) {
    cout << "Cards of table: []" << endl;
  }else{
    while(!table->isEmpty()){
      if (counter == 0) {
        datatemp = table->pop();
        temp->push(datatemp);
        cout << "Cards of the table: [" << datatemp;
      }else{
        datatemp = table->pop();
        temp->push(datatemp);
        cout << " " << datatemp;
      }
      counter++;
    }
    if (table->isEmpty()) {
      cout << "]" << endl;
    }

    while (!temp->isEmpty()) {
      datatemp = temp->pop();
      table->push(datatemp);
    }
  }


  counter = 0;
  if (player1->isEmpty()) {
    cout << "Cards of the first player: []" << endl;
  }else{
    while(!player1->isEmpty()){
      if (counter == 0) {
        datatemp = player1->pop();
        temp->push(datatemp);
        cout << "Cards of the first player: [" << datatemp;
      }else{
        datatemp = player1->pop();
        temp->push(datatemp);
        cout << " " << datatemp;
      }
      counter++;
    }
    if (player1->isEmpty()) {
      cout << "]" << endl;
    }

    while (!temp->isEmpty()) {
      datatemp = temp->pop();
      player1->push(datatemp);
    }
  }

  counter = 0;
  if (player2->isEmpty()) {
    cout << "Cards of the second player: []" << endl;
  }else{
    while(!player2->isEmpty()){
      if (counter == 0) {
        datatemp = player2->pop();
        temp->push(datatemp);
        cout << "Cards of the second player: [" << datatemp;
      }else{
        datatemp = player2->pop();
        temp->push(datatemp);
        cout << " " << datatemp;
      }
      counter++;
    }
    if (player2->isEmpty()) {
      cout << "]" << endl;
    }

    while (!temp->isEmpty()) {
      datatemp = temp->pop();
      player2->push(datatemp);
    }
  }

  counter = 0;
  if (bin->isEmpty()) {
    cout << "Cards of bin: []" << endl;
  }else{
    while(!bin->isEmpty()){
      if (counter == 0) {
        datatemp = bin->pop();
        temp->push(datatemp);
        cout << "Cards of bin: [" << datatemp;
      }else{
        datatemp = bin->pop();
        temp->push(datatemp);
        cout << " " << datatemp;
      }
      counter++;
    }
    if (bin->isEmpty()) {
      cout << "]" << endl;
    }

    while (!temp->isEmpty()) {
      datatemp = temp->pop();
      bin->push(datatemp);
    }
  }


}
