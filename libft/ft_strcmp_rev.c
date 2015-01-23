/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_rev.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 12:18:25 by bbarakov          #+#    #+#             */
/*   Updated: 2014/12/13 13:23:43 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long		ft_strcmp_rev(void *str1, void *str2)
{
	int			i;
	char		*s1;
	char		*s2;

	s1 = str1;
	s2 = str2;
	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s2[i] - (unsigned char)s1[i]);
		i++;
	}
	return ((unsigned char)s2[i] - (unsigned char)s1[i]);
}
