/*Last modified on 4th Feb 2022.
 * In future add indexing of history.
 * add timer for basic, medium, advanced and expert user.
 */
//{
#define MAX_ERRORS 5
// means maximum 5 errors are allowed to user
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "D:\C Language\All C Programs\1) Cxxdroid Application\Header Files\color.h"

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
char current_date[30];				// stored globally to check while printing rank of user
char present_time[30];				// stored globally to check while printing rank of user

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
int arrange_result_database();
void show_temp_word_history();
void save_current_date_time();
void today_date(char *date);
void current_time(char *time);
void commands();

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
	system("cls");
	printf("Hii Dear\U0001F64b\U0001F44b WELCOME TO \033[1;31m\"SUPER WORD GAME \U000000A9\"\033[0m Dev:- Suraj Kumar Giri\n\n");
	system("pause");
	cyan('f');
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

	green('f');
	puts("Do you want to see 'hindi' meaning of word given by computer in the game.");
	puts("press 1 for yes else press any key to continue:");
	scanf("%d", &want_hindi_meaning);
	fflush(stdin);

	// removing file if exist in one condition abnormal termination else it will auto remove in last becuase it's last line of code in main()'
	remove("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\word game\\temp_user_computer_word");

	system("cls");
	advcolor('f', 195);
	puts("Please write your name:");
	reset();
	printf("$ ");
	gets(user_name);
	system("cls");
	uppercase(user_name); // convert user_name to uppercase

	int check1 = 0;
	int check2 = 0;
	int check3 = 1;					  // word for first time only.
	no_of_correct_entry = 0;		  // for count no. of correct words entered by user
	int no_of_word_enter_by_user = 1; // including wrong

	// game started
	commands(); // to show the list of commands which can be used by user anytime in game

	while (1) // game started
	{
		int terminate = 0; // increase if user wants to terminate the game immediately
		while (1)
		{
			printf("\n\033[1;31m%02d.\033[0m It's\033[1;36m %s \033[0mTurn. So, Write your word:\n", no_of_word_enter_by_user, user_name);
			printf("$ ");
			magenta('f');
			gets(user_word);
			if (user_word[0] == '\0')
				continue;
			else if (strcmp(user_word, "#clear") == 0)
			{
				system("cls");
				continue;
			}
			else if (strcmp(user_word, "#exit") == 0)
			{
				terminate++;
				break;
			}
			else if (strcmp(user_word, "#cmd") == 0)
			{
				commands();
				continue;
			}
			else if (strcmp(user_word, "#") == 0)
			{
				show_temp_word_history();
				continue;
			}
			break;
		}
		if (terminate == 1)
			break;

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
	score_saver();			  // to save the score of user in database
	save_current_date_time(); // to save the date and time of user access
	/*leanderboard is not showing then it's sure that there is problem within function leaderboard() or any other function called from leaderboard() */
	leaderboard(); // to show leaderboard and position of user in leaderboard along with prizes

	remove("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\word game\\temp_user_computer_word");
	printf("\n\033[1;32m******Main Exited successfuly******\033[0m\n");
	return 0;
} // end of main()

