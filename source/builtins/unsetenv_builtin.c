/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 19:22:17 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/24 12:31:22 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"
#include "ft_sh1_prototypes.h"

int			compare(char *cmd, char *env)
{
	int			i;

	i = 0;
	while (env && env[i] && env[i] != '=')
		++i;
	if (ft_strncmp(env, cmd, i) == 0)
		return (i);
	return (0);
}

int			proceed_unset(char *cmd, char ***env)
{
	int			i;
	int			cmp;

	i = 0;
	if (ft_strcmp(cmd, "*") == 0)
	{
		ft_str3del(*env);
		*env = 0;
		return (0);
	}
	while (*env && (*env)[i])
	{
		if ((cmp = compare(cmd, (*env)[i])) != 0)
		{
			*env = set_my_env(*env, cmd, cmp, -1);
			return (1);
		}
		++i;
	}
	return (1);
}

void		unsetenv_builtin(char **cmd, char ***env)
{
	int			i;

	i = 1;
	if (cmd[i] == 0)
	{
		err_msg("unsetenv: Too few arguments.\n");
		return ;
	}
	while (cmd[i])
	{
		if (proceed_unset(cmd[i], env) == 0)
			return ;
		++i;
	}
}
