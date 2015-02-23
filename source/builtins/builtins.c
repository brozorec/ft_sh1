/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 19:22:17 by bbarakov          #+#    #+#             */
/*   Updated: 2015/02/05 12:52:36 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"
#include "ft_sh1_prototypes.h"

char		*trim_quot_marks(char *str)
{
	char		*new;
	int			i;
	int			j;

	new = 0;
	i = 0;
	j = 0;
	new = ft_strnew(ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '"')
		{
			++i;
			continue;
		}
		new[j++] = str[i++];
	}
	free(str);
	if ((i - j) % 2 != 0)
	{
		err_msg("Unmatched \".\n");
		return (0);
	}
	return (new);
}

int			get_len(char **ptr, int flag)
{
	int		i;

	i = 0;
	while (ptr && ptr[i])
		++i;
	if (flag == 1)
		return (i + 1);
	else if (flag == -1)
		return (i - 1);
	return (i);
}

void		finish_env(char **env_var, char **str, int flag)
{
	if (flag == 1)
	{
		*env_var = ft_strdup(*str);
		free(*str);
	}
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
	while (environ && environ[i])
	{
		if (flag == -1 && str && ft_strncmp(environ[i], str, cmp) == 0)
		{
			++i;
			continue;
		}
		env[j++] = ft_strdup(environ[i++]);
	}
	finish_env(&env[j], &str, flag);
	env[len] = 0;
	if (flag != 0)
		ft_strdel(environ);
	return (env);
}

void		opt_builtin(char **cmd, char ***env, t_res **res)
{
	if (!ft_strcmp(cmd[0], "cd"))
		cd_builtin(cmd, env, res);
	else if (!ft_strcmp(cmd[0], "exit"))
		exit_builtin(cmd, env);
	else if (!ft_strcmp(cmd[0], "env"))
		env_builtin(cmd, *env);
	else if (!ft_strcmp(cmd[0], "setenv"))
		setenv_builtin(cmd, env, res);
	else if (!ft_strcmp(cmd[0], "unsetenv"))
		unsetenv_builtin(cmd, env);
	else if (!ft_strcmp(cmd[0], "pwd"))
		pwd_builtin(*env);
}
