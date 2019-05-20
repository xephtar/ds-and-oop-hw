//Ömer Faruk Davarcı 150160048
//OOP ASSIGNMENT 2

#include<iostream>
#define MAX_OPERATOR_SIZE 100

class Operator{
  int center_x;
  int center_y;
  int op_size;
public:
  Operator(int x, int y, int size){
      center_x = x;
      center_y = y;
      op_size = size;
  };//constructor

  void reset(int new_x, int new_y, int new_size){
      center_y = new_y;
      center_x = new_x;
      op_size = new_size;
  };

  void set_x(int new_x){
      center_x = new_x;
  };
  int get_x(){
      return center_x;
  };

  void set_y(int new_y){
      center_y = new_y;
  };
  int get_y(){
      return center_y;
  };

  void set_size(int new_size){
      op_size = new_size;
  };
  int get_size(){
      return op_size;
  };
};

class ArithmeticOperator: public Operator {
    char sign;
public:
    ArithmeticOperator(int x, int y, int size, char sign);

    char get_sign(){
        return sign;
    };
    //Prints out operator's center location, size, and sign character
    void print_operator();
};

class OperatorGrid{
    int grid_rows;
    int grid_cols;
    char **grid;

    int num_operators;
    ArithmeticOperator *operators[MAX_OPERATOR_SIZE];

public:
    OperatorGrid(int rows, int cols);
    ~OperatorGrid();

    void insert_operator(ArithmeticOperator *, int);
    void delete_operator(ArithmeticOperator *);
    bool place_operator(ArithmeticOperator *);
    bool move_operator(int x, int y, char direction, int move_by);
    void print_operators();
    bool is_border_error(ArithmeticOperator *);
    bool is_conflict_error(ArithmeticOperator *);
};

using namespace std;


//constructor for ArithmeticOperator
ArithmeticOperator::ArithmeticOperator(int x, int y, int size, char sign): Operator(x,y,size){
    if(sign == '+' || sign == '-' || sign == '/' || sign == 'x'){
        this->sign = sign;
    }else{
        cout << "SIGN parameter is invalid!" << endl;
    }
}

//prints out operator's center location, size, and sign character
void ArithmeticOperator::print_operator(){
    cout << "ARITHMETIC_OPERATOR[" << sign << "], CENTER_LOCATION[" << this->get_x() << "," << this->get_y() <<"], SIZE["<<this->get_size()<<"]" << endl;
}

//prints all operators on grid
void OperatorGrid::print_operators(){
    for(int i = 1 ; i <= num_operators ; i++){
        operators[i]->print_operator();
    }
}

//grid constructor
OperatorGrid::OperatorGrid(int rows, int cols){
    num_operators = 0;
    grid_cols = cols;
    grid_rows = rows;
    grid = new char*[rows+1];
    for(int i=0;i<=rows;i++){
        grid[i] = new char[cols+1];
        for(int j=0;j<=cols;j++){
            grid[i][j] = 0;
        }
    }
}

//grid destructor
OperatorGrid::~OperatorGrid(){
    for(int i=1; i <= num_operators; i++){
        delete operators[i];
    }
    for(int i=0; i <= grid_rows; i++) {
        delete[] grid[i];
    }
    delete[] grid;
    cout << "DESTRUCTOR: GIVE BACK[" << grid_rows << "," << grid_cols << "] chars." << endl;
    cout << "DESTRUCTOR: GIVE BACK[" << num_operators <<"] Operators." << endl;
}

bool OperatorGrid::is_border_error(ArithmeticOperator *p) {
    if(p->get_x() > grid_rows || p->get_y() > grid_cols || p->get_x() < 1 || p->get_y() < 1){
        return true;
    }//checks if center of the operator out of grid

    if(p->get_sign() == '-'){//to minus character we just checking the Y-axis
        if(p->get_y() + p->get_size() > grid_cols){
            return true;
        }
        if(p->get_y() - p->get_size() < 1){
            return true;
        }
    }else{//to other characters we check all edges
        if(p->get_y() + p->get_size() > grid_cols){
            return true;
        }
        if(p->get_y() - p->get_size() < 1){
            return true;
        }
        if(p->get_x() + p->get_size() > grid_rows){
            return true;
        }
        if(p->get_x() - p->get_size() < 1){
            return true;
        }
    }

    return false;
}

