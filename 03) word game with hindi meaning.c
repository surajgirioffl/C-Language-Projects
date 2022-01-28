//{
#define MAX_ERRORS 5
// means maximum 5 errors are allowed to user
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "D:\\C Language\\All C Programs\\1) Cxxdroid Application\\Repositories\\C Language Special\\C_Language_Projects\\Header Files Used In this Repository\\color.h"

// Global variables
int score;
int count_in_file; // for availability of word in file.
char user_word[100];
char user_name[50];
char computer_word[100];
int count_in_temp;					// for availability of word in temporary file that contains previous words of one game.
int wrong;							// for counting wrong word on the basis of any condition
int no_of_correct_entry = 0;		// for count no. of correct words entered by user
unsigned long required_word_number; // for store word number given by computer from Dictionary to find its hindi_meaning

// functions
char *computer_turn(char ch);
int search_from_temp_data(char string[]);
void temp_user_computer_word();
void permanent_computer_data();
void permanent_user_data();
int search_from_dictionary(char string[]);
void uppercase(char string[]);
long displacement_for_ptr(char ch);
int unwated_char_founder(char string[]);
void game_conditions();
void score_saver();
int check_user_word();
void hindi_meaning();
void leaderboard();
void arrange_result_database();
void show_temp_word_history();

//{
//========Starting of main()==========
int main()
{
	// assigning 0 to all counting Global variables so, in case restart of game takes place all data will reset to zero
	wrong = 0;
	count_in_temp = 0;
	count_in_file = 0;
	score = 0;

	int read_condition;
	int want_hindi_meaning = 0;
	printf("Hii Dear\U0001F64b\U0001F44b WELCOME TO   \033[1;31m \"SUPER WORD GAME \U000000A9\"\033[0m Dev:- Suraj Kumar Giri\n\n");
	system("pause");
	puts("\npress 1 for see details and conditions of this game. OR Press any key to continue to game......");
	scanf("%d", &read_condition);
	fflush(stdin);
	if (read_condition == 1)
	{
		game_conditions(); // functions to read_condition

		yellow('f');
		puts("\nWow, You have read the condition. Your target must be to achieve gold medal\n");
		puts("So, Let's start.........\n");
		reset();
	}

	puts("Do you want to see hindi meaning of word given by computer in the game.");
	puts("press 1 for yes else press any key to continue:");
	scanf("%d", &want_hindi_meaning);
	fflush(stdin);

	// removing file if exist in one condition abnormal termination else it will auto remove in last becuase it's last line of code in main()'
	remove("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\word game\\temp_user_computer_word");

	system("cls");
	puts("Please write your name:");
	gets(user_name);
	system("cls");
	uppercase(user_name); // convert user_name to uppercase

	int check1 = 0;
	int check2 = 0;
	int check3 = 1;					  // word for first time only.
	no_of_correct_entry = 0;		  // for count no. of correct words entered by user
	int no_of_word_enter_by_user = 1; // including wrong
	// game started
	while (1)
	{
		while (1)
		{
			printf("\n\033[1;31m%02d.\033[0m It's\033[1;36m %s \033[0mTurn. So, Write your word:\n", no_of_word_enter_by_user, user_name);
			magenta('f');
			gets(user_word);
			if (user_word[0] == '#')
				show_temp_word_history();
			else
				break;
		}
		no_of_word_enter_by_user++;
		reset();
		uppercase(user_word);

		check1 = search_from_dictionary(user_word);
		if (no_of_correct_entry != 0)
		{
			check2 = search_from_temp_data(user_word);
			check3 = check_user_word(); // user word is global so function will auto take
		}

		permanent_user_data(); // function calling to save current right/wrong word of user permanently in database

		if (check1 != 0 && check2 == 0 && check3 != 0)
		{
			/*printf("I am inside if.");
		  printf("%d is the no.",no_of_correct_entry);*/
			// temp_user_computer_word(user_word); //to save current user word
			score += 2;

			// now it's computer turn
			char ch = user_word[strlen(user_word) - 1];
			yellow('f');
			printf("\n==>> %s\n", computer_turn(ch));
			reset();
			if (want_hindi_meaning == 1)
				hindi_meaning(); // function calling for hindi meaning

			temp_user_computer_word(); // to save current computer_word and user_word

			permanent_computer_data(); // function calling to save current word of computer permanently in database

			no_of_correct_entry++;
		}

		else
		{
			red('f');
			if (check1 == 0) // word not found in Dictionary
				printf("wrong word \" %s \" entered. Not found in dictionary\n", user_word);
			if (check2 != 0)
				printf("previos written word \" %s \" entered\n", user_word);
			if (check3 == 0)
				printf("First character of your word \" %s \" is not match with last character of computer word\n", user_word);

			wrong++;
			score = score - 2; // 2 point will deducted if wrong word

			if (wrong == MAX_ERRORS + 1)
				break;

			if ((MAX_ERRORS - wrong) == 0)
				printf("\nYou have made %d mistakes. And you can't make any more mistakes else you will be terminated from game with your gained score.\n", MAX_ERRORS);
			else
				printf("\nYou have made %d mistakes. And you can make only %d more mistake/mistakes.\n", wrong, MAX_ERRORS - wrong);
			reset();
		}
	} // end of while. so end of game

	cyan('f');
	printf("\n\n||||||||||====SCORE CARD OF Mr. %s====||||||||||\n", user_name);

	white('f');
	printf("You have scored %d points.\n", score);
	reset();
	score_saver(); // to save the score of user in database
	leaderboard(); // to show leaderboard and position of user in leaderboard along with prizes

	remove("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\word game\\temp_user_computer_word");
	return 0;
} // end of main()

