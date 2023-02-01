/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tosinga <tosinga@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 18:39:53 by tosinga       #+#    #+#                 */
/*   Updated: 2022/02/02 18:39:53 by tosinga       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_length(char const *s, char c)
{
	int	a;

	a = 0;
	while (s[a] && s[a] != c)
		a++;
	return (a);
}

static int	ft_count_splits(char const *s, char c)
{
	int	count;
	int	a;

	count = 0;
	while (*s)
	{
		a = ft_count_length(s, c);
		if (a > 0)
		{
			count++;
			s += a;
		}
		else
			(s++);
	}
	return (count);
}

static char	**ft_make_splits(char const *s, char **arr, char c)
{
	int	sub;
	int	sub_count;

	sub_count = 0;
	while (*s)
	{
		sub = ft_count_length(s, c);
		if (sub > 0)
		{
			arr[sub_count] = ft_substr(s, 0, sub);
			if (arr[sub_count] == 0)
				return (ft_free(arr));
			sub_count++;
			s += sub;
		}
		else
			(s++);
	}
	arr[sub_count] = 0;
	return (arr);
}

char	**ft_split(char const *s, char c)
{	
	int		count;
	char	**arr;

	if (s == 0)
		return (0);
	count = ft_count_splits(s, c);
	arr = (char **)malloc((count + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	arr = ft_make_splits(s, arr, c);
	return (arr);
}
