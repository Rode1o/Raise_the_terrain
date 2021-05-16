#include "data.h"

/**
 * main - draw a heightmap grid and modify display of it with UI
 *
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: 1 on usage error, -1 on init errors, 0 on success
 */
int main(int argc, char *argv[])
{
	SDL_Window *_window = NULL;
	SDL_Renderer *_renderer = NULL;
	int ret = 0;
	UINT _width = 0, _height;
	RTT_data **data = NULL;
	FILE *fp;

	if (argc < 2)
	{
		dprintf(2, "Usage: terrain filename\n");
		return (1);
	}
	/* START THE WINDOW AND RENDERER*/
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		dprintf(2,  "Couldn't initialize SDL: %s\n", SDL_GetError());
		return (-1);
	}
	if (SDL_CreateWindowAndRenderer(WIND_W, WIND_H,
					SDL_WINDOW_RESIZABLE, &_window, &_renderer))
	{
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		     "Couldn't create window and renderer: %s", SDL_GetError());
	return (3);
	}
	/* FILE TO OPEN */
	fp = fopen(argv[1], "r");
	if (fp == NULL)
	{
		dprintf(2, "Failed to open grid's coords file %s.\n", argv[1]);
		SDL_DestroyWindow(_window);
		SDL_DestroyRenderer(_renderer);
		return (-1);
	}
	ret = start_matrix(&data, fp, &_width, &_height);
	if (ret != -1)
		open_terrain(_renderer, data, _width, _height);
	free_data(data);
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
	return (ret);
}