void score_saver() // a+ is well working
{
	FILE *ptr;
	ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\word game\\result.txt", "a"); // to create file first time (work if file not exist. if we use another mode then there is lots of issues)
	fclose(ptr);

	ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\word game\\result.txt", "r+");
	if (ptr == NULL)
	{
		perror("Sorry, Unable to access score_saver database now. Error code 121.");
		exit(EXIT_FAILURE);
	}
	int index = 0;
	int score_from_file;
	char name_from_file[50];
	// file contains index then score then name

	while (feof(ptr) == 0) // reading
	{
		fscanf(ptr, "%d\t%d", &index, &score_from_file);
		fgetc(ptr); // for taking tab whitespace
		fgets(name_from_file, 50, ptr);
	}

	fprintf(ptr, "%d\t%d\t%s\n", ++index, score, user_name);
	fclose(ptr);
}

char *computer_turn(char ch)
{
	FILE *ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\Dictionary\\english_word.csv", "r");
	if (ptr == NULL)
	{
		perror("Database is not reachable right now. Error code 111");
		exit(-1);
	}
	// displacing pointer to particular postion for fast access
	// long displacement = displacement_for_ptr(ch);
	// fseek(ptr, displacement, SEEK_SET);

	int check1;
	int check2 = 0;
	while (feof(ptr) == 0)
	{
		fscanf(ptr, "%lu", &required_word_number);
		// fflush(ptr);
		fgetc(ptr);
		fgets(computer_word, 100, ptr);

		computer_word[strlen(computer_word) - 1] = 0;

		if (computer_word[0] == ch)
		{
			check1 = unwated_char_founder(computer_word);
			if (check1 == 0)
			{
				if (no_of_correct_entry != 0)
					check2 = search_from_temp_data(computer_word);
				if (check2 == 0)
				{
					fclose(ptr);
					return computer_word;
				}
			}
		}
	} // end of while
}

int search_from_temp_data(char string[])
{
	count_in_temp = 0;
	FILE *ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\word game\\temp_user_computer_word", "r");
	if (ptr == NULL)
	{
		perror("Unable to access database to check word temporiraly. Error Code 105");
		exit(EXIT_FAILURE);
	}

	char temp_word_from_file[100];

	while (feof(ptr) == 0)
	{
		fgets(temp_word_from_file, 100, ptr);
		temp_word_from_file[strlen(temp_word_from_file) - 1] = 0;
		if (strcmp(string, temp_word_from_file) == 0)
		{
			count_in_temp++;
			break;
		}
	}
	fclose(ptr);
	return count_in_temp;
}

