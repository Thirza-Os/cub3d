#ifndef DDA_H
# define DDA_H

#include <stdint.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
#include <math.h>
#include <stdio.h>

#include "./cub_structs.h"
#include "../libft/include/libft.h"


t_dda	*init_dda(t_player *player);
void	dda(t_program *program);
void	dda_col(t_dda *dda, int col);
void	draw_info_calc(t_dda *dda);
void	fill_buffer(t_mlx_state *mlx_state, t_dda *dda, int col);
void	textures(t_mlx_state *mlx_state, t_dda *dda, int col);
void	hooks(void *param);
bool	hitting_wall(const t_dda *dda, int row, int col);

void	print_dda(t_dda *dda);
#endif
