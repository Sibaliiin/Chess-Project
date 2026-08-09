#include	<stdio.h>
#include	<stdlib.h>
#include	<stdint.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

#define	WHITE_PAWN	0
#define	WHITE_ROOK	1
#define	WHITE_BISHOP	2
#define	WHITE_KNIGHT	3
#define	WHITE_QUEEN	4
#define	WHITE_KING	5
#define	BLACK_PAWN	6
#define	BLACK_ROOK	7
#define	BLACK_BISHOP	8
#define	BLACK_KNIGHT	9
#define	BLACK_QUEEN	10
#define	BLACK_KING	11
#define	EMPTY_TILE	12

#define	RANK_1	0x00000000000000FFULL
#define	RANK_2	0x000000000000FF00ULL
#define	RANK_3	0x0000000000FF0000ULL
#define	RANK_4	0x00000000FF000000ULL
#define	RANK_5	0x000000FF00000000ULL
#define	RANK_6	0x0000FF0000000000ULL
#define	RANK_7	0x00FF000000000000ULL
#define	RANK_8	0xFF00000000000000ULL

#define FILE_A	0x8080808080808080ULL
#define FILE_B	0x4040404040404040ULL
#define FILE_C	0x2020202020202020ULL
#define FILE_D	0x1010101010101010ULL
#define FILE_E	0x0808080808080808ULL
#define FILE_F	0x0404040404040404ULL
#define FILE_G	0x0202020202020202ULL
#define FILE_H	0x0101010101010101ULL

// variables
char move[4];
int move_from = 0;
int move_to = 0;
u64 one_64 = 1ULL;
u8 legality_flags = 0;
u8 legality_mask = 15;

