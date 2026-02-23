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



// Function to validate command-line arguments.

int validate_args(int argc, char *argv[], Flist **head, Flist **Invalid_h)
{
	for(int i = 1; i < argc; i++)
	{
		int Invalid_flag = 1;
		
		// if => file extension is present.
		if(strstr(argv[i], ".") != NULL)
		{
			// if => file extension is ".txt".
			if(strcmp(strstr(argv[i], "."), ".txt") == 0)
			{
				FILE *fp = fopen(argv[i], "r");

				// if => file present.
				if(fp != NULL)
				{
					fseek(fp, 0, SEEK_END);
					int end_pos = ftell(fp);
					rewind(fp);
					// file is not empty.
					if(end_pos > 1)
					{
						int flag = 0;
						for(int j = 1; j < i; j++)
						{
							// if file is duplicate, then update flag to 1 and break inner for loop.  
							if(strcmp(argv[j], argv[i]) == 0)
							{
								flag = 1;
								break;	
							}
						}	

						// if file is not duplicate, not empty, file is present and extension is .txt, then valid.
						if(flag == 0)
						{
							Invalid_flag = 0;
							// valid files are inserted.
							insert_last_to_Flist(argv[i], head);
						}
					}
					fclose(fp);
				}
			}
		}		
		// invalid files are inserted.
		if(Invalid_flag == 1)
		{
			insert_last_to_Flist(argv[i], Invalid_h);
		}
	}
	// prints invalid files if present.
	if((*Invalid_h) != NULL)
	{
		printf("%s", red);
		printf("\nInvalid / duplicate / empty / non-existent files => ");
		print_Flist(*Invalid_h);
		printf("%s", normal);
	}
	// if no valid files are present, then return FAILURE.
	if((*head) == NULL)
	{
		return FAILURE;
	}
	// prints valid files if present.
	printf("%s", green);
	printf("\nValid files => ");
	print_Flist(*head);
	printf("%s", normal);
	return SUCCESS;
}




// Function to insert Flist node to last. 

int insert_last_to_Flist(char *f_name, Flist **head)
{
	// create new node.
	Flist *new = malloc(sizeof(Flist));
	if(new == NULL)
	{
		return FAILURE;
	}
	strcpy(new->f_name,f_name);
	new->link = NULL;
	// if no node is present.
	if((*head) == NULL)
	{
		*head = new;
	}
	else	// if node is present.
	{
		Flist *temp = *head;
		while(temp->link != NULL)
		{
			temp = temp->link;
		}
		temp->link = new;
	}
	return SUCCESS;
}



// Function to print Flist.

void print_Flist(Flist *head)
{
	// if no node is present.
	if(head == NULL)
	{
		printf("%s", red);
		printf("List is Empty.\n");
		printf("%s", normal);
	}
	else	// if node is present.
	{
		while(head != NULL)
		{
			printf("\"%s\" ", head->f_name);
			head = head->link;
		}
		printf("\n");
	}
}




// Function to delete Flist nodes.

int delete_Flist(Flist **head)
{
	// if no node is present.
	if((*head) == NULL)
	{
		printf("%s", red);
		printf("Error: List is empty, so cannot delete nodes.\n");
		printf("%s", normal);
		return FAILURE;
	}	
	else	// if node is present.
	{
		Flist *prev;
		while((*head) != NULL)
		{
			prev = *head;
			*head = (*head)->link;
			free(prev);
		}
	}
}




// Function to delete main nodes and sub nodes.

void delete_main_nodes(main_node *arr)
{
	for(int i = 0; i < 27; i++)
	{
		// if sub node is present, then main node is also present.
		if(arr[i].s_link != NULL)
		{
			// delete main nodes and sub nodes.
			main_node *tm_node = &arr[i];
			main_node *prev_m;
			int flag = 0;
			while(tm_node != NULL)
			{
				// delete sub nodes.
				sub_node *ts_node = tm_node->s_link;
				sub_node *prev;
				while(ts_node != NULL)
				{
					prev = ts_node;
					ts_node = ts_node->link;
					free(prev);
				}
				// cannot delete first node, so skip first main node.
				if(flag == 0)
				{
					flag = 1;
					tm_node = tm_node->m_link;
				}
				else 	// if => not first node, then delete main nodes.
				{
					prev_m = tm_node;
					tm_node = tm_node->m_link;
					free(prev_m);
				}
			}
			// update first node structure members.
			arr[i].m_link = NULL;
			arr[i].s_link = NULL;
			arr[i].f_count = 1;
			strcpy(arr[i].word, "\0");
		}
	}
}



