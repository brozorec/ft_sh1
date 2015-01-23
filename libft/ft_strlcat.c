/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 16:27:17 by bbarakov          #+#    #+#             */
/*   Updated: 2014/11/10 12:03:21 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*s;
	size_t		dlen;
	size_t		slen;

	s = (char *)src;
	dlen = ft_strlen(dst);
	slen = ft_strlen(s);
	if (size <= dlen)
		return (size + slen);
	dst += dlen;
	size -= (dlen + 1);
	while (*s && size)
	{
		*dst = *s;
		dst++;
		size--;
		s++;
	}
	*dst = '\0';
	return (dlen + slen);
}
