#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "map.h"

int main( int argc, char ** argv )
{

  /* some things we need to set this up */
  SDL_Surface * pScreen;
  SDL_Surface * pTemp;
  SDL_Surface * pImage;
  SDL_Rect ImageRect;

  SDL_Event event;

  int mapx, mapy;
  int x, y;
  Map * pTestMap;
  Map * pTestMap1;

  if( argc < 2 )
      PrintError( "Map1, Map2\n", "" );

  /* setup SDL */
  SDL_Init( SDL_INIT_VIDEO );
  pScreen = SDL_SetVideoMode(640,480,32, SDL_HWSURFACE | SDL_DOUBLEBUF );
  atexit( SDL_Quit );

  /* load the image and setup the image */
  pTemp = SDL_LoadBMP( "image.bmp" );
  SDL_SetColorKey( pTemp, SDL_SRCCOLORKEY, ( Uint32 ) 
		   SDL_MapRGB( pTemp->format, 255, 0, 255 ) );

  pImage = SDL_DisplayFormatAlpha( pTemp );
  SDL_FreeSurface( pTemp );
  x = 30;
  y = 180;
  ImageRect.x = 0;
  ImageRect.y = 0;
  ImageRect.w = pImage->w;
  ImageRect.h = pImage->h;
  
  /* load the map and optimize the map */
  pTestMap = LoadMap( argv[ 1 ], pScreen->w - 20, 240 );
  if( !pTestMap )
      PrintError( "Could not load map %s\n", GetError() );
  
  /* load the background map and optimize it */
  pTestMap1 = LoadMap( argv[ 2 ], pScreen->w - 20 , 240 );
  if( !pTestMap1 )
    PrintError( "Could not load map %s\n", GetError() );

  SDL_EnableKeyRepeat( 250, 0 );

  /* scroll for the length of the map */
  while( 1 )
  {

    /* get input */
    while( SDL_PollEvent( &event ) )
    {
      switch( event.type )
	{
	case SDL_KEYDOWN:
	  switch( event.key.keysym.sym )
	    {
	    case SDLK_q:
	      exit( 0 ); break;
	    case SDLK_UP:
	      y-=1; break;
	    case SDLK_DOWN:
	      y+=1; break;
	    case SDLK_RIGHT:
	      x+=1; break;
	    case SDLK_LEFT:
	      x-=1; break;
	    }
	}
    }

    /* calculate the movements */

    mapx = x + ImageRect.w/2 - pScreen->w / 2;
    mapy = y + ImageRect.h/2 - pScreen->h / 2;


    if( mapx > ( pTestMap->Width * pTestMap->TileWidth - ( pScreen->w - 20 )) )
      mapx = pTestMap->Width * pTestMap->TileWidth - ( pScreen->w - 20 ) ;
    if( mapx < 0 )
      mapx = 0;

    if( mapy > ( pTestMap->Height * pTestMap->TileHeight - pScreen->h + 240) )
      mapy = pTestMap->Height * pTestMap->TileHeight - pScreen->h + 240;
    if( mapy < 0 )
      mapy = 0;
    
    ImageRect.x = x - mapx;
    ImageRect.y = y - mapy;

    UpdateMap( pTestMap );
    
    /* print the background map at 1/2 speed and forground map normal speed */
    PrintMap( pScreen, 10, 10, pTestMap1, ( int )mapx >> 1, mapy );
    PrintMap( pScreen, 10, 10, pTestMap, mapx, mapy );
   
    /* print image */
    SDL_BlitSurface( pImage, NULL, pScreen, &ImageRect );

    ImageRect.x = x;
    ImageRect.y = y;

    /* check for collision */
    if( MapCollision( pTestMap, 10, 10, &ImageRect ) )
      {
	printf( "%d\n", MapCollision( pTestMap, 10, 10, &ImageRect ) );
      }

    /* flip the screen */
    SDL_Flip( pScreen );
    /* give the OS a break */
    SDL_Delay( 10 );
  }
  /* pause to see the beauty of the map */
  SDL_Delay( 1000 );

  /* clean up our mess */
  CleanMap( pTestMap );
  CleanMap( pTestMap1 );
  SDL_FreeSurface( pScreen );
  /* return happy */
  return EXIT_SUCCESS;

}
