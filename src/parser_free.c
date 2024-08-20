/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_free.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 21:11:55 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/20 21:12:00 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	free_parser(char **elements, bool state)
{
	size_t	row;

	row = 0;
	while (row <= SIZE)
	{
		if (elements[row] != NULL)
			free(elements[row]);
		row++;
	}
	free(elements);
	return (state);
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
