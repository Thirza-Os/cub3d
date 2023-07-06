/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 14:19:58 by rbrune        #+#    #+#                 */
/*   Updated: 2023/07/06 14:19:59 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(char *message)
{
	printf("Error\n");
	printf("%s\n", message);
	exit (1);
}

void	*ft_malloc_check(void *s)
{
	if (s == 0)
	{
		printf("Error\n");
		exit(1);
	}
	return (s);
}
