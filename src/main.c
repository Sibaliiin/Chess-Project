#include	<stdio.h>
#include	<stdint.h>

// variables
char move[4];



// function initilaizations
void binary_printer_64(uint64_t x);
int move_from(char *move);
int move_to(char *move);



int main()
{
	// setting up the board	
	uint64_t pieces[13];	
	pieces[0] = 65280ULL;                   // white pawns
	pieces[1] = 129ULL;                     // white rooks
	pieces[2] = 66ULL;                      // white knights
	pieces[3] = 36ULL;                      // white bishops
	pieces[4] = 16ULL;                      // white queens
	pieces[5] = 8ULL;                       // white kings
                                            
	pieces[6] = 71776119061217280ULL;       // black pawns
	pieces[7] = 9295429630892703744ULL;     // black rooks
	pieces[8] = 4755801206503243776ULL;     // black knights
	pieces[9] = 2594073385365405696ULL;     // black bishops
	pieces[10] = 1152921504606846976ULL;    // black queens
	pieces[11] = 576460752303423488ULL;     // black kings

	pieces[12] = 281474976645120ULL;        // empty tiles


	printf("Chess program.\n");
	putchar('\n');
	printf(" --+---+---+---+---+---+---+---+---+\n");	
	printf(" 8 | r | n | b | q | k | b | n | r |\n");
	printf(" --+---+---+---+---+---+---+---+---+\n");
	printf(" 7 | p | p | p | p | p | p | p | p |\n");
	printf(" --+---+---+---+---+---+---+---+---+\n");
	printf(" 6 |   |   |   |   |   |   |   |   |\n");
	printf(" --+---+---+---+---+---+---+---+---+\n");
    printf(" 5 |   |   |   |   |   |   |   |   |\n");
	printf(" --+---+---+---+---+---+---+---+---+\n");
    printf(" 4 |   |   |   |   |   |   |   |   |\n");
	printf(" --+---+---+---+---+---+---+---+---+\n");
    printf(" 3 |   |   |   |   |   |   |   |   |\n");
	printf(" --+---+---+---+---+---+---+---+---+\n");
    printf(" 2 | P | P | P | P | P | P | P | P |\n");
	printf(" --+---+---+---+---+---+---+---+---+\n");
	printf(" 1 | R | N | B | Q | K | B | N | R |\n");
	printf(" --+---+---+---+---+---+---+---+---+\n");
	printf("   | a | b | c | d | e | f | g | h |\n\n");

	// print the indices of the tiles
	for (int i=64; i>0; i--)
	{
		if ((i%8) == 0)
		{
			putchar('\n');
		}
		printf("%d\t", i);

	}
	putchar('\n');
	putchar('\n');

	// printing the values of chess pieces (debug)
	for (int i=0; i<13; i++)
	{		
		printf("%d:\t", i);
		binary_printer_64(pieces[i]);
	}

	// inputting a move
	printf("Please enter a move: ");
	scanf(" %s", move);
	printf("\nDEBUG INFO: YOUR MOVE\n");
	printf("move[0] = %c, data = %d\n", move[0], move[0]);
	printf("move[1] = %c, data = %d\n", move[1], move[1]);
	printf("move[2] = %c, data = %d\n", move[2], move[2]);
	printf("move[3] = %c, data = %d\n", move[3], move[3]);

	printf("data = %d, file = %d\n", move[0], move[0]-96);
	printf("data = %d, row = %d\n", move[1], move[1]-48);
	printf("data = %d, file = %d\n", move[2], move[2]-96);
	printf("data = %d, row = %d\n", move[3], move[3]-48);

	printf("%d\n", move_from(move));
	printf("%d\n", move_to(move));
/*
	for (int i=40; i<120; i++)
	{
		printf("c = %c, d = %d\n", i, i);
	}
*/

	return 0;
}


// function declarations
void binary_printer_64(uint64_t x)
{
      for (int i = 63; i >= 0; i--)
      {
            uint64_t index = 1;
            index = index << i;

            if ((x & index) == index)
            {
                  putchar('1');
            }
            else
            {
                  putchar('0');
            }

            if (i%8 == 0)
            {
                  putchar(' ');
            }
      }

      putchar('\n');
}

int move_from(char *move)
{
	int col = move[0] - 96;
	int row = move[1] - 48;
	int pos = (9-col) + (8*(row-1));

	return pos;
}

int move_to(char *move)
{
	int col = move[2] - 96;
	int row = move[3] - 48;
	int pos = (9-col) + (8*(row-1));

	return pos;
}
