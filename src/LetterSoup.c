/*
 ============================================================================
 Name        : LetterSoup.c
 Author      : César Vargas
 Version     :
 Copyright   : Your copyright notice
 Description : Letter Soup in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ReadWords();
void WriteMatrix();
void Vertical	(int WordNumber, int WordSize, int MatrixPositionX, int MatrixPositionY, int WordDirection);
void Horizontal	(int WordNumber, int WordSize, int MatrixPositionX, int MatrixPositionY, int WordDirection);
void Diagonal	(int WordNumber, int WordSize, int MatrixPositionX, int MatrixPositionY, int WordDirection);
void (*p[3])	(int WordNumber, int WordSize, int MatrixPositionX, int MatrixPositionY, int WordDirection) = {Vertical, Horizontal, Diagonal};
void FillMatrix();

char Words[5][10] = {"          ","          ","          ","          ","          "};
char Matrix[10][10] = {"          ","          ","          ","          ","          ","          ","          ","          ","          ","          "};

int main(void)
{
	ReadWords();
	FillMatrix();
	WriteMatrix();

	return EXIT_SUCCESS;
}
void ReadWords()
{
	FILE *fp;
	char ch;
	int x = 0;
	int y = 0;

	fp = fopen("Words.txt","r");

	// Verify if file opened correctly
	if( fp == NULL )
	{
		perror("Error while opening the file Words.txt.\n");
	    exit(EXIT_FAILURE);
	}

	// Keeps the cycle until the file is finished or five words are completed
	while( ( ch = fgetc(fp) ) != EOF && x < 5 )
	{
		Words[x][y] = ch;
	    printf("%c",ch);
		y++;

	    // When a word is stored in Words array or 10 letters has been stored in the current word, it continues with next word
	    if(ch == '\n' || y == 10)
	    {
	    	x++;
	    	y = 0;
	    }
	}

	fclose(fp);
}
void WriteMatrix()
{
	FILE *fp;

	fp = fopen("Matrix.txt","w");

	// Verify if file opened correctly
	if( fp == NULL )
	{
		perror("Error while opening the file Matriz.txt.\n");
	    exit(EXIT_FAILURE);
	}

	for(int y=0; y<10; y++)
	{
		fprintf(fp, "\n\t");

		for(int x=0; x<10; x++)
		{
			if(Matrix[x][y] == ' ')	fprintf(fp, "- ");
			else			fprintf(fp, "%c ", Matrix[x][y]);
		}
	}

	fclose(fp);
}
void Vertical	(int WordNumber, int WordSize, int MatrixPositionX, int MatrixPositionY, int WordDirection)
{
	printf("Vertical\t WordNumber: %d\t WordSize: %d\t X: %d\t Y: %d\t Direction: %d\t\n", WordNumber, WordSize, MatrixPositionX, MatrixPositionY, WordDirection);

	for(int z=0 ; z<WordSize ; z++)
	{
		Matrix[MatrixPositionX][MatrixPositionY] = Words[WordNumber][z];

		if(WordDirection == 1)	MatrixPositionY++;
		else					MatrixPositionY--;
	}
}
void Horizontal	(int WordNumber, int WordSize, int MatrixPositionX, int MatrixPositionY, int WordDirection)
{
	printf("Horizontal\t WordNumber: %d\t WordSize: %d\t X: %d\t Y: %d\t Direction: %d\t\n", WordNumber, WordSize, MatrixPositionX, MatrixPositionY, WordDirection);

	for(int z=0 ; z<WordSize ; z++)
	{
		Matrix[MatrixPositionX][MatrixPositionY] = Words[WordNumber][z];

		if(WordDirection == 1)	MatrixPositionX++;
		else					MatrixPositionX--;
	}
}
void Diagonal	(int WordNumber, int WordSize, int MatrixPositionX, int MatrixPositionY, int WordDirection)
{
	printf("Diagonal\t WordNumber: %d\t WordSize: %d\t X: %d\t Y: %d\t Direction: %d\t\n", WordNumber, WordSize, MatrixPositionX, MatrixPositionY, WordDirection);

	for(int z=0 ; z<WordSize ; z++)
	{
		Matrix[MatrixPositionX][MatrixPositionY] = Words[WordNumber][z];

		if		(WordDirection == 2)
		{
			MatrixPositionX++;
			MatrixPositionY++;
		}
		else if	(WordDirection == 1)
		{
			MatrixPositionX++;
			MatrixPositionY--;
		}
		else if	(WordDirection == -1)
		{
			MatrixPositionX--;
			MatrixPositionY++;
		}
		else if	(WordDirection == -2)
		{
			MatrixPositionX--;
			MatrixPositionY--;
		}
	}
}
void FillMatrix()
{
	int WordSize[5];

	/********************************
	*	Get the size of all words	*
	********************************/

	for(int x=0; x<5; x++)
	{
		for(int y=1; y<=10; y++)
		{
			if(Words[x][y] == '\n' || y == 10)
			{
				WordSize[x] = y;
				y = 11;
			}
		}
	}

	// initialize random seed
	srand(time(NULL));

	for(int x=0 ; x<5 ; x++)
	{
		// It uses to finished do...while when a word fit into the matrix
		int WordSuccessfullyAssigned = 0;

		do
		{
			// Select random position of word in matrix
			int MatrixPositionX = rand() % 10;
			int MatrixPositionY = rand() % 10;

			// Select random word orientation
			int WordOrientation = rand() %  3;
			int WordDirection 	= 0;

			// Spaces inside matrix that can be occupied
			int SpacesPX = abs(MatrixPositionX-10);
			int SpacesNX = MatrixPositionX+1;
			int SpacesPY = abs(MatrixPositionY-10);
			int SpacesNY = MatrixPositionY+1;

			// This flag is used to know when a word fit in the matrix
			int WordMatrizFit	= 1;

			/****************************************************************************
			*	if random position is empty then proceed to find the direction of word	*
			****************************************************************************/

			if(Matrix[MatrixPositionX][MatrixPositionY] == ' ')
			{
				if	   (WordOrientation == 0) 	// Vertical
				{
					if		(SpacesPY >= WordSize[x])	WordDirection =  1;
					else if	(SpacesNY >= WordSize[x])	WordDirection = -1;
				}
				else if(WordOrientation == 1)	// Horizontal
				{
					if		(SpacesPX >= WordSize[x])	WordDirection =  1;
					else if	(SpacesNX >= WordSize[x])	WordDirection = -1;
				}
				else if(WordOrientation == 2)	// Diagonal
				{
					if		((SpacesPY >= WordSize[x]) && (SpacesPX >= WordSize[x])) 	WordDirection =   2;
					else if	((SpacesNY >= WordSize[x]) && (SpacesPX >= WordSize[x])) 	WordDirection =   1;
					else if	((SpacesPY >= WordSize[x]) && (SpacesNX >= WordSize[x])) 	WordDirection =  -1;
					else if	((SpacesNY >= WordSize[x]) && (SpacesNX >= WordSize[x])) 	WordDirection =  -2;
				}
			}

			/************************************************************************************
			*	if found a word position and word direction that fits in matrix,				*
			*	verifies if spaces that will take are empty or can be shared with same letter	*
			************************************************************************************/

			if(WordDirection != 0)
			{
				int CopyMatrixPositionY = MatrixPositionY;
				int CopyMatrixPositionX = MatrixPositionX;

				for(int z=0 ; z<WordSize[x] ; z++)
				{
					if( Matrix[CopyMatrixPositionX][CopyMatrixPositionY] == ' ' ||
						Matrix[CopyMatrixPositionX][CopyMatrixPositionY] == Words[x][z])
					{
						if	   (WordOrientation == 0) 	// Vertical
						{
							if(WordDirection == 1)	CopyMatrixPositionY++;
							else					CopyMatrixPositionY--;
						}
						else if(WordOrientation == 1)	// Horizontal
						{
							if(WordDirection == 1)	CopyMatrixPositionX++;
							else					CopyMatrixPositionX--;
						}
						else if(WordOrientation == 2)	// Diagonal
						{
							if		(WordDirection == 2)
							{
								CopyMatrixPositionX++;
								CopyMatrixPositionY++;
							}
							else if	(WordDirection == 1)
							{
								CopyMatrixPositionX++;
								CopyMatrixPositionY--;
							}
							else if	(WordDirection == -1)
							{
								CopyMatrixPositionX--;
								CopyMatrixPositionY++;
							}
							else if	(WordDirection == -2)
							{
								CopyMatrixPositionX--;
								CopyMatrixPositionY--;
							}
						}
					}
					else
					{
						WordMatrizFit	= 0;
						z = WordSize[x]+1;
					}
				}

				if(WordMatrizFit)
				{
					(*p[WordOrientation])(x, WordSize[x], MatrixPositionX, MatrixPositionY, WordDirection);
					WordSuccessfullyAssigned = 1;
				}
			}
		}
		while(!WordSuccessfullyAssigned);
	}
}
