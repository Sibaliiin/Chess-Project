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
//
// printing functions
void print_board(char *board_display);
void print_board_debug(char *board_display, u64 *pieces);
void print_indices();
void print_values(u64 *pieces);
void binary_printer_64(u64 x);

// updating the board
void update_board(char *board_display, u64 *pieces, char *board_char);

// deciphering the player's move
//
// move --> tile index
int move_from_tile(char *move);
int move_to_tile(char *move);
// index --> bitboard
u64 move_tile_bitboard(int tile);
// find the piece index
int move_bitboard_index(u64 bitboard, u64 pieces[]);


int main()
{
	// setting up the pieces
	u64 pieces[15];	
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
						 
	pieces[13] = 0ULL;			 // move from
	pieces[14] = 0ULL;			 // move to

	// setting up the characters for the board
	char board_char[13];
	board_char[0] = 'P';
	board_char[1] = 'R';
	board_char[2] = 'N';
	board_char[3] = 'B';
	board_char[4] = 'Q';
	board_char[5] = 'K';
	board_char[6] = 'p';
	board_char[7] = 'r';
	board_char[8] = 'n';
	board_char[9] = 'b';
	board_char[10] = 'q';
	board_char[11] = 'k';
	board_char[12] = ' ';

	// setting up the board
	//char fen_string_pieces[100] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
	//char fen_string[100] = "8/1P3p2/7K/3R4/pP6/6k1/p3r2R/6r1 w - - 0 1";
	char board_display[65];

	// Game Loop
	int your_turn = 0;

	while(your_turn < 2)
	{

		// resetting the player's move (memory safety measure)
		move[0] = 0;
		move[1] = 0;
		move[2] = 0;
		move[3] = 0;

		pieces[13] = 0ULL;		
		pieces[14] = 0ULL;	
		
		// update and display the board based on the bitmap
		update_board(board_display, pieces, board_char);
		print_board_debug(board_display, pieces);

		// The player inputs a move
		printf("Please enter a move: ");
		scanf(" %s", move);
	
		// Figure out which pieces we are trying to move
		//
		// These two functions give us back the "index" of the correct bitboard from the bitmap. For example:
		// If "get_piece_from" returns "0", then we are manipulating the White Pawn's bitboard
		// If "get_piece_to" returns "12", then we want to put a piece onto one of the empty tiles, so we are manipulating the "Empty Tiles" bitboard.

		printf("Move (from) tile:\t%d\n", move_from_tile(move));
		printf("Move (to) tile:  \t%d\n", move_to_tile(move));
		
		pieces[13] = move_tile_bitboard(move_from_tile(move));
		pieces[14] = move_tile_bitboard(move_to_tile(move));

		binary_printer_64(pieces[13]);
		putchar('\n');
		binary_printer_64(pieces[14]);
		putchar('\n');

		printf("Move (from) piece: '%c'\n", board_char[move_bitboard_index(pieces[13], pieces)]);
		printf("Move (to) piece:   '%c'\n", board_char[move_bitboard_index(pieces[14], pieces)]);

		printf("\n+--------------\n");
		printf("| New round!\tyour_turn = %d\n", your_turn);
		printf("+--------------\n");
		

		your_turn += 1;
	}

	printf("game loop has been stopped. stopping program!\n");

	return 0;
}



// function declarations
void binary_printer_64(u64 x)
{
      for (int i = 63; i >= 0; i--)
      {
            u64 index = 1;
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

// move --> tile index
int move_from_tile(char *move)
{
	int col = move[0] - 96;
	int row = move[1] - 48;
	int tile = (9-col) + (8*(row-1));

	return tile;
}

int move_to_tile(char *move)
{
	int col = move[2] - 96;
	int row = move[3] - 48;
	int tile = (9-col) + (8*(row-1));

	return tile;
}

// tile --> bitboard
u64 move_tile_bitboard(int tile)
{
	return one_64 << (tile-1);
}

// find the piece index
int move_bitboard_index(u64 bitboard, u64 pieces[])
{
	int index = 0;

	for (int i=0; i<13; i++)
	{
		if ((bitboard & pieces[i]) == bitboard)
		{
			index = i;
		}
	}

	return index;
}


// print the board
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

void update_board(char *board_display, u64 *pieces, char *board_char)
{

	for (int j=0; j<13; j++)
	{
		for (int i=63; i>=0; i--)
		{
			uint64_t index = 1;
		
			index = index << i;
	    		if ((index & pieces[j]) == index)
			{
				board_display[63-i] = board_char[j];
			}
	
		}

	}
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
