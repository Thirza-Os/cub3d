/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 18:38:43 by tosinga       #+#    #+#                 */
/*   Updated: 2022/02/02 18:38:43 by tosinga       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(long i, int c)
{
	if (i < INT_MIN || i > INT_MAX)
	{
		if (c > 0)
			return (-1);
		if (c < 0)
			return (0);
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	long	i;
	int		c;

	i = 0;
	c = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		c = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		i = (i * 10 + *str - '0');
		str++;
	}
	return (ft_check(i * c, c));
}
