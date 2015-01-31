/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/28 18:40:14 by bbarakov          #+#    #+#             */
/*   Updated: 2015/01/31 16:42:30 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_sh1.h"

int
	examine_path(t_cd *lst, char **env)
{
	struct stat 	buf;

	if ((lst->opt_p == 0 && lst->opt_l == 0) || lst->opt_l == 1)
	{
		lstat(lst->path, &buf);
		if (S_ISLNK(buf.st_mode))
		{
			if (chdir(lst->path) == -1)
			{
				cd_errors(&lst);
				return (0);
			}
			change_or_add_env_var("PWD=", lst->path, &env);
			change_or_add_env_var("OLDPWD=", lst->old_dir, &env);
			lst_init_or_free(&lst);
			return (0);
		}
	}
	return (1);
}

char
	*construct_path(t_cd *lst, char **env)
{
	char 			*path;

	path = 0;
	if (lst->name && lst->name[0] == '~')
		path = take_home_or_oldpwd("HOME=", &(lst->name[1]), env);
	else if (lst->name && lst->name[0] == '/')
		path = ft_strdup(lst->name);
	else
		path = ft_str3join(lst->old_dir, "/", lst->name);
	return (path);
}

int
	cd_proceed(char **cmd, char ***env, t_cd **lst)
{
	int 		i;

	if (cmd[1] == 0)
		(*lst)->path = take_home_or_oldpwd("HOME=", 0, *env);
	else if (cmd[1][0] == '-')
	{
		i = get_options_or_take_oldpwd(cmd[1], lst, *env, 1);
		if (i == 0)
			return (0);
		else if (i == 2)
			return (1);
		(*lst)->name = ft_strdup(cmd[2]);
	}
	else
		(*lst)->name = ft_strdup(cmd[1]);
	(*lst)->input = ft_strdup((*lst)->name);
	(*lst)->path = construct_path(*lst, *env);
	(*lst)->saved_path = ft_strdup((*lst)->path);
	if ((examine_path(*lst, *env)) == 0)
		return (0);
	return (1);
}

int
	failure_first_try(t_cd **lst, char **env)
{
	free((*lst)->path);
	(*lst)->path = second_try((*lst)->name, env);
	if (examine_path(*lst, env) == 0)
		return (0);
	if (chdir((*lst)->path) == -1)
	{
		cd_errors(lst);
		return (0);
	}
	return (1);
}

void
	cd_builtin(char **cmd, char ***env)
{
	t_cd		*lst;

	lst = 0;
	lst_init_or_free(&lst);
	getcwd(lst->old_dir, 4096);
	if (cd_proceed(cmd, env, &lst) == 0)
		return ;
	if (chdir(lst->path) == -1)
	{
		if (failure_first_try(&lst, *env) == 0)
			return ;
	}
	getcwd(lst->new_dir, 4096);
	change_or_add_env_var("PWD=", lst->new_dir, env);
	change_or_add_env_var("OLDPWD=", lst->old_dir, env);
	lst_init_or_free(&lst);
}








