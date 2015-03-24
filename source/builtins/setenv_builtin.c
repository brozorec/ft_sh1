/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:29:07 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/24 12:37:28 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"
#include "ft_sh1_prototypes.h"

int			already_set(char **cmd, char ***env)
{
	int			i;

	i = 0;
	while (*env && (*env)[i])
	{
		if (compare(cmd[1], (*env)[i]) > 0 && cmd[2] == 0)
		{
			free((*env)[i]);
			(*env)[i] = ft_strjoin(cmd[1], "=");
			return (1);
		}
		else if (compare(cmd[1], (*env)[i]) > 0 && cmd[3] == 0)
		{
			free((*env)[i]);
			(*env)[i] = ft_str3join(cmd[1], "=", cmd[2]);
			return (1);
		}
		++i;
	}
	return (0);
}

void		proceed_set(char **cmd, char ***env)
{
	char		*var;

	var = 0;
	if (ft_strchr(cmd[1], '='))
	{
		err_msg("setenv: Syntax Error.\n");
		return ;
	}
	if (already_set(cmd, env) == 0)
	{
		if (cmd[2] == 0)
			var = ft_strjoin(cmd[1], "=");
		else if (cmd[3] == 0)
			var = ft_str3join(cmd[1], "=", cmd[2]);
		*env = set_my_env(*env, var, 0, 1);
	}
}

void		setenv_builtin(char **cmd, char ***env, t_res **res)
{
	char		*path;

	if (cmd[1] == 0)
	{
		print_env(*env);
		return ;
	}
	if (get_len(cmd, 0) > 3)
	{
		err_msg("setenv: Too many arguments.\n");
		return ;
	}
	proceed_set(cmd, env);
	if (ft_strcmp("PATH", cmd[1]) == 0)
	{
		free((*res)->paths[0]);
		path = take_env_var("PATH=", 0, *env);
		(*res)->paths[0] = ft_strjoin("PATH=", path);
		free(path);
	}
	if (ft_strcmp("HOME", cmd[1]) == 0)
	{
		free((*res)->home);
		(*res)->home = take_env_var("HOME=", 0, *env);
	}
}
