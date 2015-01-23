/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 12:11:37 by bbarakov          #+#    #+#             */
/*   Updated: 2014/11/13 11:22:27 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*s;

	if (size == 0)
		return (0);
	s = (char *)malloc(sizeof(*s) * (size + 1));
	if (s == 0)
		return (0);
	ft_memset(s, '\0', size + 1);
	return (s);
}
