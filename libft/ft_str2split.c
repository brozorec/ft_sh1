/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str2split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 15:27:17 by bbarakov          #+#    #+#             */
/*   Updated: 2015/02/09 15:32:38 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*str_cut(char *str, char c, char d, int *j)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = 0;
	while (str && (str[i] == c || str[i] == d))
		i++;
	while (str && str[i] != c && str[i] != d && str[i] != '\0')
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

static int		member_count(char *str, char c, char d)
{
	int		i;
	int		j;
	int		count;

	count = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i] != c && str[i] != d && str[i] != '\0')
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

char			**ft_str2split(char const *s, char c, char d)
{
	char	**tab;
	char	*copy;
	int		len;
	int		i;
	int		j;

	if (!s)
		return (0);
	copy = (char *)s;
	len = member_count(copy, c, d);
	tab = (char **)malloc(sizeof(*tab) * (len + 1));
	if (tab == 0)
		return (0);
	i = 0;
	j = 0;
	while (i < len)
	{
		tab[i] = str_cut(copy + j, c, d, &j);
		i++;
	}
	tab[len] = 0;
	return (tab);
}
