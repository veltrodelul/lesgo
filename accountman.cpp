#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_strings(char str1[20],char str2[20],int size,int size2)
{
	if (size != size2)
		return 0;
	for (int i = 0; i < size; i++)
		if (str1[5+i] != str2[i])
			return 0;
	return 1;
}

int check_file(FILE* check, char checked_string[20])
{
	char check_string[50];

	FILE* checkfile;
	checkfile = check;
	if (checkfile != NULL)
	{
		fseek(checkfile, 0, SEEK_SET);
		while(fgets(check_string,sizeof(check_string),checkfile))
		{
			if (strncmp(check_string, "user: ", 5) == 0)
			{

				int i = 5;
				int check_string_size = 0;
				int checked_string_size = 0;
				int j = 0;
				while ((check_string[i] >= 'a' && check_string[i] <= 'z') || (check_string[i] >= 'A' && check_string[i] <='Z') || (check_string[i] >= '0' && check_string[i] <= '9'))
					i++;
				while ((checked_string[j] >= 'a' && checked_string[j] <= 'z' ) || (checked_string[j] >= 'A' && checked_string[j] <= 'Z') || (checked_string[j] >= '0' && checked_string[j] <= '9'))
					j++;
				checked_string_size = j;
				check_string_size = i - 5;
			    if (compare_strings(check_string, checked_string, check_string_size, checked_string_size))
					return 1;
			}
		}
	}
	return 0;
}

int check_account(char username_login[20],char password_login[20],FILE* checkfile)
{

	char user_check[20];
	char pass_check[20] ;
	fseek(checkfile, 0, SEEK_SET);
	int ok = 0;
	while(fgets(user_check, sizeof(user_check), checkfile))
	{
		int i = 5;
		int user_check_size = -5;
		while ((user_check[i] >= 'a' && user_check[i] <= 'z') || (user_check[i] >= 'A' && user_check[i] <= 'Z') || (user_check[i] >= '0' && user_check[i] <= '9'))
			i++;
		user_check_size += i;

		if (ok == 1)
		{
			if (compare_strings(user_check, password_login, user_check_size, strlen(password_login)) && !feof(checkfile))
			{
				return 1;
			}
		}


		if (compare_strings(user_check, username_login, user_check_size, strlen(username_login)) && !feof(checkfile))
		{
			ok = 1;
		}		
	}
	return 0;




}

void log(FILE* dafile)
{
	char username_login[20];
	char password_login[20];

	printf("Log in :\n");
	printf("username: ");
	scanf_s("%s", &username_login, 20);
	strcat_s(username_login, "\0");

	printf("password: ");
	scanf_s("%s", &password_login, 20);
	strcat_s(username_login, "\0");

	if(check_account(username_login, password_login,dafile))
	{
		puts("The credentials are correct");
	}
	else
		puts("Username or password is wrong");
}

void reg(FILE* file_output)
{
	char username_register[50];
	printf_s("Register: \n");
	printf_s("username: ");
	scanf_s("%s",&username_register, 50);

	strcat_s(username_register,"\0");

		
	while (strlen(username_register) > 15)
	{
		puts("username can't be longer than 15 characters, try again");
		printf("username: ");
		scanf_s("%s", &username_register, 20);
	}


	while (check_file(file_output, username_register) == 1)
	{
		puts("username already used, try again\n");
		printf("username: ");
		scanf_s("%s",&username_register,50);
		while (strlen(username_register) > 15)
		{
			puts("username can't be longer than 15 characters, try again");
			printf("username: ");
			scanf_s("%s", &username_register, 20);
		}

	}

	printf_s("password: ");
	char password_register[20];
	scanf_s("%s", &password_register, 20);
	
	puts("You have been registered");

	fprintf_s(file_output, "user:%s\n", username_register);
	fprintf_s(file_output, "pass:%s\n", password_register);

	log(file_output);
}

int main()
{
	FILE* file_input;
	fopen_s(&file_input, "input.txt", "r");

	FILE* file_output;
	fopen_s(&file_output, "output.txt", "a+");
	if (file_output == NULL)
		exit;

	printf_s("Press 0 for login / Press 1 for register\n");

	int login_choice;
	scanf_s("%d", &login_choice);

	if (login_choice == 1)
	{
		reg(file_output);
	}
	else
	{
		log(file_output);
	}
	


}