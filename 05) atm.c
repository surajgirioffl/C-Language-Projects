//{
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "/storage/emulated/0/All C Programs/1) Cxxdroid Application/Header Files/color.h"
//}
//primary functions
void banking();
void payment_service();
void fund_transfer();
void account_service();
void others_service();

//sub-functions of "banking()" function
void withdrawl();

//Other universal(say because they are used most) functions used in program
void main_menu(); //for welcome menu
void new_user();
//void old_user(); //not required
int input_pin();
unsigned long random_int_generator();
unsigned long create_balance(char name[]);
int pin_check(int pint, unsigned long id);
char *username_finder(unsigned long id); //it will return address of char type variable but returning address is work for global or static variable only
char username[30];						 //variable
unsigned long forget_id();
unsigned long balance_enquiry();
unsigned long user_id; //variable

/*=====STARTING OF PROGRAM=====*/
int main()
{
	cyan('f'); //cyan color
	system("time\n");
	system("date\n");
	yellow('f'); //yellow color foreground
	printf("=====WELCOME TO STATE BANK OF INDIA=====\n");
	reset(); //for reset the color and attributes of text

	puts("Please Select your choice from following:");
	puts("01. For New User (Don't have User ID)");
	puts("02. For Old User (Having User ID)");
	puts("03. For old user who forget his User ID");
	puts("04. For Super User (Having Spcial User Access Code)");
	puts("05. Exit");

	int choice;
	white('f');
	puts("write your choice:");
	scanf("%d", &choice);
	reset(); //to reset the color and attributes
	fflush(stdin);

	switch (choice)
	{
	case 1:
		new_user();
		break;

	case 2:
		//goto old_user;
		break;

	case 3:
		red('h');
		printf("Note Down:: Your User Id is %lu\n", forget_id());
		reset();
		break;

	case 5:
		exit(EXIT_FAILURE);
		break;

	default:
		red('f');
		printf("wrong choice selected\n");
		reset();
		break;
	}
	//old_user: //for old user*/don't know why not working

	puts("\nWrite your User Id.");
	scanf("%lu", &user_id); //id from user from console
	fflush(stdin);

	//now inputting pin from User
	int user_pin;
	user_pin = input_pin(); //pin from user from console

	FILE *ptr;
	unsigned long file_id; //id of user from file i.e database
	int file_pin;		   //pin of user from database
	ptr = fopen("/storage/emulated/0/All C Programs/1) Cxxdroid Application/File IO in C/ATM/id_plus_pin", "r");
	if (ptr == NULL)
	{
		printf("\nServer Not Reachable. Unable to access the database. EXIT CODE 1\n");
		exit(EXIT_FAILURE);
	}
	while (feof(ptr) == 0)
	{
		fscanf(ptr, "%lu", &file_id);
		fscanf(ptr, "%d\n", &file_pin);
		if (file_id == user_id)
			break;
	}

	if (file_pin == user_pin && file_id == user_id)
	{
		cyan('f');
		printf("\nYour PIN is correct and now you can access your account.\n");
		//Calling of Menu
		printf("\n===WELCOME MR. %s=====\n", username_finder(user_id));
		reset();
		main_menu(); //for print welcome menu on console
	}
	else
	{
		red('f'); //for red foreground
		printf("\nGet Lost. You have entered wrong PIN or User Id");
		reset(); //for reset all colors and attributes
	}
	fclose(ptr);
	return 0;
}

//{
//for main menu
void main_menu()
{
	int choice; //for choice of switch case
	puts("Select your choice from the following:");
	puts("01. Banking");
	puts("02. Payment Service");
	puts("03. Fund Transfer");
	puts("04. Account Service");
	puts("05. Others Service");
	puts("06. Exit");

	scanf("%d", &choice);
	getchar();

	switch (choice)
	{
	case 1:
		banking();
		break;

	case 2:
		payment_service();
		break;

	case 3:
		fund_transfer();
		break;

	case 4:
		account_service();
		break;

	case 5:
		others_service();
		break;

	case 6:
		exit(0);
		break;
	}
}

/*1)====BANKING OPTION RELATED FUNCTION=====*/
void banking()
{
	puts("\n|||WELCOME TO BANKING SERVICE|||");
	puts("Select your choice from the following:");
	puts("01. Cash Withdrawl");
	puts("02. Fast Withdrawl");
	puts("03. Cash Deposite");
	puts("04. Balance Enquiry");
	puts("05. Mini statement");
	puts("06. PIN Generation (For New Customer Only)");
	puts("07. PIN Change (For Existing Customer)");
	puts("08. Exit");
	int choice; //for choice of switch case
	scanf("%d", &choice);
	fflush(stdin);

	switch (choice)
	{
	case 1: //for cash withdrawl
		withdrawl();
		break;

	case 4:
		magenta('f');
		printf("Your Account Balance is INR %lu\n", balance_enquiry());
		reset();
		break;
	}
}

//withdrawal
void withdrawl() {}

/*2)====PAYMENT_SERVICE OPTION RELATED FUNCTION=====*/
void payment_service() {}

/*3)====FUND_TRANSFER OPTION RELATED FUNCTION=====*/
void fund_transfer() {}

/*4)====ACCOUNT_SERVICE OPTION RELATED FUNCTION=====*/
void account_service() {}