bool OperatorGrid::is_conflict_error(ArithmeticOperator *p) {

    //the center x, y and size parameters of ArithmeticOperator
    int x = p->get_x();
    int y = p->get_y();
    int size = p->get_size();

    //the edge x and y parameters of ArithmeticOperator
    int x_min_edge = x - size;
    int x_max_edge = x + size;
    int y_min_edge = y - size;
    int y_max_edge = y + size;

    if(p->get_sign() == '-'){
        for (int i = y_min_edge; i <= y_max_edge; i++) {
            if(i > 0 && i <= grid_cols && x > 0 && x <=grid_rows){
                if(grid[x][i]){
                    return true;
                }
            }
        }
    }
    if(p->get_sign() == '+'){
        for (int i = y_min_edge; i <= y_max_edge; i++) {
            if(i > 0 && i <= grid_cols && x > 0 && x <=grid_rows){
                if(grid[x][i]){
                    return true;
                }
            }
        }
        for (int i = x_min_edge; i <= x_max_edge; i++) {
            if(i > 0 && i <= grid_rows && y > 0 && x <=grid_rows){
                if(grid[i][y]){
                    return true;
                }
            }
        }
    }

    if(p->get_sign() == '/'){
        int j = y_min_edge;
        for (int i = x_min_edge; i <= x_max_edge ; i++) {
            if(i > 0 && j > 0 && i <= grid_rows && j <= grid_cols){
                if(grid[i][j]){
                    return true;
                }
                j++;
            }
        }
    }
    if(p->get_sign() == 'x'){
        int j = y_max_edge;
        for (int i = x_min_edge; i <= x_max_edge ; i++) {
            if(i > 0 && j > 0 && i <= grid_rows && j <= grid_cols){
                if(grid[i][j]){
                    return true;
                }
                j--;
            }
        }

        j = y_min_edge;
        for (int i = x_min_edge; i <= x_max_edge ; i++) {
            if(i > 0 && j > 0 && i <= grid_rows && j <= grid_cols){
                if(grid[i][j]){
                    return true;
                }
                j++;
            }
        }
    }
    return false;
}

bool OperatorGrid::place_operator(ArithmeticOperator *p){
    if(p->get_sign() == '-' || p->get_sign() == '+' || p->get_sign() == 'x' || p->get_sign() == '/'){
        if(is_border_error(p) && is_conflict_error(p)){//checks both errors
            cout << "BORDER ERROR: Operator "<< p->get_sign() <<" with size " << p->get_size() << " can not be placed on (" << p->get_x() << "," << p->get_y()<< ")." << endl;
            cout << "CONFLICT ERROR: Operator "<< p->get_sign() <<" with size " << p->get_size() << " can not be placed on (" << p->get_x() << "," << p->get_y()<< ")." << endl;
            return false;
        }else if(is_border_error(p)){//checks border error
            cout << "BORDER ERROR: Operator "<< p->get_sign() <<" with size " << p->get_size() << " can not be placed on (" << p->get_x() << "," << p->get_y()<< ")." << endl;
            return false;
        }else if(is_conflict_error(p)){//checks conflict error
            cout << "CONFLICT ERROR: Operator "<< p->get_sign() <<" with size " << p->get_size() << " can not be placed on (" << p->get_x() << "," << p->get_y()<< ")." << endl;
            return false;
        }else{// if there is no error create an ArithmeticOperator to operators array
            cout << "SUCCESS: Operator " << p->get_sign() << " with size " <<  p->get_size() << " is placed on (" << p->get_x() << "," << p->get_y()<< ")." << endl;
            num_operators++;
            insert_operator(p,num_operators);
            operators[num_operators] = new ArithmeticOperator(p->get_x(), p->get_y(), p->get_size() , p->get_sign());
            return true;
        }
    }else{
        return false;
    }
}


void OperatorGrid::insert_operator(ArithmeticOperator *p, int number) {//inserts the given ArithmeticOperator to grid
    int x = p->get_x();
    int y = p->get_y();
    int size = p->get_size();

    int x_min_edge = x - size;
    int x_max_edge = x + size;
    int y_min_edge = y - size;
    int y_max_edge = y + size;

    if(p->get_sign() == '-'){
        for (int i = y_min_edge; i <= y_max_edge; i++) {
            grid[x][i] = number;
        }
    }
    if(p->get_sign() == '+'){
        for (int i = y_min_edge; i <= y_max_edge; i++) {
            grid[x][i] = number;
        }
        for (int i = x_min_edge; i <= x_max_edge; i++) {
            grid[i][y] = number;
        }
    }
    if(p->get_sign() == '/'){
        int j = y_max_edge;
        for (int i = x_min_edge; i <= x_max_edge ; i++) {
            grid[i][j] = number;
            j--;
        }
    }
    if(p->get_sign() == 'x'){
        int j = y_max_edge;
        for (int i = x_min_edge; i <= x_max_edge ; i++) {
            grid[i][j] = number;
            j--;
        }

        j = y_min_edge;
        for (int i = x_min_edge; i <= x_max_edge ; i++) {
            grid[i][j] = number;
            j++;
        }
    }
}

