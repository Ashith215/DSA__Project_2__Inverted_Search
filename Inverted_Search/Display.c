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



// Function to display database.

void display(main_node *arr)
{
	int j = 1;
	for(int i = 0; i < 27; i++)
	{
		// if sub node is present, then main node is not empty.
		if(arr[i].s_link != NULL)
		{
			if(j == 1)
			{
				printf("-------------------------------------------------------------------------------------------------\n");
				printf("      \tIndex\tWord\t\t\tFile Count\tFile Name[Word Count]\n");
				printf("-------------------------------------------------------------------------------------------------\n");
			}
			
			main_node *tm_node = &arr[i];
			while(tm_node != NULL)
			{
				// prints counts, index, word, file count.
				printf("Word %d: %-2d\t%-20s\t%d\t\t", j, i, tm_node->word, tm_node->f_count);
				j++;
				sub_node *ts_node = tm_node->s_link;
				while(ts_node != NULL)
				{
					// prints file name and word aount.
					printf("%s[%d] ", ts_node->f_name, ts_node->w_count);
					ts_node = ts_node->link;
				}
				printf("\n");
				tm_node = tm_node->m_link;
			}	
		}
	}
	if(j != 1)
	{
		printf("-------------------------------------------------------------------------------------------------\n");
	}
	else 	// if no database is empty.
	{
		printf("%s", red);
		printf("Error: No database present.\n");
		printf("%s", green);
	}
}




