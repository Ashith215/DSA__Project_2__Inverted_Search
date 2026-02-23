/*
 *
 *      Name            :       Ashith P Amin
 *
 *      Date            :       23 / 12 / 2025
 *
 *      Description     :       Inverted Search Project
 *
 *                              1. Validation:
 *                                      -> argc value should be greater than 1.
 *                                      -> After 1st arguments remaining arguments should be .txt files.
 *                                      -> .txt file should exist, non-duplicate, non-empty and extension should be .txt.
 *                                      -> If all above cases are true for a file, then its a valid file and invalid files are skipped.
 *
 *                              2. Create Database:
 *                                      -> If no valid files are present, then print error.
 *                                      -> Create database can only be done once by using inputs from command-line.
 *                                      -> If update database is done previously.
 *                                      -> Then files which already present and also present in CLA inputs are skipped.
 *                                      -> For remaining files which are not present database is created.
 *                                      -> If no update is done previously, then valid files database is created.
 *
 *                              3. Display Database:
 *                                      -> Displays database created with index, word, file count, file name and word count.
 *
 *                              4. Search Database:
 *                                      -> Word is entered by user first, if word is present in database.
 *                                      -> Then index, word, file count, file name and word count is printed only of that word.
 *                                      -> If not present, then prints word not found.
 *
 *                              5. Save Database:
 *                                      -> First user enters .txt file name to save the data present in database.
 *                                      -> Then validation is done for that file.
 *                                      -> Entered file should have extension .txt.
 *                                      -> If file is already present with some data, then asks user whether to overwrite or not.
 *                                      -> If choosen overwrite, then the files data is overwritten by database data.
 *                                      -> If file is not present and if file is empty, then directly data is saved.
 *
 *                              6. Update Database:
 *                                      -> If database is created, then update database is not possible.
 *                                      -> Update cannot be done more than once.
 *                                      -> User entered file should contain saved database data to update else error is printed.
 *
 *                              7. Exit:
 *                                      -> Exited after freeing the all allocated memories.
 *
 */








#include "Inverted_search.h"


// Function to create database.

int create_database(main_node *arr, Flist *head, int *create_flag, int update_flag, int *flag, Flist **Invalid_h)
{
	// if create database is already done once.
	if(*create_flag == 1)
	{
		printf("%s", red);
		printf("\nAlready Database is Created.\n");
		printf("%s", green);
		return FAILURE;
	}

	// if no valid files present.
	if(head == NULL)
	{
		printf("%s", red);
		printf("\nNo valid files are present to create database.\n");
		printf("%s", green);
		return FAILURE;
	}

	// if valid files present.
	while(head != NULL)
	{
		FILE *fp = fopen(head->f_name, "r");
		if(fp == NULL)
		{
			return FAILURE;
		}
		
		fseek(fp, 0, SEEK_END);
		int pos = ftell(fp);
		rewind(fp);
		char c;
		int check = 0;
		while(1)
		{
			char str[pos];
			fscanf(fp, "%s", str);
			
			int end = ftell(fp);
			// if file pointer reaches End Of File, then break the loop.
			if(end == pos)
			{
				break;
			}
			
			int ind;
			// if first character is uppercase.
			if(str[0] >= 'A' && str[0] <= 'Z')
			{
				ind = str[0] - 'A';
			} 	// if first character is lowercase.
			else if(str[0] >= 'a' && str[0] <= 'z')
			{
				ind = str[0] - 'a';
			}
			else	// if first character is not uppercase or lowercase.
			{
				ind = 26;
			}

			// if update database is done before creating database.
			if(update_flag == 1 && check == 0)
			{
				check = 1;
				// validate to create database after update function is called and if not valid then break inner loop.
				if(validate_to_create_database_after_update(arr, ind, str, head->f_name, Invalid_h) == FAILURE)
				{
					break;
				}
			}
			*flag = 1;
			// insert last to main node function is called.
			insert_last_to_main_node(arr, ind, str, head->f_name);
		}
		fclose(fp);
		head = head->link;
	}
	*create_flag = 1;
	return SUCCESS;
}




// create hash table function is called.

void create_HT(main_node *arr, int size)
{
	// creating empty main node.
	for(int i = 0; i<size; i++)
	{
		arr[i].f_count = 1;
		arr[i].m_link = NULL;
		arr[i].s_link = NULL;	
	}
}




