/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 18:39:38 by tosinga       #+#    #+#                 */
/*   Updated: 2023/06/14 13:30:34 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*own_dst;
	const char	*own_src;

	own_dst = dst;
	own_src = src;
	if (dst == src)
		return (dst);
	if (dst > src)
	{
		while (len > 0)
		{
			own_dst[len - 1] = own_src[len - 1];
			len--;
		}
	}
	else
	{
		ft_memcpy(own_dst, own_src, len);
	}
	return (dst);
}
