/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 10:48:00 by bbarakov          #+#    #+#             */
/*   Updated: 2014/11/08 10:59:02 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(s1);
	while (s2[i] && n)
	{
		s1[j] = s2[i];
		i++;
		j++;
		n--;
	}
	s1[j] = '\0';
	return (s1);
}
