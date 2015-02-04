/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:29:07 by bbarakov          #+#    #+#             */
/*   Updated: 2015/02/04 15:29:49 by bbarakov         ###   ########.fr       */
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

	var = 0;
	if (already_set(cmd, env) == 0)
	{
		if (cmd[2] == 0)
		{
			if (ft_strchr(cmd[2], '='))
			{
				err_msg("setenv: Syntax Error.\n");
				return ;
			}
			var = ft_realloc(cmd[1], 2);
			var = ft_strcat(var, "=");
		}
		else if (cmd[3] == 0)
		{
			var = ft_str3join(cmd[1], "=", cmd[2]);
		}
		*env = set_my_env(*env, var, 0, 1);
	}
}

void		setenv_builtin(char **cmd, char ***env)
{
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
}
