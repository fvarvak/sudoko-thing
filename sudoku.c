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



bool sudoku_solve(SudokuBoard *board)
{
  int n;
  SudokuBoard work;
  Position p = sudoku_get_pos_with_cellvalue(board, EMPTYCELL);
  
  if (IsNullPos(p))
    return !sudoku_is_invalid(board);
  
  sudoku_copy(board, &work);

  for (n = 1; n <= 9; n++)
  {
    sudoku_set_cell(&work, p.row, p.col, n);
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

void sudoku_print(SudokuBoard *board)
{
  int r;
  for (r = 0; r < SNUMSETS; r++)
  { 
    char buf[20], *s;
	int c;
	for (s = buf, c = 0; c < SNUMSETS; s++, c++)
	{
	  if (c > 0 && !(c % 3))
	    *s++ = ' ';
	  *s = sudoku_get_cell(board, r, c) + '0';
	}
	*s = 0;
	assert(buf[0]);
	assert(strlen(buf) >= SNUMSETS);
	if (!(r % 3))
	  printf("\n");
	printf("%s\n", buf);
  }	
}

int main()
{
  SudokuBoard board;
  sudoku_read(stdin, &board);
  if (sudoku_solve(&board))
  {
    printf("A solution:\n");
    sudoku_print(&board);
  }
  else
    printf("No solutions found!\n");
  return 0;
}