/*to save the score of user in database.*/
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
	int maxIndex = arrange_result_database();
	/*maxIndex is returned because we have added some extra line in leaderboard. Actually, I have
	 * added last update date and time in the arraged_leaderboard database. And if we read that
	 * part then it creates problem in comparing etc in this function.
	 * by this maxIndex we will read only till if maxIndex found
	 */

	int index;
	int score_from_file;
	char name_from_file[100];
	char *date_from_file = (char *)calloc(50, sizeof(char));
	char *time_from_file = (char *)calloc(50, sizeof(char));
	int user_rank;

	// file contains index then score then name in a ordered way
	FILE *ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\word game\\ordered_leaderboard.txt", "r");
	FILE *ptr2 = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\word game\\ordered_date_and_time.txt", "r");

	if (ptr == NULL || ptr2 == NULL)
	{
		perror("unable to access leaderboard. exit code 108");
		exit(EXIT_FAILURE);
	}

	// modified here because time and date is added in leaderboard
	/*modification skipped because I have create seperate file for arranged date and time*/
	// problem in reading multiple file at same time
	while (feof(ptr) == 0 && index < maxIndex) // && feof(ptr2) == 0)
	{
		fscanf(ptr, "%d\t%d", &index, &score_from_file);
		fgetc(ptr); // for taking tab whitespace
		fgets(name_from_file, 50, ptr);
		name_from_file[strlen(name_from_file) - 1] = 0;

		fgets(date_from_file, 50, ptr2);
		fgets(time_from_file, 50, ptr2);
		fgetc(ptr2);									// to take extra newline
		date_from_file[strlen(date_from_file) - 1] = 0; // 1 extra space available in date but extra space available at both places i.e in database as well as variable present in memory i.e current_date
		time_from_file[strlen(time_from_file) - 1] = 0;
		if (score_from_file == score && strcmp(user_name, name_from_file) == 0 && strcmp(present_time, time_from_file) == 0 && strcmp(current_date, date_from_file) == 0)
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
	printf("$ ");
	fflush(stdin);
	gets(choice);

	printf("\n");
	index = 0;
	/*modified from here on 30th Jan 2022, becaus date and time database created today and we have to print  them also along with leaderboard.*/
	if (strcmp(choice, "yes") == 0 || strcmp(choice, "Yes") == 0 || choice[0] == 'y' || choice[0] == 'Y')
	{
		int c;
		rewind(ptr);
		rewind(ptr2);
		// priting the header
		printf("\033[4m\033[38;5;142mRank    \033[38;5;190mScore     \033[38;5;189mName                                          \033[38;5;152mDate           \033[38;5;14mTime\033[0m\n");

		while (feof(ptr) == 0)
		{
			// c = fgetc(ptr);
			// if (c == EOF)
			// 	break;
			// printf("%c", c);
			fscanf(ptr, "%d\t%d", &index, &score_from_file);
			fgetc(ptr); // for taking tab whitespace
			fgets(name_from_file, 50, ptr);
			name_from_file[strlen(name_from_file) - 1] = 0;

			fgets(date_from_file, 50, ptr2);
			fgets(time_from_file, 50, ptr2);
			fgetc(ptr2); // for taking extra one newline (means total 2 newline avaialble but fgets() auto send pointer to next newline)
			date_from_file[strlen(date_from_file) - 1] = 0;
			time_from_file[strlen(time_from_file) - 1] = 0;

			// printing time
			if (index == user_rank) // highlighting the user rank in the leaderboard
			{
				printf("\033[1;32m----------------------------------------------------------------------------------------\n");
				printf("\033[1;31m%02d	\033[38;5;190m%02d	\033[38;5;189m%-25s \033[38;5;152m%25s \033[38;5;14m%15s\n\033[0m", index, score_from_file, name_from_file, date_from_file, time_from_file);
				printf("\033[1;32m----------------------------------------------------------------------------------------\n");
			}
			else
				printf("\033[38;5;142m%02d	\033[38;5;190m%02d	\033[38;5;189m%-25s \033[38;5;152m%25s \033[38;5;14m%15s\n", index, score_from_file, name_from_file, date_from_file, time_from_file);

			/* if index reached at maximum index then we will break the loop because we have    also printed the 'last update date and time' in the database and we have to print them also but they are not in the list
			 */
			if (index == maxIndex)
				break;
		}
		fgetc(ptr);						 // for reading a newline
		fgets(name_from_file, 100, ptr); // to print last update time and date
		printf("\n\033[1;32m%s\033[0m\n", name_from_file);
	}
	fclose(ptr);
	fclose(ptr2);

	white('f');
	printf("\nThanks Mr. %s.\nBye bye....\nSee you soon.....", user_name);
	reset();
}

