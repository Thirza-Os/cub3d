/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rickmain.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/01 10:54:03 by rbrune        #+#    #+#                 */
/*   Updated: 2023/02/01 11:02:19 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main (int ac, char **av)
{
	mlx_image_t			*g_img;
	mlx_t				*mlx_p;
	

	(void)ac;
	(void)av;
	mlx_p = mlx_init(1000, 1000, "Cub3d", true);
	g_img = mlx_new_image(mlx_p, 1000, 1000);
	mlx_image_to_window(mlx_p, g_img, 0, 0);
}