#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <math.h>

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/include/libft.h"

# include "./cub_structs.h"

bool	init_mlx(t_program *program);
void	clean_cub(t_program *program, t_player *player);

#endif