int arrange_result_database()
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

	// char(*p2)[30]; // for name_from_file
	// p2 = (char(*)[30])malloc(max_index * 30 * sizeof(char));
	char **p2 = (char **)malloc(max_index * sizeof(char *));
	for (int i = 0; i < max_index; i++)
		p2[i] = (char *)malloc(50 * sizeof(char));

	if (p == NULL || p2 == NULL)
		printf("Heap memory not available in RAM.");
	int *save_address = p;

	int i = 0;
	rewind(ptr);							// to point the pointer to beginning of the file
	while (feof(ptr) == 0 && i < max_index) //&&i<max_index is added and bug fixes because control go one iteration further after reading last then EOF encounter but I have allocated memory for only 1 less than max_index. feof() is the cause of this bug because of one line extra reading. Research about it.
	{
		fscanf(ptr, "%d\t%d", &index, &score_from_file);
		fgetc(ptr); // for taking tab whitespace
		fgets(name_from_file, 50, ptr);
		name_from_file[strlen(name_from_file) - 1] = '\0'; // remving trailing newline from string
		*p = score_from_file;
		p++;
		strcpy(p2[i], name_from_file);
		i++;
		memset(name_from_file, 0, sizeof(name_from_file));
	}
	fclose(ptr);
	/*This is the last point of execution. I thing there is problem in allocating memory in 2 dimensions*/

	/*modified on 31st Jan 2022 for adding date and time in ordered_leaderboard database*/
	// start
	// opening user_played_date.txt which stores original date
	fflush(stdin);
	char file_data[100]; // to read data from file
	FILE *date_ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\word game\\user_played_date.txt", "r");
	if (date_ptr == NULL)
	{
		printf("Couldn't open date file. Error code 908\n'");
		exit(EXIT_FAILURE);
	}

	// char(*date_from_file)[30] = (char(*)[30])malloc(max_index * 30 * sizeof(char)); // for date string
	char **date_from_file = (char **)malloc(max_index * sizeof(char *));
	for (int i = 0; i < max_index; i++)
		date_from_file[i] = (char *)malloc(30 * sizeof(char));

	i = 0;
	int temp_data;								 // to tempory store index from file
	while (feof(date_ptr) == 0 && i < max_index) //&&i<max_index is added and bug fixes because control go one iteration further after reading last then EOF encounter but I have allocated memory for only 1 less than max_index. feof() is the cause of this bug because of one line extra reading. Research about it.
	{
		// fgetc(date_ptr);						// for reading index
		fscanf(date_ptr, "%d", &temp_data);
		fgetc(date_ptr);				 // for reading space
		fgets(file_data, 100, date_ptr); // for reading date string
		// now remving newline added by fgets()
		file_data[strlen(file_data) - 1] = '\0';
		strcpy(date_from_file[i++], file_data); // saving date in variable available in memory currently
	}
	fclose(date_ptr);

	fflush(stdin);
	// opening user_played_time.txt which stores original time
	FILE *time_ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\word game\\user_played_time.txt", "r");
	if (time_ptr == NULL)
	{
		printf("Couldn't open time file. Error code 909\n'");
		exit(EXIT_FAILURE);
	}

	// char(*time_from_file)[30] = (char(*)[30])malloc(max_index * 30 * sizeof(char)); // for date string

	char **time_from_file = (char **)malloc(max_index * sizeof(char *));
	for (int i = 0; i < max_index; i++)
		time_from_file[i] = (char *)malloc(30 * sizeof(char));

	i = 0;
	while (feof(time_ptr) == 0 && i < max_index) //&&i<max_index is added and bug fixes because control go one iteration further after reading last then EOF encounter but I have allocated memory for only 1 less than max_index. feof() is the cause of this bug because of one line extra reading. Research about it.
	{
		// fgetc(time_ptr);
		fscanf(time_ptr, "%d", &temp_data); // for reading index
		fgetc(time_ptr);					// for reading whitespace
		fgets(file_data, 100, time_ptr);	// for reading time string
		// now remving newline added by fgets()
		file_data[strlen(file_data) - 1] = '\0';
		strcpy(time_from_file[i++], file_data); // saving date in variable available in memory currently
	}
	fclose(time_ptr);
	//  end
	fflush(stdin);
	int temp;
	p = save_address;
	char save_user_name[50]; // to save user name in changing of data which save from losing data
	char save_date[30];		 // save the date temporiraly which save from losing data
	char save_time[30];		 // save the time temporiraly which save from losing data

	fflush(stdin);
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

				strcpy(save_date, date_from_file[i]);
				strcpy(date_from_file[i], date_from_file[j]);
				strcpy(date_from_file[j], save_date);

				strcpy(save_time, time_from_file[i]);
				strcpy(time_from_file[i], time_from_file[j]);
				strcpy(time_from_file[j], save_time);
			}
		}
	}
	fflush(stdin);
	// now making new file to print the order data
	ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\word game\\ordered_leaderboard.txt", "w");
	FILE *ptr2 = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\word game\\ordered_date_and_time.txt", "w"); // for saving date and time in sperate file from ordered_leaderboard.txt becasue in that file there will become 3 strings and it's not possible to read them and seperate easily and then compare

	for (int i = 0; i < max_index; i++)
	{
		// fprintf(ptr, "%02d\t%02d\t%-20s\t%-10s\t%s\n", i + 1, p[i], p2[i], date_from_file[i], time_from_file[i]);
		fprintf(ptr, "%02d\t%02d\t%s\n", i + 1, p[i], p2[i]);
		fprintf(ptr2, "%s\n%s\n\n", date_from_file[i], time_from_file[i]);
	}

	char *date_now = (char *)calloc(20, sizeof(char));
	char *time_now = (char *)calloc(20, sizeof(char));
	today_date(date_now);
	current_time(time_now);
	fprintf(ptr, "\nLast time Leaderboard updated on %s at %s\n", date_now, time_now);

	fclose(ptr);
	fclose(ptr2);
	free(p);
	// free(p2);
	for (int i = 0; i < max_index; i++)
	{
		free(date_from_file[i]);
		free(time_from_file[i]);
		free(p2[i]);
	}
	// free(date_from_file);
	// free(time_from_file);
	return max_index;
}

