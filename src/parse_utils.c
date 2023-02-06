#include "cub3d.h"

int ft_isspace(char c)
{
    if (c == 32 || (c > 8 && c < 14))
        return (1);
    return (0);
}
