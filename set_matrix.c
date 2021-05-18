#include "data.h"
/**
 * start_matrix - initialized a grid matrix.
 * @dataref: variable to set in caller once we're done
 * @fp: file to read from
 * @width: variable to set with matrix rows
 * @height: variable to set with matrix columns
 *
 * Return: -1 on failure,0 on success
 */
int start_matrix(RTT_data ***dataref, FILE *fp,
	      UINT *width, UINT *height)
{
	char *bufer, *token;
	UINT coordx = 1, coordy = 1, row = 0, column = 0;
	size_t n = 0;
	RTT_data **data = NULL, *hook;

	while (getline(&bufer, &n, fp) != -1)/*get size*/
	{
		if (coordy < column + 2)
		{
			coordy *= 2;
			data = realloc(data, sizeof(RTT_data *) * coordy);
			if (data == NULL)
				return (-1);
			*dataref = data;
		}
		token = strtok(bufer, " ");
		data[column] = malloc(sizeof(RTT_data));
		if (data[column] == NULL)
			return (-1);
		data[column][0].next = 1;
		while (token != NULL && *token != '\n')
		{
			if (coordx < row + 2)
			{
				coordx *= 2;
				hook = realloc(data[column], sizeof(RTT_data) * coordx);
				if (hook == NULL)
					return (-1);
				data[column] = hook;
			}
			data[column][row].next = 0;
			data[column][row].z = atoi(token);
			row++;
			token = strtok(NULL, " ");
		}
		data[column][row].next = 1;
		column++;
		if (row > *width)
			*width = row;
		row = 0;
		coordx = 1;
		free(bufer);
		n = 0;
	}
	*height = column + 1;
	++*width;
	data[column] = NULL;
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
			/*VERTICAL LINES*/
			if (!data[y][x + 1].next)
				SDL_RenderDrawLine(_renderer, data[y][x].x,
						   data[y][x].y, data[y][x + 1].x,
						   data[y][x + 1].y);
			/*HORIZONTAL LINES*/
			if (x < point_nxt)
				SDL_RenderDrawLine(_renderer, data[y][x].x, data[y][x].y,
						   data[y + 1][x].x, data[y + 1][x].y);
			x++;
		}
		y++;
		x = 0;
	}
}