void show_temp_word_history()
{
	// advcolor('b', 8);  // for white background color
	advcolor('f', 148); // for black foreground color
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

// start
/*Take argument as character pointer(to store string) and store today's date in string format at the obtanined address 'date'*/
void today_date(char *date)
{
	// date on cmd returns date and also ask for new date. e.g 'The current date is: 28-01-2022' and ask for new date in new line.
	// so we use 'date /t' to get only the exact date without extra string
	FILE *ptr = popen("date /t", "r");
	if (ptr == NULL)
		strcpy(date, "N/A");
	else
	{
		int i = 0;
		while (feof(ptr) == 0)
		{
			date[i] = fgetc(ptr);
			i++;
		}
		// two newline characters returns after showing time in cmd. So, we have to remove both and add NULL
		date[i - 3] = '\0'; // to add NULL at end of string for termination conditionk
	}
}
// end

// start
/*Take argument as character pointer(to store string) and store current time in string format at the obtanined address 'time'*/
void current_time(char *time)
{
	// time on cmd returns current time and also ask for new time. 'The current time is: 21:35:24.90' and ask for new time in new line
	// so we use 'time  /t' to get only the exact time without extra string and in 12h format
	FILE *ptr = popen("time /t", "r");
	if (ptr == NULL)
		strcpy(time, "N/A");
	else
	{
		int i = 0;
		while (feof(ptr) == 0)
		{
			time[i] = fgetc(ptr);
			i++;
		}
		// two newline characters returns after showing time in cmd. So, we have to remove both and add NULL
		time[i - 2] = '\0'; // to add NULL at end of string for termination condition}
	}
	// end
}

/*save date and time of current user in database*/
void save_current_date_time()
{
	// for date
	FILE *ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\word game\\user_played_date.txt", "a+");
	if (ptr == NULL)
	{
		printf("\nUnable to access database. Exit code 901.\n");
		exit(EXIT_FAILURE);
	}
	today_date(current_date);
	int index = 0;
	char data_from_file[50];

	// to get last index
	while (feof(ptr) == 0)
	{
		fscanf(ptr, "%d\t", &index);
		fgets(data_from_file, 50, ptr); // it will auto add newline to data_from_file but we don't remove it becaue we are not going to print it now
	}

	fprintf(ptr, "%d\t%s\n", ++index, current_date);
	fclose(ptr);

	// for time
	/*opening in apend mode because last index is already available*/
	freopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\word game\\user_played_time.txt", "a", ptr);
	if (ptr == NULL)
	{
		printf("\nUnable to access database. Exit code 902.\n");
		exit(EXIT_FAILURE);
	}
	current_time(present_time);

	fprintf(ptr, "%d\t%s\n", index, present_time);
	fclose(ptr);
}

// to display the list of all command that can be used by user inside the game
void commands()
{
	green('f');
	printf("You can use the following commands in the game anywhere anytime:-\n");
	advcolor('f', 50);
	puts("\033[1;34m01. \033[1;36m'#'\033[1;34m for show last words history:");
	puts("02. \033[1;36m'#clear'\033[1;34m for clear the screen any time.");
	puts("03. \033[1;36m'#exit' \033[1;34mto giveup or save and exit the game instantly.");
	puts("04. \033[1;36m'#cmd' \033[1;34mto display this command panel");
}