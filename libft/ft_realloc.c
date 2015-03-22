/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/19 20:45:17 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/16 15:11:30 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *s, size_t size)
{
	void	*tmp;

	if (s == 0)
	{
		if ((s = (void *)malloc(sizeof(*s) * size)) != 0)
			return (s);
		else
			return (0);
	}
	if ((tmp = (void *)malloc(sizeof(*s) * (ft_strlen(s) + size))) == 0)
		return (0);
	ft_strncpy(tmp, s, ft_strlen(s) + 1);
	free(s);
	return (tmp);
}
