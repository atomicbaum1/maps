/**************************************************
 * _____________________[_]_____________________
 *[_____________________________________________]
 * || FileName: error.c                       ||
 * || Description: Prints out the error and   ||
 * ||              then exits, saves typing   ||
 * || Created: Tue 12 Sep 2006                ||
 * || Modified: Tue 12 Sep 2006               ||
 * || Revision: 0                             ||
 * ||_________________________________________||
 * |___________________________________________|
 *                      | |
 *                      | |
 *                      | |
 *                   .\\|||//.
 */

#include "error.h"

void PrintError( const char * pError, const char * pExtra )
{
  fprintf( stderr, pError, pExtra );
  exit( EXIT_FAILURE );
}

const char * SetError( const char * pErr )
{
  static const char * Error;
  if( strcmp( pErr, NOERROR ) != 0 )
    Error = pErr;
  return Error;
}

const char * GetError()
{
  return SetError( NOERROR );
}
