/**************************************************
 * _____________________[_]_____________________
 *[_____________________________________________]
 * || FileName: map.h                         ||
 * || Description: Deals with and displays a  ||
 * ||              tilemap using SDL          ||
 * || Created: Sun 10 Sep 2006                ||
 * || Modified: Nov 15 Sep 2006               ||
 * || Revision: 1 - Finished up map prints    ||
 * ||           2 - created save map function ||
 * ||           3 - added support for new     ||
 * ||               sprite tile               ||
 * ||           4 - added simple blit tile    ||
 * ||               and took out buffer and   ||
 * ||               added translucent tiles   ||
 * ||_________________________________________||
 * |___________________________________________|
 *                      | |
 *                      | |
 *                      | |
 *                   .\\|||//.
 */

#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "tile.h"
#include "image.h"
#include "error.h"
#include "collision.h"

#define ALLOCMAPERROR "Could not allocate map"
#define OPENMAPERROR "Could not open map"
#define LOADMAPERROR "Could not load map"
#define OPENTILEIMGERROR "Could not open tile bitmap"
#define ALLOCNUMBERMAPERROR "Could not allocate number map"

/* -= Structure Map =-
 * Description: The main map that uses tiles and is able
 *              to print a map to the screen
 * Members:
 *         pTile - a pointer to an array of tile pointers that
 *                 will be allocated depending on the 
 *                 number of unique tiles in the map
 *         ppImages - pointer to the array of SDL_Surface
 *                    pointers that hold the "pool" of
 *                    Images that tiles can pick from
 *         NumTiles - the number of unique tiles
 *         NumTileImages - the number of tile images to load
 *         DrawWidth, DrawHeight - width & height to draw at
 *         Width, Height - the width and height of the
 *                         map in tiles
 *         TileWidth, TileHeight - the width and height
 *                                 of the tiles for quick
 *                                 access
 *         ppNumberMap - a 2d array of numbers. Each 
 *                       number corresponds to a tile
 *                       in the array of tiles
 */

typedef struct Map
{
  Tile ** ppTile;
  SDL_Surface ** ppImages;
  int NumTiles;
  int NumTileImages;
  int DrawWidth, DrawHeight;
  int Width, Height;
  int TileWidth, TileHeight;
  int ** ppNumberMap;
}Map;

/* Functions for the Map structure */

/*Name: LoadMap
 *Description: Loads a map from a file
 *Parameters: pMapName - File name to load the map from
 *            width - the width of the map's drawing area
 *            height - the height of the map's drawing area
 *Returns: pointer to the new map
 */
Map * LoadMap( const char * pMapName, int width, int height );

/*Name: UpdateMap
 *Description: Updates the Map animation tiles
 *Parameters: pMap - pointer to the map to update
 *Returns: void
 */
void UpdateMap( Map * pMap );

/*Name: PrintMap
 *Description: Prints a map to the buffer
 *Parametsrs: pBuffer - buffer to print the map to
 *            X, Y - x and y position to blit to on the screen
 *            pMap - pointer to the map that is to be printed
 *            MapY, MapY - x and y coordinates of the map that will
 *                   be printed to 0,0 of the screen
 *Returns: void
 */
void PrintMap( SDL_Surface * pBuffer, int X, int Y, Map * pMap, 
	       int MapX, int MapY );

/*Name: MapCollision
 *Description: Checks for map collision using the tile collision
 *             for the whole map ( rectangle collision )
 *Parameters: pMap - pointer to the map to check for collision
 *            X, Y - x and y position for offset ( not 0, 0 starting )
 *            pRect - the rectangle to check for collision at
 *Returns: 0 if no collision and the collision value of the tile
 *         if there is a collision
 */
int MapCollision( Map * pMap, int X, int Y, SDL_Rect * pRect );

/*Name: CleanMap
 *Description: Cleans up the map when finished
 *Parameters: pMap - the map to be cleaned
 *Returns: void
 */
void CleanMap( Map * pMap );

#endif
