#include "../../include/cub_parser.h"
#include "../../include/cub3D.h"

static	char	*_ident_error(char *msg, int error)
{
	ft_putendl_fd(msg, 2);
	if (error != 0)
		errno = error;
	return (NULL);
}

char	*_parse_ident(char **elements, int index, char *line)
{
	char	*temp;

	if (elements[index] != NULL)
		return (_ident_error("Invalid object input", EINVAL));
	if (index < 4)
		elements[index] = ft_substr(line, 2, (ft_strlen(line) - 2));
	else
		elements[index] = ft_substr(line, 1, (ft_strlen(line) - 1));
	if (elements[index] == NULL)
		return (_ident_error("substring failed", 0));
	temp = ft_strtrim(elements[index], WHITESPACE);
	if (temp == NULL)
		return (_ident_error("trim failed", 0));
	return (temp);
}

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
