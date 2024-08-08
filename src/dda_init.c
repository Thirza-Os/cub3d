#include "../include/cub3D.h"

// void	pre_dda_values_init(t_dda *dda)
// {
//     (void)dda;
// 	// int				i;
// 	// const char		dirs[4] = "NESW";
// 	// const double	values[4][4] = {{0, -1, 0.66, 0}, {1, 0, 0, 0.66},
// 	// 								{0, 1, -0.66, 0}, {-1, 0, 0, -0.66}};
// 	//
// 	// i = 0;
// 	// while (i < 4)
// 	// {
// 	// 	if (dirs[i] == dda->p->starting_dir)
// 	// 	{
// 	// 		dda->player_dir.col = values[i][0];
// 	// 		dda->player_dir.row = values[i][1];
// 	// 		dda->plane.col = values[i][2];
// 	// 		dda->plane.row = values[i][3];
// 	// 		break ;
// 	// 	}
// 	// 	i++;
// 	// }
// }

static int	set_texture_struct(t_dda *dda)
{
    (void)dda;
	// dda->textures[N_INDEX] = NULL;
	// dda->textures[S_INDEX] = NULL;
	// dda->textures[W_INDEX] = NULL;
	// dda->textures[E_INDEX] = NULL;
	// dda->textures[N_INDEX] = mlx_load_png(dda->p->path_north_texture);
	// if (!dda->textures[N_INDEX])
	// 	return (1);
	// dda->textures[S_INDEX] = mlx_load_png(dda->p->path_south_texture);
	// if (!dda->textures[S_INDEX])
	// 	return (1);
	// dda->textures[W_INDEX] = mlx_load_png(dda->p->path_west_texture);
	// if (!dda->textures[W_INDEX])
	// 	return (1);
	// dda->textures[E_INDEX] = mlx_load_png(dda->p->path_east_texture);
	// if (!dda->textures[E_INDEX])
	// 	return (1);
	return (0);
}

t_dda	*dda_init(t_player *p)
{
	t_dda	*dda;
    (void)p;

	dda = (t_dda *)malloc(sizeof(t_dda));
	if (!dda)
	{
		return (NULL);
	}
    set_texture_struct(NULL);
	// dda->p = NULL;
	// dda->p = p;
	// dda->player_pos.col = dda->p->player_pos.col + 0.5;
	// dda->player_pos.row = dda->p->player_pos.row + 0.5;
	// pre_dda_values_init(dda);
	// if (set_texture_struct(dda))
	// {
	// 	printf("nog maken\n");
	// 	return (NULL);
	// }
	return (dda);
}
