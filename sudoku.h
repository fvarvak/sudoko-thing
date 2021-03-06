
#ifndef SUDOKU_H
#define SUDOKU_H
#include <stdio.h>
#include <stdbool.h>

#define SSETSIZE 9
#define SNUMSETS 9

#define EMPTYCELL 0

typedef int SudokuCell;

/* represents a row, column or box of sudoku board
   row: left to right
   column: top to bottom
   box: left to right, then top to bottom
*/
typedef struct {
  SudokuCell cells[SSETSIZE];
} SudokuSet;

typedef struct {
  SudokuCell cells[SSETSIZE*SNUMSETS];
} SudokuBoard;

/* position on sudoku board */
typedef struct {
  int row;
  int col;
} Position;
 
bool IsNullPos(Position p); 
Position Pos(int r, int c);
Position NullPos();

/* main check to validate the board */
bool sudoku_is_invalid(SudokuBoard *board);

 
/* returns true if number was set at the specified location on the board, false otherwise */
bool sudoku_set_cell(SudokuBoard *board, int rownum, int colnum, SudokuCell number);

/* copies source to target, source & target must not be null */
void sudoku_copy(SudokuBoard *source, SudokuBoard *target);

void sudoku_get_row(SudokuBoard *board, int rownum, SudokuSet *row);
void sudoku_get_col(SudokuBoard *board, int colnum, SudokuSet *col);
void sudoku_get_box(SudokuBoard *board, int boxnum, SudokuSet *box);
SudokuCell sudoku_get_cell(SudokuBoard *board, int rownum, int colnum);

Position sudoku_get_pos_with_cellvalue(SudokuBoard *board, SudokuCell cellvalue);

bool suduko_read(FILE * in, SudokuBoard * board);
void sudoku_print(SudokuBoard *board);

#endif  /* SUDOKU_H */