/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/27 11:00:30 by bbarakov          #+#    #+#             */
/*   Updated: 2015/01/27 13:25:24 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_sh1.h"

void		err_msg(char *err)
{
	int			i;

	i = 0;
	while (err[i])
	{
		write(2, &err[i], 1);
		++i;
	}
}

void		exit_err(int i)
{
	if (i > 0)
	{
		err_msg("exit: Badly formed number.\n");
		return ;
	}
	err_msg("exit: Expression Syntax.\n");
	return ;
}

void		cd_options_err(char a)
{
	err_msg("ft_sh1: cd: -");
	err_msg(&a);
	err_msg(": invalid option\ncd: usage: cd [-L|-P] [dir]\n");
}

void		cd_errors(char *path, char *cwdbuf)
{
	struct stat		buf;
	char			*new_path;

	if (path[0] != '/')
	{
		new_path = ft_strjoin(cwdbuf, "/");
		new_path = ft_strjoin(new_path, path);
	}
	else
		new_path = ft_strdup(path);
	if (stat(new_path, &buf) == -1)
	{
		err_msg("cd: no such file or directory: ");
		err_msg(path);
		err_msg("\n");
		return ;
	}
	if (S_ISDIR(buf.st_mode))
	{
		err_msg("cd: permission denied: ");
		err_msg(path);
		err_msg("\n");
	}
	else
	{
		err_msg("cd: not a directory: ");
		err_msg(path);
		err_msg("\n");
	}
}
