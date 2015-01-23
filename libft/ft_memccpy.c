/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 14:22:28 by bbarakov          #+#    #+#             */
/*   Updated: 2014/11/08 15:22:39 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*dstr;
	unsigned char		*sstr;
	unsigned char		ch;

	dstr = dst;
	sstr = (unsigned char *)src;
	ch = (unsigned char)c;
	while (n && sstr)
	{
		*dstr = *sstr;
		dstr++;
		if (*sstr == ch)
			return (dstr);
		sstr++;
		n--;
	}
	return (0);
}
