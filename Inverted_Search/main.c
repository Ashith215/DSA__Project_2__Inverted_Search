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


// main function with command-line arguments(CLA).

int main(int argc, char *argv[])
{
	// argc should be greater than 1.
	if(argc > 1)
	{
		Flist *head = NULL;
		Flist *Invalid_h = NULL;
		main_node arr[27];

		// create hash table function is called.

		create_HT(arr, 27);

		// validate command-line arguments function is called.

		if(validate_args(argc, argv, &head, &Invalid_h) == FAILURE)
		{
			printf("%s", red);
			printf("\nError: Entered files are not valid.\n");
			printf("Usage: \n");
			printf("Valid Input 	   : ./a.out <.txt file-1> <.txt file-2> ...\n");
			printf("File requirements  : Entered file should exist, non-empty and non-duplicate.\n\n");
			printf("%s", normal);
			return FAILURE;
		}
		// if invalid files are present delete Flist nodes function is called. 
		if(Invalid_h != NULL)
		{
			delete_Flist(&Invalid_h);
		}

		int create_flag = 0;
		int update_flag = 0;
		int flag = 0;
		int choice;

		do
		{
			printf("\n:::::::::::::::::::::INVERTED SEARCH MENU:::::::::::::::::::::::\n\n");
			printf("1. Create Database.\n2. Display Database.\n3. Search Database.\n4. Save Database.\n5. Update Database.\n6. Exit.\n");
			printf("\n::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n");

			printf("Enter Your Choice: ");
			scanf("%d", &choice);
					
			char f_name[min];

			printf("%s", green);
			switch(choice)
			{
				// create Database.
				case 1:
					// create database function is called.
					if(create_database(arr, head, &create_flag, update_flag, &flag, &Invalid_h) == SUCCESS)
					{
						// if => database created.
						if(flag == 1)
						{
							// if => file name entered in CLA is present in updated database.
							if(Invalid_h != NULL)
							{
								printf("%s", red);
								printf("\nAlready updated files => ");
								// print Flist function is called.
								print_Flist(Invalid_h);
								printf("%s", green);
								printf("\nDatabase successfully created files => ");
								// print created files function is called.
								print_created(head, Invalid_h);
							}
							else
							{
								// if => file name entered in CLA is not present in updated database.
								if(update_flag == 1 && Invalid_h == NULL)
								{
									printf("\nCreated database successfully of all files => ");
									// print Flist function is called.
									print_Flist(head);
								}
								else	// if => update database is not done before.
								{
									printf("\nCreated Database Successfully.\n");
								}
							}
						}
						else	// if => all file name entered in CLA is present in updated database.
						{
							printf("%s", red);
							printf("\nError: cannot create database all valid files are updated already.\n");
							printf("%s", green);
						}

						// if invalid files are present delete Flist nodes function is called. 
						if(Invalid_h != NULL)
						{
							delete_Flist(&Invalid_h);
						}
					}
					break;
				// Display Database.
				case 2:
					printf("\n");
					// display function is called.
					display(arr);
					break;
				// Search Database.
				case 3:
					printf("%s", normal);
					char str[max];
					printf("Enter the word to search: ");
					scanf("%s", str);
					printf("%s", green);

					// search function is called.
					if(search(arr, str) == FAILURE)
					{
						printf("%s", red);
						printf("\nWord -> \"%s\" is not found in database.\n%s", str, normal);
						printf("%s", green);
					}
					else
					{
						printf("\nWord -> \"%s\" is found in database.\n", str);
					}
					break;
				// Save Database.
				case 4:
					printf("%s", normal);
					printf("Enter the file name to store database: ");
					scanf("%s", f_name);
					printf("%s", green);
					
					// if => database is empty.
					if(update_flag == 0 && create_flag == 0)
					{
						printf("%s", red);
						printf("\nError: Database is not created or updated, so cannot save data.\n");
						printf("%s", green);
					}
					else
					{
						// validate file to save function is called.
						if(validate_file_to_save(f_name) == SUCCESS)
						{
							// save function is called.
							if(save(arr, f_name) == FAILURE)
							{
								return FAILURE;
							}
						}
					}
					break;
				// Update Database.
				case 5:
					printf("%s", normal);
					printf("Enter file name to update database: ");
					scanf("%s", f_name);
					printf("%s", green);

					// validate file to update function is called.
					if(validate_file_to_update(f_name) == SUCCESS)
					{
						// update function is called.
						if(update(arr, f_name, &update_flag, create_flag) == SUCCESS)
						{
							printf("\nDatabase updated successfully.\n");
						}
					}
					break;
				// Exit.
				case 6:
					printf("\nExiting...\n\n");
					break;
				// default case.
				default:
					getchar();
					printf("%s", red);
					printf("\nInvalid Choice.\n");
			}
			printf("%s", normal);
		}while(choice != 6);
		
		// if head is not NULL, then delete Flist nodes.
		if(head != NULL)
		{
			delete_Flist(&head);
		}

		// delete main nodes function is called.
		delete_main_nodes(arr);

		return SUCCESS;
	}
	else	// if argc is 1.
	{
		printf("%s", red);
		printf("\nError: Invalid argument : ");
		for(int i = 0; i < argc; i++)
		{
			printf("%s ", argv[i]);
		}
		printf("\nUsage: \n");
		printf("Valid Input 	   : ./a.out <.txt file-1> <.txt file-2> ...\n");
		printf("File requirements  : Entered file should exist, non-empty and non-duplicate.\n\n");
		printf("%s", normal);
	}
	return FAILURE;
}



