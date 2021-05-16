#include "data.h"
/**
 * start_matrix - initialized a grid matrix.
 * @dataref: variable to set in caller once we're done
 * @fp: file to read from
 * @width: variable to set with matrix width
 * @height: variable to set with matrix height
 *
 * Return: -1 on failure,0 on success
 */
int start_matrix(RTT_data ***dataref, FILE *fp,
	      UINT *width, UINT *height)
{
	char *bufer, *token;
	UINT coordx = 1, coordy = 1, x = 0, y = 0;
	size_t n = 0;
	RTT_data **data = NULL, *hook;

	while (getline(&bufer, &n, fp) != -1)
	{
		if (coordy < y + 2)
		{
			coordy *= 2;
			data = realloc(data, sizeof(RTT_data *) * coordy);
			if (data == NULL)
				return (-1);
			*dataref = data;
		}
		token = strtok(bufer, " ");
		data[y] = malloc(sizeof(RTT_data));
		if (data[y] == NULL)
			return (-1);
		data[y][0].next = 1;
		while (token != NULL && *token != '\n')
		{
			if (coordx < x + 2)
			{
				coordx *= 2;
				hook = realloc(data[y], sizeof(RTT_data) * coordx);
				if (hook == NULL)
					return (-1);
				data[y] = hook;
			}
			data[y][x].next = 0;
			data[y][x].z = atoi(token);
			x++;
			token = strtok(NULL, " ");
		}
		data[y][x].next = 1;
		y++;
		if (x > *width)
			*width = x;
		x = 0;
		coordx = 1;
		free(bufer);
		n = 0;
	}
	*height = y + 1;
	++*width;
	data[y] = NULL;
	*dataref = data;
	return (0);
}

/**
 * draw_matrix - draw a matrix
 * @data: matrix to draw
 * @_renderer: renderer to use
 *
 * Return: nothing
 */
void draw_matrix(RTT_data **data, SDL_Renderer *_renderer)
{
	UINT x = 0, y = 0, point_nxt;

	while (data[y] != NULL)
	{
		point_nxt = 0;
		if (data[y + 1] != NULL)
			while (data[y + 1][x].next != 1)
			{
				x++;
				point_nxt++;
			}
		x = 0;
		while (!data[y][x].next)
		{
			if (!data[y][x + 1].next)
				SDL_RenderDrawLine(_renderer, data[y][x].x,
						   data[y][x].y, data[y][x + 1].x,
						   data[y][x + 1].y);
			if (x < point_nxt)
				SDL_RenderDrawLine(_renderer, data[y][x].x, data[y][x].y,
						   data[y + 1][x].x, data[y + 1][x].y);
			x++;
		}
		y++;
		x = 0;
	}
}
