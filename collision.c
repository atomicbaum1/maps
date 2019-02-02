/**************************************************
 * _____________________[_]_____________________
 *[_____________________________________________]
 * || FileName: collision.c                   ||
 * || Description: Checks for collisions      ||
 * ||              between 4 ints or 2 rects  ||
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

#include "collision.h"

int Inside( int Ax, int Ay, int Aw, int Ah,
	    int Bx, int By, int Bw, int Bh )
{

  /* create the variables to hold x+width and y+height
   * to act as the two sides of the rectangle
   * the normal x and y are the other two sides of the
   * rectangle
   */
  
  int Aright, Abottom;
  int Bright, Bbottom;
  
  Aright = Ax + Aw;
  Abottom = Ay + Ah;
  
  Bright = Bx + Bw;
  Bbottom = By + Bh;
  

  /* now we check for collision on each side
   * if one side is not within the other, then
   * no collision has taken place ( which is more likely )
   */
  
  if( Abottom <= By )
    return MISSED;
  
  if( Ay >= Bbottom )
    return MISSED;
  
  if( Aright <= Bx )
    return MISSED;
  
  if( Ax >= Bright )
    return MISSED;
  
  return COLLIDED;
}

int Collision( SDL_Rect * pRectA, SDL_Rect * pRectB )
{
  return Inside( pRectA->x, pRectA->y, pRectA->w, pRectA->h,
		 pRectB->x, pRectB->y, pRectB->w, pRectB->h );
}


