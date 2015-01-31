/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/27 11:00:30 by bbarakov          #+#    #+#             */
/*   Updated: 2015/01/31 17:00:47 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_sh1.h"

void		err_msg(char *err)
{
	int			i;

	i = 0;
	while (err && err[i])
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

void		cd_errors(t_cd **lst)
{
	struct stat		buf;

	if (stat((*lst)->saved_path, &buf) == -1 && stat((*lst)->path, &buf) == -1)
	{
		err_msg("cd: no such file or directory: ");
		err_msg((*lst)->input);
		err_msg("\n");
		lst_init_or_free(lst);
		return ;
	}
	if (S_ISDIR(buf.st_mode))
	{
		err_msg("cd: permission denied: ");
		err_msg((*lst)->input);
		err_msg("\n");
	}
	else
	{
		err_msg("cd: not a directory: ");
		err_msg((*lst)->input);
		err_msg("\n");
	}
	lst_init_or_free(lst);
}
