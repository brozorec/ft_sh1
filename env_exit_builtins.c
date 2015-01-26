/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exit_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/26 19:50:44 by bbarakov          #+#    #+#             */
/*   Updated: 2015/01/26 20:10:46 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_sh1.h"

void		env_builtin(char **env)
{
	int			i;

	i = 0;
	while (env[i])
	{
		ft_putstr(env[i]);
		ft_putstr("\n");
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

void		exit_builtin(char **cmd)
{
	int			status;
	int			i;

	i = 0;
	if (cmd[1] == 0)
		exit(0);
	while (cmd[1][i])
	{
		if (ft_isdigit(cmd[1][i]) == 0)
		{
			exit_err(i);
			return ;
		}
		++i;
	}
	if (cmd[2] != 0)
	{
		err_msg("exit: Expression Syntax.\n");
		return ;
	}
	status = ft_atoi(cmd[1]);
	exit(status);
}
