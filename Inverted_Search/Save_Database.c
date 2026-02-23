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



// Function to save database.

int save(main_node *arr, char *f_name)
{
	FILE *fp = fopen(f_name, "w");
	// if file is not created.
	if(fp == NULL)
	{
		printf("%s", red);
		printf("Error: file unable to open in write mode.\n");
		printf("%s", green);
		return FAILURE;
	}	

	for(int i = 0; i < 27; i++)
        {
		// if sub node is present. 
                if(arr[i].s_link != NULL)
                {
			// prints main node and sub node to user entered .txt file.
                        main_node *tm_node = &arr[i];
                        while(tm_node != NULL)
                        {
				// prints index, word, file count into .txt file entered by user.
				fprintf(fp, "#%d;%s;%d;", i, tm_node->word, tm_node->f_count);
                                sub_node *ts_node = tm_node->s_link;
                                while(ts_node != NULL)
                                {
					// prints file name, word count into .txt file entered by user.
					fprintf(fp, "%s;%d;", ts_node->f_name, ts_node->w_count);
                                        ts_node = ts_node->link;
                                }
				// prints # and newline into .txt file entered by user.
				fprintf(fp, "#\n");
                                tm_node = tm_node->m_link;
                        }
                }
        }
	fclose(fp);
	printf("\nSaved to Database Successfully.\n");
	return SUCCESS;
}



// Function to validate file to save database.

int validate_file_to_save(char *f_name)
{
	// if => file name has extension.
	if(strstr(f_name, ".") != NULL)
	{
		// if => file name extension is .txt.
		if(strcmp(strstr(f_name, "."), ".txt") == 0)
		{
			FILE *fp = fopen(f_name, "r");
			// if => file is present.
			if(fp != NULL)
			{
				fseek(fp, 0, SEEK_END);
				int pos = ftell(fp);
				rewind(fp);

				// File present and is not empty.
				if(pos > 1)
				{
					int op = 0;
					printf("\nDo you want to overwrite %s file (Yes - 1 / No - 0): ", f_name);
					scanf("%d", &op);
					//if => no overwriting file data.
					if(op == 0)
					{
						printf("%s", red);
						printf("\nOverwriting cancelled.\n");
						printf("%s", green);
						fclose(fp);
						return FAILURE;
					}
					else	// if => overwritting file data.
					{
						printf("\nOverwriting the \"%s\" file content.\n", f_name);
					}
				}
				
				// File present and empty.
				fclose(fp);
			}
			// file not present.
			return SUCCESS;
		}
		else	// if => file extension is not .txt.
		{
			printf("%s", red);
			printf("\nError: Entered file %s do not have .txt extension.\n", f_name);
			printf("%s", green);
		}
	}
	else		// if => file doesn't have extension.
	{
		printf("%s", red);
		printf("\nError: Entered file %s do not extension.\n", f_name);
		printf("%s", green);
	}
	return FAILURE;
}