/*5)====OTHERS_SERVICE OPTION RELATED FUNCTION=====*/
void others_service() {}

/*====OTHER EVERGREEN FUNCTIONS USED IN PROGRAM=====*/
int input_pin() //for both new and old User
{
	char pin[5];
	char temp = '\0';
	int i = 0;
	puts("write your 4 digits PIN to access your account:");
	fflush(stdin);
	while (temp != '\n' && i < 4) //we can also use '\r' at the place of '\n'
	{
		temp = getch();
		pin[i] = temp;
		printf("*");
		i++;
	}
	pin[i] = '\0';
	return atoi(pin); //atoi() converts integral string to integer
}

void new_user() //It contains all lines of code to create database for new user
{
	char name[30];
	unsigned long balance;
	unsigned long id;
	//pin is 1234 for new user
	unsigned long account_number;

	puts("Please enter your name:");
	gets(name);

	/*1st we create data of new user by respective function then we will put that data in database*/
	//1. for balance creation
	balance = create_balance(name);
	//2. for generate id
	id = random_int_generator() % 10000; //%10000 is used to make no. small
	red('f');
	printf("\nCaution:: Your User ID is %lu. Don't forget it. Write Down it.\n", id);
	reset();
	//3. for generate account_number
	sleep(1); //due to this time_t get changed and we will receive different value from rand()
	account_number = random_int_generator();
	//4. pin is 1234 for new user
	//5. name is stored in variable here.

	//for new user we have create his database
	/* Now we will create database*/
	FILE *ptr;
	//1. for id and name
	ptr = fopen("/storage/emulated/0/All C Programs/1) Cxxdroid Application/File IO in C/ATM/id_plus_name", "a");
	if (ptr == NULL)
		perror("File not found");
	fprintf(ptr, "%lu\n", id);
	fprintf(ptr, "%s\n", name);
	fclose(ptr);

	//2. for id and balance (id balance)
	ptr = fopen("/storage/emulated/0/All C Programs/1) Cxxdroid Application/File IO in C/ATM/id_plus_balance", "a");
	fprintf(ptr, "%lu  %lu\n", id, balance);
	fclose(ptr);

	//3. for id and PIN
	ptr = fopen("/storage/emulated/0/All C Programs/1) Cxxdroid Application/File IO in C/ATM/id_plus_pin", "a");
	fprintf(ptr, "%lu  %d\n", id, 1234);
	fclose(ptr);

	//3. for id and account_number
	ptr = fopen("/storage/emulated/0/All C Programs/1) Cxxdroid Application/File IO in C/ATM/id_plus_account_number", "a");
	fprintf(ptr, "%lu  %lu\n", id, account_number);
	fclose(ptr);
}

unsigned long create_balance(char name[])
{
	unsigned long balance = 0;
	for (int i = 0; name[i] != '\0'; i++)
		balance += pow(name[i], 2);
	return balance;
}

unsigned long random_int_generator()
{
	time_t seed_value;
	seed_value = time(NULL);
	srand(seed_value);
	return rand();
}

char *username_finder(unsigned long id)
{
	FILE *ptr;
	unsigned long file_id;
	ptr = fopen("/storage/emulated/0/All C Programs/1) Cxxdroid Application/File IO in C/ATM/id_plus_name", "r");
	if (ptr == NULL)
	{
		printf("Server Not Reachable. Unable to access the database\n");
		exit(EXIT_FAILURE);
	}
	while (feof(ptr) == 0)
	{
		fscanf(ptr, "%lu\n", &file_id);
		fgets(username, 30, ptr);
		if (file_id == id)
		{
			fclose(ptr);
			username[(strlen(username) - 1)] = 0; //for removing \n which remain just before \0 (due to fgets() features)
			return username;
		}
	}
}

unsigned long forget_id()
{
	char name[30];
	puts("Please write your registed name properly:");
	gets(name);

	FILE *ptr;
	unsigned long id;
	char name_from_file[30];
	ptr = fopen("/storage/emulated/0/All C Programs/1) Cxxdroid Application/File IO in C/ATM/id_plus_name", "r");
	if (ptr == NULL)
	{
		perror("Unable to access the database.\n");
		exit(EXIT_FAILURE);
	}

	short check = 0;
	while (feof(ptr) == 0)
	{
		fscanf(ptr, "%lu\n", &id);
		fgets(name_from_file, 30, ptr);
		name_from_file[strlen(name_from_file) - 1] = 0;
		if (strcmp(name, name_from_file) == 0)
		{
			check++;
			fclose(ptr);
			return id;
		}
	}
	yellow('f');
	if (check == 0)
	{
		printf("No such name \"%s\" available in database.\n", name);
		exit(EXIT_FAILURE);
	}
	reset();
}

unsigned long balance_enquiry()
{
	unsigned long id;
	unsigned long balance;
	FILE *ptr;
	ptr = fopen("/storage/emulated/0/All C Programs/1) Cxxdroid Application/File IO in C/ATM/id_plus_balance", "r");

	if (ptr == NULL)
	{
		perror("Unable to access the database\n");
		exit(EXIT_FAILURE);
	}
	while (feof(ptr) == 0)
	{
		fscanf(ptr, "%lu", &id);
		fscanf(ptr, "%lu\n", &balance);
		if (id == user_id)
			return balance;
	}
}
//}