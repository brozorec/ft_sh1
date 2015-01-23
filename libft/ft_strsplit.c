/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 19:18:24 by bbarakov          #+#    #+#             */
/*   Updated: 2014/11/15 16:49:47 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*str_cut(char *str, char c, int *j)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = 0;
	while (str[i] == c)
		i++;
	while (str[i] != c && str[i] != '\0')
	{
		len++;
		i++;
	}
	new = ft_strnew(len);
	if (new == 0)
		return (0);
	ft_memcpy(new, &str[i - len], len);
	*j += i;
	return (new);
}

static int		member_count(char *str, char c)
{
	int		i;
	int		j;
	int		count;

	count = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i] != c && str[i] != '\0')
		{
			j++;
			i++;
		}
		if (j != 0)
			count++;
		else
			i++;
	}
	return (count);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	char	*copy;
	int		len;
	int		i;
	int		j;

	if (!s)
		return (0);
	copy = (char *)s;
	len = member_count(copy, c);
	tab = (char **)malloc(sizeof(*tab) * (len + 1));
	if (tab == 0)
		return (0);
	i = 0;
	j = 0;
	while (i < len)
	{
		tab[i] = str_cut(copy + j, c, &j);
		i++;
	}
	tab[len] = 0;
	return (tab);
}
