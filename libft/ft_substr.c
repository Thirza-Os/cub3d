/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 18:40:24 by tosinga       #+#    #+#                 */
/*   Updated: 2022/02/02 18:40:24 by tosinga       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
