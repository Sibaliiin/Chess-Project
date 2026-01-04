#include	<stdio.h>
#include	<stdint.h>

// variables
char move[4];

// function initilaizations
void binary_printer_64(uint64_t x);

int main()
{
	// setting up the board	
	uint64_t pieces[13];	
	pieces[0] = 65280ULL;
	pieces[1] = 129ULL;
	pieces[2] = 66ULL;
	pieces[3] = 36ULL;
	pieces[4] = 16ULL;
	pieces[5] = 8ULL;
	pieces[6] = 71776119061217280ULL;
	pieces[7] = 9295429630892703744ULL;
	pieces[8] = 4755801206503243776ULL;
	pieces[9] = 2594073385365405696ULL;
	pieces[10] = 1152921504606846976ULL;
	pieces[11] = 576460752303423488ULL;
	pieces[12] = 281474976645120ULL;


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
	//
	//
	//
	

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
