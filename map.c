/**************************************************
 * _____________________[_]_____________________
 *[_____________________________________________]
 * || FileName: map.c                         ||
 * || Description: Deals with and displays a  ||
 * ||              tilemap using SDL          ||
 * || Created: Sun 10 Sep 2006                ||
 * || Modified: Fri 15 Sep 2006               ||
 * || Revision: 1 - Finished up map prints    ||
 * ||           2 - created save map function ||
 * ||           3 - added support for new     ||
 * ||               sprite tile               ||
 * ||_________________________________________||
 * |___________________________________________|
 *                      | |
 *                      | |
 *                      | |
 *                   .\\|||//.
*/

#include "map.h"

/* Functions for the Map structure */

/*=================================================
 * File format for the map goes as follows
 * > Name of the bitmap the tiles are in
 * > Number of tiles in the bitmap (not invisible)
 * > Number of tile images
 * > Width of the tiles in pixels
 * > Height of the tiles in pixels
 * > Width of the Map in tiles
 * > Height of the Map in tiles
 * > > Tile Sprite Properties
 * > List of collision tiles with collision number
 * > List of map tiles
 *=================================================*/
Map * LoadMap( const char * pMapName, int width, int height )
{
  /* temporary storage variables */
  Map * pMap;
  FILE * pMapFile;
  SDL_Surface * pTempImage;
  SDL_Rect TileDetails;
  char pTempString[ 64 ];
  int i, j;
  int Columns;

  /* allocate space for the map */
  pMap = malloc( sizeof( Map ) );
  if( !pMap )
    {
      SetError( ALLOCMAPERROR );
      return NULL;
    }

  /* open the map */
  pMapFile = fopen( pMapName, "r" );
  if( !pMapFile )
    {
      SetError( OPENMAPERROR );
      return NULL;
    }

  /* get the setup information */
  fscanf( pMapFile, "%s", pTempString );
  fscanf( pMapFile, "%i", &pMap->NumTiles );
  fscanf( pMapFile, "%i", &pMap->NumTileImages );
  fscanf( pMapFile, "%i%i", &pMap->TileWidth, &pMap->TileHeight );
  fscanf( pMapFile, "%i%i", &pMap->Width, &pMap->Height );

  /* load the bitmap of tiles then  allocate space for the tiles
     and seperate them into individual tiles */
  pTempImage = IMG_Load( pTempString );
  if( !pTempImage )
    {
      SetError( OPENTILEIMGERROR );
      return NULL;
    }

  TileDetails.x = TileDetails.y = 0;
  TileDetails.w = pMap->TileWidth;
  TileDetails.h = pMap->TileHeight;

  Columns = ( pTempImage->w / pMap->TileWidth );

  /* grab the frames from the image */
  pMap->ppImages = malloc(  pMap->NumTileImages * sizeof( SDL_Surface * ) );
  if( !pMap->ppImages )
    {
      SetError( ALLOCIMGERROR );
      return NULL;
    }

  /* get frames and check for error */
  for( i ^= i; i < pMap->NumTileImages; ++i )
    {
      pMap->ppImages[ i ] = GetFrame( pTempImage, &TileDetails, Columns, i );
      if( !pMap->ppImages[ i ] )
	return NULL;
    }
  /* free what we loaded */
  SDL_FreeSurface( pTempImage );

  /* set the tile image pool to display format */
  for( i ^= i; i < pMap->NumTileImages; ++i )
    {     
      pTempImage = SDL_DisplayFormatAlpha( pMap->ppImages[ i ] );
      if( !pTempImage )
	{
	  SetError( DISPLAYFORMATERROR );
	  return NULL;
	}
      
      SDL_FreeSurface( pMap->ppImages[ i ] );
      pMap->ppImages[ i ] = pTempImage;
    }

  /* alloacte tile array */
  pMap->ppTile = malloc( pMap->NumTiles * sizeof( Tile * ) );
  if( !pMap->ppTile )
    {
      SetError( ALLOCTILEERROR );
      return NULL;
    }

  /* load the tiles and check for null ( error already set ) */
  for( i ^= i; i < pMap->NumTiles; ++i )
    {
      pMap->ppTile[ i ] = LoadTile( pMap->ppImages, pMapFile );
      if( !pMap->ppTile[ i ] )
	return NULL;
    }

  /* allocate the 2d array for the number pointer */
  pMap->ppNumberMap = malloc( pMap->Width * sizeof( int * ) );
  if( !pMap->ppNumberMap )
    {
      SetError( ALLOCNUMBERMAPERROR );
      return NULL;
    }

  /* allocate the number map */
  for( i ^= i; i < pMap->Width; ++i )
    {
      pMap->ppNumberMap[ i ] = malloc( pMap->Height * sizeof( int ) );
      if( !pMap->ppNumberMap[ i ] )
	{
	  SetError( ALLOCNUMBERMAPERROR );
	  return NULL;
	}
    }

  /* load the number map */
  for( i ^= i; i < pMap->Height; ++i )
    for( j ^= j; j < pMap->Width; ++j )
      fscanf( pMapFile, "%i", &pMap->ppNumberMap[ j ][ i ] );

  pMap->DrawWidth = width;
  pMap->DrawHeight = height;

  /* clean up */
  fclose( pMapFile );

  /* return our fresh map */
  return pMap;
}

