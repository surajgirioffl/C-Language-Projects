//{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include "D:\\C Language\\All C Programs\\1) Cxxdroid Application\\Header Files\\color.h"

void remove_space(char string[]); // remove_space from begining of string (remove space from 0th position of array)
void upper_case(char string[]);
void found_words_history(char string[]);
void notfound_words_history(char string[]);
void display_history();
void add_word_in_dictionary(); // to add word in Dictionary by super user

void enter_password(); // used in case of super user
int check_password();  // return 1 for correct and 0 for wrong
char password[30];	   // used in case of super user
void save_super_user_name(char name[]);
int check_word(char eng_word_user[]);		 // to check word written available in database or not. return 0 if word not found and return 1 if word found
void save_word(char word[], char meaning[]); // to save words written by super user.
int check_in_superuser_database(char word[]);
//}

//{
char eng_word_file[100];			 // from FILE
char hindi_word[500];				 // from FILE
unsigned long required_word_number;	 // from FILE
unsigned long word_number_for_check; // from file to check the correct word
//}

int main()
{
	printf("Hii Dear\U0001F64b\U0001F44b WELCOME TO \033[1;31m\"ENG-HINDI DICTIONARY\U000000A9\"\033[0m Dev:- Suraj Kumar Giri\n");
	system("pause");
	char eng_word_user[100];  // from user
	unsigned short count = 0; // to check availability of a word
	FILE *ptr;
	char again; // to repeat the whole program again

	do
	{
		system("cls");
		cyan('f');
		puts("write any english word to find it's hindi meaning:");
		while (1)
		{
			printf("$ ");
			gets(eng_word_user);
			if (strcmp(eng_word_user, "\0") == 0)
				continue;
			else
				break;
		}
		reset();

		upper_case(eng_word_user); // to convert into uppercase

		count = check_word(eng_word_user); // to check availability of word in original database

		if (count == 0) // count=0; means word not found in main database
		{
			// count==0 it means word not found in Dictionary original data base. so, now we check word in super user data
			int check = check_in_superuser_database(eng_word_user);
			if (check == 0)
			{
				red('f');
				printf("Sorry, No such word \"%s\" found in database", eng_word_user);
				reset();

				notfound_words_history(eng_word_user); // to save this searched word in history to access later

				goto again; // to restart the program
			}
			else
				found_words_history(eng_word_user); // to save this searched word in history to access later
		}

		else if (required_word_number < 91922)
		{
			ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\Dictionary\\hindi_word_1.csv", "r");
			if (ptr == NULL)
			{
				perror("Database is not reachable right now. Error code 102");
				exit(-1);
			}

			found_words_history(eng_word_user); // to save this searched word in history to access later

			while (feof(ptr) == 0)
			{
				fscanf(ptr, "%lu", &word_number_for_check);
				fgets(hindi_word, 500, ptr);
				if (word_number_for_check == required_word_number)
					break;
			}
			fclose(ptr);
		} // else-if close

		else if (required_word_number < 183119)
		{
			ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\Dictionary\\hindi_word_2.csv", "r");
			if (ptr == NULL)
			{
				red('f');
				perror("Database is not reachable right now. Error code 113");
				reset();
				exit(-1);
			}

			found_words_history(eng_word_user); // to save found words in history to access it later

			while (feof(ptr) == 0)
			{
				fscanf(ptr, "%lu", &word_number_for_check);
				fgets(hindi_word, 500, ptr);
				if (word_number_for_check == required_word_number)
					break;
			}
			fclose(ptr);
		} // 2nd else-if close

		// printing of Meaning part
		printf("\n\"Hindi Meaning\", [Antonym and more info], \"Sentence\" related to the word \"%s\" are following:\f", eng_word_user);
		magenta('h');
		printf("\n%-100s\n", hindi_word);
		reset();

		// last part for each iteration
	again:
		yellow('f');
		puts("\n\n==>> Press \'any key\' except below mentioned for search new word again.");
		puts("==>> Press \'f\' to display searched words history.");
		puts("==>> Press \'a\' Super User Section (Add Words to dictionary)");
		puts("==>> Press # for Exit.");
		puts("==>> Press Enter to continue search.");
		printf("$ ");
		scanf("%c", &again);
		fflush(stdin);
		reset();
		if (again == 'f')
			display_history();
		else if (again == 'a')
			add_word_in_dictionary();
	} while (again != '#');

	advcolor('f', 206);
	printf("\033[1;4m");
	printf("\nThanking You \U0001F607.\nThanks for using \033[1;31m\"Eng-Hindi Dictionary \U000000A9\"\033[0m");
	white('f');
	printf("\nDeveloped by Mr. Suraj Kumar Giri\nSee you soon. Bye Bye...");
	reset();
	return 0;
} // end of main()