// insert last to main node function is called.

int insert_last_to_main_node(main_node *arr, int index, char *str, char *f_name)
{
	// case - 1 => No node.
	
	if(arr[index].s_link == NULL)
	{
		// empty main node word is updated.
		strcpy(arr[index].word, str);
		// new sub node is created.
		sub_node *new = malloc(sizeof(sub_node));
		if(new == NULL)
		{
			return FAILURE;
		}

		new->w_count = 1;
		strcpy(new->f_name, f_name);
		new->link = NULL;
		arr[index].s_link = new;
		return SUCCESS;
	}

	// case - 2 => Word present in main node.
	
	sub_node *ts_node;
	sub_node *prevs_node;
	main_node *tm_node = &arr[index];
	main_node *prevm_node = NULL;
	while(tm_node != NULL)
	{
		// if word is found.
		if(strcmp(tm_node->word, str) == 0)
		{
			ts_node = tm_node->s_link;
			while(ts_node != NULL)
			{
				// if file name is found.
				if(strcmp(ts_node->f_name, f_name) == 0)
				{
					(ts_node->w_count)++;
					return SUCCESS;
				}
				prevs_node = ts_node;
				ts_node = ts_node->link;
			}
			// new sub node is created.
			sub_node *new = malloc(sizeof(sub_node));
			if(new == NULL)
			{
				return FAILURE;
			}
			new->w_count = 1;
			strcpy(new->f_name, f_name);
			new->link = NULL;
			prevs_node->link = new;
			(tm_node->f_count)++;
			return SUCCESS;
		}
		prevm_node = tm_node;
		tm_node = tm_node->m_link;
	}	


	// case - 3 => Word not present in any of the created main node. 
	
	// new main node is created.
	main_node *new_m = malloc(sizeof(main_node));
	if(new_m == NULL)
	{
		return FAILURE;
	}
	new_m->f_count = 1;
	strcpy(new_m->word, str);
	new_m->m_link = NULL;

	// new sub node is created.
	sub_node *new_s = malloc(sizeof(sub_node));
	if(new_s == NULL)
	{
		return FAILURE;
	}
	new_s->w_count = 1;
	strcpy(new_s->f_name, f_name);
	new_s->link = NULL;

	new_m->s_link = new_s;
	// if previous node is NULL.
	if(prevm_node == NULL)
	{
		arr[index].m_link = new_m;
	}
	else // if previous node is not NULL.
	{
		prevm_node->m_link = new_m;
	}
	return SUCCESS;
}





// validate to create database after update function is called.

int validate_to_create_database_after_update(main_node *arr, int index, char *str, char *f_name, Flist **Invalid_h)
{
	// case - 1 => if empty main node.
	
	if(arr[index].s_link == NULL)
	{
		return SUCCESS;
	}

	// case - 2 => if main node is not empty.
	
	sub_node *ts_node;
	main_node *tm_node = &arr[index];
	while(tm_node != NULL)
	{
		// if word is found.
		if(strcmp(tm_node->word, str) == 0)
		{
			ts_node = tm_node->s_link;
			while(ts_node != NULL)
			{
				// if file name is found then insert last to invalid Flist and return FAILURE.
				if(strcmp(ts_node->f_name, f_name) == 0)
				{
					insert_last_to_Flist(f_name, Invalid_h);
					return FAILURE;
				}
				ts_node = ts_node->link;
			}
		}
		tm_node = tm_node->m_link;
	}

	// case - 3 => if file name not present in all available sub nodes of main nodes at index.

	return SUCCESS;
}




// Function to print created.

void print_created(Flist *head, Flist *I_h)
{
	// if both head and I_h is not NULL.
	if(head != NULL && I_h != NULL)
	{
		while(head != NULL)
		{
			Flist *temp = I_h;
			int flag = 1;
			while(temp != NULL)
			{
				// if file name in head matches with file name in I_h, then update flag to 0.
				if(strcmp(head->f_name, temp->f_name) == 0)
				{
					flag = 0;
				}
				temp = temp->link;
			}
			// if flag is 1.
			if(flag == 1)
			{
				printf("\"%s\" ", head->f_name);
			}
			head = head->link;
		}
	}
	printf("\n");
}




