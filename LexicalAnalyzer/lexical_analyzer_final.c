#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

bool matched = false;



int main()
{
	/* File pointer to hold reference to our file */
	FILE *FilePtr;

	char character;
	int number_characters = 0;
	int number_whitespace = 0;


	/*
	 * Open file in r (read) mode.
	 * "data/file1.txt" is complete file path to read
	 */
	FilePtr = fopen("input.txt", "r");

	/* fopen() return NULL if the file don't exist or the path is wrong */
	if (FilePtr == NULL)
	{
		/* Unable to open file hence exit */
		printf("Unable to open file.\n");
		printf("Please check whether file exists and you have read privilege.\n");
		system("pause");
		exit(EXIT_FAILURE);
	}

	/* File open success message */
	printf("File opened successfully. Reading file contents character by character. \n\n");

	/* loop that count the number of characters inside our file */
	while ((character = fgetc(FilePtr)) != EOF) {
		number_characters++;
	}
	printf("number of characters: %d\n", number_characters);

	rewind(FilePtr);
	/* loop that count the number of whitespaces to know how many words we may have */
	while ((character = fgetc(FilePtr)) != EOF) {
		if (character == '"')
		{
			character = fgetc(FilePtr);
			while (character != '"')
			{
				character = fgetc(FilePtr);
			}
		}
		if (character == ' ' || character == '\t' || character == '\n')
			number_whitespace++;
	}
	printf("number of whitespaces: %d\n", number_whitespace);

	int test = number_whitespace;
	/* we can create an array that will stock our lexemes since we know how */
	char array_lexemes[100][100];
	array_lexemes[number_whitespace][100];


	rewind(FilePtr); // go back at the beginning of the file
	int row = 0;
	int col = 0;
	do
	{
		/* Read single character from file */
		character = fgetc(FilePtr);

		if (character == '"')
		{
			printf("%c", character);
			array_lexemes[row][col++] = character;
			character = fgetc(FilePtr);
			while (character != '"')
			{
				printf("%c", character);
				array_lexemes[row][col] = character;
				col++;
				character = fgetc(FilePtr);
			}
			array_lexemes[row][col++] = character;
		}

		if (character == ' ' || character == '\t' || character == '\n' || character == EOF)
		{
			array_lexemes[row][col] = '\0';
			row++;
			col = 0;
		}
		else
		{
			array_lexemes[row][col] = character;
			col++;
		}

		/* Print character read on console */
		printf("%c", character);

	} while (character != EOF); /* Repeat this if last read character is not EOF */


	/* Done with this file, close file to release resource */
	fclose(FilePtr);

	FilePtr = fopen("output.txt", "a+");
	fprintf(FilePtr, "**********Start of the analyze**********\n\n");
	fclose(FilePtr);

	int loop_analyzor = 0;
	while (loop_analyzor <= number_whitespace)
	{
		compare_lexeme(array_lexemes[loop_analyzor]);
		printf("%s\n", array_lexemes[loop_analyzor]);
		loop_analyzor++;
	}

	FilePtr = fopen("output.txt", "a+");
	fprintf(FilePtr, "\n\n**********End of the analyze**********\n\n");
	fclose(FilePtr);

	system("pause");
	return 0;
}


int compare_lexeme(char lexeme[]) {
	//this function compares the given lexeme to every token defined by calling the functions in the given order
	//if no token matches, error is printed and 1 is returned.
	//if matched, the following checks are skipped


	compare_string(lexeme);



	if (matched == false)
		compare_keyword(lexeme);

	if (matched == false)
		compare_variable_type(lexeme);

	if (matched == false)
		compare_whitespace(lexeme);

	if (matched == false)
		compare_arithmetic_operators(lexeme);

	if (matched == false)
		compare_assignment_operator(lexeme);

	if (matched == false)
		compare_comparison_operators(lexeme);

	if (matched == false)
		compare_lbrace(lexeme);

	if (matched == false)
		compare_rbrace(lexeme);

	if (matched == false)
		compare_lparent(lexeme);

	if (matched == false)
		compare_rparent(lexeme);

	if (matched == false)
		compare_terminator(lexeme);

	if (matched == false)
		compare_separator(lexeme);

	if (matched == false)
		compare_integer(lexeme);

	if (matched == false)
		compare_id(lexeme);

	if (matched == false)
	{
		printf("%s is not a viable token", lexeme);
		FILE * fp;
		int i;
		fp = fopen("output.txt", "a+");
		if (fp == NULL)
		{
			printf("Error opening file!\n");
		}
		fprintf(fp, "Error: Is not a viable token: %s\n", lexeme);
		fclose(fp);
		return 1;
	}

	matched = false;
}