// other functions
void upper_case(char string[])
{
	for (int i = 0; string[i] != '\0'; i++)
		string[i] = toupper(string[i]);
}

void remove_space(char string[])
{
	for (int i = 0; string[i] != '\0'; i++)
		string[i] = string[i + 1];
}

void found_words_history(char string[])
{
	FILE *ptr;
	ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\Dictionary\\found_words_history", "r+");
	if (ptr == NULL)
		perror("Unable to access database to save history. Error Code 156\n");
	int n = 0; // to get word number to save new word in history with proper indexing
	char text[100];
	while (feof(ptr) == 0)
	{
		fscanf(ptr, "%d", &n);
		fgets(text, 100, ptr); // it auto make pointer to new line
	}
	fprintf(ptr, "%d %s\n", ++n, string);
	fclose(ptr);
}

void notfound_words_history(char string[])
{
	FILE *ptr;
	ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\Dictionary\\notfound_words_history", "r+");
	if (ptr == NULL)
		perror("Unable to access database to save history. Error Code 123\n");
	int n = 0; // to get word number to save new word in history with proper indexing
	char text[100];
	while (feof(ptr) == 0)
	{
		fscanf(ptr, "%d", &n);
		fgets(text, 100, ptr); // it auto make pointer to new line
	}
	fprintf(ptr, "%d %s\n", ++n, string);
	fclose(ptr);
}

void display_history()
{
	int choice;
	puts("\n1. For History of \" Searched And Found Words\"");
	puts("2. For History of \" Searched And Not Found Words\"");
	scanf("%d", &choice);
	fflush(stdin);

	FILE *ptr;
	switch (choice)
	{
	case 1:
		ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\Dictionary\\found_words_history", "r");
		if (ptr == NULL)
			perror("Sorry, Unable to access database now. Error code 111");
		advcolor('f', 213);

		while (feof(ptr) == 0)
			printf("%c", fgetc(ptr));
		fclose(ptr);
		printf("\n");
		reset();
		break;

	case 2:
		ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\Dictionary\\notfound_words_history", "r");
		if (ptr == NULL)
			perror("Sorry, Unable to access database now. Error code 112");

		advcolor('f', 123);
		while (feof(ptr) == 0)
			printf("%c", fgetc(ptr));
		printf("\n");
		reset();
		fclose(ptr);
		break;

	default:
		printf("wrong choice selected.\n");
		break;
	}
	system("color 3");
	system("pause");
}

/*======SUPER USER ZONE=======*/
void add_word_in_dictionary()
{
	//{
	red('f');
	puts("\nwarning:- This features is only for development purpose and Better User Exeperience");
	cyan('f');
	puts("If you add wrong info then you will never able to access \"Super User Section from Next Time\"");
	//}
	char name[30];
	puts("write your name please:");
	gets(name);
	enter_password();			  // for enter the password from console
	int check = check_password(); // it return 0 for correct pass word and 1 for wrong password
	if (check == 0)
	{
		red('f');
		printf("\n\nSorry your password is incorrect and you can't access the super user attributes.\nPlease Contact Developer Mr. Suraj (+91 8227974640) for details about password and others attributes. Thanking You\n");
		system("pause");
	}
	else
	{
		save_super_user_name(name); // for save user name
		printf("\nHii Mr. %s Welcome in Super User Attribute.", name);
		// variable declaration
		char word[40];
		char meaning[100];
		puts("Please write the word that you want to add in Dictionary:");
		gets(word);

		upper_case(word);							   // for convert in uppercase
		int save = check_word(word);				   // return 1 if word found and 0 if word not found (for main dictionary database)
		int save2 = check_in_superuser_database(word); // return 1 if word found and 0 if word not found (from super User database)
													   // 1 meand word in available in respective data base. so we don't take such word as super user word.
		if (save == 1 || save2 == 1)				   // word found in database
		{
			red('f');
			printf("Sorry, \" %s \" is available in database. You can't add available words of database\n", word);
			reset();
			system("pause");
		}
		else
		{
			printf("write meaning of \" %s \" \n", word);
			magenta('f');
			gets(meaning);
			reset();

			save_word(word, meaning);
			yellow('f');
			puts("\nThanks Dear. Your contribution added in database successfuly:\n");
			system("pause");
			reset();
		}
	}
}

