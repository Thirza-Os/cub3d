/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 21:23:22 by tosinga       #+#    #+#                 */
/*   Updated: 2024/08/20 21:27:28 by tosinga       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_char_arr(char **arr)
{
	size_t	row;

	row = 0;
	while (arr[row] != NULL)
	{
		free(arr[row]);
		row++;
	}
	free(arr);
}

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
