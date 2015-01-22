/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_unset_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 19:22:17 by bbarakov          #+#    #+#             */
/*   Updated: 2015/01/22 20:44:37 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_sh1.h"

void		setenv_builtin(char **cmd, char ***env)
{
	char		*var;

	if (cmd[1] == 0)
	{
		env_builtin(*env);
		return ;
	}
	else if (cmd[2] == 0)
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
	else
	{
		write(2 ,"error setenv\n", 14);
		return ;
	}
	*env = set_my_env(*env, var, 0, 1);
}

int			compare(char *cmd, char *env)
{
	int			i;

	i = 0;
	while (env[i] && env[i] != '=')
		++i;
	if (ft_strncmp(env, cmd, i) == 0)
		return (i);
	return (0);
}

void		proceed_unset(char *cmd, char ***env)
{
	int			i;
	int			len;

	i = 0;
	while ((*env)[i])
	{
		if ((len = compare(cmd, (*env)[i])) != 0)
			*env = set_my_env(*env, cmd, len, -1);
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
		++i;
	}
}
