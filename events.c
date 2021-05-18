#include "data.h"

/**
 * open_terrain - loop to draw terrain
 * @_renderer: renderer to use
 * @data: data to draw
 * @_width: width of matrix
 * @_height: height of matrix
 *
 * Return: 0 on succes
 */
int open_terrain(SDL_Renderer *_renderer, RTT_data **data,
	     int _width, int _height)
{
	SDL_Event events;
	int quit, zoom, zoomin, draw = 1;
	float rotate = M_PI / -4, incline = 3 * M_PI / -8;
	/*SETING THE ZOOM IN AND ZOOM OUT*/
	zoom = _height < _width ? _height : _width;
	zoomin = WIND_H > WIND_W ? WIND_H / 1.0 : WIND_W / 1.0;
	zoomin /= zoom;
	zoom = zoomin;
	quit = 0;
	while (!quit)
	{
		if (draw == 1)
		{
			SDL_SetRenderDrawColor(_renderer, 0, 165, 165, 165);
			SDL_RenderClear(_renderer);
			SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 0);
			update_matrix(data, zoom, incline, rotate,
				       WIND_W / 2, WIND_H / 2, _width, _height);
			draw_matrix(data, _renderer);
			SDL_RenderPresent(_renderer);
			draw = 0;
		}
	/* SETING KEY EVENTS WASD(ROTATE), UPKEY AND DOWNKEY(ZOOM)*/
		while (SDL_PollEvent(&events) != 0)
		{
			if (events.type == SDL_QUIT ||
			    (events.type == SDL_KEYDOWN &&
			     events.key.keysym.sym == SDLK_ESCAPE))
				quit = 1;
			if (events.type == SDL_KEYDOWN &&
			    events.key.keysym.sym == SDLK_a)
				rotate -= M_PI / 128;
			if (events.type == SDL_KEYDOWN &&
			    events.key.keysym.sym == SDLK_d)
				rotate += M_PI / 128;
			if (events.type == SDL_KEYDOWN &&
			    events.key.keysym.sym == SDLK_w)
				incline += M_PI / 256;
			if (events.type == SDL_KEYDOWN &&
			    events.key.keysym.sym == SDLK_s)
				incline -= M_PI / 256;
			if (events.type == SDL_KEYDOWN &&
			    events.key.keysym.sym == SDLK_UP)
				if (zoom <= zoomin)
					zoom += 1;
			if (events.type == SDL_KEYDOWN &&
			    events.key.keysym.sym == SDLK_DOWN)
				if (zoom > 5)
					zoom -= 1;
			draw = 1;
		}
	}
	return (0);
}



/**
 * update_matrix - Handle the rotation and zoom
 * @flipyz: rotation around yz axis
 * @flipxy: rotation around xy axis
 * @midx: x point in center
 * @midy: y point in center
 * @width: width of matrix
 * @height: height of matrix
 * @data: matrix to calculate
 * @zoom: zoom for matrix
 *
 *Return: nothing
 */
void update_matrix(RTT_data **data, int zoom, float flipyz,
		    float flipxy, int midx, int midy, int width, int height)
{
	int x, y = 0;
	float initx, inity;

	while (data[y] != NULL)
	{
		while (!data[y][x].next)
		{
			initx = zoom * (x + 1 - width / 2.0);
			inity = zoom * (y + 1 - height / 2.0);
			data[y][x].x = (initx * cos(flipxy) - inity *  sin(flipxy)) + midx;
			inity = inity * cos(flipxy) + initx * sin(flipxy);
			data[y][x].y = ((inity * cos(flipyz) +
					 data[y][x].z * zoom / SCALE * sin(flipyz)) + midy);
			x++;
		}
		y++;
		x = 0;
	}
}

