/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 19:06:22 by bbarakov          #+#    #+#             */
/*   Updated: 2014/11/09 13:29:51 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	char		*str;
	size_t		len;

	str = (char *)s1;
	if (*s2 == 0)
		return (str);
	len = ft_strlen(s2);
	while (*str != '\0' && n > 0)
	{
		if (ft_strncmp(str, s2, len) == 0 && n >= len)
		{
			return (str);
		}
		str++;
		n--;
	}
	return (0);
}