void OperatorGrid::delete_operator(ArithmeticOperator *p) {//clears the locations on the grid where the given ArithmeticOperator is
    int x = p->get_x();
    int y = p->get_y();
    int size = p->get_size();

    int x_min_edge = x - size;
    int x_max_edge = x + size;
    int y_min_edge = y - size;
    int y_max_edge = y + size;

    if(p->get_sign() == '-'){
        for (int i = y_min_edge; i <= y_max_edge; i++) {
            grid[x][i] = 0;
        }
    }
    if(p->get_sign() == '+'){
        for (int i = y_min_edge; i <= y_max_edge; i++) {
            grid[x][i] = 0;
        }
        for (int i = x_min_edge; i <= x_max_edge; i++) {
            grid[i][y] = 0;
        }
    }
    if(p->get_sign() == '/'){
        int j = y_max_edge;
        for (int i = x_min_edge; i <= x_max_edge ; i++) {
            grid[i][j] = 0;
            j--;
        }
    }
    if(p->get_sign() == 'x'){
        int j = y_max_edge;
        for (int i = x_min_edge; i <= x_max_edge ; i++) {
            grid[i][j] = 0;
            j--;
        }

        j = y_min_edge;
        for (int i = x_min_edge; i <= x_max_edge ; i++) {
            grid[i][j] = 0;
            j++;
        }
    }
}

