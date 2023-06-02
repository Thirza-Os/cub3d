/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 18:40:17 by tosinga       #+#    #+#                 */
/*   Updated: 2022/02/02 18:40:18 by tosinga       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned long	a;
	unsigned long	b;

	a = 0;
	if (*needle == 0)
		return ((char *)haystack);
	while (haystack[a] && len > a)
	{
		if (haystack[a] == needle[0])
		{
			b = 0;
			while (haystack[a + b] == needle[b] && needle[b] && (a + b) < len)
			{
				if (needle[b + 1] == '\0')
					return ((char *)&haystack[a]);
				b++;
			}
		}
		a++;
	}
	return (0);
}
