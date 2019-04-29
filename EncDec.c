#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
/*........
..........A project by Anshul Singh Pilkhwal........ 
											........*/
FILE *fp;

char text[10000];
char encText[10000];
char decText[10000];
char pass[4];
char filename[20];

void hinput();
void ninput();
void encr();
void decr();
void intro();
void input();
void filedec(char file[]);
void encode(char str[]);
void decode(char str[]);


void ninput()
{
	int i=0;
	printf("Enter The Message\n");
	scanf(" %[^\n]s",&text);
	encr();
}


void hinput()
{
int i = 0;
printf("Enter The Message \n");
	
	for(i=0; i<10000; i++)
    {
        text[i] = getch();
        if(text[i]==13)
        {
	break;
		}
		else if (text[i]==8)
		{
			printf ("\b \b");
		}
		else
		{
			printf("*");
		}
    }
	encr();
}


void encr()
{
	int i=0;
	printf("\nEnter a 4 Character passcode to protect.\n");
	for(i=0; i<4; i++)
	{
		pass[i] = getch();
		if(pass[i]==13)
        {
	break;
		}
		else if (pass[i]==8)
		{
			printf ("\b \b");
			i -= 2;
		}
		else
		{
			printf("*");
		}
	}
	encode(text);
}


void decr()
{
	int i;
	char code[4], ch;
	printf ("\n\nPress 'd' to decrypt or any other key to exit: ");
	ch = getch();
	switch (ch)
	{
		case 'd':
			{
				int flag=0;
				printf("\nEnter Your Password: ");
				for(i=0; i<4; i++)
				{
					code[i] = getch();
					if(code[i]==13)
			        {
				break;
					}
					else if (code[i]==8)
					{
						printf ("\b \b");
						i -= 2;
					}
					else
					{
						printf("*");
					}
				}
				for(i=0;i<4;i++)
				{
					if(pass[i] != code[i])
					{
						flag = 1;
						break;
					}
				}
				if (flag == 1)
				{
					printf ("\nWrong password!");
					exit(0);
				}
				else
				{
					decode(encText);
				}
				break;
			}
		default:
			{
				exit(0);
			}
	}
}


void main()
{
	intro();
	printf ("\n\tProgram terminated.");
} 


void intro()
{
	char ch;
	printf ("\t \t \t ENCRYPTION v0.1.4 %c\n");
	printf ("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
	printf ("\nPress 'e' to encrypt data or 'd' to decrypt from file: ");
	scanf ("%c", &ch);
	if (ch == 'e' || ch == 'E')
	{
		input();
	}
	else if (ch == 'd' || ch == 'D')
	{
		printf ("\nEnter filename: ");
		scanf (" %s", filename);
		filedec(filename);
	}
}


void input()
{
	char choice;
	printf("\n--------------------------------------------------------------------------\n");
	printf("1.Normal Input\n2.Hidden Input\n0.Close\n");
	printf("--------------------------------------------------------------------------\n");
	printf("Press Corresponding number to continue:");
	scanf("%d",&choice);
	if(choice==1)
	{
		ninput();
	}
	else if(choice==2)
	{
		hinput();
	}
	else if(choice==0)
	{
		exit(0);
	}
	else
	{
		printf("Invalid Selection \n");		
		exit(0);
	}
	decr();
}


void filedec(char file[])
{
	char pw[4] = "";
	int i = 0;
	printf ("Give the Decryption Pin: ");
	for(i=0; i<4; i++)
	{
		pw[i] = getch();				//Works only for 64-bit systems
		if(pw[i] == 13)
        {
	break;
		}
		else if (pw[i] == 8)
		{
			printf ("\b \b");
			i -= 2;
		}
		else
		{
			printf("*");
		}
	}

	if(strcmp("1221", pw) != 0)
	{
		printf ("\nWrong Passcode! Access Denied\n");
		exit(0);
	}

	fp = fopen(file, "r");
	if (fp == NULL)
	{
		printf ("\nFile does not exit");
		exit(0);
	}
	fscanf (fp, "%s", text);
	decode (text);
}


void encode(char str[])
{
	int i, len, length;
	len = length = strlen(str);
	int lensqr;
	lensqr=  pow(len, 2) - 50;
	for (i=0; i<length; i++)
	{
		encText[i] = (char)(str[i] + lensqr);
		lensqr -= 3;
	}
	printf ("\nEncoded text:\n%s", encText);
	fp=fopen("enc.txt","w");
	fprintf(fp,"%s", encText);
	fclose(fp);
}


void decode(char str[])
{
	int len, length;
	len = length = strlen(str);
	int lensqr = pow(len, 2) - 50;
	int i;
	for (i=0; i<length; i++)
	{
		decText[i] = (char)(str[i] - lensqr);
		lensqr -= 3;
	}	
	printf ("\nDecoded text:\n%s", decText);
}