void UpdateMap( Map * pMap )
{
  int i;
  for( i ^= i; i < pMap->NumTiles; ++i )
    UpdateTile( pMap->ppTile[ i ] );
}

void PrintMap( SDL_Surface * pBuffer, int X, int Y, Map * pMap, 
	       int MapX, int MapY )
{
  int TX, TY;
  int PosX, PosY;
  int TileWidth, TileHeight;
  int StartTileX, StartTileY;
  int DrawWidth, DrawHeight;
  int CurrentCounterX, CurrentCounterY;
  SDL_Rect Src, Dest;

  /* get the tile width and height */
  TileWidth = pMap->TileWidth;
  TileHeight = pMap->TileHeight;
  
  /* get the draw width and height */
  DrawWidth = pMap->DrawWidth;
  DrawHeight = pMap->DrawHeight;
  
  /* start tiles */
  StartTileX = MapX / TileWidth;
  StartTileY = MapY / TileHeight;  
  
  /* start the src and dest */
  Src.x = Src.y = 0;
  Src.w = TileWidth;
  Src.h = TileHeight;  
  Dest = Src;  

  /* start drawing */
  for( PosY ^= PosY, TY = StartTileY, CurrentCounterY = DrawHeight;
       CurrentCounterY > 0; 
       CurrentCounterY -= ( TileHeight - Src.y ), ++PosY, ++TY, 
	 Src.y = 0, Src.h = TileHeight )
    {
      /* get the destination y */
      Dest.y = Y + ( PosY * TileHeight ) - ( MapY % TileHeight );
 
      /* specal cases for start and end tiles */
      if( TY == StartTileY )
	{
	  Src.y = MapY % TileHeight;
	  Dest.y += Src.y;
	}
      if( CurrentCounterY - TileHeight < 0 )
	Src.h = Dest.h = CurrentCounterY;
      
      for( PosX ^= PosX, TX = StartTileX, CurrentCounterX = DrawWidth;
	   CurrentCounterX > 0; 
	   CurrentCounterX -= ( TileWidth - Src.x ), ++PosX, ++TX, 
	     Src.x = 0, Src.w = TileWidth )
	{
	  /* get the destination x and src width */
	  Dest.x = X + ( PosX * TileWidth ) - ( MapX % TileWidth );
	  
	  /* specal cases for start and end tiles */
	  if( TX == StartTileX )
	    {
	      Src.x = MapX % TileWidth;
	      Dest.x += Src.x;
	    }
	  if( CurrentCounterX - TileWidth < 0 )
	    Src.w = Dest.w = CurrentCounterX;
	  
	  /* now draw the tiles */
	  SDL_BlitSurface( pMap->ppTile[ pMap->ppNumberMap[ TX ][ TY ] ]->pDisplayImage,
			   &Src, pBuffer, &Dest );	  
	}
      
    }
}

int MapCollision( Map * pMap, int X, int Y, SDL_Rect * pRect )
{
  int i, j;
  int Width, Height;
  SDL_Rect TestRect;
  
  TestRect.w = pMap->TileWidth;
  TestRect.h = pMap->TileHeight;

  Width = pMap->Width;
  Height = pMap->Height;

  /* find a tile with collision */
  for( i ^= i; i < Height; ++i )
    for( j ^= j; j < Width; ++j )
      {
	/* if the tile has collision ( non-zero ) */
	if( pMap->ppTile[ pMap->ppNumberMap[ j ][ i ] ]->Collision )
	  {
	    /* setup x and y */
	    TestRect.x = j * pMap->TileWidth + X;
	    TestRect.y = i * pMap->TileHeight + Y;

	    /* check for collision if collided return tile's collision # */
	    if( Collision( &TestRect, pRect ) )
	      return pMap->ppTile[ pMap->ppNumberMap[ j ][ i ] ]->Collision;
	    
	  }
      }
  /* no collision found */
  return 0;
}

void CleanMap( Map * pMap )
{
  int i;
  
  /* clean up the tiles first */
  for( i = 0; i < pMap->NumTiles; ++i )
      CleanTile( pMap->ppTile[ i ] );
  free( pMap->ppTile );
  pMap->ppTile = NULL;  
  
  /* free the number map */
  for( i = 0; i < pMap->Width; ++i )
    {
      free( pMap->ppNumberMap[ i ] );
      pMap->ppNumberMap[ i ] = NULL;
    }
  
  free( pMap->ppNumberMap );
  pMap->ppNumberMap = NULL;

  /* free the images */
  for( i = 0; i < pMap->NumTileImages; ++i )
    {
      SDL_FreeSurface( pMap->ppImages[ i ] );
      pMap->ppImages[ i ] = NULL;
    }
  free( pMap->ppImages );
  pMap->ppImages = NULL;
  
  /* free the map */
  free( pMap );
  pMap = NULL;
}

