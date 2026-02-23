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



// Function to search word in database.

int search(main_node *arr, char *str)
{
	int index, flag = 0;
	// if first character is uppercase.
	if(str[0] >= 'A' && str[0] <= 'Z')
	{
		index = str[0] - 'A';
	}	// if first character is lowercase.
	else if(str[0] >= 'a' && str[0] <= 'z')
	{
		index = str[0] - 'a';	
	}
	else	// if first character is not uppercase or lowercase.
	{
		index = 26;
	}
        
	// if sub node is present, then main node is not empty.
	if(arr[index].s_link != NULL)
        {
		// found in main node.
                main_node *tm_node = &arr[index];
                while(tm_node != NULL)
                {
			// if => word is found, then print main node and sub node details.
			if(strcmp(tm_node->word, str) == 0)
			{
				flag = 1;
        			printf("\n-------------------------------------------------------------------------------------------------\n");
                		printf(" Index\tWord\t\t\tFile Count\tFile Name[Word Count]\n");
        			printf("-------------------------------------------------------------------------------------------------\n");
                               	printf(" %-2d\t%-20s\t%d\t\t", index, tm_node->word, tm_node->f_count);
                               	sub_node *ts_node = tm_node->s_link;
                               	while(ts_node != NULL)
                               	{
                               	        printf("%s[%d] ", ts_node->f_name, ts_node->w_count);
                               	        ts_node = ts_node->link;
                               	}
                               	printf("\n");
			}
                        tm_node = tm_node->m_link;
                }
	}

	if(flag == 1)
	{
       		printf("-------------------------------------------------------------------------------------------------\n");
		return SUCCESS;
	}

	// word not found in any of the main node.
	return FAILURE;
}




