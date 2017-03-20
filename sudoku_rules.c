
#include "sudoku.h"
#include <assert.h>
#include <string.h>


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

void sudoku_get_box(SudokuBoard *board, int boxnum, SudokuSet *box)
{
  int i;
  assert(board && box && boxnum >=0 && boxnum < SNUMSETS);
  for (i = 0; i < SNUMSETS; i++)
  {
    int startrow = (boxnum / 3) * 3;
	int startcol = (boxnum % 3) * 3;
	int row = startrow + i / 3;
	int col = startcol + i % 3;
    box->cells[i] = board->cells[row * SSETSIZE + col];
  }
}

static bool has_duplicates(SudokuSet *set)
{
  int i;
  bool chk[SSETSIZE];  /*  = { false, false, false, false, false, false, false, false, false }; */
  memset(chk, 0, sizeof(chk));
  for (i = 0; i < SSETSIZE; i++)
  {
    int n = set->cells[i];
	if (n == EMPTYCELL) 
	  continue;
	assert(n > 0 && n <= SSETSIZE);
	if (chk[n-1])
	  return true;
	chk[n-1] = true;
  }
  return false;
}

bool sudoku_is_invalid(SudokuBoard *board)
{
  int i;
  SudokuSet set;
  for(i = 0; i < SNUMSETS; i++)
  {
    sudoku_get_row(board, i, &set);
    if (has_duplicates(&set))
	  return true;
	sudoku_get_col(board, i, &set);
    if (has_duplicates(&set))
	  return true;
	sudoku_get_box(board, i, &set);
    if (has_duplicates(&set))
	  return true;
  }
  return false;
}


bool sudoku_set_cell(SudokuBoard *board, int rownum, int colnum, SudokuCell digit)
{
  
  assert(digit >= 0 && digit <= 9 );
  board->cells[rownum*9 + colnum] = digit;
  return true;
} 

SudokuCell sudoku_get_cell(SudokuBoard *board, int rownum, int colnum)
{
 assert(rownum >= 0 && rownum <= SSETSIZE);
 assert(colnum >= 0 && colnum <= SSETSIZE);
 return board->cells[rownum*9 + colnum];
}

Position NullPos()
{
  return Pos(-1, -1);
}

bool IsNullPos(Position p)
{
  Position np = NullPos();
  return np.row == p.row && np.col == p.col;
}

Position Pos(int r, int c)
{
  Position p;
  p.row = r;
  p.col = c;
  return p;
}

Position sudoku_get_pos_with_cellvalue(SudokuBoard *board, SudokuCell cellvalue)
{
  int r, c;
  for (r = 0; r < SNUMSETS; r++)
    for (c = 0; c < SNUMSETS; c++)
	  if (sudoku_get_cell(board, r, c) == cellvalue)
	    return Pos(r, c);
  return NullPos();
}