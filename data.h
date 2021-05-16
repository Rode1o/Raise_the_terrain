#ifndef GRIDH
#define GRIDH

#define SCALE 70
#define UINT unsigned int
#define M_PI
#define WIND_W 1024
#define WIND_H 768
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

/**
 * struct RTT_data - base coords for point on matrix
 *
 * @x: x coordinate
 * @y: y coordinate
 * @z: z coordinate
 * @next: whether it is the last node in the array
 */
typedef struct RTT_data
{
	int z, next;
	int x, y;
}RTT_data;


/*SET POINTS TO MATRIX*/
int start_matrix(RTT_data ***data, FILE *fp,
	      UINT *width, UINT *height);
/*CONVERT TO ISOMETRIC*/
void update_matrix(RTT_data **data, int zoom, float flipyz,
		    float flipxy, int midx, int midy, int width, int height);
/*DRAWING MATRIX*/
void draw_matrix(RTT_data **data, SDL_Renderer *_renderer);
/*LOOP AND EVENTS*/
int open_terrain(SDL_Renderer *_renderer, RTT_data **data,
	     int _width, int _height);
void free_data(RTT_data **data);

#endif
