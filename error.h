/**************************************************
 * _____________________[_]_____________________
 *[_____________________________________________]
 * || FileName: error.h                       ||
 * || Description: Prints out the error and   ||
 * ||              then exits, saves typing   ||
 * || Created: Tue 12 Sep 2006                ||
 * || Modified: Sat 18 Nov 2006               ||
 * || Revision: 1 - Created SetError and Get  ||
 * ||               Error functions and       ||
 * ||               expanded PrintError       ||
 * ||_________________________________________||
 * |___________________________________________|
 *                      | |
 *                      | |
 *                      | |
 *                   .\\|||//.
 */

#ifndef ERROR_H
#define ERROR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <SDL/SDL.h>

#define NOERROR ""
#define BUFFSIZE 1024

/*Name: PrintError
 *Description: Prinst the error and exits
 *Parameters: pError - the error to print
 *            pExtra - extra info for geterror
 *Returns: void
 */
void PrintError( const char * pError, const char * pExtra );

/*Name: SetError
 *Description: Sets the error so get error can
 *             pick it up
 *Parameters: pointer to an error message
 *Returns: error message
 */

const char * SetError( const char * pErr );

/*Name: GetError
 *Description: Returns a string set by SetError
 *Parameters: pointer to a string of error
 *Return: pointer to a string of characters
 */
const char * GetError();

#endif
