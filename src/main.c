/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/09 22:23:20 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/22 19:22:55 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// static	void	run_game(t_program *program)
// {
// 	program->dda = init_dda(program->player);
// 	if (program->dda == NULL)
// 		free_cub(program, errno);
// 	if (init_mlx(program) != true)
// 		free_cub(program, errno);
// 	mlx_loop_hook(program->mlx_state->mlx, hooks, program);
// 	mlx_loop_hook(program->mlx_state->mlx, &render, (void *)program);
// 	mlx_close_hook(program->mlx_state->mlx, &_free_cub, (void *)program);
// 	mlx_loop(program->mlx_state->mlx);
// }

int	main(int argc, char **argv)
{
	t_program	*program;

	if (argc != 2)
	{
		ft_putstr_fd("Expect 1 argument for the map\n", 2);
		return (1);
	}
	program = ft_calloc(1, sizeof(*program));
	if (program == NULL)
	{
		perror("init program");
		return (2);
	}
	program->player = ft_calloc(1, sizeof(*program->player));
	if (program->player == NULL)
	{
		perror("Failed to create player");
		free_cub(program, 3);
		return (3);
	}
	if (parser(argv[1], program) != true)
		free_cub(program, 4);
	// run_game(program);
	return (0);
}
