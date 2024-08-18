#include "../../include/cub_parser.h"

bool	_check_token(char *line, char **elements, bool flag)
{
	if (flag == true)
	{
		if (line[0] == '1')
		{
			elements[SIZE] = ft_strjoin_cub3d(elements[SIZE], line);
			if (elements[SIZE] == NULL)
			{
				ft_putendl_fd("Failed to join strings", 2);
				return (false);
			}
		}
		else
		{
			errno = EINVAL;
			ft_putendl_fd("Invalid input: Invalid map\n", 2);
			return (false);
		}
	}
	return (true);
}

char	*ft_strjoin_cub3d(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	index;

	s1_len = ft_strlen(s1);
	str = ft_calloc(s1_len + ft_strlen(s2) + 1, sizeof(*str));
	if (str == NULL)
		return (NULL);
	index = 0;
	ft_memcpy(str, s1, s1_len);
	while (s2[index] != '\0')
	{
		str[s1_len] = s2[index];
		s1_len++;
		index++;
	}
	str[s1_len] = '\0';
	return (str);
}

bool	check_cub(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (len == 0 || ft_strncmp(&arg[len - 4], ".cub", 5) != 0)
	{
		ft_putstr_fd("Not a .cub file!\n", 2);
		return (false);
	}
	return (true);
}

bool	check_png(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (len == 0 || ft_strncmp(&arg[len - 4], ".png", 4) != 0)
	{
		ft_putstr_fd("Not a .png file!\n", 2);
		return (false);
	}
	return (true);
}

int	ft_atorgb(const char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		i = (i * 10 + *str - '0');
		str++;
	}
	if (i < 0 || i > 255)
		return (-1);
	return (i);
}
