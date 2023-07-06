/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks_determine_ra.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/06 14:02:08 by rbrune        #+#    #+#                 */
/*   Updated: 2023/07/06 14:02:09 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "../engine.h"

void	determine_ra(t_cub3d *eng, int direction)
{
	if (direction == 1)
		eng->ra = eng->player_a - 0.2;
	else if (direction == 2)
	{
		if (eng->player_a < PI + 0.2)
			eng->ra = eng->player_a + PI - 0.2;
		else
			eng->ra = eng->player_a - PI - 0.2;
	}
	else if (direction == 3)
	{
		if (eng->player_a < PI / 2)
			eng->ra = eng->player_a + PI / 2 - 0.2;
		else
			eng->ra = eng->player_a - PI / 2 - 0.2;
	}
	else if (direction == 4)
	{
		if (eng->player_a < PI / 2)
			eng->ra = eng->player_a - PI / 2 - 0.2;
		else
			eng->ra = eng->player_a + PI / 2 - 0.2;
	}
}
