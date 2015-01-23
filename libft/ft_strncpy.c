/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 18:15:04 by bbarakov          #+#    #+#             */
/*   Updated: 2014/11/06 19:18:33 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	unsigned int p;
	unsigned int k;

	p = 0;
	k = n;
	while (src[p] != '\0' && k > 0)
	{
		dest[p] = src[p];
		p++;
		k--;
	}
	if (n > p)
	{
		while (p != n)
		{
			dest[p] = '\0';
			p++;
		}
	}
	return (dest);
}
