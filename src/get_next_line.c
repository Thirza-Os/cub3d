#include "cub3d.h"

static char	*ft_strjoin_free(char const *s1, char const *s2, size_t i)
{
	char	*str;
	size_t	a;
	size_t	b;

	str = (char *)malloc(ft_strlen(s1) + i + 1);
	if (str == NULL)
	{
		free ((char *)s1);
		return (NULL);
	}
	a = ft_strlen(s1);
	b = 0;
	ft_memcpy(str, s1, a);
	while (s2[b] && i > b)
	{
		str[a] = s2[b];
		a++;
		b++;
	}
	str[a] = '\0';
	free((char *)s1);
	return (str);
}

static int	fill_buff(int fd, char **remain, char *buff)
{
	ssize_t	ret_read;

	if (*remain)
	{
		ret_read = ft_strlen(*remain);
		ft_memcpy(buff, *remain, ret_read + 1);
		free(*remain);
		*remain = 0;
	}
	else
	{
		ret_read = read(fd, buff, (sizeof(char) * BUFFER_SIZE));
		if (ret_read < 0)
		{
			free(buff);
			return (-1);
		}
		buff[ret_read] = '\0';
	}
	return (ret_read);
}

static ssize_t	n_line(ssize_t ret_read, int fd, char *buff, char **ret_buff)
{
	while (ret_read > 0 && ft_memchr(buff, '\n', ret_read) == NULL)
	{
		if (*ret_buff == NULL)
			*ret_buff = ft_strdup(buff);
		else
			*ret_buff = ft_strjoin_free(*ret_buff, buff, ret_read);
		if (*ret_buff == 0)
		{
			free(*ret_buff);
			free(buff);
			return (-1);
		}
		ret_read = read(fd, buff, (sizeof(char) * BUFFER_SIZE));
		if (ret_read < 0)
		{
			free(buff);
			free(*ret_buff);
			return (-1);
		}
		buff[ret_read] = '\0';
	}
	return (ret_read);
}

static void	w_line(ssize_t ret_read, char *buff, char **ret_buff, char **remain)
{
	ssize_t		index;

	if (ret_read > 0 && ft_memchr(buff, '\n', ret_read) != NULL)
	{
		index = (size_t)ft_memchr(buff, '\n', ret_read) - (size_t)buff;
		if (index + 1 != ret_read)
			*remain = ft_strdup(buff + (index + 1));
		if (*ret_buff == NULL)
			*ret_buff = ft_substr(buff, 0, index + 1);
		else
			*ret_buff = ft_strjoin_free(*ret_buff, buff, index + 1);
	}
}

char	*get_next_line(int fd)
{
	char		*buff;
	char		*ret_buff;
	static char	*remain;
	ssize_t		ret_read;

	ret_buff = NULL;
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buff == 0)
	{
		free(remain);
		remain = NULL;
		return (NULL);
	}
	ret_read = n_line((fill_buff(fd, &remain, buff)), fd, buff, &ret_buff);
	if (ret_read < 0)
		return (NULL);
	w_line(ret_read, buff, &ret_buff, &remain);
	if (ret_buff == NULL)
	{
		free(remain);
		remain = NULL;
	}
	free(buff);
	return (ret_buff);
}
