#include "data.h"
/**
 * free_data - frees data
 *
 * @data: data to free
 *
 * Return: Nothing
 */
void free_data(RTT_data **data)
{
	int i = 0;

	if (data != NULL)
		if (*data != NULL)
		{
			while (data[i] != NULL)
				free(data[i++]);
			free(data);
		}
}

