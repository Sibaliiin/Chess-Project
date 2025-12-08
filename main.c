#include	<stdio.h>
#include	<stdint.h>


typedef struct {

	uint64_t whitePawns;
	uint64_t whiteRooks;
	uint64_t whiteKnights;
	uint64_t whiteBishops;
	uint64_t whiteQueens;
	uint64_t whiteKing;

	uint64_t blackPawns;
	uint64_t blackRooks;
	uint64_t blackKnights;
	uint64_t blackBishops;
	uint64_t blackQueens;
	uint64_t blackKing;

	uint64_t emptySquares;
} Bitmap;



void binary_printer_64(uint64_t x);
int  move_decode_s(char move[4]);
int  move_decode_e(char move[4]);



int main()
{
	// setting the struct
	Bitmap StartingPieces;

	StartingPieces.whitePawns = 65280ULL;
	StartingPieces.whiteRooks = 129ULL;
	StartingPieces.whiteKnights = 66ULL;
	StartingPieces.whiteBishops = 36ULL;
	StartingPieces.whiteQueens = 16ULL;
	StartingPieces.whiteKing = 8ULL;

	StartingPieces.blackPawns = 71776119061217280ULL;
	StartingPieces.blackRooks = 9295429630892703744ULL;
	StartingPieces.blackKnights = 4755801206503243776ULL;
	StartingPieces.blackBishops = 2594073385365405696ULL;
	StartingPieces.blackQueens = 1152921504606846976ULL;
	StartingPieces.blackKing = 576460752303423488ULL;

	StartingPieces.emptySquares = 281474976645120ULL;
	
	// copying the struct into an array, easier to work with
	uint64_t pieces[13];
	
	pieces[0] = StartingPieces.whitePawns;
	pieces[1] = StartingPieces.whiteRooks;
	pieces[2] = StartingPieces.whiteKnights;
	pieces[3] = StartingPieces.whiteBishops;
	pieces[4] = StartingPieces.whiteQueens;
	pieces[5] = StartingPieces.whiteKing;
	pieces[6] = StartingPieces.blackPawns;
	pieces[7] = StartingPieces.blackRooks;
	pieces[8] = StartingPieces.blackKnights;
	pieces[9] = StartingPieces.blackBishops;
	pieces[10] = StartingPieces.blackQueens;
	pieces[11] = StartingPieces.blackKing;
	pieces[12] = StartingPieces.emptySquares;

	char move[4];

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

	// printing the values of chess pieces (debug)
	for (int i=0; i<13; i++)
	{		
		printf("%d:\t", i);
		binary_printer_64(pieces[i]);
	}

	// inputting a move
	printf("Enter a move: ");
	scanf("%s", move);
	putchar('\n');
	printf("%s\n", move);

	printf("move_decode_s = %d\n", move_decode_s(move));
	printf("move_decode_e = %d\n", move_decode_e(move));
	
	uint64_t move_s = 1 << move_decode_s(move);
	uint64_t move_e = 1 << move_decode_e(move);


	binary_printer_64(move_s);

	for (int i=0; i<13; i++)
	{
		if ((move_s & pieces[i]) == move_s)		
		{
			printf("pieces[i] = %d\n", i);
		}
	}
	
	binary_printer_64(move_e);

	for (int i=0; i<13; i++)
	{
		if ((move_e & pieces[i]) == move_e)		
		{
			printf("pieces[i] = %d\n", i);
		}
	}


	return 0;
}



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

int move_decode_s(char move[4])
{
	int col = (int)move[0] - 97;
	int row = (int)move[1] - 49;
	
	return ((8-col) + (8*row))-1;
}

int move_decode_e(char move[4])
{
	int col = (int)move[2] - 97;
	int row = (int)move[3] - 49;
	
	return ((8-col) + (8*row))-1;
}