void temp_user_computer_word()
{
	FILE *ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\word game\\temp_user_computer_word", "a");
	if (ptr == NULL)
	{
		perror("Unable to access database to save word temporiraly. Exit Code 106");
		exit(EXIT_FAILURE);
	}
	fprintf(ptr, "%s\n%s\n", user_word, computer_word);
	fclose(ptr);
}

void permanent_computer_data()
{
	FILE *ptr;
	ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\word game\\permanent_computer_data", "a");
	if (ptr == 0)
	{
		red('f');
		perror("Unable To Access Database To Write All Data Permanently. Error Code 103");
		reset();
		exit(EXIT_FAILURE);
	}

	static int index1; // for no. of word counter
	static int count_call_in_computer;
	if (count_call_in_computer == 0)
		fprintf(ptr, "\n\nDatabase For Mr. %s\n", user_name);

	fprintf(ptr, "%d %s\n", index1, computer_word);
	index1++;

	/*if(count_in_file==1 && count_in_temp==0)
  fprintf(ptr,"Right Word --> Point+1.\n");
  else
  fprintf("Wrong Word --> Point-5.\n");
  */
	count_call_in_computer++;
	if (wrong == MAX_ERRORS + 1) /*EDIT:*/ //+1 because till max_errors, user can play and after any further error program will terminated
		fprintf(ptr, "\n\n");
	fclose(ptr);
}

void permanent_user_data()
{
	FILE *ptr;
	ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\word game\\permanent_user_data", "a");
	if (ptr == 0)
	{
		red('f');
		perror("Unable To Access Database To Write All Data Permanently. Error Code 102");
		reset();
		exit(EXIT_FAILURE);
	}

	static int index; // for no. of word counter
	static int count_call_in_user;
	if (count_call_in_user == 0)
		fprintf(ptr, "\n\nDatabase of Mr. %s\n", user_name);

	fprintf(ptr, "%d %s\t", index, user_word);
	index++;

	if (count_in_file != 0 && count_in_temp == 0)
		fprintf(ptr, "Right Word --> Point will +2.\n");
	else
		fprintf(ptr, "Wrong Word --> Point will -2.\n");

	count_call_in_user++;
	if (wrong == MAX_ERRORS + 1) /*EDIT:*/ //+1 because till max_errors, user can play and after any further error program will terminated
		fprintf(ptr, "\n\n");
	fclose(ptr);
}

int search_from_dictionary(char string[])
{
	count_in_file = 0;
	unsigned long word_number;
	char word_from_file[100];

	FILE *ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\Dictionary\\english_word.csv", "r");
	if (ptr == NULL)
	{
		perror("Database is not reachable right now. Error code 101");
		exit(-1);
	}
	/*long displacement = displacement_for_ptr(string[0]);
	fseek(ptr, displacement, 0);*/

	while (feof(ptr) == 0)
	{
		fscanf(ptr, "%lu", &word_number);
		// fflush(ptr);
		getc(ptr);
		fgets(word_from_file, 100, ptr);

		word_from_file[strlen(word_from_file) - 1] = 0;

		if (strcmp(word_from_file, string) == 0)
		{
			count_in_file++;
			break;
		}
	}
	fclose(ptr);
	return count_in_file;
}

void uppercase(char string[])
{
	for (int i = 0; string[i] != '\0'; i++)
		string[i] = toupper(string[i]);
}

int unwated_char_founder(char string[])
{
	int count = 0;
	// int length= strlen(string);
	for (int i = 0; string[i] != '\0'; i++)
	{
		if (string[i] == '.' || string[i] == '/' || string[i] == ' ' || string[i] == '-' || strlen(string) == 1 || strlen(string) == 2 || string[i] == 39 || string[i] == 38 || string[i] == '!')
			count++;
	}
	return count;
}

