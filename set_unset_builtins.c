/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_unset_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 19:22:17 by bbarakov          #+#    #+#             */
/*   Updated: 2015/01/23 14:23:58 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_sh1.h"

int			already_set(char **cmd, char ***env)
{
	int			i;

	i = 0;
	while ((*env)[i])
	{
		if (compare(cmd[1], (*env)[i]) > 0 && cmd[2] == 0)
		{
			(*env)[i] = ft_realloc(cmd[1], 2);
			(*env)[i] = ft_strcat((*env)[i], "=");
			return (1);
		}
		else if (compare(cmd[1], (*env)[i]) > 0 && cmd[3] == 0)
		{
			(*env)[i] = ft_realloc(cmd[1], ft_strlen(cmd[2]) + 2);
			(*env)[i] = ft_strcat((*env)[i], "=");
			(*env)[i] = ft_strcat((*env)[i], cmd[2]);
			return (1);
		}
		++i;
	}
	return (0);
}

void		proceed_set(char **cmd, char ***env)
{
	char		*var;

	if (already_set(cmd, env) == 0)
	{
		if (cmd[2] == 0)
		{
			var = ft_realloc(cmd[1], 2);
			var = ft_strcat(var, "=");
		}
		else if (cmd[3] == 0)
		{
			var = ft_realloc(cmd[1], ft_strlen(cmd[2]) + 2);
			var = ft_strcat(var, "=");
			var = ft_strcat(var, cmd[2]);
		}
		*env = set_my_env(*env, var, 0, 1);
	}
}

void		setenv_builtin(char **cmd, char ***env)
{
	if (cmd[1] == 0)
	{
		env_builtin(*env);
		return ;
	}
	if (get_len(cmd, 0) > 3)
	{
		write(2 ,"error setenv\n", 14);
		return ;
	}
	proceed_set(cmd, env);
}

void		proceed_unset(char *cmd, char ***env)
{
	int			i;
	int			cmp;

	i = 0;
	while ((*env)[i])
	{
		if ((cmp = compare(cmd, (*env)[i])) != 0)
		{
			*env = set_my_env(*env, cmd, cmp, -1);
		}
		++i;
	}
}

void		unsetenv_builtin(char **cmd, char ***env)
{
	int			i;

	i = 1;
	if (cmd[i] == 0)
	{		
		write(2 ,"error unsetenv\n", 16);
		return ;
	}
	while (cmd[i])
	{
		proceed_unset(cmd[i], env);
		ft_putstr("here");
		++i;
	}
}
