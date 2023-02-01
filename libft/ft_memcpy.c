/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 18:39:36 by tosinga       #+#    #+#                 */
/*   Updated: 2022/02/02 18:39:36 by tosinga       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//ft_memmove depends on memcpy
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
