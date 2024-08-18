#include "../include/cub3D.h"

bool	clean_parser(char **elements)
{
	size_t	row;

	row = 0;
	if (elements != NULL)
	{
		while (elements[row] != NULL)
		{
			free(elements[row]);
			row++;
		}
		free(elements);
	}
	return (false);
}

void	_free_helper(char **str, char **str1)
{
	if (*str != NULL)
	{
		free(*str);
		*str = NULL;
	}
	if (*str1 != NULL)
	{
		free(*str1);
		*str1 = NULL;
	}
}
