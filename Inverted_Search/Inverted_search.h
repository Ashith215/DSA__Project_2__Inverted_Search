/*
 *
 * 	Name		:	Ashith P Amin
 *
 * 	Date		:	23 / 12 / 2025
 *	
 *	Description	:	Inverted Search Project
 *				
 *				1. Validation:
 *					-> argc value should be greater than 1.
 *					-> After 1st arguments remaining arguments should be .txt files.
 *					-> .txt file should exist, non-duplicate, non-empty and extension should be .txt.
 *					-> If all above cases are true for a file, then its a valid file and invalid files are skipped.
 *
 *				2. Create Database:
 *					-> If no valid files are present, then print error.
 *					-> Create database can only be done once by using inputs from command-line.
 *					-> If update database is done previously. 
 *					-> Then files which already present and also present in CLA inputs are skipped.    
 *					-> For remaining files which are not present database is created.
 *					-> If no update is done previously, then valid files database is created.
 *
 *				3. Display Database:
 *					-> Displays database created with index, word, file count, file name and word count.
 *
 *				4. Search Database:
 *					-> Word is entered by user first, if word is present in database.
 *					-> Then index, word, file count, file name and word count is printed only of that word.
 *					-> If not present, then prints word not found.
 *
 *				5. Save Database:
 *					-> First user enters .txt file name to save the data present in database.
 *					-> Then validation is done for that file.
 *					-> Entered file should have extension .txt.
 *					-> If file is already present with some data, then asks user whether to overwrite or not.
 *					-> If choosen overwrite, then the files data is overwritten by database data.
 *					-> If file is not present and if file is empty, then directly data is saved.
 *
 *				6. Update Database:
 *					-> If database is created, then update database is not possible.
 *					-> Update cannot be done more than once.
 *					-> User entered file should contain saved database data to update else error is printed.
 *
 *				7. Exit:
 *					-> Exited after freeing the all allocated memories.  
 *
 */









#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// All macro's

#define SUCCESS 0
#define FAILURE -1
#define min 100
#define max 100000
#define red "\x1b[31m"
#define green "\x1b[32m"
#define normal "\x1b[m"


// Flist structure.

typedef struct Flist
{
	char f_name[min];
	struct Flist *link;
}Flist;


// sub_node structure.

typedef struct sub_node
{
	char f_name[min];
	int w_count;
	struct sub_node *link;
}sub_node;


// main_node structure.

typedef struct main_node
{
	int f_count;
	char word[max];
	struct main_node *m_link;
	sub_node *s_link;
}main_node;


// Function prototypes.

int validate_args(int argc, char *argv[], Flist **head, Flist **Invalid_h);
int insert_last_to_Flist(char *f_name, Flist **head);
void print_Flist(Flist *head);
int delete_Flist(Flist **head);
void delete_main_nodes(main_node *arr);
void create_HT(main_node arr[], int size);
int create_database(main_node *arr, Flist *head, int *create_flag, int update_flag, int *flag, Flist **Invalid_h);
int insert_last_to_main_node(main_node *arr, int index, char *str, char *f_name);
int validate_to_create_database_after_update(main_node *arr, int index, char *str, char *f_name, Flist **Invalid_h);
void print_created(Flist *head, Flist *Invalid_h);
void display(main_node *arr);
int search(main_node *arr, char *str);
int save(main_node *arr, char *f_name);
int validate_file_to_save(char *f_name);
int update(main_node *arr, char *f_name, int *update_flag, int create_flag);
int validate_file_to_update(char *f_name);



#endif
