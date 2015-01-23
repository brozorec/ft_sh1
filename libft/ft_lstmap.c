/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 19:27:15 by bbarakov          #+#    #+#             */
/*   Updated: 2014/11/16 15:12:24 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*elem;
	t_list	*new_list;

	elem = 0;
	new_list = 0;
	if (lst && f)
	{
		while (lst)
		{
			elem = ft_lstnew(lst->content, lst->content_size);
			if (!elem)
				return (0);
			elem = f(lst);
			ft_lstpush(&new_list, elem);
			lst = lst->next;
		}
	}
	return (new_list);
}