bool OperatorGrid::move_operator(int x, int y, char direction, int move_by) {
    int number = grid[x][y];
    if(!number){// if it is 0, so it is empty do not do anything
        return false;
    }
    int old_x = operators[number]->get_x();
    int old_y = operators[number]->get_y();
    int size = operators[number]->get_size();
    if(direction == 'R'){
        delete_operator(operators[number]);
        operators[number]->reset(old_x,old_y+move_by,size);
        if(is_conflict_error(operators[number]) && is_border_error(operators[number])){
            cout << "BORDER ERROR: " << operators[number]->get_sign() <<" can not be moved from ("<<old_x<<","<<old_y<<") to ("<<operators[number]->get_x()<<","<<operators[number]->get_y()<<")." << endl;
            cout << "CONFLICT ERROR: " << operators[number]->get_sign() <<" can not be moved from ("<<old_x<<","<<old_y<<") to ("<<operators[number]->get_x()<<","<<operators[number]->get_y()<<")." << endl;
            operators[number]->reset(old_x,old_y,size);
            insert_operator(operators[number],number);
            return false;
        }else if(is_border_error(operators[number])){
            cout << "BORDER ERROR: " << operators[number]->get_sign() <<" can not be moved from ("<<old_x<<","<<old_y<<") to ("<<operators[number]->get_x()<<","<<operators[number]->get_y()<<")." << endl;
            operators[number]->reset(old_x,old_y,size);
            insert_operator(operators[number],number);
            return false;
        }else if(is_conflict_error(operators[number])){
            cout << "CONFLICT ERROR: " << operators[number]->get_sign() <<" can not be moved from ("<<old_x<<","<<old_y<<") to ("<<operators[number]->get_x()<<","<<operators[number]->get_y()<<")." << endl;
            operators[number]->reset(old_x,old_y,size);
            insert_operator(operators[number],number);
            return false;
        }else{
            insert_operator(operators[number], number);
            cout << "SUCCESS: " << operators[number]->get_sign() <<" moved from ("<<old_x<<","<<old_y<<") to ("<<operators[number]->get_x()<<","<<operators[number]->get_y()<<")." << endl;
            return true;
        }
    }
    if(direction == 'L'){
        delete_operator(operators[number]);
        operators[number]->reset(old_x,old_y-move_by,size);
        if(is_conflict_error(operators[number]) && is_border_error(operators[number])){
            cout << "BORDER ERROR: " << operators[number]->get_sign() <<" can not be moved from ("<<old_x<<","<<old_y<<") to ("<<operators[number]->get_x()<<","<<operators[number]->get_y()<<")." << endl;
            cout << "CONFLICT ERROR: " << operators[number]->get_sign() <<" can not be moved from ("<<old_x<<","<<old_y<<") to ("<<operators[number]->get_x()<<","<<operators[number]->get_y()<<")." << endl;
            operators[number]->reset(old_x,old_y,size);
            insert_operator(operators[number],number);
            return false;
        }else if(is_border_error(operators[number])){
            cout << "BORDER ERROR: " << operators[number]->get_sign() <<" can not be moved from ("<<old_x<<","<<old_y<<") to ("<<operators[number]->get_x()<<","<<operators[number]->get_y()<<")." << endl;
            operators[number]->reset(old_x,old_y,size);
            insert_operator(operators[number],number);
            return false;
        }else if(is_conflict_error(operators[number])){
            cout << "CONFLICT ERROR: " << operators[number]->get_sign() <<" can not be moved from ("<<old_x<<","<<old_y<<") to ("<<operators[number]->get_x()<<","<<operators[number]->get_y()<<")." << endl;
            operators[number]->reset(old_x,old_y,size);
            insert_operator(operators[number],number);
            return false;
        }else{
            cout << "SUCCESS: " << operators[number]->get_sign() <<" moved from ("<<old_x<<","<<old_y<<") to ("<<operators[number]->get_x()<<","<<operators[number]->get_y()<<")." << endl;
            insert_operator(operators[number], number);
            return true;
        }
    }
    if(direction == 'D'){
        delete_operator(operators[number]);
        operators[number]->reset(old_x+move_by,old_y,size);
        if(is_conflict_error(operators[number]) && is_border_error(operators[number])){
            cout << "BORDER ERROR: " << operators[number]->get_sign() <<" can not be moved from ("<<old_x<<","<<old_y<<") to ("<<operators[number]->get_x()<<","<<operators[number]->get_y()<<")." << endl;
            cout << "CONFLICT ERROR: " << operators[number]->get_sign() <<" can not be moved from ("<<old_x<<","<<old_y<<") to ("<<operators[number]->get_x()<<","<<operators[number]->get_y()<<")." << endl;
            operators[number]->reset(old_x,old_y,size);
            insert_operator(operators[number],number);
            return false;
        }else if(is_border_error(operators[number])){
            cout << "BORDER ERROR: " << operators[number]->get_sign() <<" can not be moved from ("<<old_x<<","<<old_y<<") to ("<<operators[number]->get_x()<<","<<operators[number]->get_y()<<")." << endl;
            operators[number]->reset(old_x,old_y,size);
            insert_operator(operators[number],number);
            return false;
        }else if(is_conflict_error(operators[number])){
            cout << "CONFLICT ERROR: " << operators[number]->get_sign() <<" can not be moved from ("<<old_x<<","<<old_y<<") to ("<<operators[number]->get_x()<<","<<operators[number]->get_y()<<")." << endl;
            operators[number]->reset(old_x,old_y,size);
            insert_operator(operators[number],number);
            return false;
        }else{
            cout << "SUCCESS: " << operators[number]->get_sign() <<" moved from ("<<old_x<<","<<old_y<<") to ("<<operators[number]->get_x()<<","<<operators[number]->get_y()<<")." << endl;
            insert_operator(operators[number], number);
            return true;
        }
    }
    if(direction == 'U'){
        delete_operator(operators[number]);
        operators[number]->reset(old_x-move_by,old_y,size);
        if(is_conflict_error(operators[number]) && is_border_error(operators[number])){
            cout << "BORDER ERROR: " << operators[number]->get_sign() <<" can not be moved from ("<<old_x<<","<<old_y<<") to ("<<operators[number]->get_x()<<","<<operators[number]->get_y()<<")." << endl;
            cout << "CONFLICT ERROR: " << operators[number]->get_sign() <<" can not be moved from ("<<old_x<<","<<old_y<<") to ("<<operators[number]->get_x()<<","<<operators[number]->get_y()<<")." << endl;
            operators[number]->reset(old_x,old_y,size);
            insert_operator(operators[number],number);
            return false;
        }else if(is_border_error(operators[number])){
            cout << "BORDER ERROR: " << operators[number]->get_sign() <<" can not be moved from ("<<old_x<<","<<old_y<<") to ("<<operators[number]->get_x()<<","<<operators[number]->get_y()<<")." << endl;
            operators[number]->reset(old_x,old_y,size);
            insert_operator(operators[number],number);
            return false;
        }else if(is_conflict_error(operators[number])){
            cout << "CONFLICT ERROR: " << operators[number]->get_sign() <<" can not be moved from ("<<old_x<<","<<old_y<<") to ("<<operators[number]->get_x()<<","<<operators[number]->get_y()<<")." << endl;
            operators[number]->reset(old_x,old_y,size);
            insert_operator(operators[number],number);
            return false;
        }else{
            cout << "SUCCESS: " << operators[number]->get_sign() <<" moved from ("<<old_x<<","<<old_y<<") to ("<<operators[number]->get_x()<<","<<operators[number]->get_y()<<")." << endl;
            insert_operator(operators[number], number);
            return true;
        }
    }
    return false;
}