int compare_id(char lexeme[])
{
	//comparing for id is done by comparing every single charakter of the given string with the given rule
	bool tmp = true;
	int length, i;
	length = strlen(lexeme);

	for (i = 0; i < length; i++)
	{

		if (isalpha(lexeme[0]) != 0)
			i = i + 1;
		else
		{
			tmp = false;
			break;
		}
		if (!isalpha(lexeme[i]))
		{
			if (!isdigit(lexeme[i]))
				if (!lexeme[i] == '\0')
					tmp = false;
			break;
		}
	}
	if (tmp == true)
	{
		//is the lexeme is an id, open the output file and append the table entry.  Same with every other compare function
		FILE * fp;
		int i;
		fp = fopen("output.txt", "a+");
		if (fp == NULL)
		{
			printf("Error opening file!\n");
		}
		fprintf(fp, "ID, %s\n", lexeme);
		fclose(fp);
		matched = true;
	}
}

int compare_integer(char lexeme[])
{
	//comparing for int is done by comparing every single charakter of the given string with the given rule
	bool tmp = true;
	int length, i;
	length = strlen(lexeme);
	for (i = 0; i < length; i++)
	{
		if (lexeme[0] == "-")
			i = i + 1;
		if (!isdigit(lexeme[i]))
		{
			tmp = false;
			break;
		}
	}
	if (tmp == true)
	{
		FILE * fp;
		int i;
		fp = fopen("output.txt", "a+");
		if (fp == NULL)
		{
			printf("Error opening file!\n");
		}
		fprintf(fp, "INT, %s\n", lexeme);
		fclose(fp);
		matched = true;
		matched = true;
	}
}

int compare_keyword(char a[])
{
	//comparing for keyword is done by comparing the complete string to the possible keywords. 
	//Same applicable to every other token where theres only a finite amount of possibilities

	char keyword[][7] = { "if","IF","else","ELSE","while","WHILE","return","RETURN" };
	for (int i = 0; i < 8; i++)
	{
		if (strcmp(a, keyword[i]) == 0)
		{
			FILE * fp;
			int i;
			fp = fopen("output.txt", "a+");
			if (fp == NULL)
			{
				printf("Error opening file!\n");
			}
			fprintf(fp, "KEYWORD, %s\n", a);
			fclose(fp);
			matched = true;
			break;
		}
	}

}

int compare_assignment_operator(char a[])
{

	char assignment_operator[][2] = { "=" };

	if (strcmp(a, assignment_operator[0]) == 0)
	{
		FILE * fp;
		int i;
		fp = fopen("output.txt", "a+");
		if (fp == NULL)
		{
			printf("Error opening file!\n");
		}
		fprintf(fp, "ASSIGNMENT_OPERATOR, %s\n", a);
		fclose(fp);
		matched = true;

	}
}

int compare_string(char a[])
{
	if (a[0] == '"')
	{
		FILE * fp;
		int i;
		fp = fopen("output.txt", "a+");
		if (fp == NULL)
		{
			printf("Error opening file!\n");
		}
		fprintf(fp, "STRING, %s\n", a);
		fclose(fp);
		matched = true;
	}
}

int compare_rparent(char a[])
{

	char rparent[][2] = { ")" };

	if (strcmp(a, rparent[0]) == 0)
	{
		FILE * fp;
		int i;
		fp = fopen("output.txt", "a+");
		if (fp == NULL)
		{
			printf("Error opening file!\n");
		}
		fprintf(fp, "RPARENT, %s\n", a);
		fclose(fp);
		matched = true;
	}
}

