/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 12:05:45 by bbarakov          #+#    #+#             */
/*   Updated: 2014/12/01 11:43:58 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_listnew(void const *content)
{
	t_list		*new;
	size_t		len;

	new = NULL;
	new = (t_list *)malloc(sizeof(t_list));
	if (new)
	{
		if (content == NULL)
			new->content = NULL;
		else
		{
			len = ft_strlen(content);
			new->content = (void *)malloc(len + 1);
			if (new->content == NULL)
				return (0);
			ft_memcpy(new->content, content, len);
		}
		new->next = NULL;
	}
	return (new);
}