// function initilaizations
//
// printing functions
void print_board(char *board_display);
void print_board_debug(char *board_display, u64 *pieces);
void print_indices();
void print_values(u64 *pieces);
void binary_printer_64(u64 x);
void binary_printer_square(u64 x);

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
	
	// Movement Bitboards
	//
	// Knight
	u64 knight_move[65];
	knight_move[0] = 0ULL;
	knight_move[1] = 132096ULL;
	knight_move[2] = 329728ULL;
	knight_move[3] = 659712ULL;
	knight_move[4] = 1319424;
	knight_move[5] = 2638848;
	knight_move[6] = 5277696;
	knight_move[7] = 10489856;
	knight_move[8] = 4202496;
	knight_move[9] = 33816580;
	knight_move[10] = 84410376;
	knight_move[11] = 168886289;
	knight_move[12] = 337772578;
	knight_move[13] = 675545156;
	knight_move[14] = 1351090312;
	knight_move[15] = 2685403152;
	knight_move[16] = 1075839008;
	knight_move[17] = 8657044482;
	knight_move[18] = 21609056261;
	knight_move[19] = 21609056261;
	knight_move[20] = 86469779988;
	knight_move[21] = 172939559976;
	knight_move[22] = 345879119952;
	knight_move[23] = 687463207072;
	knight_move[24] = 275414786112;
	knight_move[25] = 2216203387392;
	knight_move[26] = 5531918402816;
	knight_move[27] = 11068131838464;
	knight_move[28] = 22136263676928;
	knight_move[29] = 44272527353856;
	knight_move[30] = 88545054707712;
	knight_move[31] = 175990581010432;
	knight_move[32] = 70506185244672;
	knight_move[33] = 567348067172352;
	knight_move[34] = 1416171111120896;
	knight_move[35] = 2833441750646784;
	knight_move[36] = 5666883501293568;
	knight_move[37] = 11333767002587136;
	knight_move[38] = 22667534005174272;
	knight_move[39] = 45053588738670592;
	knight_move[40] = 18049583422636032;
	knight_move[41] = 145241105196122112;
	knight_move[42] = 362539804446949376;
	knight_move[43] = 725361088165576704;
	knight_move[44] = 1450722176331153408;
	knight_move[45] = 2901444352662306816;
	knight_move[46] = 5802888705324613632;
	knight_move[47] = 11533718717099671552ULL;
	knight_move[48] = 4620693356194824192;
	knight_move[49] = 288234782788157440;
	knight_move[50] = 576469569871282176;
	knight_move[51] = 1224997833292120064;
	knight_move[52] = 2449995666584240128;
	knight_move[53] = 4899991333168480256;
	knight_move[54] = 9799982666336960512ULL;
	knight_move[55] = 1152939783987658752;
	knight_move[56] = 2305878468463689728;
	knight_move[57] = 1128098930098176;
	knight_move[58] = 2257297371824128;
	knight_move[59] = 4796069720358912;
	knight_move[60] = 9592139440717824;
	knight_move[61] = 19184278881435648;
	knight_move[62] = 38368557762871296;
	knight_move[63] = 4679521487814656;
	knight_move[64] = 9077567998918656;
	
	binary_printer_square(knight_move[0]); putchar('\n');  // so that the compiler won't scream at me... (unused var.)
	/*
	// knight attack test
	// starts on the 19th tile, so we have to shift accordingly
	u64 knight_attack = 43234889994ULL;
	u64 current = 0ULL;
	for (int i=1; i<=64; i++)
	{
		printf("%d\n", i);
		if (i < 19)
		{	
			current = knight_attack>>(19-i);
			
			if (move_tile_bitboard(i) == (move_tile_bitboard(i) & FILE_A))
			{
				current = current & ~(FILE_G | FILE_H);
			}
	
			if (move_tile_bitboard(i) == (move_tile_bitboard(i) & FILE_B))
			{
				current = current & ~(FILE_H);
			}

			if (move_tile_bitboard(i) == (move_tile_bitboard(i) & FILE_G))
			{
				current = current & ~(FILE_A);
			}

			if (move_tile_bitboard(i) == (move_tile_bitboard(i) & FILE_H))
			{
				current = current & ~(FILE_A | FILE_B);
			}

			printf("%lu\n", current);
		}

		if (i > 19)
		{
			current = knight_attack<<(i-19);
			
			if (move_tile_bitboard(i) == (move_tile_bitboard(i) & FILE_A))
			{
				current = current & ~(FILE_G | FILE_H);
			}
	
			if (move_tile_bitboard(i) == (move_tile_bitboard(i) & FILE_B))
			{
				current = current & ~(FILE_H);
			}

			if (move_tile_bitboard(i) == (move_tile_bitboard(i) & FILE_G))
			{
				current = current & ~(FILE_A);
			}

			if (move_tile_bitboard(i) == (move_tile_bitboard(i) & FILE_H))
			{
				current = current & ~(FILE_A | FILE_B);
			}

			printf("%lu\n", current);
		}

		if (i==19)
		{
			printf("%lu\n", current);
		}

		knight_attack = 43234889994ULL;
	}
	*/

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
	board_char[12] = '.';

	// setting up the board
	//char fen_string_pieces[100] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
	//char fen_string[100] = "8/1P3p2/7K/3R4/pP6/6k1/p3r2R/6r1 w - - 0 1";
	
	// Storing the position for graphics purposes
	char board_display[65];

	// Game Loop
	int your_turn = 0;

	while(your_turn == 0)
	{
		// resetting the player's move (memory safety measure)
		move[0] = 0;
		move[1] = 0;
		move[2] = 0;
		move[3] = 0;

		move_from = 0;
		move_to = 0;

		pieces[13] = 0ULL;		
		pieces[14] = 0ULL;	
		
		// update and display the board based on the bitmap
		update_board(board_display, pieces, board_char);
		print_board(board_display);

		// The player inputs a move
		printf("Please enter a move: ");
		scanf(" %s", move);
		putchar('\n');
	
		// exit the program if move[0] is 'q'
		if (move[0] =='q')
		{
			break;
		}
		
		//printf("Move (from) tile:\t%d\n", move_from_tile(move));
		//printf("Move (to) tile:  \t%d\n", move_to_tile(move));
		
		pieces[13] = move_tile_bitboard(move_from_tile(move));
		pieces[14] = move_tile_bitboard(move_to_tile(move));
		
		/*
		binary_printer_64(pieces[13]);
		putchar('\n');
		binary_printer_64(pieces[14]);
		putchar('\n');
		*/

		move_from = move_bitboard_index(pieces[13], pieces);
		move_to = move_bitboard_index(pieces[14], pieces);
		//printf("Move (from) piece: '%c'\n", board_char[move_from]);
		//printf("Move (to) piece:   '%c'\n", board_char[move_to]);

		// Making the move: manipulating the bitboards
		pieces[move_from] = pieces[move_from] | pieces[14];
		pieces[move_from] = pieces[move_from] ^ pieces[13];
		pieces[move_to] = pieces[move_to] ^ pieces[14];
		pieces[move_to] = pieces[move_to] | pieces[13];
	}

	printf("Closing program. Goodbye!\n");

	return EXIT_SUCCESS;
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

