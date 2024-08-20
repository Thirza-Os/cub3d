/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_ident_utils.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 21:23:37 by tosinga       #+#    #+#                 */
/*   Updated: 2024/08/20 21:23:37 by tosinga       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
