/**************************************************
 * _____________________[_]_____________________
 *[_____________________________________________]
 * || FileName: collision.h                   ||
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

#ifndef COLLISION_H
#define COLLISION_H

#include <SDL/SDL.h>

#define MISSED 0
#define COLLIDED 1

/*Name: Inside
 *Description: Like collision checks to see if one
 *             rectangle is inside of the other
 *Parameters: Ax, Ay, Aw, Ah - first rectangle
 *            Bx, Bx, Bw, Bh - second rectangle
 *Returns: 1 if collision 0 if not
 */
int Inside( int Ax, int Ay, int Aw, int Ah,
	    int Bx, int By, int Bw, int Bh );

/*Name: Collision
 *Description: Detects a collision between two
 *             SDL_Rectangles
 *Parameters: RectA - first rectangle to be tested
 *            RectB - second rectangle to be tested
 *Retruns: 1 if collision 0 if not
 */
int Collision( SDL_Rect * pRectA, SDL_Rect * pRectB );

#endif
