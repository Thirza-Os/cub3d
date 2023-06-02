/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 18:40:20 by tosinga       #+#    #+#                 */
/*   Updated: 2022/02/02 18:40:20 by tosinga       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*str;
	int				i;
	unsigned char	d;

	d = c;
	i = ft_strlen(s);
	str = (char *)s;
	while (i >= 0)
	{
		if (s[i] == d)
			return (str + i);
		--i;
	}
	return (0);
}
