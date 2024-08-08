#include "../include/cub3D.h"
#include "cub_structs.h"
#include "libft.h"
#include <stdint.h>

static	bool	init_buffer(t_mlx_state *mlx_state)
{
	int	row;

	mlx_state->img_buffer = ft_calloc(SCR_HEIGHT + 1, sizeof(uint32_t *));
	if (mlx_state->img_buffer == NULL)
	{
		perror("img_buffer rows");
		return (false);
	}
	row = 0;
	while (row < SCR_HEIGHT)
	{
		mlx_state->img_buffer[row] = ft_calloc(SCR_WIDTH + 1, sizeof(uint32_t));
		if (mlx_state->img_buffer[row] == NULL)
		{
			perror("img_buffer cols");
			return (false);
		}
		row++;
	}
	return true;
}

bool	init_mlx(t_program *program)
{
	program->mlx_state = ft_calloc(1, sizeof(*program->mlx_state));
	if (program->mlx_state == NULL)
	{
		perror("init mlx_state");
		return (false);
	}
	program->mlx_state->mlx = mlx_init(SCR_WIDTH, SCR_HEIGHT, "test", true);
	if (!program->mlx_state->mlx)
	{
		perror(mlx_strerror(mlx_errno));
		return (false);
	}
	program->mlx_state->img = mlx_new_image(program->mlx_state->mlx, SCR_WIDTH, SCR_HEIGHT);
	if (!program->mlx_state->img)
	{
		perror(mlx_strerror(mlx_errno));
		return (false);
	}
	if (mlx_image_to_window(program->mlx_state->mlx, program->mlx_state->img, 0, 0) == -1)
	{
		perror(mlx_strerror(mlx_errno));
		return (false);
	}
	return (init_buffer(program->mlx_state));
}

// static void	free_textures(t_dda *dda)
// {
// 	if (dda->textures[N_INDEX] != NULL)
// 		mlx_delete_texture(dda->textures[N_INDEX]);
// 	if (dda->textures[S_INDEX] != NULL)
// 		mlx_delete_texture(dda->textures[S_INDEX]);
// 	if (dda->textures[W_INDEX] != NULL)
// 		mlx_delete_texture(dda->textures[W_INDEX]);
// 	if (dda->textures[E_INDEX] != NULL)
// 		mlx_delete_texture(dda->textures[E_INDEX]);
// }
