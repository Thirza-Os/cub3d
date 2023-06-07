/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 13:03:26 by rbrune        #+#    #+#                 */
/*   Updated: 2023/06/07 12:36:00 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "../engine.h"

void	drawgame(t_program *program);

int	main(int argc, char *argv[])
{
	t_program	program;

	if (argc != 2)
		print_error("Invalid argument(s)");
	program = parser(argv);
	drawgame(&program);
	system("leaks cub3d");
	return (0);
}