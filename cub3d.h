/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/01 10:55:06 by rbrune        #+#    #+#                 */
/*   Updated: 2023/02/01 12:49:07 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./MLX42/include/MLX42/MLX42.h"
# include "./libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef struct s_cub3d {
	mlx_image_t	*g_img_p;
	mlx_t		*mlx_p;
	int			player_x;
	int			player_y;
	
} t_cub3d;

#endif