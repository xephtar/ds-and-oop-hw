#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LINE 30
#define MAX_LENGTH 3
#define LAST_WORD 2
#define INITIAL_VALUE 1

struct grid_s {
  char type;
  int size;
  int row;
  int column;
};

struct instructions_s {
  char type[MAX_LENGTH];
  int size;
  int row;
  int column;
};

struct index {
  int index_x;
  int index_y;
  int size;
};

void grid_success(int x, int y);
void conflict_error_g(struct grid_s gridArr[MAX_LINE], int n);
void border_error_g(struct grid_s gridArr[MAX_LINE], int n);
void success_message_g(struct grid_s gridArr[MAX_LINE], int n);

void success_message_s(int size, int x,int y, int n, char type, char key);
void conflict_error_s(int size,int x,int y, int n, char type, char key);
void border_error_s(int size,int x,int y, int n, char type, char key);

int main(int argc, char *argv[])
{
  FILE *fp;
  fp = fopen(argv[1], "r");
  int gridN = 0;

  //Storing grid.txt
  struct grid_s gridArr[MAX_LINE];
  if (fp != NULL) {
    //takes grid size
    fscanf(fp, "%d %d", &gridArr[gridN].row, &gridArr[gridN].column);

    gridN++;

    //takes operators and locations
    while (fscanf(fp, "%s %d %d %d", &gridArr[gridN].type, &gridArr[gridN].row, &gridArr[gridN].column, &gridArr[gridN].size) != EOF) {

      gridN++;
    }

    fclose(fp);
  }

  int grid_row = gridArr[0].row;
  int grid_column = gridArr[0].column;

  //grid created
  char grid[MAX_LINE][MAX_LINE] = {{'\0'}};
  //main index for all points
  struct index all_grid_index[MAX_LINE][MAX_LINE];

  //Grid success message
  grid_success(grid_row, grid_column);

  //Puts charachers in array
  for (int i = INITIAL_VALUE; i < gridN; i++) {
    int max_row = gridArr[i].row + gridArr[i].size;
    int max_col = gridArr[i].column + gridArr[i].size;
    int min_row = gridArr[i].row - gridArr[i].size;
    int min_col = gridArr[i].column - gridArr[i].size;
    int zero = 0;
    bool c_issue = true;
    bool b_issue = true;

    switch (gridArr[i].type) {

      case '+':{
      if (max_row > grid_row || min_row <= zero || max_col > grid_column || min_col <= zero) {
        b_issue = false;
      }

      for (int x = min_row; x <= max_row; x++) {
        for (int y = min_col; y <= max_col; y++) {
          if (grid[gridArr[i].row][y] != '\0' || grid[x][gridArr[i].column] != '\0') {
            c_issue = false;
          }
        }
      }

      if (c_issue && b_issue){
        for (int x = min_row; x <= max_row; x++) {
          grid[x][gridArr[i].column] = '+';
          all_grid_index[x][gridArr[i].column].index_x = gridArr[i].row;
          all_grid_index[x][gridArr[i].column].index_y = gridArr[i].column;
          all_grid_index[x][gridArr[i].column].size = gridArr[i].size;
        }
        for (int y = min_col; y <= max_col; y++) {
          grid[gridArr[i].row][y] = '+';
          all_grid_index[gridArr[i].row][y].index_y = gridArr[i].column;
          all_grid_index[gridArr[i].row][y].index_x = gridArr[i].row;
          all_grid_index[gridArr[i].row][y].size = gridArr[i].size;


        }
        success_message_g(gridArr, i);
      }else if (b_issue != true && !c_issue != true){
        border_error_g(gridArr, i);
        conflict_error_g(gridArr, i);
      }else if(!b_issue){
        border_error_g(gridArr, i);
      }else if(!c_issue){
        conflict_error_g(gridArr, i);
      }
      }
      break;


      case '-':{
      if (max_col > grid_column || min_col <= zero || gridArr[i].row > grid_row || gridArr[i].row <= zero){
        b_issue = false;
      }

      for (int y = min_col; y <= max_col; y++) {
          if (grid[gridArr[i].row][y] != '\0') {
            c_issue = false;
          }
      }

      if (c_issue && b_issue){
        for (int y = min_col; y <= max_col; y++) {
            grid[gridArr[i].row][y] = '-';
            all_grid_index[gridArr[i].row][y].index_y = gridArr[i].column;
            all_grid_index[gridArr[i].row][y].index_x = gridArr[i].row;
            all_grid_index[gridArr[i].row][y].size = gridArr[i].size;
        }
        success_message_g(gridArr, i);
      }else if(!b_issue && !c_issue){
        border_error_g(gridArr, i);
        conflict_error_g(gridArr, i);
      }else if(!b_issue){
        border_error_g(gridArr, i);
      }else if(!c_issue){
        conflict_error_g(gridArr, i);
      }
      }
      break;

      case 'x':{
      if (max_row > grid_row || min_row <= zero || max_col > grid_column || min_col <= zero) {
        b_issue = false;
      }

      int y = min_col;
      for (int x = min_row; x <= max_row; x++) {
        if (grid[x][y] != '\0') {
          c_issue = false;
        }
        y++;
      }
      int x = max_row;
      for (int y = min_col; y <= max_col; y++) {
        if (grid[x][y] != '\0') {
          c_issue = false;
        }
        x--;
      }

      if (c_issue && b_issue){
        int y = min_col;
        for (int x = min_row; x <= max_row; x++) {
          grid[x][y] = 'x';
          all_grid_index[x][y].index_y = gridArr[i].column;
          all_grid_index[x][y].index_x = gridArr[i].row;
          all_grid_index[x][y].size = gridArr[i].size;
          y++;
        }
        int x = max_row;
        for (int y = min_col; y <= max_col; y++) {
          grid[x][y] = 'x';
          all_grid_index[x][y].index_y = gridArr[i].column;
          all_grid_index[x][y].index_x = gridArr[i].row;
          all_grid_index[x][y].size = gridArr[i].size;
          x--;
        }
        success_message_g(gridArr, i);
      }else if(!b_issue && !c_issue){
        border_error_g(gridArr, i);
        conflict_error_g(gridArr, i);
      }else if(!b_issue){
        border_error_g(gridArr, i);
      }else if(!c_issue){
        conflict_error_g(gridArr, i);
      }
      }
      break;


      case '/':{
      if (max_row > grid_row || min_row <= zero || max_col > grid_column || min_col <= zero) {
        b_issue = false;
      }

      int x = max_row;
      for (int y = min_col; y <= max_col; y++) {
        if (grid[x][y] != '\0') {
          c_issue = false;
        }
        x--;
      }

      if (c_issue && b_issue){
        int x = max_row;
        for (int y = min_col; y <= max_col; y++) {
          grid[x][y] = '/';
          all_grid_index[x][y].index_y = gridArr[i].column;
          all_grid_index[x][y].index_x = gridArr[i].row;
          all_grid_index[x][y].size = gridArr[i].size;
          x--;
        }
        success_message_g(gridArr, i);
      }else if(!b_issue && !c_issue){
        border_error_g(gridArr, i);
        conflict_error_g(gridArr, i);
      }else if(!b_issue){
        border_error_g(gridArr, i);
      }else if(!c_issue){
        conflict_error_g(gridArr, i);
      }
      }
      break;

    }
  }

  //Storing instructions.txt
  fp = fopen(argv[2], "r");
  int instN = INITIAL_VALUE;
  struct instructions_s instArr[MAX_LINE];
  if (fp != NULL) {

    //takes moves and locations
    while (fscanf(fp, "%s %d %d %d", instArr[instN].type, &instArr[instN].row, &instArr[instN].column, &instArr[instN].size) != EOF) {

      instN++;
    }

    fclose(fp);
  }

  //moves characters
  for (int i = INITIAL_VALUE; i < instN; i++){
    char last_key = instArr[i].type[LAST_WORD];
    char type_of_point = grid[instArr[i].row][instArr[i].column];
    int main_x = all_grid_index[instArr[i].row][instArr[i].column].index_x;
    int main_y = all_grid_index[instArr[i].row][instArr[i].column].index_y;
    int main_size =  all_grid_index[instArr[i].row][instArr[i].column].size;
    int min_row = main_x - main_size - instArr[i].size;
    int min_col = main_y - main_size - instArr[i].size;
    int max_row = main_x + main_size + instArr[i].size;
    int max_col = main_y + main_size + instArr[i].size;
    int new_main_x_u = main_x - instArr[i].size;
    int new_main_x_d = main_x + instArr[i].size;
    int new_main_y_l = main_y - instArr[i].size;
    int new_main_y_r = main_y + instArr[i].size;

    //
    int zero = 0;

    bool c_issue = true;
    bool b_issue = true;
    switch (last_key) {
      case 'U':{
        switch (type_of_point) {
          case '+':{

            if (min_row <= zero) {
              b_issue = false;
            }

            for (int x = new_main_x_u-main_size; x <= new_main_x_u+main_size; x++) {
              if(x > zero){
                if ((grid[x][main_y] != '\0') && (main_x != all_grid_index[x][main_y].index_x || main_y != all_grid_index[x][main_y].index_y)) {
                  c_issue = false;
                }
              }
            }
            for (int y = main_y-main_size; y <= main_y+main_size; y++) {
              if (y > zero) {
                if ((grid[new_main_x_u][y] != '\0') && (main_x != all_grid_index[new_main_x_u][y].index_x || main_y != all_grid_index[new_main_x_u][y].index_y)) {
                  c_issue = false;
                }
              }
            }

            if (b_issue && c_issue) {
              for (int x = main_x-main_size; x <= main_x+main_size; x++) {
                grid[x][main_y] = '\0';
                all_grid_index[x][main_y].index_x = zero;
                all_grid_index[x][main_y].index_y = zero;
                all_grid_index[x][main_y].size = zero;
              }
              for (int y = main_y-main_size; y <= main_y+main_size; y++) {
                grid[main_x][y] = '\0';
                all_grid_index[main_x][y].index_x = zero;
                all_grid_index[main_x][y].index_y = zero;
                all_grid_index[main_x][y].size = zero;
              }
              for (int x = new_main_x_u-main_size; x <= new_main_x_u+main_size; x++) {
                grid[x][main_y] = '+';
                all_grid_index[x][main_y].index_x = new_main_x_u;
                all_grid_index[x][main_y].index_y = main_y;
                all_grid_index[x][main_y].size = main_size;
              }
              for (int y = main_y-main_size; y <= main_y+main_size; y++) {
                grid[new_main_x_u][y] = '+';
                all_grid_index[new_main_x_u][y].index_x = new_main_x_u;
                all_grid_index[new_main_x_u][y].index_y = main_y;
                all_grid_index[new_main_x_u][y].size = main_size;
              }

              success_message_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!(b_issue || c_issue)){
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!b_issue) {
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!c_issue) {
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }
          }
          break;

          case '-':{
            if (new_main_x_u <= zero) {
              b_issue = false;
            }

            for (int y = main_y-main_size; y <= main_y+main_size; y++) {
              if (new_main_x_u > zero) {
                if (grid[new_main_x_u][y] != '\0' && (main_x != all_grid_index[main_x-instArr[i].size][y].index_x || main_y != all_grid_index[main_x-instArr[i].size][y].index_y)) {
                  c_issue = false;
                }
              }
            }

            if (b_issue && c_issue) {
              for (int y = main_y-main_size; y <= main_y+main_size; y++) {
                grid[main_x][y] = '\0';
                all_grid_index[main_x][y].index_x = zero;
                all_grid_index[main_x][y].index_y = zero;
                all_grid_index[main_x][y].size = zero;
              }

              for (int y = main_y-main_size; y <= main_y+main_size; y++) {
                grid[new_main_x_u][y] = '-';
                all_grid_index[new_main_x_u][y].index_x = new_main_x_u;
                all_grid_index[new_main_x_u][y].index_y = main_y;
                all_grid_index[new_main_x_u][y].size = main_size;
              }
              success_message_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!(b_issue || c_issue)){
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!b_issue) {
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!c_issue){
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }
          }
          break;

          case 'x':{
            if (min_row <= zero) {
              b_issue = false;
            }

            int y = main_y - main_size;
            for (int x = min_row; x <= new_main_x_u+main_size; x++) {
              if(x > zero && y > zero){
                if (grid[x][y] != '\0' && (main_x != all_grid_index[x][y].index_x || main_y != all_grid_index[x][y].index_y)) {
                  c_issue = false;
                }
              }
              y++;
            }
            int x = main_x + main_size;
            for (int y = min_col; y <= main_y+main_size; y++) {
              if(x > zero && y > zero){
                if (grid[x][y] != '\0' && (main_x != all_grid_index[x][y].index_x || main_y != all_grid_index[x][y].index_y)) {
                  c_issue = false;
                }
              }
              x--;
            }

            if (b_issue && c_issue) {

              int y = main_y-main_size;
              for (int x = main_x-main_size; x <= main_x+main_size; x++) {
                grid[x][y] = '\0';
                all_grid_index[x][y].index_y = zero;
                all_grid_index[x][y].index_x = zero;
                all_grid_index[x][y].size = zero;
                y++;
              }
              int x = main_x+main_size;
              for (int y = main_y-main_size; y <= main_y+main_size; y++) {
                grid[x][y] = '\0';
                all_grid_index[x][y].index_y = zero;
                all_grid_index[x][y].index_x = zero;
                all_grid_index[x][y].size = zero;
                x--;
              }

              y = main_y-main_size;
              for (int x = new_main_x_u-main_size; x <= new_main_x_u+main_size; x++) {
                grid[x][y] = 'x';
                all_grid_index[x][y].index_y = main_y;
                all_grid_index[x][y].index_x = new_main_x_u;
                all_grid_index[x][y].size = main_size;
                y++;
              }
              x = new_main_x_u+main_size;
              for (int y = main_y-main_size; y <= main_y+main_size; y++) {
                grid[x][y] = 'x';
                all_grid_index[x][y].index_y = main_y;
                all_grid_index[x][y].index_x = new_main_x_u;
                all_grid_index[x][y].size = main_size;
                x--;
              }

              success_message_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!(b_issue || c_issue)){
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!b_issue) {
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!c_issue) {
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }
          }
          break;

          case '/':{
            if (min_row <= zero) {
              b_issue = false;
            }

            int x = new_main_x_u+main_size;
            for (int y = main_y-main_size; y <= main_y+main_size; y++) {
              if(x > zero && y > zero){
                if (grid[x][y] != '\0' && (main_x != all_grid_index[x][y].index_x || main_y != all_grid_index[x][y].index_y)) {
                  c_issue = false;
                }
              }
              x--;
            }

            if (b_issue && c_issue) {
              int x = main_x+main_size;
              for (int y = main_y-main_size; y <= main_y+main_size; y++) {
                grid[x][y] = '\0';
                all_grid_index[x][y].index_y = zero;
                all_grid_index[x][y].index_x = zero;
                all_grid_index[x][y].size = zero;
                x--;
              }

              x = new_main_x_u+main_size;
              for (int y = main_y-main_size; y <= main_y+main_size; y++) {
                grid[x][y] = '/';
                all_grid_index[x][y].index_y = main_y;
                all_grid_index[x][y].index_x = new_main_x_u;
                all_grid_index[x][y].size = main_size;
                x--;
              }
              success_message_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!(b_issue || c_issue)){
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!b_issue) {
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!c_issue) {
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }

          }
          break;
        }
      }
      break;

      case 'D':{
        switch (type_of_point) {
          case '+':{
            if (max_row > grid_row) {
              b_issue = false;
            }

            for (int x = new_main_x_d-main_size; x <= new_main_x_d+main_size; x++) {
              if (x > zero) {
                if (grid[x][main_y] != '\0' && (all_grid_index[x][main_y].index_x != main_x || all_grid_index[x][main_y].index_y != main_y)) {
                  c_issue = false;
                }
              }
            }
            for (int y = main_y-main_size; y <= main_y+main_size; y++) {
              if (y > zero) {
                if (grid[new_main_x_d][y] != '\0' && (all_grid_index[new_main_x_d][y].index_x != main_x || all_grid_index[new_main_x_d][y].index_y != main_y)) {
                  c_issue = false;
                }
              }
            }

            if (b_issue && c_issue) {
              for (int x = main_x-main_size; x <= main_x+main_size; x++) {
                grid[x][main_y] = '\0';
                all_grid_index[x][main_y].index_x = zero;
                all_grid_index[x][main_y].index_y = zero;
                all_grid_index[x][main_y].size = zero;
              }
              for (int y = main_y-main_size; y <= main_y+main_size; y++) {
                grid[main_x][y] = '\0';
                all_grid_index[main_x][y].index_x = zero;
                all_grid_index[main_x][y].index_y = zero;
                all_grid_index[main_x][y].size = zero;
              }
              for (int x = new_main_x_d-main_size; x <= new_main_x_d+main_size; x++) {
                grid[x][main_y] = '+';
                all_grid_index[x][main_y].index_x = new_main_x_d;
                all_grid_index[x][main_y].index_y = main_y;
                all_grid_index[x][main_y].size = main_size;
              }
              for (int y = main_y-main_size; y <= main_y+main_size; y++) {
                grid[new_main_x_d][y] = '+';
                all_grid_index[new_main_x_d][y].index_x = new_main_x_d;
                all_grid_index[new_main_x_d][y].index_y = main_y;
                all_grid_index[new_main_x_d][y].size = main_size;
              }

              success_message_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!(b_issue || c_issue)) {
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!b_issue) {
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!c_issue) {
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }

          }
          break;

          case '-':{
            if (new_main_x_d > grid_row) {
              b_issue = false;
            }

            for (int y = main_y-main_size; y <= main_y+main_size; y++) {
              if (new_main_x_d > zero) {
                if (grid[new_main_x_d][y] != '\0' && (main_x != all_grid_index[new_main_x_d][y].index_x || main_y != all_grid_index[new_main_x_d][y].index_y)) {
                  c_issue = false;
                }
              }
            }

            if (b_issue && c_issue) {
              for (int y = main_y-main_size; y <= main_y+main_size; y++) {
                grid[main_x][y] = '\0';
                all_grid_index[main_x][y].index_x = zero;
                all_grid_index[main_x][y].index_y = zero;
                all_grid_index[main_x][y].size = zero;
              }

              for (int y = main_y-main_size; y <= main_y+main_size; y++) {
                grid[new_main_x_d][y] = '-';
                all_grid_index[new_main_x_d][y].index_x = new_main_x_d;
                all_grid_index[new_main_x_d][y].index_y = main_y;
                all_grid_index[new_main_x_d][y].size = main_size;
              }
              success_message_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!(b_issue || c_issue)){
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!b_issue) {
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!c_issue){
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }
          }
          break;

          case 'x':{
            if (max_row > grid_row) {
              b_issue = false;
            }

            int y = main_y - main_size;
            for (int x = new_main_x_d-main_size; x <= new_main_x_d+main_size; x++) {
              if(x > zero && y > zero){
                if (grid[x][y] != '\0' && (main_x != all_grid_index[x][y].index_x || main_y != all_grid_index[x][y].index_y)) {
                  c_issue = false;
                }
              }
              y++;
            }
            int x = new_main_x_d + main_size;
            for (int y = main_y-main_size; y <= main_y+main_size; y++) {
              if(x > zero && y > zero){
                if (grid[x][y] != '\0' && (main_x != all_grid_index[x][y].index_x || main_y != all_grid_index[x][y].index_y)) {
                  c_issue = false;
                }
              }
              x--;
            }

            if (b_issue && c_issue) {

              int y = main_y-main_size;
              for (int x = main_x-main_size; x <= main_x+main_size; x++) {
                grid[x][y] = '\0';
                all_grid_index[x][y].index_y = zero;
                all_grid_index[x][y].index_x = zero;
                all_grid_index[x][y].size = zero;
                y++;
              }
              int x = main_x+main_size;
              for (int y = main_y-main_size; y <= main_y+main_size; y++) {
                grid[x][y] = '\0';
                all_grid_index[x][y].index_y = zero;
                all_grid_index[x][y].index_x = zero;
                all_grid_index[x][y].size = zero;
                x--;
              }

              y = main_y-main_size;
              for (int x = new_main_x_d-main_size; x <= new_main_x_d+main_size; x++) {
                grid[x][y] = 'x';
                all_grid_index[x][y].index_y = main_y;
                all_grid_index[x][y].index_x = new_main_x_d;
                all_grid_index[x][y].size = main_size;
                y++;
              }
              x = new_main_x_d+main_size;
              for (int y = main_y-main_size; y <= main_y+main_size; y++) {
                grid[x][y] = 'x';
                all_grid_index[x][y].index_y = main_y;
                all_grid_index[x][y].index_x = new_main_x_d;
                all_grid_index[x][y].size = main_size;
                x--;
              }

              success_message_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!(b_issue || c_issue)){
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!b_issue) {
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!c_issue) {
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }
          }
          break;

          case '/':{
            if (new_main_x_d+main_size > grid_row) {
              b_issue = false;
            }

            int x = new_main_x_d+main_size;
            for (int y = main_y-main_size; y <= main_y+main_size; y++) {
              if(x > zero && y > zero){
                if (grid[x][y] != '\0' && (main_x != all_grid_index[x][y].index_x || main_y != all_grid_index[x][y].index_y)) {
                  c_issue = false;
                }
              }
              x--;
            }

            if (b_issue && c_issue) {
              int x = main_x+main_size;
              for (int y = main_y-main_size; y <= main_y+main_size; y++) {
                grid[x][y] = '\0';
                all_grid_index[x][y].index_y = zero;
                all_grid_index[x][y].index_x = zero;
                all_grid_index[x][y].size = zero;
                x--;
              }

              x = new_main_x_d+main_size;
              for (int y = main_y-main_size; y <= main_y+main_size; y++) {
                grid[x][y] = '/';
                all_grid_index[x][y].index_y = main_y;
                all_grid_index[x][y].index_x = new_main_x_d;
                all_grid_index[x][y].size = main_size;
                x--;
              }
              success_message_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!(b_issue || c_issue)){
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!b_issue) {
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!c_issue) {
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }
          }
          break;

        }
      }
      break;

      case 'L':{
        switch (type_of_point) {
          case '+':{
            if (min_col <= zero) {
              b_issue = false;
            }

            for (int y = min_col; y <= new_main_y_l+main_size; y++) {
              if (y > zero) {
                if ((grid[main_x][y] != '\0') && (main_x != all_grid_index[main_x][y].index_x || main_y != all_grid_index[main_x][y].index_y)) {
                  c_issue = false;
                }
              }
            }
            for (int x = main_x-main_size; x <= main_x+main_size; x++) {
              if(x > zero){
                if ((grid[x][new_main_y_l] != '\0') && (main_x != all_grid_index[x][new_main_y_l].index_x || main_y != all_grid_index[x][new_main_y_l].index_y)) {
                  c_issue = false;
                }
              }
            }

            if (b_issue && c_issue) {
              for (int y = main_y-main_size; y <= main_y+main_size; y++) {
                grid[main_x][y] = '\0';
                all_grid_index[main_x][y].index_x = zero;
                all_grid_index[main_x][y].index_y = zero;
                all_grid_index[main_x][y].size = zero;
              }
              for (int x = main_x-main_size; x <= main_x+main_size; x++) {
                grid[x][main_y] = '\0';
                all_grid_index[x][main_y].index_x = zero;
                all_grid_index[x][main_y].index_y = zero;
                all_grid_index[x][main_y].size = zero;
              }
              for (int y = new_main_y_l-main_size; y <= new_main_y_l+main_size; y++) {
                grid[main_x][y] = '+';
                all_grid_index[main_x][y].index_x = main_x;
                all_grid_index[main_x][y].index_y = new_main_y_l;
                all_grid_index[main_x][y].size = main_size;
              }
              for (int x = main_x-main_size; x <= main_x+main_size; x++) {
                grid[x][new_main_y_l] = '+';
                all_grid_index[x][new_main_y_l].index_x = main_x;
                all_grid_index[x][new_main_y_l].index_y = new_main_y_l;
                all_grid_index[x][new_main_y_l].size = main_size;
              }

              success_message_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!(b_issue || c_issue)){
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!b_issue) {
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!c_issue) {
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }

          }
          break;

          case '-':{
            if (new_main_y_l-main_size <= zero) {
              b_issue = false;
            }

            for (int x = main_x-main_size; x <= main_x+main_size; x++) {
              if (new_main_y_l > zero) {
                if (grid[x][new_main_y_l] != '\0' && (main_x != all_grid_index[x][new_main_y_l].index_x || main_y != all_grid_index[x][new_main_y_l].index_y)) {
                  c_issue = false;
                }
              }
            }

            if (b_issue && c_issue) {
              for (int y = main_y-main_size; y <= main_y+main_size; y++) {
                grid[main_x][y] = '\0';
                all_grid_index[main_x][y].index_x = zero;
                all_grid_index[main_x][y].index_y = zero;
                all_grid_index[main_x][y].size = zero;
              }

              for (int y = new_main_y_l-main_size; y <= new_main_y_l+main_size; y++) {
                grid[main_x][y] = '-';
                all_grid_index[main_x][y].index_x = main_x;
                all_grid_index[main_x][y].index_y = new_main_y_l;
                all_grid_index[main_x][y].size = main_size;
              }
              success_message_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!(b_issue || c_issue)){
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!b_issue) {
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!c_issue){
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }

          }
          break;

          case 'x':{
            if (min_col <= zero) {
              b_issue = false;
            }

            int x = main_x - main_size;
            for (int y = min_col; y <= new_main_y_l+main_size; y++) {
              if(x > zero && y > zero){
                if (grid[x][y] != '\0' && (main_x != all_grid_index[x][y].index_x || main_y != all_grid_index[x][y].index_y)) {
                  c_issue = false;
                }
              }
              x++;
            }
            int y = main_y + main_size;
            for (int x = min_row; x <= main_x+main_size; x++) {
              if(x > zero && y > zero){
                if (grid[x][y] != '\0' && (main_x != all_grid_index[x][y].index_x || main_y != all_grid_index[x][y].index_y)) {
                  c_issue = false;
                }
              }
              y--;
            }

            if (b_issue && c_issue) {

              int y = main_y-main_size;
              for (int x = main_x-main_size; x <= main_x+main_size; x++) {
                grid[x][y] = '\0';
                all_grid_index[x][y].index_y = zero;
                all_grid_index[x][y].index_x = zero;
                all_grid_index[x][y].size = zero;
                y++;
              }
              int x = main_x+main_size;
              for (int y = main_y-main_size; y <= main_y+main_size; y++) {
                grid[x][y] = '\0';
                all_grid_index[x][y].index_y = zero;
                all_grid_index[x][y].index_x = zero;
                all_grid_index[x][y].size = zero;
                x--;
              }

              x = main_x-main_size;
              for (int y = new_main_y_l-main_size; y <= new_main_y_l+main_size; y++) {
                grid[x][y] = 'x';
                all_grid_index[x][y].index_y = new_main_y_l;
                all_grid_index[x][y].index_x = main_x;
                all_grid_index[x][y].size = main_size;
                x++;
              }
              y = new_main_y_l+main_size;
              for (int x = main_x-main_size; x <= main_x+main_size; x++) {
                grid[x][y] = 'x';
                all_grid_index[x][y].index_y = new_main_y_l;
                all_grid_index[x][y].index_x = main_x;
                all_grid_index[x][y].size = main_size;
                y--;
              }

              success_message_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!(b_issue || c_issue)){
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!b_issue) {
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!c_issue) {
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }
          }
          break;

          case '/':{
            if (min_col <= zero) {
              b_issue = false;
            }

            int y = new_main_y_l+main_size;
            for (int x = main_x-main_size; x <= main_x+main_size; x++) {
              if (x > zero && y > zero) {
                if (grid[x][y] != '\0' && (main_x != all_grid_index[x][y].index_x || main_y != all_grid_index[x][y].index_y)) {
                  c_issue = false;
                }
              }
              y--;
            }

            if (b_issue && c_issue) {
              int y = main_y+main_size;
              for (int x = main_x-main_size; x <= main_x+main_size; x++) {
                grid[x][y] = '\0';
                all_grid_index[x][y].index_y = zero;
                all_grid_index[x][y].index_x = zero;
                all_grid_index[x][y].size = zero;
                y--;
              }

              y = new_main_y_l+main_size;
              for (int x = main_x-main_size; x <= main_x+main_size; x++) {
                grid[x][y] = '/';
                all_grid_index[x][y].index_y = new_main_y_l;
                all_grid_index[x][y].index_x = main_x;
                all_grid_index[x][y].size = main_size;
                y--;
              }
              success_message_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!(b_issue || c_issue)){
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!b_issue) {
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!c_issue) {
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }

          }
          break;

        }
      }
      break;

      case 'R':{
        switch (type_of_point) {
          case '+':{
            if (max_col > grid_column) {
              b_issue = false;
            }

            for (int y = new_main_y_r-main_size; y <= new_main_y_r+main_size; y++) {
              if (y > zero) {
                if ((grid[main_x][y] != '\0') && (main_x != all_grid_index[main_x][y].index_x || main_y != all_grid_index[main_x][y].index_y)) {
                  c_issue = false;
                }
              }
            }
            for (int x = main_x-main_size; x <= main_x+main_size; x++) {
              if (x > zero) {
                if ((grid[x][new_main_y_r] != '\0') && (main_x != all_grid_index[x][new_main_y_r].index_x || main_y != all_grid_index[x][new_main_y_r].index_y)) {
                  c_issue = false;
                }
              }
            }

            if (b_issue && c_issue) {
              for (int y = main_y-main_size; y <= main_y+main_size; y++) {
                grid[main_x][y] = '\0';
                all_grid_index[main_x][y].index_x = zero;
                all_grid_index[main_x][y].index_y = zero;
                all_grid_index[main_x][y].size = zero;
              }
              for (int x = main_x-main_size; x <= main_x+main_size; x++) {
                grid[x][main_y] = '\0';
                all_grid_index[x][main_y].index_x = zero;
                all_grid_index[x][main_y].index_y = zero;
                all_grid_index[x][main_y].size = zero;
              }
              for (int y = new_main_y_r-main_size; y <= new_main_y_r+main_size; y++) {
                grid[main_x][y] = '+';
                all_grid_index[main_x][y].index_x = main_x;
                all_grid_index[main_x][y].index_y = new_main_y_r;
                all_grid_index[main_x][y].size = main_size;
              }
              for (int x = main_x-main_size; x <= main_x+main_size; x++) {
                grid[x][new_main_y_r] = '+';
                all_grid_index[x][new_main_y_r].index_x = main_x;
                all_grid_index[x][new_main_y_r].index_y = new_main_y_r;
                all_grid_index[x][new_main_y_r].size = main_size;
              }

              success_message_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!(b_issue || c_issue)){
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!b_issue) {
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!c_issue) {
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }

          }
          break;

          case '-':{
            if (new_main_y_r+main_size > grid_column) {
              b_issue = false;
            }

            for (int y = new_main_y_r-main_size; y <= new_main_y_r-main_size; y++) {
              if (y > zero) {
                if (grid[main_x][y] != '\0' && (main_x != all_grid_index[main_x][y].index_x || main_y != all_grid_index[main_x][y].index_y)) {
                  c_issue = false;
                }
              }
            }

            if (b_issue && c_issue) {
              for (int y = main_y-main_size; y <= main_y+main_size; y++) {
                grid[main_x][y] = '\0';
                all_grid_index[main_x][y].index_x = zero;
                all_grid_index[main_x][y].index_y = zero;
                all_grid_index[main_x][y].size = zero;
              }

              for (int y = new_main_y_r-main_size; y <= new_main_y_r+main_size; y++) {
                grid[main_x][y] = '-';
                all_grid_index[main_x][y].index_x = main_x;
                all_grid_index[main_x][y].index_y = new_main_y_r;
                all_grid_index[main_x][y].size = main_size;
              }
              success_message_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!(b_issue || c_issue)){
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!b_issue) {
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!c_issue){
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }

          }
          break;

          case 'x':{
            if (max_col > grid_column) {
              b_issue = false;
            }

            int x = main_x - main_size;
            for (int y = new_main_y_r-main_size; y <= new_main_y_r+main_size; y++) {
              if(x > zero && y > zero){
                if (grid[x][y] != '\0' && (main_x != all_grid_index[x][y].index_x || main_y != all_grid_index[x][y].index_y)) {
                  c_issue = false;
                }
              }
              x++;
            }
            int y = new_main_y_r + main_size;
            for (int x = main_x-main_size; x <= main_x+main_size; x++) {
              if(x > zero && y > zero){
                if (grid[x][y] != '\0' && (main_x != all_grid_index[x][y].index_x || main_y != all_grid_index[x][y].index_y)) {
                  c_issue = false;
                }
              }
              y--;
            }

            if (b_issue && c_issue) {

              int y = main_y-main_size;
              for (int x = main_x-main_size; x <= main_x+main_size; x++) {
                grid[x][y] = '\0';
                all_grid_index[x][y].index_y = zero;
                all_grid_index[x][y].index_x = zero;
                all_grid_index[x][y].size = zero;
                y++;
              }
              int x = main_x+main_size;
              for (int y = main_y-main_size; y <= main_y+main_size; y++) {
                grid[x][y] = '\0';
                all_grid_index[x][y].index_y = zero;
                all_grid_index[x][y].index_x = zero;
                all_grid_index[x][y].size = zero;
                x--;
              }

              x = main_x-main_size;
              for (int y = new_main_y_r-main_size; y <= new_main_y_r+main_size; y++) {
                grid[x][y] = 'x';
                all_grid_index[x][y].index_y = new_main_y_r;
                all_grid_index[x][y].index_x = main_x;
                all_grid_index[x][y].size = main_size;
                x++;
              }
              y = new_main_y_r+main_size;
              for (int x = main_x-main_size; x <= main_x+main_size; x++) {
                grid[x][y] = 'x';
                all_grid_index[x][y].index_y = new_main_y_r;
                all_grid_index[x][y].index_x = main_x;
                all_grid_index[x][y].size = main_size;
                y--;
              }

              success_message_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!(b_issue || c_issue)){
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!b_issue) {
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!c_issue) {
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }
          }
          break;

          case '/':{
            if (max_col > grid_column) {
              b_issue = false;
            }

            int y = new_main_y_r+main_size;
            for (int x = main_x-main_size; x <= main_x+main_size; x++) {
              if (x > zero && y > zero) {
                if (grid[x][y] != '\0' && (main_x != all_grid_index[x][y].index_x || main_y != all_grid_index[x][y].index_y)) {
                  c_issue = false;
                }
              }
              y--;
            }

            if (b_issue && c_issue) {
              int y = main_y+main_size;
              for (int x = main_x-main_size; x <= main_x+main_size; x++) {
                grid[x][y] = '\0';
                all_grid_index[x][y].index_y = zero;
                all_grid_index[x][y].index_x = zero;
                all_grid_index[x][y].size = zero;
                y--;
              }

              y = new_main_y_r+main_size;
              for (int x = main_x-main_size; x <= main_x+main_size; x++) {
                grid[x][y] = '/';
                all_grid_index[x][y].index_y = new_main_y_r;
                all_grid_index[x][y].index_x = main_x;
                all_grid_index[x][y].size = main_size;
                y--;
              }
              success_message_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!(b_issue || c_issue)){
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!b_issue) {
              border_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }else if (!c_issue) {
              conflict_error_s(instArr[i].size,main_x,main_y,i,type_of_point,last_key);
            }

          }
          break;
        }
      }
      break;
    }
  }
  // //prints instructions
  // for (int i = INITIAL_VALUE; i < instN; i++) {
  //   printf("%s (%d,%d) %d\n", instArr[i].type, instArr[i].row, instArr[i].column, instArr[i].size);
  // }
  //
  // //Draws grid
  // for (int i = INITIAL_VALUE; i <= grid_row; i++) {
  //   for (int j = INITIAL_VALUE; j <= grid_column; j++) {
  //     if (j == grid_column) {
  //       printf(" [%c] %d,%d (%d,%d(%d))\n", grid[i][j] ,i ,j,all_grid_index[i][j].index_x,all_grid_index[i][j].index_y,all_grid_index[i][j].size);
  //     }else{
  //       printf(" [%c] %d,%d (%d,%d(%d))", grid[i][j] ,i ,j,all_grid_index[i][j].index_x,all_grid_index[i][j].index_y,all_grid_index[i][j].size);
  //     }
  //   }
  // }

  return EXIT_SUCCESS;
}
//grid messages
void grid_success(int x, int y) {
  printf("A grid is created: %d %d\n", x, y);
}
void conflict_error_g(struct grid_s gridArr[MAX_LINE], int n) {
  printf("CONFLICT ERROR: Operator %c with size %d can not be placed on (%d,%d)\n", gridArr[n].type ,gridArr[n].size, gridArr[n].row, gridArr[n].column);
}
void border_error_g(struct grid_s gridArr[MAX_LINE], int n) {
  printf("BORDER ERROR: Operator %c with size %d can not be placed on (%d,%d)\n", gridArr[n].type ,gridArr[n].size, gridArr[n].row, gridArr[n].column);
}
void success_message_g(struct grid_s gridArr[MAX_LINE], int n) {
  printf("SUCCESS: Operator %c with size %d is placed on (%d,%d)\n", gridArr[n].type ,gridArr[n].size, gridArr[n].row, gridArr[n].column);
}

