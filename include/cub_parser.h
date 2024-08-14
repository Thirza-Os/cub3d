#ifndef DDA_H
# define DDA_H

#include <stdbool.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

#include "./cub_structs.h"

# include "../libft/include/libft.h"



bool	parser(char *arg);
bool	check_cub(char *arg);
char	**tokenize_input(char *argv);

#endif
