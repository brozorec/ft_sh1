/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 17:10:41 by bbarakov          #+#    #+#             */
/*   Updated: 2014/11/12 13:12:23 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int		i;
	char	*str;

	str = (char *)s1;
	if (*s2 == 0)
		return (str);
	i = ft_strlen(s2);
	while (*str != '\0')
	{
		if (ft_strncmp(str, s2, i) == 0)
			return (str);
		str++;
	}
	return (0);
}