void enter_password()
{
	int i;

	white('f');
	puts("write access code provided by developer:");
	for (i = 0; i < 8; i++)
	{
		password[i] = getch();
		printf("*");
	}
	password[i] = '\0'; // because '\n' is added then condition fails. so I have to remove it.

	reset();
} // done

int check_password() // return 1 for correct and 0 for wrong
{
	FILE *ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\Dictionary\\super user password list", "r");
	if (ptr == NULL)
	{
		perror("Unable to access database to check your password. Error Code 142");
		exit(EXIT_FAILURE);
	}

	char password_from_file[30];
	int count = 0;

	while (feof(ptr) == 0)
	{
		fscanf(ptr, "%s\n", password_from_file);
		// printf("%s.  ", password_from_file);
		//	printf("  ₹%s", password);
		// printf("\n@%s@ is password and @%s@ is the password from file\n",password,password_from_file);
		if (strcmp(password_from_file, password) == 0)
		{
			count++;
			break;
		}
	}
	fclose(ptr);
	if (count == 0)
		return 0; // password not found
	else
		return 1; // password found
}

void save_super_user_name(char name[])
{
	FILE *ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\Dictionary\\super user name list", "a");
	fprintf(ptr, "%s	", name);
	fprintf(ptr, "%s\n", password);
	fclose(ptr);
}

int check_word(char eng_word_user[])
{
	unsigned short count = 0;
	FILE *ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\Dictionary\\english_word.csv", "r");
	if (ptr == NULL)
	{
		perror("Database is not reachable right now. Error code 101");
		exit(-1);
	}
	while (feof(ptr) == 0)
	{
		fscanf(ptr, "%lu", &required_word_number);
		fgets(eng_word_file, 100, ptr);

		eng_word_file[strlen(eng_word_file) - 1] = 0;
		// puts(eng_word_file);
		remove_space(eng_word_file); // function calling

		if (strcmp(eng_word_file, eng_word_user) == 0)
		{
			count++;
			break;
		}
	}
	fclose(ptr);

	return count;
}

void save_word(char word[], char meaning[])
{
	FILE *ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\Dictionary\\words added by super user", "a");
	if (ptr == NULL)
	{
		perror("Unable to access database now to save your word. Error Code 404");
		exit(EXIT_FAILURE);
	}
	fprintf(ptr, "%s\n", word);
	fprintf(ptr, "%s\n", meaning);
	fclose(ptr);
}

// checking word in superuser database
int check_in_superuser_database(char word[])
{
	int check = 0;
	FILE *ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\Dictionary\\words added by super user", "r");
	if (ptr == NULL)
	{
		perror("\033[1;31mDatabase is not reachable right now. Error code 103");
		reset();
		exit(-1);
	}

	// found_words_history(eng_word_user); //to save found words in history to access it later
	char super_user_word[60];
	while (feof(ptr) == 0)
	{
		fgets(super_user_word, 60, ptr);
		fgets(hindi_word, 500, ptr);

		super_user_word[strlen(super_user_word) - 1] = 0; // to remove auto new line added by fgets()
		upper_case(super_user_word);					  // converting super user word from file into uppercase becase our user's word is already converted in to same'
		if (strcmp(super_user_word, word) == 0)
		{
			check++;
			break;
		}
	}

	fclose(ptr);
	if (check == 0)
		return 0; // for not found
	else
		return 1; // for found
}
