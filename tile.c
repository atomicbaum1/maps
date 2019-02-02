/**************************************************
 * _____________________[_]_____________________
 *[_____________________________________________]
 * || FileName: tile.c                        ||
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

#include "tile.h"

/*==================================
 * Tile File Format:
 * > Number of Tile Images
 * > List of Image Numbers
 * > Delay Between Sprites
 * > Collision Number
 *==================================*/
Tile * LoadTile( SDL_Surface ** ppImages, FILE * pTileFile )
{
  int i;
  Tile * pTile;

  /* allocate space for the tile */
  pTile = malloc( sizeof( Tile ) );
  if( !pTile )
    {
      SetError( ALLOCTILEERROR );
      return NULL;
    }
  
  /* load the information from the tilefile */
  fscanf( pTileFile, "%i", &pTile->NumImages );
  pTile->pImageNumbers = malloc( pTile->NumImages * sizeof( int ) );

  if( !pTile->pImageNumbers )
    {
      SetError( ALLOCIMGNUMERROR );
      return NULL;
    }

  for( i = 0; i < pTile->NumImages; ++i )
    fscanf( pTileFile, "%i", &pTile->pImageNumbers[ i ] );

  fscanf( pTileFile, "%i", &pTile->DelayMax );
  fscanf( pTileFile, "%i", &pTile->Collision );
  
  /* last things to setup */
  pTile->CurrentImage = 0;
  pTile->CurrentDelay = 0;
  pTile->ppImages = ppImages;
  pTile->pDisplayImage = 
    pTile->ppImages[ pTile->pImageNumbers[ pTile->CurrentImage ] ];
  
  return pTile;
}

void UpdateTile( Tile * pTile )
{
  /* update delay and if the delay is greater than delay max,
     update the image */
  ++pTile->CurrentDelay;
  
  if( pTile->CurrentDelay > pTile->DelayMax )
    {
      pTile->CurrentDelay = 0;
      ++pTile->CurrentImage;
    }

  /* if the image is out of the array bounds, assign it to zero */
  if( pTile->CurrentImage >= pTile->NumImages )
    pTile->CurrentImage = 0;
  
  pTile->pDisplayImage = 
    pTile->ppImages[ pTile->pImageNumbers[ pTile->CurrentImage ] ];
  
}

void CleanTile( Tile * pTile )
{
  /* free the things specific to this tile first */
  free( pTile->pImageNumbers );
  pTile->pImageNumbers = NULL;
  /* free the tile */
  free( pTile );
  pTile = NULL;
}
