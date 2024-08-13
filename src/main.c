/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 22:23:20 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/13 01:46:26 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
#include "../include/dda.h"

char *map = "\
111111111111111111111111\n\
100000000000000000000001\n\
100000000000000000000001\n\
100000000000000000000001\n\
100000111110000101010001\n\
100000100010000000000001\n\
100000100010000100010001\n\
100000100010000000000001\n\
100000111110000101010001\n\
100000000000000000000001\n\
100000000000000000000001\n\
100000000000000000000001\n\
100000000000000000000001\n\
100000000000N00000000001\n\
100000000000000000000001\n\
100000000000000000000001\n\
111111111000000000000001\n\
110100001000000000000001\n\
110000101000000010000001\n\
110100001000000101000001\n\
110111111000000010000001\n\
110000000000000000000001\n\
111111111000000000000001\n\
111111111111111111111111\n";

t_player	*parser(t_program *program, const char *Gamemap)
{
	t_player	*player;
	size_t		row = 0;
	size_t		col = 0;

	player = ft_calloc(1, sizeof(*player));
	if (player == NULL)
	{
		perror("player");
		return (NULL);
	}
	player->map = ft_split(Gamemap, '\n');

	while (player->map[row] != NULL)
	{
		col = 0;
		while (player->map[row][col] != '\0')
		{
			if (player->map[row][col] == 'N' || player->map[row][col] == 'S' || player->map[row][col] == 'W' || player->map[row][col] == 'E')
			{
				player->player_pos.row = row;
				player->player_pos.col = col;
				player->starting_dir = player->map[row][col];
				player->map[row][col] = '0';
			}
			col++;
		}
		row++;
	}

	player->col_size = col;
	player->row_size = row;
	program->paths[0] = "tex/NO.png";
	program->paths[1] = "tex/EA.png";
	program->paths[2] = "tex/SO.png";
	program->paths[3] = "tex/WE.png";
	player->floor_color = 255;
	player->ceiling_color = 125;
	return (player);
}

int	main(int argc, char **argv)
{
	t_program	*program;
	t_player	*player;

	(void)argc;
	(void)argv;
	program = ft_calloc(1, sizeof(*program));
	if (program == NULL)
	{
		perror("init program");
		return (1);
	}
	player = parser(program, map);
	if (player == NULL)
		clean_cub(program);
	program->dda = init_dda(player);
	if (program->dda == NULL)
		clean_cub(program);
	if (init_mlx(program) != true)
		clean_cub(program);
	mlx_loop_hook(program->mlx_state->mlx, hooks, program);
    mlx_loop_hook(program->mlx_state->mlx, &render, (void *)program);
	mlx_close_hook(program->mlx_state->mlx, clean_cub, program);
	mlx_loop(program->mlx_state->mlx);
	return (0);
}