long displacement_for_ptr(char ch)
{
	if (ch == 'A')
		return 42;
	else if (ch == 'B')
		return 187443;
	else if (ch == 'C')
		return 364270;
	else if (ch == 'D')
		return 648158;
	else if (ch == 'E')
		return 807268;
	else if (ch == 'F')
		return 921066;
	else if (ch == 'G')
		return 1065609;
	else if (ch == 'H')
		return 1169673;
	else if (ch == 'I')
		return 1290209;
	else if (ch == 'J')
		return 1414491;
	else if (ch == 'K')
		return 1414491; // it's not available in database. passing previous value
	else if (ch == 'L')
		return 1463404;
	else if (ch == 'M')
		return 1563384;
	else if (ch == 'N')
		return 1563384; // it's not available in database. passing previous value
	else if (ch == 'O')
		return 1776138;
	else if (ch == 'P')
		return 1776138; // it's not available in database. passing previous value
	else if (ch == 'Q')
		return 2110975;
	else if (ch == 'R')
		return 2135362;
	else if (ch == 'S')
		return 2297633;
	else if (ch == 'T')
		return 2723498;
	else if (ch == 'U')
		return 2934296;
	else if (ch == 'V')
		return 2934296; // it's not available in database. passing previous value
	else if (ch == 'W')
		return 3068026;
	else if (ch == 'X')
		return 3198690;
	else if (ch == 'Y')
		return 3201544;
	else if (ch == 'Z')
		return 3213036;
	/* Position of alphabet that i have found in dictionary database.
position of A is 42
position of B is 187443
position of C is 364270
position of D is 648158
position of E is 807268
position of F is 921066
position of G is 1065609
position of H is 1169673
position of I is 1290209
position of J is 1414491
position of L is 1463404
position of M is 1563384
position of O is 1776138
position of Q is 2110975
position of R is 2135362
position of S is 2297633
position of T is 2723498
position of U is 2934296
position of W is 3068026
position of X is 3198690
position of Y is 3201544
position of Z is 3213036
*/
}

void game_conditions()
{
	cyan('f');
	puts("Following are the conditions and details of game.");
	reset();

	magenta('f');
	puts("1. write correct word.");
	puts("2. Don't repeat same word.");
	puts("3. You have to write the word whose 1st character is same as the last character of computer word(except 1st time)");
	white('f');
	puts("4. You will rewarded 2 point for each correct word.");
	red('f');
	printf("5. 2 points will deducted for each wrong word. and maximum %d wrong words are allowed in game.\n", MAX_ERRORS);
	reset();
	printf("6. Press '#' anytime at the place of typing word to see history of word by you and computer in current game.\n");
}

int check_user_word()
{
	// now checking that 1st char or user_word is same as last char of computer or not (started from 2nd iteration of while)
	int check = 0;
	if (no_of_correct_entry != 0) // no_of_correct_entry=0 means no word given computer till now.
	{
		if (user_word[0] == computer_word[strlen(computer_word) - 1])
			check++;
	}
	return check; // means check=0 means wrong word entered. check=1 means right word.
}
//}

