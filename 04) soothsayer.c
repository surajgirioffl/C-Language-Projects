#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include "D:\\C Language\\All C Programs\\1) Cxxdroid Application\\Header Files\\color.h"

void terms_and_conditions();
void selection_matrix(); // for tisha yantra
void questions_list();
void save_user(char *user_name, int question_choice);
void check_user(char *user_name, int question_choice);
int calculation_part(int a, int b);
void chakra_name_finder(int chakra_no);
char chakra_name[50];
void display_result(int lucky_choice);
void save_result(char *name, int choice);
char result[400];

long numberBelow16(long number);
long randomNumber();

int main()
{
    green('f');
    terms_and_conditions();
    reset();

    char name[30];
    int question_choice;
    long lucky_choice = 0;
    int restart = 1;
    char choice_for_restart;

    red('f');
    printf("=======WELCOME TO FUTURE TELLER (भविष्यवक्ता)========\n");
    reset();
    cyan('f');
    puts("Please write your name:");
    printf("$ ");
    gets(name);
    reset();

    while (1) // for repeating the program till user need
    {
        magenta('f');
        puts("\nPlease Select your question from following: (कृपया निम्नलिखित में से अपने प्रश्न का चयन करें:)");
        questions_list(); // function to print all questions list
        printf("\nwrite your choice: (अपनी पसंद लिखें:)\n");
        scanf("%d", &question_choice);
        fflush(stdin);
        reset();

        FILE *ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\future_teller\\user_record.txt", "r");
        if (ptr != NULL && strcmp(name, "suraj") != 0 && strcmp(name, "suraj kumar giri") != 0 && strcmp(name, "suraj giri") != 0 && strcmp(name, "dipu") != 0)
            check_user(name, question_choice);
        save_user(name, question_choice);

        puts("\nPlease write any number greater than 0 peacefully after remembering The GOD (कृपया प्रभु का स्मरण करके शांतिपूर्वक किसी एक नंबर का चयन करें:)");
        Beep(1000, 2000); // Beep(frequnecy, time_in_millisecond);     //for playing a beep sound
        /*
         *removed display of selection matrix on 4th March 2022
         *Number must be greater than 0 and all process will be random
         */
        // selection_matrix(); // function to print tisha yantra
        printf("\nwrite your choice: (अपनी पसंद लिखें:)\n");
        scanf("%lu", &lucky_choice);
        fflush(stdin);
        if (lucky_choice <= 0)
        {
            red('f');
            puts("\nWrong Number Entered!. So, you are rejected\n");
            exit(EXIT_FAILURE);
        }

        /*now using random operation on 'lucky_choice' to get the number for choice */
        lucky_choice = numberBelow16(lucky_choice);

        // now checking that number returns by function is in required range or not
        if (lucky_choice <= 0 || lucky_choice > 15)
        {
            red('f');
            puts("\nSomething went wrong.\nExit code 502");
            exit(EXIT_FAILURE);
        }

        int chakra_no = calculation_part(question_choice, lucky_choice);
        chakra_name_finder(chakra_no);

        display_result(lucky_choice);
        save_result(name, question_choice);

        red('f');
        printf("\n=====Currently Mr./Mrs %s used this program %d times=====\n", name, restart);

        cyan('f');
        printf("\nFor exit press \"#\" otherwise press any key continue:\n");

        scanf("%c", &choice_for_restart);
        fflush(stdin);
        if (choice_for_restart == '#')
            break;
        restart++;
    }
    return 0;
}

void questions_list()
{
    FILE *p = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\future_teller\\questions_list.txt", "r");
    if (p == NULL)
        perror("unable to reach to file");

    yellow('f');
    while (feof(p) == 0)
    {
        char c = fgetc(p);
        printf("%c", c);
    }
    fclose(p);
    reset();
}

void selection_matrix()
{
    red('f');
    printf("\t\t|\U00000950 |13|10|07|\n");
    printf("\t\t|11|06|01|12|\n");
    printf("\t\t|05|08|15|02|\n");
    printf("\t\t|14|03|04|09|");
    reset();
}

