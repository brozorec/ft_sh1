/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 15:29:46 by bbarakov          #+#    #+#             */
/*   Updated: 2015/02/06 18:14:25 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"
#include "ft_sh1_prototypes.h"

void
	lst_init_or_free(t_cd **lst)
{
	if (*lst == 0)
	{
		*lst = (t_cd *)malloc(sizeof(t_cd));
		(*lst)->opt_l = 0;
		(*lst)->opt_p = 0;
		(*lst)->name = 0;
		(*lst)->path = 0;
		(*lst)->input = 0;
		(*lst)->saved_path = 0;
	}
	else
	{
		free((*lst)->path);
		free((*lst)->name);
		free((*lst)->input);
		free((*lst)->saved_path);
		free(*lst);
	}
}

char
	*second_try(char *name, char **env)
{
	char				*path;
	char				*new_path;
	char				*truncated;
	int					i;

	if ((path = lookup_paths("CDPATH=", name, env)) != 0)
	{
		return (path);
	}
	truncated = ft_strdup(ft_strchr(name, '/'));
	i = ft_strlen(name) - ft_strlen(truncated);
	ft_bzero(&name[i], ft_strlen(truncated));
	if ((path = lookup_paths("CDPATH=", name, env)) != 0)
	{
		new_path = ft_strjoin(path, truncated);
		free(truncated);
		return (new_path);
	}
	return (0);
}

int
	get_options_or_take_oldpwd(char *cmd, t_cd **lst, char **env, int i)
{
	while (cmd[i])
	{
		if (cmd[i] != 'L' && cmd[i] != 'P')
		{
			cd_options_err(cmd[i]);
			return (0);
		}
		else if (cmd[i] == 'L' && (*lst)->opt_p == 0)
			(*lst)->opt_l = 1;
		else if (cmd[i] == 'P' && (*lst)->opt_l == 0)
			(*lst)->opt_p = 1;
		++i;
	}
	if ((*lst)->opt_p == 0 && (*lst)->opt_l == 0)
	{
		if (((*lst)->path = take_env_var("OLDPWD=", 0, env)) == 0)
		{
			err_msg(": No such file or directory.\n");
			return (0);
		}
		return (2);
	}
	return (1);
}
