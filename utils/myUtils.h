/**
 * @file myUtils.h
 * @author Stu Steiner
 * @date 29 Dec 2015
 * @brief The basic myUtils.h that will be used during the quarter
 *
 * The myUtils.h defines the basic menu and strip functions that will be
 * required during the course of the quarter.
 */
#ifndef MYUTILS_H
#define MYUTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tokenize/makeArgs.h"

#define MAX 100


/**
 * @brief Prompts the user for a menu choice.
 *
 * Prompts the user for a menu choice and ensures the value
 * entered by the user is within range.
 *
 * @note The carriage return is removed from the input buffer
 *
 * @return int - Representing the menu choice
 */
int menu();

/**
 * @brief Strinps the \r and \n from the string if they exist.
 *
 * Walks through the character array one character at a time
 * if a '\r' or '\n' are encountered it is changed to a '\0'
 * entered by the user is within range.
 *
 * @param The character array potentially containing a '\r' and/or '\n'
 *
 * @warning - The passed in pointer is checked - exit(-99) if NULL
 */
void strip(char *array);


/**
 * Opens the ushrc file if it exists. If it does not exist, NULL is returned and will be
 * handled in the main().
 * @return FILE *
 */
FILE * openRC();

/**
 * Opens the history file and writes the history command linked list to it
 * @return FILE *
 */
FILE * openRCHistory();


/**
 * Called to read in HISTCOUNT and HISTFILECOUNT from .ushrc
 * @param fin
 * @param histCount
 * @param histFileCount
 */
void getCounts(FILE * fin, int * histCount, int * histFileCount);

#endif
