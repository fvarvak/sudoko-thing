
#include "sudoku.h"
#include <assert.h>

void sudoku_copy(SudokuBoard *source, SudokuBoard *target)
{
  assert(source && target && source != target);
  memcpy(target, source, sizeof(SudokuBoard));
}

void sudoku_get_row(SudokuBoard *board, int rownum, SudokuSet *row)
{
  int i;
  assert(board && row && rownum >= 0 && rownum < SNUMSETS);
  for (i = 0; i < SNUMSETS; i++)
    row->cells[i] = board->cells[rownum*SSETSIZE+i];
}

void sudoku_get_col(SudokuBoard *board, int colnum, SudokuSet *col)
{
  int i;
  assert(board && col && colnum >= 0 && colnum < SNUMSETS);
  for (i = 0; i < SNUMSETS; i++)
    col->cells[i] = board->cells[i*SSETSIZE+colnum];
} 