/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str3join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/27 15:18:21 by bbarakov          #+#    #+#             */
/*   Updated: 2015/01/27 15:24:44 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str3join(char const *s1, char const *s2, char const *s3)
{
	char	*new;
	int		len;

	if (!s1 && !s2 && !s3)
		return (0);
	if (!s1 && !s2)
		return (ft_strdup(s3));
	if (!s1 && !s3)
		return (ft_strdup(s2));
	if (!s2 && !s3)
		return (ft_strdup(s1));
	if (!s1)
		return (ft_strjoin(s2, s3));
	if (!s2)
		return (ft_strjoin(s1, s3));
	if (!s3)
		return (ft_strjoin(s1, s2));
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	if ((new = (char *)malloc(sizeof(*new) * (len + 1))) == 0)
		return (0);
	ft_strcpy(new, s1);
	ft_strcat(new, s2);
	ft_strcat(new, s3);
	return (new);
}
