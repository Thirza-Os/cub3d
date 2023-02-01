/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 18:40:22 by tosinga       #+#    #+#                 */
/*   Updated: 2022/02/02 18:40:22 by tosinga       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str2;
	int		a;
	int		len;

	if (s1 == 0)
		return (0);
	a = 0;
	len = ft_strlen(s1);
	while (s1[a] && ft_strchr(set, s1[a]))
		a++;
	while (len > 0 && ft_strchr(set, s1[len]))
		len--;
	str2 = ft_substr(s1, a, len - a + 1);
	return (str2);
}
