/**************************************************
 * _____________________[_]_____________________
 *[_____________________________________________]
 * || FileName: tile.h                        ||
 * || Description: The tile is a part of the  ||
 * ||              map as a whole. The Tiles  ||
 * ||              can have collision and     ||
 * ||              can be animated            ||
 * || Created: Thu 14 Sep 2006                ||
 * || Modified: Thu 14 Sep 2006               ||
 * || Revision: 0                             ||
 * ||_________________________________________||
 * |___________________________________________|
 *                      | |
 *                      | |
 *                      | |
 *                   .\\|||//.
 */

#ifndef TILE_H
#define TILE_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "error.h"
#include "collision.h"
#include "image.h"

#define ALLOCTILEERROR "Could not allocate tile"
#define ALLOCIMGNUMERROR "Could not allocate image numbers"

/* -=Structure Tile=-
 * Description: The tile is a part of a map. The tiles can hold collision
 *              numbers and can be animated.
 * Members: pDisplayImage - pointer to an SDL_Surface that is going to 
 *                          be the current surface displayed.
 *          ppImages - pointer to the array of all of the available
 *                      images as pointers
 *          NumImages - number of Sprite images spacific to this tile
 *          CurrentImage - the current image that is being displayed
 *                         ( acts like the current element of the array
 *                           not the number of the image )
 *          pImageNumbers - pointer to the array of image number that 
 *                          correspond to the array of Images
 *          CurrentDelay - the counter that counts how many delays have
 *                         passed
 *          DelayMax - the maximum the delay can be and if Current delay
 *                     is bigger than DelayMax, then advance the image and
 *                     set Current delay to 0
 *          Collision - the collision number ( <= 0 if there is no collision
 *
 */

typedef struct Tile
{
  SDL_Surface * pDisplayImage;
  SDL_Surface ** ppImages;
  int NumImages, CurrentImage;
  int * pImageNumbers;
  int CurrentDelay, DelayMax;
  int Collision;
}Tile;

/*Name: LoadTile
 *Description: Called from the LoadMap function, this takes in a file
 *             pointer so it can start at the correct location in the
 *             map file to read in the tile
 *Parameters: 
 *            ppImages - pointer to the array of Surface pointers that 
 *                        the tile can pick from
 *            pTileFile - pointer to the file that the information of
 *                        the tile is on
 *Returns: pointer to the new tile
 */
Tile * LoadTile( SDL_Surface ** ppImages, FILE * pTileFile );

/*Name: UpdateTile
 *Description: Updates the tiles currentdelay and if it is greater than
 *             the maxdelay then it will update the tiles animation
 *Parameters: pTile - pointer to the tile to update
 *Returns: void
 */
void UpdateTile( Tile * pTile );

/*Name: CleanTile
 *Description: called by clean map, this cleans up a tile
 *             after the user is finished with it
 *Parameters: pTile - pointer to a tile to be cleaned
 *Returns: void
 */
void CleanTile( Tile * pTile );

#endif
