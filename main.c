#include	<stdio.h>
#include	<stdint.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float  f32;
typedef double f64;

// variables
char move[4];
u64 one_64 = 1ULL;

// function initilaizations
// printing functions
void print_board(char *board_display);
void print_board_debug(char *board_display, u64 *pieces);
void print_indices();
void print_values(u64 *pieces);
void binary_printer_64(uint64_t x);

int move_from(char *move);
int move_to(char *move);
int get_piece_from(char *move, uint64_t pieces[]);
int get_piece_to(char *move, uint64_t pieces[]);



int main()
{
	// setting up the pieces
	uint64_t pieces[13];	
	pieces[0]  = 65280ULL;                   // white pawns
	pieces[1]  = 129ULL;                     // white rooks
	pieces[2]  = 66ULL;                      // white knights
	pieces[3]  = 36ULL;                      // white bishops
	pieces[4]  = 16ULL;                      // white queens
	pieces[5]  = 8ULL;                       // white kings              
	pieces[6]  = 71776119061217280ULL;       // black pawns
	pieces[7]  = 9295429630892703744ULL;     // black rooks
	pieces[8]  = 4755801206503243776ULL;     // black knights
	pieces[9]  = 2594073385365405696ULL;     // black bishops
	pieces[10] = 1152921504606846976ULL;     // black queens
	pieces[11] = 576460752303423488ULL;      // black kings
	pieces[12] = 281474976645120ULL;         // empty tiles

	// setting up the board
	char fen_string_pieces[100] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
	char fen_string[100] = "8/1P3p2/7K/3R4/pP6/6k1/p3r2R/6r1 w - - 0 1";
	char board_display[65];

	// writing to the board display string from the given fen string
	int j = 0;
	for (int i=0; i<sizeof(fen_string_pieces); i++)
	{
		// letters
		if    (  
			fen_string_pieces[i] == 'r' ||
			fen_string_pieces[i] == 'n' ||
			fen_string_pieces[i] == 'b' ||
			fen_string_pieces[i] == 'q' ||
			fen_string_pieces[i] == 'k' ||
			fen_string_pieces[i] == 'p' ||
			fen_string_pieces[i] == 'R' ||
			fen_string_pieces[i] == 'N' ||
			fen_string_pieces[i] == 'B' ||
			fen_string_pieces[i] == 'Q' ||
			fen_string_pieces[i] == 'K' ||
			fen_string_pieces[i] == 'P'
			)
		{
			board_display[j] = fen_string_pieces[i];
			j += 1;
		}

		// numbers
		if (fen_string_pieces[i] == '1')
		{
			for (int k=0; k<1; k++)
			{
				board_display[j] = ' ';
				j+=1;
			}
		}

		if (fen_string_pieces[i] == '2')
		{
			for (int k=0; k<2; k++)
			{
				board_display[j] = ' ';
				j+=1;
			}
		}

		if (fen_string_pieces[i] == '3')
		{
			for (int k=0; k<3; k++)
			{
				board_display[j] = ' ';
				j+=1;
			}
		}

		if (fen_string_pieces[i] == '4')
		{
			for (int k=0; k<4; k++)
			{
				board_display[j] = ' ';
				j+=1;
			}
		}

		if (fen_string_pieces[i] == '5')
		{
			for (int k=0; k<5; k++)
			{
				board_display[j] = ' ';
				j+=1;
			}
		}

		if (fen_string_pieces[i] == '6')
		{
			for (int k=0; k<6; k++)
			{
				board_display[j] = ' ';
				j+=1;
			}
		}

		if (fen_string_pieces[i] == '7')
		{
			for (int k=0; k<7; k++)
			{
				board_display[j] = ' ';
				j+=1;
			}
		}

		if (fen_string_pieces[i] == '8')
		{
			for (int k=0; k<8; k++)
			{
				board_display[j] = ' ';
				j+=1;
			}
		}
		
		// terminating character
		if (fen_string_pieces[i] == '\0')
		{
			break;
		}
	}

	//print_board(board_display);
	putchar('\n');
	print_board_debug(board_display, pieces);

	// Game Loop
	int your_turn = 0;

	while(your_turn < 1)
	{
		printf("Please enter a move: ");
		scanf(" %s", move);
		
		print_values(pieces);
		printf("piece index: %d\n", get_piece_from(move, pieces));
		printf("piece index: %d\n", get_piece_to(move, pieces));
		
		move[0] = 0;
		move[1] = 0;
		move[2] = 0;
		move[3] = 0;
		
		printf("New round! %d\n", your_turn);
		print_board_debug(board_display, pieces);

		your_turn += 1;

	}
	/*
	// inputting a move
	printf("Please enter a move: ");
	scanf(" %s", move);

	printf("piece index: %d\n", get_piece_from(move, pieces));
	printf("piece index: %d\n", get_piece_to(move, pieces));

	print_indices();
	print_values(pieces);
	print_board(board_display);

	move[0] = 0;
	move[1] = 0;
	move[2] = 0;
	move[3] = 0;

	*/

	printf("game loop has been stopped. stopping program!\n");

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

int get_piece_from(char *move, uint64_t pieces[])
{
	u64 piece_index;
	u64 from_index;

	from_index = one_64 << (move_from(move)-1);

	for (int i=0; i<13; i++)
	{
		

		if ((from_index & pieces[i]) == from_index)
		{
			piece_index = i;
		}
	}

	printf("from_index =\t");
	binary_printer_64(from_index);

	return piece_index;
}

int get_piece_to(char *move, uint64_t pieces[])
{
	u64 piece_index;
	u64 to_index;

	to_index = one_64 << (move_to(move)-1);

	for (int i=0; i<13; i++)
	{
		

		if ((to_index & pieces[i]) == to_index)
		{
			piece_index = i;
		}
	}

	printf("to_index =\t");
	binary_printer_64(to_index);

	return piece_index;
}

void print_board(char *board_display)
{
	// draw a board
	printf("+---+---+---+---+---+---+---+---+\n");
	for (int i=1; i<=64; i++)
	{
		printf("| %c ", board_display[i-1]);
		if (i%8 == 0)
		{
			putchar('|');
			putchar('\n');
			printf("+---+---+---+---+---+---+---+---+\n");
		}
	}
}


void print_board_debug(char *board_display, u64 *pieces)
{
	printf("+---+---+---+---+---+---+---+---+\tChess Program.\n");
	printf("| %c | %c | %c | %c | %c | %c | %c | %c |\n",
		board_display[0], board_display[1], board_display[2], board_display[3],
		board_display[4], board_display[5], board_display[6], board_display[7]);
	
	printf("+---+---+---+---+---+---+---+---+\t");
	
	binary_printer_64(pieces[0]);
	printf("\tWhite Pawns\n");


	printf("| %c | %c | %c | %c | %c | %c | %c | %c |\t",
		board_display[8], board_display[9], board_display[10], board_display[11],
		board_display[12], board_display[13], board_display[14], board_display[15]);
	
	binary_printer_64(pieces[1]);
	printf("\tWhite Rooks\n");
	
	printf("+---+---+---+---+---+---+---+---+\t");

	binary_printer_64(pieces[2]);
	printf("\tWhite Knights\n");

	printf("| %c | %c | %c | %c | %c | %c | %c | %c |\t",
		board_display[16], board_display[17], board_display[18], board_display[19],
		board_display[20], board_display[21], board_display[22], board_display[23]);

	binary_printer_64(pieces[3]);
	printf("\tWhite Bishops\n");

	printf("+---+---+---+---+---+---+---+---+\t");

	binary_printer_64(pieces[4]);
	printf("\tWhite Queens\n");

	printf("| %c | %c | %c | %c | %c | %c | %c | %c |\t",
		board_display[24], board_display[25], board_display[26], board_display[27],
		board_display[28], board_display[29], board_display[30], board_display[31]);

	binary_printer_64(pieces[5]);
	printf("\tWhite King\n");
	
	printf("+---+---+---+---+---+---+---+---+\t");

	printf("\n");

	printf("| %c | %c | %c | %c | %c | %c | %c | %c |\t",
		board_display[32], board_display[33], board_display[34], board_display[35],
		board_display[36], board_display[37], board_display[38], board_display[39]);

	binary_printer_64(pieces[6]);
	printf("\tBlack Pawns\n");

	printf("+---+---+---+---+---+---+---+---+\t");

	binary_printer_64(pieces[7]);
	printf("\tBlack Rooks\n");

	printf("| %c | %c | %c | %c | %c | %c | %c | %c |\t",
		board_display[40], board_display[41], board_display[42], board_display[43],
		board_display[44], board_display[45], board_display[46], board_display[47]);

	binary_printer_64(pieces[8]);
	printf("\tBlack Knights\n");
	
	printf("+---+---+---+---+---+---+---+---+\t");

	binary_printer_64(pieces[9]);
	printf("\tBlack Bishops\n");
	
	printf("| %c | %c | %c | %c | %c | %c | %c | %c |\t",
		board_display[48], board_display[49], board_display[50], board_display[51],
		board_display[52], board_display[53], board_display[54], board_display[55]);

	binary_printer_64(pieces[10]);
	printf("\tBlack Queens\n");
	
	printf("+---+---+---+---+---+---+---+---+\t");

	binary_printer_64(pieces[11]);
	printf("\tBlack King\n");
	
	printf("| %c | %c | %c | %c | %c | %c | %c | %c |\n",
		board_display[56], board_display[57], board_display[58], board_display[59],
		board_display[60], board_display[61], board_display[62], board_display[63]);


	printf("+---+---+---+---+---+---+---+---+\t");

	binary_printer_64(pieces[12]);
	printf("\tEmpty Tiles\n");
	
}

void print_indices()
{
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
}

void print_values(u64 *pieces)
{
	// printing the values of chess pieces (debug)
	for (int i=0; i<13; i++)
	{		
		printf("%d:\t", i);
		binary_printer_64(pieces[i]);
		putchar('\n');
	}
}