int compare_terminator(char a[])
{
	char terminator[][2] = { ";" };

	if (strcmp(a, terminator[0]) == 0)
	{
		FILE * fp;
		int i;
		fp = fopen("output.txt", "a+");
		if (fp == NULL)
		{
			printf("Error opening file!\n");
		}
		fprintf(fp, "TERMINATOR, %s\n", a);
		fclose(fp);
		matched = true;
	}
}

int compare_lparent(char a[])
{

	char lparent[][2] = { "(" };

	if (strcmp(a, lparent[0]) == 0)
	{
		FILE * fp;
		int i;
		fp = fopen("output.txt", "a+");
		if (fp == NULL)
		{
			printf("Error opening file!\n");
		}
		fprintf(fp, "LPARENT, %s\n", a);
		fclose(fp);
		matched = true;
	}
}

int compare_rbrace(char a[])
{

	char rbrace[][2] = { "}" };

	if (strcmp(a, rbrace[0]) == 0)
	{
		FILE * fp;
		int i;
		fp = fopen("output.txt", "a+");
		if (fp == NULL)
		{
			printf("Error opening file!\n");
		}
		fprintf(fp, "RBRACE, %s\n", a);
		fclose(fp);
		matched = true;
	}
}

int compare_lbrace(char a[])
{

	char lbrace[][2] = { "{" };

	if (strcmp(a, lbrace[0]) == 0)
	{
		FILE * fp;
		int i;
		fp = fopen("output.txt", "a+");
		if (fp == NULL)
		{
			printf("Error opening file!\n");
		}
		fprintf(fp, "LBRACE, %s\n", a);
		fclose(fp);
		matched = true;
	}
}

int compare_whitespace(char a[])
{

	char whitespace[][3] = { " ", "\t", "\n" };
	for (int i = 0; i < 3; i++)
	{
		if (strcmp(a, whitespace[i]) == 0)
		{
			FILE * fp;
			int i;
			fp = fopen("output.txt", "a+");
			if (fp == NULL)
			{
				printf("Error opening file!\n");
			}
			fprintf(fp, "WHITESPACE, %s\n", a);
			fclose(fp);
			matched = true;
			break;
		}
	}

}

int compare_variable_type(char a[])
{
	char variable_type[][10] = { "int","INT","char","CHAR" };
	for (int i = 0; i < 4; i++)
	{
		if (strcmp(a, variable_type[i]) == 0)
		{
			FILE * fp;
			int i;
			fp = fopen("output.txt", "a+");
			if (fp == NULL)
			{
				printf("Error opening file!\n");
			}
			fprintf(fp, "VARIABLE_TYPE, %s\n", a);
			fclose(fp);
			matched = true;
			matched = true;
			break;
		}
	}
}

int compare_comparison_operators(char a[])
{
	char comparison_operators[][3] = { "<", ">", "==", "!=", "<=", ">=" };
	for (int i = 0; i < 6; i++)
	{
		if (strcmp(a, comparison_operators[i]) == 0)
		{
			FILE * fp;
			int i;
			fp = fopen("output.txt", "a+");
			if (fp == NULL)
			{
				printf("Error opening file!\n");
			}
			fprintf(fp, "COPARISON_OPERATOR, %s\n", a);
			fclose(fp);
			matched = true;

			break;
		}
	}
}

int compare_arithmetic_operators(char a[])
{
	char arithmetic_operators[][2] = { "+", "-", "*", "/" };
	for (int i = 0; i < 4; i++)
	{
		if (strcmp(a, arithmetic_operators[i]) == 0)
		{
			FILE * fp;
			int i;
			fp = fopen("output.txt", "a+");
			if (fp == NULL)
			{
				printf("Error opening file!\n");
			}
			fprintf(fp, "ARITHMETIC_OPERATOR, %s\n", a);
			fclose(fp);

			matched = true;
			break;
		}
	}
}

int compare_separator(char a[])
{
	char separator[][2] = { "," };
	if (strcmp(a, separator[0]) == 0)
	{
		FILE * fp;
		int i;
		fp = fopen("output.txt", "a+");
		if (fp == NULL)
		{
			printf("Error opening file!\n");
		}
		fprintf(fp, "SEPARATOR, %s\n", a);
		fclose(fp);
		matched = true;
	}
}