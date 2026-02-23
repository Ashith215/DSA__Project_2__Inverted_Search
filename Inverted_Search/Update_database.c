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



// Function to update database.

int update(main_node *arr, char *f_name, int *update_flag, int create_flag)
{
	// if => already updated database once.
	if(*update_flag == 1)
	{
		printf("%s", red);
		printf("\nDatabase already updated.\n");
		printf("%s", green);
		return FAILURE;
	}	

	// if => already created database once.
	if(create_flag == 1)
	{
		printf("%s", red);
		printf("\nError: After creating database update database not possible\n");
		printf("%s", green);
		return FAILURE;
	}

	FILE *fp = fopen(f_name, "r");
	// if => file is not present.
	if(fp == NULL)
	{
		printf("%s", red);
		printf("\nError: File is not present.\n");
		printf("%s", green);
		return FAILURE;
	}

	fseek(fp, 0, SEEK_END);
	int end_pos = ftell(fp);
	rewind(fp);
	// if => empty file.
	if(end_pos < 2)
	{
		printf("%s", red);
		printf("\nError: File is empty.\n");
		printf("%s", green);
		return FAILURE;
	}

	while(fgetc(fp) != EOF)
	{
		int index, file_count;
		char word[max];

		// reads index and main node values.
		int r1 = fscanf(fp, "%d;%[^;];%d;", &index, word, &file_count);
		if(r1 < 3)
		{
			printf("%s", red);
			printf("\nError: Updating wrong backup file.\n");
			printf("%s", green);
			fclose(fp);
			return FAILURE;
		}
		
		for(int i = 0; i < file_count; i++)
		{
			int word_count;
			char file_name[min];

			// reads sub node values.
			int r2 = fscanf(fp, "%[^;];%d;", file_name, &word_count);
			if(r2 < 2)
			{
				printf("%s", red);
				printf("\nError: Updating wrong backup file.\n");
				printf("%s", green);
				fclose(fp);
				return FAILURE;
			}
			
			for(int j = 0; j < word_count; j++)
			{
				// insert last to main node function is called.
				insert_last_to_main_node(arr, index, word, file_name);
			}
		}	
		for(int k = 0; k < 2; k++)
		{
			// skips # and new-line(\n) after each line.
			fgetc(fp);
		}
	}
	*update_flag = 1;

	fclose(fp);
	return SUCCESS;
}




// Function to validate file to update.

int validate_file_to_update(char *f_name)
{
	// if => file contains extension.
	if(strstr(f_name, ".") != NULL)
        {
		// if => file contains .txt extension.
                if(strcmp(strstr(f_name, "."), ".txt") == 0)
                {
                        FILE *fp = fopen(f_name, "r");
			// if => file is not present.
                        if(fp == NULL)
                        {
				printf("%s", red);
				printf("\nError: File is not present.\n");
				printf("%s", green);
				return FAILURE;
                        }
			// if => file is present.
			fclose(fp);
                        return SUCCESS;
                }
        }
	// if => no extention, no .txt extension.
	printf("%s", red);
	printf("\nError: File extension is not present.\n");
	printf("%s", green);
        return FAILURE;	
}





