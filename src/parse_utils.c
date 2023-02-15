#include "cub3d.h"

int	ft_isspace(char c)
{
	if (c == 32 || (c > 8 && c < 14))
		return (1);
	return (0);
}

char	**ft_free_narr(char **arr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(arr[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin_cub3d(char const *s1, char const *s2)
{
	char	*str;
	size_t	a;
	size_t	b;

	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == NULL)
	{
		free ((char *)s1);
		free ((char *)s2);
		return (NULL);
	}
	a = ft_strlen(s1);
	b = 0;
	ft_memcpy(str, s1, a);
	while (s2[b])
	{
		str[a] = s2[b];
		a++;
		b++;
	}
	str[a] = '\0';
	free((char *)s1);
	return (str);
}

int	check_cub(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (len == 0 || ft_strncmp(&arg[len - 4], ".cub", 4) != 0)
		print_error("Not a .cub file!");
	return (0);
}

int	check_png(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (len == 0 || ft_strncmp(&arg[len - 4], ".png", 4) != 0)
		return (0);
	return (1);
}

int	ft_atorgb(const char *str)
{
	long	i;

	i = 0;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		i = (i * 10 + *str - '0');
		str++;
	}
	if (i > 255)
		return (-1);
	return (i);
}