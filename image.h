/**************************************************
 * _____________________[_]_____________________
 *[_____________________________________________]
 * || FileName: image.h                       ||
 * || Description: Has functions to easily    ||
 * ||              deal with images           ||
 * || Created: Mon 11 Sep 2006                ||
 * || Modified: Mon 11 Sep 2006               ||
 * || Revision: 0                             ||
 * ||_________________________________________||
 * |___________________________________________|
 *                      | |
 *                      | |
 *                      | |
 *                   .\\|||//.
 */

#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>
#include <SDL/SDL.h>
#include "error.h"

#define OPENIMAGEERROR "Could not open image"
#define DISPLAYFORMATERROR "Could not set to display format"
#define ALLOCIMGERROR "Could not allocate image"

/*Name: GetFrame
 *Description: Gets a frame from a big image and returns it
 *Parameters: pSourceSurface - source surface from which the
 *                             frame will be taken
 *            pDimm - the dimensions of the surface to be 
 *                    returned
 *            Columns - the number of columns in the image
 *            Frame - the frame to be grabbed
 *Returns: SDL_Surface pointer to the frame
 */
SDL_Surface * GetFrame( SDL_Surface * pSourceSurface, SDL_Rect * pDimm,
                        int Columns, int Frame );
#endif
