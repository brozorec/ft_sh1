/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 15:32:26 by bbarakov          #+#    #+#             */
/*   Updated: 2014/11/15 18:27:57 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char		*new;

	if (!s || len == 0)
		return (0);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	new = (char *)malloc(sizeof(*new) * (len + 1));
	if (!new)
		return (0);
	ft_memcpy(new, s + start, len);
	new[len] = '\0';
	return (new);
}
