#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define EXTENDED 10
#define BASE 20
#define NAME 50



/*structure decleration */
typedef struct name
{
	char call[NAME];
	struct name* next;
}name;


/*functions decleration */
name* name_position(name* curr, name* head);
char* file_directory(char* path, int number);
void free_func(name* head);
int check_len(char* current_name);


int main()
{
	char* filepathone;
	char* filepathtwo;

	char ch, ch_two;
	char current_name[NAME];
	int maxlen = NAME;
	int j = 0;
	int len = BASE;
	name* head = NULL;

	filepathone = malloc(sizeof(char) * len); /*make sure free the memory*/
	if (filepathone == NULL)
	{
		printf("Memory allocation failure.\n");
		return 1;
	}
	filepathtwo = malloc(sizeof(char) * len); /*make sure free the memory*/
	if (filepathtwo == NULL)
	{
		printf("Memory allocation failed.\n");
		free(filepathone);
		return 1;
	}

	filepathone = file_directory(filepathone, 1); /*get from user the directory of the file*/
	if (filepathone == NULL)
	{
		printf("Memory allocation failed.\n");
		free(filepathtwo);
		return 1;
	}
	filepathtwo = file_directory(filepathtwo, 2);/*get from user the directory of the file*/
	if (filepathtwo == NULL)
	{
		printf("Memory allocation failed.\n");
		free(filepathone);
		return 1;
	}


	FILE* f1 = NULL;
	f1=fopen(filepathone, "r");/*make sure that the directory is correct*/
	
	while (f1 == NULL)
	{
		printf("file 1 could not be open.\n");
		filepathone = file_directory(filepathone, 1);
		FILE* f1 = fopen(filepathone, "r");
	}
	FILE* f2 = NULL;
	f2=fopen(filepathtwo, "r");/*make sure that the directory is correct*/
	
	while (f2 == NULL)
	{
		printf("file 2 could not be open.\n");
		filepathtwo = file_directory(filepathtwo, 2);
		
		FILE* f2 = fopen(filepathtwo, "r");
	}

	ch = fgetc(f1);
	j = 0;

	char curr_call[NAME];
	while (ch != EOF) /*reading from file 1*/
	{
		name* curr = malloc(sizeof(name));
		if (curr == NULL)
		{
			free_func(head);
			printf("Memory allocation failure.\n");
			fclose(f1);
			fclose(f2);
			free(filepathone);
			free(filepathtwo);
			return 1;
		}
		curr->next = NULL;
		while (ch != EOF && ch != '\n' && ch != ' ')
		{
			curr_call[j++] = ch;
			ch = fgetc(f1);
		}
		curr_call[j] = '\0';
		strcpy(curr->call, curr_call);
		head = name_position(curr, head);
		j = 0;
		while (ch == '\n' || ch == ' ')
		{
			ch = fgetc(f1);
		}
	}

	ch_two = fgetc(f2);
	j = 0;
	while (ch_two != EOF) /*reading from file 2*/
	{
		name* curr2 = malloc(sizeof(name));
		if (curr2 == NULL)
		{
			free_func(head);
			printf("Memory allocation failure.\n");
			fclose(f1);
			fclose(f2);
			free(filepathone);
			free(filepathtwo);
			return 1;
		}
		curr2->next = NULL;
		while (ch_two != EOF && ch_two != '\n' && ch_two != ' ')
		{
			curr_call[j++] = ch_two;
			ch_two = fgetc(f2);
		}
		curr_call[j] = '\0';
		strcpy(curr2->call, curr_call);
		head = name_position(curr2, head);
		j = 0;
		while (ch_two == '\n' || ch_two == ' ')
		{
			ch_two = fgetc(f2);
		}

	}

	/*writing to the output file*/
	
	name* dup = head;
	FILE* f3 = fopen("output.txt", "w");
	int i = 0,name_len=0;
	while (head != NULL)       
	{
		strcpy(current_name, head->call);
		i = 0;
		name_len = check_len(current_name);
		for (i = 0; i < name_len; i++)
		{
			ch = current_name[i];
			fwrite(&ch, sizeof(char), 1, f3);
		}
		ch = '\0';
		fwrite(&ch, sizeof(char), 1, f3);
		ch = '\n';
		fwrite(&ch, sizeof(char), 1, f3);
		head = head->next;

	}
	free_func(dup);
	free(filepathone);
	free(filepathtwo);
	fclose(f1);
	fclose(f2);
	fclose(f3);

	return 0;

	}





/*functions*/

char* file_directory(char* path, int number)
{
	printf("Please enter file directory of the %d's file including the name of the file and its type:\n", number);
	char c;
	int len = BASE, i = 0;
	c = getchar();
	char* cpy = path;
	while (c != '\n')
	{
		path[i] = c;
		i += 1;
		if (i >= len)
		{
			len += EXTENDED;
			path = realloc(path, len);
			if (path == NULL)
			{
				printf("Memory allocation failure.\n");
				return NULL;
			}
		}
		c = getchar();
	}
	path[i] = '\0';
	return path;
}


name* name_position(name* curr, name* head)
{
	name* ptr = head;   
	name* prev = NULL;   
	int val = 0;        
	if (head == NULL)
	{
		head = curr;
		return head;
	}
	val = strcmp(curr->call, ptr->call);
	while (ptr != NULL && val >= 0)
	{
		prev = ptr;
		ptr = ptr->next;
		if (ptr != NULL)
		{
			val = strcmp(curr->call, ptr->call);
		}		
	}
	if (prev == NULL)
	{
		curr->next = head;
		head = curr;
	}
	else
	{
		prev->next = curr;
		curr->next = ptr;
	}
	return head;
}



void free_func(name* head)
{
	if (head == NULL)
	{
		return;
	}
	free_func(head->next);
	free(head);
}


int check_len(char* current_name)
{
	int i = 0;
	char ch;
	ch = current_name[i];
	while (ch != '\0')
	{
		ch = current_name[i++];
		
	}
	return i;
}