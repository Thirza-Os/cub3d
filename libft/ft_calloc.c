/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 18:38:48 by tosinga       #+#    #+#                 */
/*   Updated: 2022/02/02 18:38:48 by tosinga       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	nr;
	void	*pntr;

	nr = count * size;
	pntr = (void *)malloc(nr);
	if (pntr == NULL)
		return (NULL);
	ft_bzero(pntr, nr);
	return (pntr);
}
