#include "../../include/cub_parser.h"

bool	_check_rgb_input(char **elements)
{
	size_t		index;
	char		*temp;

	index = 0;
	while (elements[index] != NULL)
		index++;
	if (index != 3)
	{
		ft_putstr_fd("Incorrect RGB input\n", 2);
		return (false);
	}
	index = 0;
	while (elements[index])
	{
		temp = ft_strtrim(elements[index], WHITESPACE);
		if (temp == NULL)
		{
			ft_putendl_fd("Faield to trimn", 2);
			return (false);
		}
		free(elements[index]);
		elements[index] = temp;
		index++;
	}
	return (true);
}