void hindi_meaning()
{
	unsigned long word_number_for_check = 0;
	char hindi_word[500];
	FILE *ptr = NULL;

	if (required_word_number < 91922)
	{
		ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\Dictionary\\hindi_word_1.csv", "r");
		if (ptr == NULL)
		{
			perror("Database is not reachable right now. Error code 151");
			exit(-1);
		}

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
	printf("\"Hindi Meaning\", [Antonym and more info], \"Sentence\" related to the word \033[1;33m\"%s\"\033[0m are following:\f", computer_word);
	// advcolor('f',53);
	white('f');
	printf("\n%s\n", hindi_word);
	reset();
}
//}

void leaderboard()
{
	// first we need to arrange the result data of users in Database in a proper order
	arrange_result_database();

	int index;
	int score_from_file;
	char name_from_file[50];
	int user_rank;

	// file contains index then score then name in a ordered way
	FILE *ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\word game\\ordered_leaderboard.txt", "r");
	if (ptr == NULL)
	{
		perror("unable to access leaderboard. exit code 108");
		exit(EXIT_FAILURE);
	}

	while (feof(ptr) == 0)
	{
		fscanf(ptr, "%d\t%d", &index, &score_from_file);
		fgetc(ptr); // for taking tab whitespace
		fgets(name_from_file, 50, ptr);

		name_from_file[strlen(name_from_file) - 1] = 0;
		if (score_from_file == score && strcmp(user_name, name_from_file) == 0)
			user_rank = index;
	}

	yellow('f');
	printf("\nHello Mr. %s your rank is %d among %d participants\n", user_name, user_rank, index);
	reset();

	magenta('f');
	if (user_rank < 10)
	{
		if (user_rank == 1)
			puts("====EXCELLENT AWESOME SUPEREB MINDBLOWING KING====\nYou are topper and you are rewarded by GOLD MEDAL");
		else if (user_rank == 2)
			puts("====NICE  AWESOME VERY GOOD====\nYou are 2nd topper and you are rewarded by SILVER MEDAL");
		else if (user_rank == 3)
			puts("====GOOD NICE====\nYou are 3rd topper and you are rewarded by BRONZE MEDAL");
		else
			puts("====GOOD====\nYou are in Top 10.");
	}
	else
		puts("SORRY you are not in top 10. So no appreciation and medal will provided.");
	reset();

	char choice[4];
	printf("\nDo you want to see leaderboard chart. yes or no:\n");
	fflush(stdin);
	gets(choice);

	printf("\n");
	if (strcmp(choice, "yes") == 0 || strcmp(choice, "Yes") == 0 || choice[0] == 'y' || choice[0] == 'Y')
	{
		int c;
		rewind(ptr);
		while (1)
		{
			c = fgetc(ptr);
			if (c == EOF)
				break;
			printf("%c", c);
		}
	}
	fclose(ptr);

	white('f');
	printf("\nThanks Mr. %s.\nBye bye....\nSee you soon.....", user_name);
	reset();
}

void arrange_result_database()
{
	FILE *ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\word game\\result.txt", "r");
	if (ptr == NULL)
	{
		perror("unable to access leaderboard. exit code 107");
		exit(EXIT_FAILURE);
	}

	int index;
	int score_from_file;
	char name_from_file[50];
	// file contains index then score then name

	while (feof(ptr) == 0) // reading for getting index
	{
		fscanf(ptr, "%d\t%d", &index, &score_from_file);
		fgetc(ptr); // for taking tab whitespace
		fgets(name_from_file, 50, ptr);
	}

	int max_index = index;
	int *p; // for score_from_file
	p = (int *)malloc(max_index * sizeof(int));

	char(*p2)[30]; // for name_from_file
	p2 = (char(*)[30])malloc(max_index * 30 * sizeof(char));

	if (p == NULL || p2 == NULL)
		printf("Heap memory not available in RAM.");
	int *save_address = p;

	int i = 0;
	rewind(ptr); // to point the pointer to beginning of the file
	while (feof(ptr) == 0)
	{
		fscanf(ptr, "%d\t%d", &index, &score_from_file);
		fgetc(ptr); // for taking tab whitespace
		fgets(name_from_file, 50, ptr);
		*p = score_from_file;
		p++;
		strcpy(p2[i], name_from_file);
		i++;
	}
	fclose(ptr);

	int temp;
	p = save_address;
	char save_user_name[30]; // to save user name in changing of data

	// bubble shot algorithm for descending order
	for (i = 0; i < max_index; i++)
	{
		for (int j = i + 1; j < max_index; j++)
		{
			if (p[i] < p[j])
			{
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;

				strcpy(save_user_name, p2[i]);
				strcpy(p2[i], p2[j]);
				strcpy(p2[j], save_user_name);
			}
		}
	}

	// now making new file to print the order data
	ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\word game\\ordered_leaderboard.txt", "w");

	for (int i = 0; i < max_index; i++)
		fprintf(ptr, "%d\t%d\t%s", i + 1, p[i], p2[i]);

	fclose(ptr);
	free(p);
	free(p2);
}

void show_temp_word_history()
{
	advcolor('b', 169); // for white background color
	advcolor('f', 232); // for black foreground color
	FILE *ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\word game\\temp_user_computer_word", "r");
	if (ptr == NULL)
		puts("sorry. No history available till now.");
	else
	{
		puts("===History of words are following:===");
		while (feof(ptr) == 0)
		{
			int ch = fgetc(ptr);
			printf("%c", ch);
		}
		puts("\n===End of history.===");
	}
	reset();
}
