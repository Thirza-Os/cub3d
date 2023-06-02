#include "cub3d.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)

{
	char		*own_dst;
	const char	*own_src;
	int			a;

	a = 0;
	own_dst = dst;
	own_src = src;
	if (dst == src)
		return (dst);
	while (n > 0)
	{
		own_dst[a] = own_src[a];
		n--;
		a++;
	}
	return (dst);
}

unsigned long	ft_strlen(const char *s)
{
	unsigned long	i;

	if (s == 0)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*pntr;
	int		len;
	int		i;

	len = ft_strlen(s1);
	pntr = (void *)malloc(len + 1);
	if (pntr == 0)
		return (0);
	i = 0;
	while (s1[i])
	{
		pntr[i] = s1[i];
		i++;
	}
	pntr[i] = '\0';
	return (pntr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*pntr;
	int		a;
	size_t	s_len;

	if (s == 0)
		return (0);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (s_len > len)
		s_len = len;
	pntr = (char *)malloc(s_len + 1);
	if (pntr == 0)
		return (0);
	a = 0;
	while (s_len > 0)
	{
		pntr[a] = s[start];
		a++;
		start++;
		s_len--;
	}
	pntr[a] = '\0';
	return (pntr);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n > 0)
	{
		if (*(unsigned char *)s == (unsigned char)c)
		{
			return ((void *)s);
		}
		s++;
		n--;
	}
	return (0);
}
