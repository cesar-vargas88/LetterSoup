/*
 ============================================================================
 Name        : LetterSoup.c
 Author      : César Vargas
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ReadWords();
void WriteMatrix();
void Vertical();
void Horizontal();
void Diagonal();
void (*p[3])() = {Vertical, Horizontal, Diagonal};
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
		y++;
	    printf("%c",ch);

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

	for(int x=0; x<10; x++)
	{
		fprintf(fp, "\n\t");

		for(int y=0; y<10; y++)
		{
			if(Matrix[x][y] == ' ')	fprintf(fp, "-\t");
			else			fprintf(fp, "%c\t", Matrix[x][y]);
		}
	}

	fclose(fp);
}
void Vertical()
{
	printf("Vertical\n");
}
void Horizontal()
{
	printf("Horizontal\n");
}
void Diagonal()
{
	printf("Diagonal\n");
}
void FillMatrix()
{
	int WordSize[5];

	// Get the size of all words
	for(int x=0; x<5; x++)
	{
		for(int y=0; y<10; y++)
		{
			if(Words[x][y] == '\n')
			{
				WordSize[x] = y;
				printf("%d ", y);
				y = 10;
			}
		}
	}

	// initialize random seed
	srand(time(NULL));

	// Select the position of word in matrix
	//int x = rand()%10;
	//int y = rand()%10;

	for(int x=0 ; x< 5 ; x++)
	{
		// Select the position of word in matrix
		(*p[rand()%3])();
	}
}
