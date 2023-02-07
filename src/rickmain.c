/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rickmain.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/01 10:54:03 by rbrune        #+#    #+#                 */
/*   Updated: 2023/02/01 11:50:17 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_keyhook(mlx_key_data_t keydata, void *cubed)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(((t_cub3d *)cubed)->mlx_p);
}

int main (int ac, char **av)
{
	t_cub3d cubed;
	int 	i = 0;
	
	(void)ac;
	(void)av;
	cubed.mlx_p = mlx_init(1000, 1000, "Cub3d", true);
	cubed.g_img_p = mlx_new_image(cubed.mlx_p, 1000, 1000);
	mlx_image_to_window(cubed.mlx_p, cubed.g_img_p, 0, 0);
	mlx_key_hook(cubed.mlx_p, &my_keyhook, (void *)&cubed);
	while (i < 1000)
	{
		mlx_put_pixel(cubed.g_img_p, i, i, 0x666666FF);
		i++;
	}
	mlx_loop(cubed.mlx_p);
}