int calculation_part(int a, int b)
{
    if (a + b <= 30)
        return a + b;
    else
        return (a + b) - 30;
}

void chakra_name_finder(int chakra_no)
{
    FILE *ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\future_teller\\chakra_list.txt", "r");
    if (ptr == NULL)
    {
        perror("Unable to open the file. Exit code 101");
        exit(-1);
    }

    int temp;
    while (feof(ptr) == 0)
    {
        fscanf(ptr, "%d", &temp);
        fgetc(ptr);
        fgets(chakra_name, 50, ptr);
        if (temp == chakra_no)
            break;
    }
    chakra_name[strlen(chakra_name) - 1] = 0;
    fclose(ptr);
}

void display_result(int lucky_choice)
{
    char file_path_details[200];
    int temp;
    sprintf(file_path_details, "D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\future_teller\\results\\%s.txt", chakra_name);
    FILE *ptr = fopen(file_path_details, "r");
    if (ptr == NULL)
    {
        perror("Unable to access database. Exit code 102");
        exit(-1);
    }

    while (feof(ptr) == 0)
    {
        fscanf(ptr, "%d", &temp);
        fgetc(ptr);
        fgets(result, 400, ptr);
        if (temp == lucky_choice)
            break;
    }
    magenta('f');
    underline();
    printf("\n====>>>>%s\n", result);
    fclose(ptr);
    reset();
}

void save_user(char *user_name, int question_choice)
{
    FILE *ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\future_teller\\user_record.txt", "a");
    fprintf(ptr, "%d\t%s\n", question_choice, user_name);
    fclose(ptr);
}

void check_user(char *user_name, int question_choice)
{
    int check = 0;
    FILE *ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\future_teller\\user_record.txt", "r");
    if (ptr == NULL)
        printf("Unable to access database.\n");

    char temp_name[50];
    int temp_no;
    while (feof(ptr) == 0)
    {
        fscanf(ptr, "%d", &temp_no);
        fgetc(ptr);
        fgets(temp_name, 50, ptr);
        temp_name[strlen(temp_name) - 1] = 0;
        if (temp_no == question_choice && strcmp(temp_name, user_name) == 0)
        {
            check++;
            break;
        }
    }
    if (check != 0)
    {
        red('f');
        printf("\nHello Mr. %s, you have asked the same question again which is not applicable. You can ask one question only once. So, Don't ask the same questiona again.\n", user_name);
        exit(-1);
    }
    fclose(ptr);
}

void terms_and_conditions()
{
    FILE *ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\future_teller\\terms_conditions.txt", "r");
    if (ptr == NULL)
    {
        perror("\nUnable to access database.");
        exit(-1);
    }
    while (feof(ptr) == 0)
    {
        char ch = fgetc(ptr);
        printf("%c", ch);
    }
    fclose(ptr);

    char choice[10];
    printf("\n$ ");
    gets(choice);
    if (strcmp(choice, "yes") == 0 || strcmp(choice, "YES") == 0 || strcmp(choice, "1") == 0)
        goto accepted;
    else
    {
        printf("\nOK. As you wish. Bye Bye...........");
        exit(0);
    }
accepted:
    fclose(ptr);
    system("cls");
}

void save_result(char *name, int choice)
{
    FILE *ptr = fopen("D:\\C Language\\All C Programs\\1) Cxxdroid Application\\File IO in C\\future_teller\\user_result.txt", "a");
    if (ptr == NULL)
    {
        perror("\nUnable to access database");
        exit(EXIT_FAILURE);
    }
    fprintf(ptr, "%s\t%d\t%s\n", name, choice, result);
    fclose(ptr);
}

/*added on 4th March 2022*/
long randomNumber()
{
    time_t seed = time(NULL);
    srand(seed);
    return rand();
}

/*take any positive number and returns a random number below 16*/
long numberBelow16(long number)
{
    if (number > 15)
    {
        number += randomNumber();
        int i = 16;
        while (i > 1)
        {
            int r = number % i;
            if (r == 0)
                i--;
            else
                return r;
        }
    }
    else
        return number;
}