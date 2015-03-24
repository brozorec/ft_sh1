/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/28 18:40:14 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/24 12:29:38 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"
#include "ft_sh1_prototypes.h"

int
	cd_proceed(char **cmd, char ***env, t_cd **lst, t_res **res)
{
	int					i;

	if (cmd[1] == 0)
		(*lst)->name = ft_strdup((*res)->home);
	else if (cmd[1][0] == '-')
	{
		if (get_options(cmd[1], lst) == -1 ||
			(i = take_oldpwd(cmd, lst, *env)) == -1)
			return (-1);
		if (i == 1)
			return (0);
		(*lst)->name = ft_strdup(cmd[2]);
	}
	else
		(*lst)->name = ft_strdup(cmd[1]);
	(*lst)->input = ft_strdup((*lst)->name);
	(*lst)->path = construct_path(*lst);
	(*lst)->saved_path = ft_strdup((*lst)->path);
	if (check_too_many_args(*lst, cmd) == -1)
		return (-1);
	examine_path(lst);
	return (0);
}

char
	*second_try(char *name, char **env)
{
	char				*path;
	char				*new_path;
	char				*truncated;
	int					i;

	if ((path = lookup_paths("CDPATH=", name, env)) != 0)
		return (path);
	truncated = ft_strdup(ft_strchr(name, '/'));
	i = ft_strlen(name) - ft_strlen(truncated);
	ft_bzero(&name[i], ft_strlen(truncated));
	if ((path = lookup_paths("CDPATH=", name, env)) != 0)
	{
		new_path = ft_strjoin(path, truncated);
		free(truncated);
		free(path);
		return (new_path);
	}
	free(truncated);
	return (0);
}

int
	chdir_to_cdpath(t_cd **lst, char ***env)
{
	free((*lst)->path);
	(*lst)->path = second_try((*lst)->name, *env);
	examine_path(lst);
	if (chdir((*lst)->path) == -1)
	{
		cd_errors(lst);
		return (-1);
	}
	return (0);
}

void
	cd_builtin(char **cmd, char ***env, t_res **res)
{
	t_cd		*lst;
	char		*oldpwd;

	lst = 0;
	lst_init_or_free(&lst);
	oldpwd = take_env_var("PWD=", 0, *env);
	if (ft_strcpy(lst->old_dir, oldpwd) == 0)
		getcwd(lst->old_dir, 4096);
	free(oldpwd);
	if (cd_proceed(cmd, env, &lst, res) == -1)
	{
		lst_init_or_free(&lst);
		return ;
	}
	if (chdir(lst->path) == -1)
	{
		if (chdir_to_cdpath(&lst, env) == -1)
		{
			lst_init_or_free(&lst);
			return ;
		}
	}
	change_or_add_env_var("PWD=", lst->path, env);
	change_or_add_env_var("OLDPWD=", lst->old_dir, env);
	lst_init_or_free(&lst);
}