//inst messages
void success_message_s(int size,int x,int y, int n, char type, char key) {
  switch (key) {
    case 'U':{
      printf("SUCCESS: %c moved from (%d,%d) to (%d,%d)\n", type, x, y, x-size, y);
    }
    break;
    case 'D':{
      printf("SUCCESS: %c moved from (%d,%d) to (%d,%d)\n", type, x, y, x+size, y);
    }
    break;
    case 'L':{
      printf("SUCCESS: %c moved from (%d,%d) to (%d,%d)\n", type, x, y, x, y-size);
    }
    break;
    case 'R':{
      printf("SUCCESS: %c moved from (%d,%d) to (%d,%d)\n", type, x, y, x, y+size);
    }
    break;
  }
}
void conflict_error_s(int size,int x,int y, int n, char type, char key) {
  switch (key) {
    case 'U':{
      printf("CONFLICT ERROR: %c can not be moved from (%d,%d) to (%d,%d)\n", type, x, y, x-size, y);
    }
    break;
    case 'D':{
      printf("CONFLICT ERROR: %c can not be moved from (%d,%d) to (%d,%d)\n", type, x, y, x+size, y);
    }
    break;
    case 'L':{
      printf("CONFLICT ERROR: %c can not be moved from (%d,%d) to (%d,%d)\n", type, x, y, x, y-size);
    }
    break;
    case 'R':{
      printf("CONFLICT ERROR: %c can not be moved from (%d,%d) to (%d,%d)\n", type, x, y, x, y+size);
    }
    break;
  }
}
void border_error_s(int size,int x,int y, int n, char type, char key) {
  switch (key) {
    case 'U':{
      printf("BORDER ERROR: %c can not be moved from (%d,%d) to (%d,%d)\n", type, x, y, x-size, y);
    }
    break;
    case 'D':{
      printf("BORDER ERROR: %c can not be moved from (%d,%d) to (%d,%d)\n", type, x, y, x+size, y);
    }
    break;
    case 'L':{
      printf("BORDER ERROR: %c can not be moved from (%d,%d) to (%d,%d)\n", type, x, y, x, y-size);
    }
    break;
    case 'R':{
      printf("BORDER ERROR: %c can not be moved from (%d,%d) to (%d,%d)\n", type, x, y, x, y+size);
    }
    break;
  }
}
