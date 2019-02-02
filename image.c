/**************************************************
 * _____________________[_]_____________________
 *[_____________________________________________]
 * || FileName: image.c                       ||
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

#include "image.h"

SDL_Surface * GetFrame( SDL_Surface * pSourceSurface, SDL_Rect * pDimm,
                        int Columns, int Frame )
{    
  SDL_Surface * pTempSurface;
  SDL_Rect SourceRect, DestRect;
  int x, y;
  
  /* Create a surface ( software for our needs )*/
  pTempSurface = SDL_CreateRGBSurface( SDL_SWSURFACE, 
				       pDimm->w, pDimm->h, 32, 
				       pSourceSurface->format->Rmask, 
				       pSourceSurface->format->Gmask,
				       pSourceSurface->format->Bmask,
				       pSourceSurface->format->Amask );
  /* check for error */
  if( !pTempSurface )
    {
      SetError( ALLOCIMGERROR );
      return NULL;
    }
  
  /* get the starting x and y  positions */
  x = pDimm->x + ( Frame % Columns ) * pDimm->w; 
  y = pDimm->y + ( Frame / Columns ) * pDimm->h;
  
  /* create the source rectangle */
  SourceRect.x = x; 
  SourceRect.y = y; 
  SourceRect.w = pDimm->w;
  SourceRect.h = pDimm->h;
  
  /* create the destination rectangle */
  DestRect.x = 0; 
  DestRect.y = 0; 
  DestRect.w = pDimm->w;
  DestRect.h = pDimm->h;

  /* turn of alpha so we blit without it being used ( if any )*/
  SDL_SetAlpha( pSourceSurface, SDL_RLEACCEL, 0 );

  /* blit the desired part of the image to the new image */
  SDL_BlitSurface( pSourceSurface ,&SourceRect, 
		   pTempSurface, &DestRect );
  
  /* return the part of the surface that we want */
  return pTempSurface;
}
