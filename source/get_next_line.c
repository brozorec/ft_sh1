/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 16:52:40 by bbarakov          #+#    #+#             */
/*   Updated: 2015/02/09 16:30:05 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_struct
	*create_new_struct(int fd)
{
	t_struct			*new;

	new = (t_struct *)malloc(sizeof(t_struct));
	if (!new)
		return (0);
	new->content = 0;
	new->index = fd;
	new->next = 0;
	return (new);
}

void
	free_and_move(int fd, t_struct **old, t_struct *tmp, t_struct *t)
{
	if ((*old)->content && ft_strlen((*old)->content) == 0)
	{
		ft_strdel(&((*old)->content));
		if (tmp)
			*old = tmp;
		while (*old)
		{
			if ((*old)->index == fd)
			{
				if (t == 0)
					tmp = (*old)->next;
				else
					t->next = (*old)->next;
				free(*old);
				*old = t;
				break ;
			}
			t = *old;
			*old = (*old)->next;
		}
	}
	if (tmp)
		*old = tmp;
}

t_struct
	*check_old(int fd, char **line, t_struct *old, t_struct *tmp)
{
	*line = 0;
	if (old == 0)
	{
		if ((old = create_new_struct(fd)) == 0)
			return (0);
		return (old);
	}
	while (old)
	{
		if (old->index == fd)
		{
			ft_strdel(line);
			*line = ft_strdup(old->content);
			ft_strdel(&(old->content));
			return (old);
		}
		tmp = old;
		old = old->next;
	}
	old = tmp;
	if ((old->next = create_new_struct(fd)) == 0)
		return (0);
	old = old->next;
	return (old);
}

int
	search_new_line(int fd, char **line, t_struct **old, t_struct *tmp)
{
	size_t				i;

	i = 0;
	if (*line == 0)
	{
		*line = ft_strnew(BUFF_SIZE + 1);
		return (0);
	}
	while ((*line)[i])
	{
		if ((*line)[i] == '\n')
		{
			(*line)[i++] = '\0';
			break ;
		}
		i++;
	}
	if (ft_strlen(*line) == i)
	{
		*line = ft_realloc(*line, i + BUFF_SIZE + 2);
		return (0);
	}
	(*old)->content = ft_strdup(*line + i);
	free_and_move(fd, old, tmp, 0);
	return (1);
}

int
	get_next_line(int const fd, char **line)
{
	static t_struct		*old;
	t_struct			*tmp;
	int					ret;
	char				buf[BUFF_SIZE + 1];

	if (line == 0)
		return (-1);
	tmp = old;
	if ((old = check_old(fd, line, old, 0)) == 0)
		return (-1);
	if (search_new_line(fd, line, &old, tmp) != 0)
		return (1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		*line = ft_strcat(*line, buf);
		if (search_new_line(fd, line, &old, tmp) != 0)
			return (1);
	}
	free_and_move(fd, &old, tmp, 0);
	if (ret < 0)
		return (-1);
	if (ft_strlen(*line) != 0)
		return (1);
	return (0);
}
