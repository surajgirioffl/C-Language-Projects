#include <stdio.h>
int main()
{
	int a, b, c, e, i;
	char d;
	float f[100], s = 0;

	printf("WELCOME TO TOTAL MATHS SOLUTION");
	printf("\n\nselect the following as per your need.");
	printf("\n1 for class I to X\n2 for Class XI and XII\n");
	printf("\nselect your choice: ");
	scanf("%d", &a);
	switch (a)
	{
	case 1:
		//For class I to X
		printf("\n\nselect the following as per your need  \n1 - For Arithmetic \n2 - For Mensuration \n3 - For Algebra \n4 - For Statics \n5 - For Probablity \n6 - For Trigonomery \n7 - For co-ordinate Geometry \n8 - For Computing \n9 - For Geometry \n10- For Conversion \n11- For squre and squre Root \n12- For cube and cube root \n12- For percentage");
		printf("\nPlease select your choice: ");
		scanf("%d", &b);
		switch (b)
		{
		case 1: //Arithmatic
			printf("\nselet the following operations as per your need \n1 - For Simple Calculator \n2 - For Find Which Types of number entered \n3 - For Find paricular types of number between given two numbers or say range ");
			printf("\nPlease select your choice: ");
			scanf("%d", &c);
			switch (c)
			{
			case 1: //calculator
				printf("\nselect the following as per your need");
				printf("\n + - For sum of n numbers: \n - - For subtraction of n number \n d - For difference of two numbers \n x - For multiply of n numbers \n / - For division of two numbers");
				printf("\nPlease write your choice: ");
				scanf(" %c", &d);
				switch (d)
				{
				case '+':
					printf("\nwrite the nubers of numbers you want to add:  ");
					scanf("%d", &e);
					for (i = 1; i <= e; i++)
					{
						printf("\nwrite the number: ");
						scanf("%f", &f[i]);
						s = s + f[i];
					}
					printf("\nsum of given numbers are %f", s);
					break;

				case '-':
					printf("\nwrite the numbers of number you want to subtract:  ");
					scanf("%d", &e);
					for (i = 0; i < e; i++)
					{
						printf("\nwrite the number: ");
						scanf("%f", &f[i]);
						if (i == 0)
						{
							s = s + f[i];
						}
						s = s - f[i];
					}
					printf("\nsubtraction of given numbers is %f", s);
					break;
				case 'd':
					printf("\nwrite the 1st number: ");
					scanf("%f", &f[1]);
					printf("\nwrite the 2nd number: ");
					scanf("%f", &f[2]);
					if (f[1] > f[2])
						printf("\nDifference of given number is %f", f[1] - f[2]);
					else
						printf("\nDifference of given number is %f", f[2] - f[1]);
					if (f[1] == f[2])
						printf("\nDifference of given number is 0");
					break;
				case 'x':
					printf("\nwrite the number of numbers you want to multiply: ");
					scanf("%d", &e);
					s = 1;
					for (i = 0; i < e; i++)
					{
						printf("\nwrite the number: ");
						scanf("%f", &f[i]);
						s = s * f[i];
					}
					printf("\nmultiplication of given numbers are %f", s);
					break;

				case '/':
					printf("\nwrite the 1st number: ");
					scanf("%f", &f[1]);
					printf("\nwrite the 2nd number: ");
					scanf("%f", &f[2]);
					printf("\nQuotient after diving %f by %f is %f", f[1], f[2], f[1] / f[2]);
					printf("\nQuotient after diving %f by %f is %f", f[2], f[1], f[2] / f[1]);
					break;

				default:
					printf("\nwrong chice selected. Please select correct one");
				}
				break;

			case 2: //To check the type of number that is entered by user
				printf("\nWrite the number: ");
				scanf("%d", &e);
				if (e == 0 || e < 0 || e > 0)
					printf("\n %d is an Integer", e);
				if (e > 0)
				{
					printf("\n %d is a Natural Number", e);
					printf("\n %d is a Positive Number", e);
				}
				if (e == 0 || e > 0)
					printf("\n %d is a Whole Number", e);
				if (e < 0)
					printf("\n %d is a Negative Number", e);
				if (e == 0)
				{
					printf("\n %d is a Neither Negative nor Positive Number", e);
					printf("\n %f is divided by all numbers. e.g 0 is divisible by 2 and 3 also, so it is even when divisible by 2 and odd when divisible by 3. So we don't take 0 as odd or even.", f[1]);
				}
				if (e == 2)
					printf("\n%d is a prime Number", e);
				if (e > 2)
				{
					f[2] = 0; //use in last to check prime with the use of composite
					for (i = 2; i < e; i++)
					{
						f[1] = e % i;
						if (f[1] == 0)
						{
							if (e > 3)
								printf("\n %d is a composite Number", e);
							f[2] = 1;
							break;
						}
					}
					if (f[2] == 0)
						printf("\n %d is a Prime Number", e);
				}
				if (e % 2 == 0 && e > 0)
					printf("\n %d is a Even Number", e);
				if (e % 2 != 0 && e > 0)
					printf("\n %d is a Odd Number", e);
				for (i = 1; i < e; i++)
				{
					f[3] = e % i;
					if (f[3] == 0)
						s = s + i;
				}
				if (s == e && e > 0)
					printf("\n %d is a Perfect Number", e);

				if (e == 0 || e < 0 || e > 0)
					printf("\n %d is a Rational Number", e);
				break;

			case 3: //To find particular types of number between given range

			default:
				printf("\nwrong choice. Please select correct choice");
			}

			break;
		default:
			printf("\nwrong choice. Please select correct choice");
		}

		break;
	default:
		printf("\nwrong choice. Please select correct choice");
	}
	return 0;
	getch();
}