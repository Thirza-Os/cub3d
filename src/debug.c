/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 01:42:12 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/09 01:43:12 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/dda.h"

void	print_dda(t_dda *dda)
{
	printf("plane row: %f, plane col: %f\n", dda->plane.row, dda->plane.col);
	printf("player_pos row: %f, player_pos col: %f\n", dda->player_pos.row, \
		dda->player_pos.col);
	printf("delta_dist row: %f, delta_dist col: %f\n", dda->delta_dist.row, \
		dda->delta_dist.col);
	printf("delta_dist row: %f, delta_dist col: %f\n", dda->delta_dist.row, \
		dda->delta_dist.col);
	printf("map_pos row: %d, map_pos col: %d\n", dda->map_pos.row, \
		dda->map_pos.col);
	printf("step_map row: %d, step_map col: %d\n", dda->step_map.row, \
		dda->step_map.col);
	printf("player_dir row: %f, player_dir col: %f\n", dda->player_dir.row, \
		dda->player_dir.col);
	printf("ray_dir row: %f, ray_dir col: %f\n", dda->ray_dir.row, \
		dda->ray_dir.col);
	printf("camera_x: %f\n", dda->camera_x);
	printf("perp_wall_dist: %f\n", dda->perp_wall_dist);
	printf("line heigth: %d\n", dda->line.heigth);
	printf("line start: %d\n", dda->line.start);
	printf("line end: %d\n", dda->line.end);
	printf("\n");
}
