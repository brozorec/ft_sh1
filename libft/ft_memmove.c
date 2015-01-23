/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 15:28:26 by bbarakov          #+#    #+#             */
/*   Updated: 2014/11/12 17:16:49 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ptr_overlap(void *s1, void *s2, size_t len)
{
	char	*copys1;
	char	*copys2;

	copys1 = s1;
	copys2 = s2;
	while (len-- && copys2++)
		if (copys1 == copys2)
			return (1);
	return (0);
}

void			*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dstcopy;
	char	*srccopy;
	int		i;

	dstcopy = dst;
	srccopy = (char *)src;
	i = ptr_overlap(dstcopy, srccopy, len);
	if (i == 0)
		return (ft_memcpy(dstcopy, srccopy, len));
	else
	{
		dstcopy += len;
		srccopy += len;
		while (len--)
			*--dstcopy = *--srccopy;
	}
	return (dstcopy);
}
