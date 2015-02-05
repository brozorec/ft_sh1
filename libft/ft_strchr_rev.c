/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_rev.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 18:40:41 by bbarakov          #+#    #+#             */
/*   Updated: 2015/02/05 12:56:57 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strchr_rev(const char *s, int c)
{
	char		*str;
	char		ch;
	int			i;
	int			len;

	i = 0;
	len = 0;
	ch = (char)c;
	if (s == 0)
		return (0);
	while (s[i] && s[i] != ch)
	{
		++i;
		++len;
	}
	str = (char *)malloc(len + 2);
	str = ft_strncpy(str, s, len + 1);
	return (str);
}
