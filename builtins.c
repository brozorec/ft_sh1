/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 19:22:17 by bbarakov          #+#    #+#             */
/*   Updated: 2015/01/24 16:02:34 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_sh1.h"

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

int			get_len(char **ptr, int flag)
{
	int		i;

	i = 0;
	while (ptr[i])
		++i;
	if (flag == 1)
		return (i + 1);
	else if (flag == -1)
		return (i - 1);
	return (i);
}

char		**set_my_env(char **environ, char *str, int cmp, int flag)
{
	int			i;
	int			j;
	int			len;
	char		**env;

	i = 0;
	j = 0;
	len = get_len(environ, flag);
	if ((env = (char **)malloc(sizeof(char *) * (len + 1))) == 0)
		return (0);
	while (environ[i])
	{
		if (flag == -1 && str && ft_strncmp(environ[i], str, cmp) == 0)
		{
			++i;
			continue;
		}
		env[j++] = ft_strdup(environ[i++]);
	}
	if (flag == 1)
	{
		env[j] = ft_strdup(str);
		free(str);
	}
	env[len] = 0;
	return (env);
}

void		opt_builtin(char **cmd, char ***env)
{
    if (!ft_strcmp(cmd[0], "cd"))
		cd_builtin(cmd, env);
	else if (!ft_strcmp(cmd[0], "exit"))
		exit(0);
	else if (!ft_strcmp(cmd[0], "env"))
		env_builtin(*env);
	else if (!ft_strcmp(cmd[0], "setenv"))
		setenv_builtin(cmd, env);
	else if (!ft_strcmp(cmd[0], "unsetenv"))
		unsetenv_builtin(cmd, env);
}
