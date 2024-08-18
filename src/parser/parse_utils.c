#include "../../include/cub_parser.h"

bool	check_cub(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (len == 0 || ft_strncmp(&arg[len - 4], ".cub", 5) != 0)
	{
		ft_putstr_fd("Not a .cub file!\n", 2);
		return (false);
	}
	return (true);
}

bool	check_png(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if (len == 0 || ft_strncmp(&arg[len - 4], ".png", 5) != 0)
	{
		ft_putendl_fd("Not a .png file!", 2);
		return (false);
	}
	return (true);
}

int	ft_atorgb(const char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		i = (i * 10 + *str - '0');
		str++;
	}
	if (i < 0 || i > 255)
		return (-1);
	return (i);
}
