#include "cub3d.h"

int	ft_isspace(char c)
{
	if (c == 32 || (c > 8 && c < 14))
		return (1);
	return (0);
}

char	**ft_free_narr(char **arr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(arr[i]);
		i++;
	}
	return (0);
}