// binary printer square
void binary_printer_square(u64 x)
{
      for (int i = 63; i >= 0; i--)
      {
            u64 index = 1;
            index = index << i;

            if ((x & index) == index)
            {
                  printf("@ ");
            }
            else
            {
                  printf(". ");
            }

            if (i%8 == 0)
            {
                  putchar('\n');
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
	//	printf("i = %d\n",i);
	//	binary_printer_64(bitboard);
	//	putchar('\n');
	//	binary_printer_64(pieces[i]);
	//	putchar('\n');

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
	for (int i=0; i<8; i++)
	{
		printf("%d %c %c %c %c %c %c %c %c\n",
		8-i,
		board_display[8*i+0], board_display[8*i+1], board_display[8*i+2], board_display[8*i+3],
		board_display[8*i+4], board_display[8*i+5], board_display[8*i+6], board_display[8*i+7]);
	}
	printf("  a b c d e f g h\n");
}

void print_board_debug(char *board_display, u64 *pieces)
{
	printf("+---+---+---+---+---+---+---+--8+\tChess Program.\n");
	printf("| %c | %c | %c | %c | %c | %c | %c | %c |\n",
		board_display[0], board_display[1], board_display[2], board_display[3],
		board_display[4], board_display[5], board_display[6], board_display[7]);
	
	printf("+---+---+---+---+---+---+---+--7+\t");
	
	binary_printer_64(pieces[0]);
	printf("\tWhite Pawns\n");


	printf("| %c | %c | %c | %c | %c | %c | %c | %c |\t",
		board_display[8], board_display[9], board_display[10], board_display[11],
		board_display[12], board_display[13], board_display[14], board_display[15]);
	
	binary_printer_64(pieces[1]);
	printf("\tWhite Rooks\n");
	
	printf("+---+---+---+---+---+---+---+--6+\t");

	binary_printer_64(pieces[2]);
	printf("\tWhite Knights\n");

	printf("| %c | %c | %c | %c | %c | %c | %c | %c |\t",
		board_display[16], board_display[17], board_display[18], board_display[19],
		board_display[20], board_display[21], board_display[22], board_display[23]);

	binary_printer_64(pieces[3]);
	printf("\tWhite Bishops\n");

	printf("+---+---+---+---+---+---+---+--5+\t");

	binary_printer_64(pieces[4]);
	printf("\tWhite Queens\n");

	printf("| %c | %c | %c | %c | %c | %c | %c | %c |\t",
		board_display[24], board_display[25], board_display[26], board_display[27],
		board_display[28], board_display[29], board_display[30], board_display[31]);

	binary_printer_64(pieces[5]);
	printf("\tWhite King\n");
	
	printf("+---+---+---+---+---+---+---+--4+\t");

	printf("\n");

	printf("| %c | %c | %c | %c | %c | %c | %c | %c |\t",
		board_display[32], board_display[33], board_display[34], board_display[35],
		board_display[36], board_display[37], board_display[38], board_display[39]);

	binary_printer_64(pieces[6]);
	printf("\tBlack Pawns\n");

	printf("+---+---+---+---+---+---+---+--3+\t");

	binary_printer_64(pieces[7]);
	printf("\tBlack Rooks\n");

	printf("| %c | %c | %c | %c | %c | %c | %c | %c |\t",
		board_display[40], board_display[41], board_display[42], board_display[43],
		board_display[44], board_display[45], board_display[46], board_display[47]);

	binary_printer_64(pieces[8]);
	printf("\tBlack Knights\n");
	
	printf("+---+---+---+---+---+---+---+--2+\t");

	binary_printer_64(pieces[9]);
	printf("\tBlack Bishops\n");
	
	printf("| %c | %c | %c | %c | %c | %c | %c | %c |\t",
		board_display[48], board_display[49], board_display[50], board_display[51],
		board_display[52], board_display[53], board_display[54], board_display[55]);

	binary_printer_64(pieces[10]);
	printf("\tBlack Queens\n");
	
	printf("+---+---+---+---+---+---+---+--1+\t");

	binary_printer_64(pieces[11]);
	printf("\tBlack King\n");
	
	printf("| %c | %c | %c | %c | %c | %c | %c | %c |\n",
		board_display[56], board_display[57], board_display[58], board_display[59],
		board_display[60], board_display[61], board_display[62], board_display[63]);


	printf("+a--+b--+c--+d--+e--+f--+g--+h--+\t");

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
