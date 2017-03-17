#include "sudoku.h"
#include <assert.h>
#include <string.h>
// Gets the board from the User and validates it.
bool sudoku_read(FILE * in, SudokuBoard * board)
{
  int i, r;
  char buff[1024];
  for (r = 0; r < SNUMSETS; r++) 
  {
    int c = 0;
    fgets(buff, 1024, in);
    for (i = 0; i < strlen(buff); i++)
    {
	  int ch = buff[i];
	  if (ch >= '0' && ch <= '9')
        sudoku_set_cell(board, r, c++, ch - '0');
	  else if (ch == '_' || ch == '-')
	    sudoku_set_cell(board, r, c++, 0);
	}
    assert(c == 9);
  }
  return true;
}

void sudoku_print(FILE * out, SudokuBoard * board)
{
}

bool sudoku_solve(SudokuBoard *board)
{
  int r, c, n;
  SudokuBoard work;
  sudoku_copy(board, &work);
  for (r = 0; r < SNUMSETS; r++)
    for (c = 0; c < SNUMSETS; c++)
	  if (sudoku_get_cell(&work, r, c) == EMPTYCELL)
	    break;
  assert(r < SNUMSETS);
  assert(c < SNUMSETS);
  for (n = 1; n <= 9; n++)
  {
    sudoku_set_cell(&work, r, c, n);
    if (sudoku_is_invalid(&work))
	  continue;
	if (sudoku_solve(&work))
	{
	  sudoku_copy(&work, board);
	  return true;
	}
  }
  return false;
}

int main()
{
  SudokuBoard board;
  sudoku_read(stdin, &board);
  return 0;
}

 