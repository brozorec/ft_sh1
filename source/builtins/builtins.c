/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 19:22:17 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/22 17:19:52 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"
#include "ft_sh1_prototypes.h"

int			builtins(char **cmd, char ***env, t_res **res)
{
	if (!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "setenv") ||
		!ft_strcmp(cmd[0], "unsetenv") || !ft_strcmp(cmd[0], "exit") ||
		!ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "pwd"))
	{
		if (!ft_strcmp(cmd[0], "cd"))
			cd_builtin(cmd, env, res);
		else if (!ft_strcmp(cmd[0], "exit"))
			exit_builtin(cmd, env, *res);
		else if (!ft_strcmp(cmd[0], "env"))
			env_builtin(cmd, *env);
		else if (!ft_strcmp(cmd[0], "setenv"))
			setenv_builtin(cmd, env, res);
		else if (!ft_strcmp(cmd[0], "unsetenv"))
			unsetenv_builtin(cmd, env);
		else if (!ft_strcmp(cmd[0], "pwd"))
			pwd_builtin(*env);
		return (1);
	}
	return (0);
}
