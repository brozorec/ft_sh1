/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/06 18:09:00 by bbarakov          #+#    #+#             */
/*   Updated: 2015/02/25 17:15:27 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"
#include "ft_sh1_prototypes.h"

t_res
	*get_reserved(char **env)
{
	t_res				*res;

	res = 0;
	res = (t_res *)malloc(sizeof(t_res));
	res->paths = get_reserved_paths();
	res->home = take_env_var("HOME=", 0, env);
	return (res);
}

int
	check_if_home(char **cmd, char **env, t_res **res)
{
	char				*copy;

	if ((*cmd)[0] == '~')
	{
		if ((*cmd)[1] != 0 && (*cmd)[1] != '/')
		{
			err_msg("Unknown user: ");
			err_msg(&(*cmd)[1]);
			err_msg(".\n");
			return (0);
		}
		copy = ft_strdup(*cmd);
		ft_strdel(cmd);
		*cmd = take_env_var("HOME=", ft_strchr(copy, '~') + 1, env);
		if (*cmd == 0)
			*cmd = ft_strjoin((*res)->home, ft_strchr(copy, '~') + 1);
		free(copy);
	}
	return (1);
}

int
	get_cmd(char *line, char ***cmd, char **env, t_res **res)
{
	int					i;

	i = 1;
	*cmd = ft_str2split(line, ' ', '\t');
	if (**cmd == 0)
		return (-1);
	while ((*cmd)[i])
	{
		if (ft_strchr((*cmd)[i], '"'))
		{
			if (((*cmd)[i] = trim_quot_marks((*cmd)[i])) == 0)
				return (-1);
		}
		else if (check_if_home(&(*cmd)[i], env, res) == 0)
			return (-1);
		++i;
	}
	if (!ft_strcmp((*cmd)[0], "cd") || !ft_strcmp((*cmd)[0], "setenv") ||
		!ft_strcmp((*cmd)[0], "unsetenv") || !ft_strcmp((*cmd)[0], "exit") ||
		!ft_strcmp((*cmd)[0], "env"))
		return (1);
	return (0);
}

void
	change_or_add_env_var(char *var, char *value, char ***env)
{
	int					i;
	int					cmp;

	i = 0;
	cmp = ft_strlen(var);
	while (*env && (*env)[i])
	{
		if (ft_strncmp((*env)[i], var, cmp) == 0)
		{
			free((*env)[i]);
			(*env)[i] = 0;
			(*env)[i] = ft_strjoin(var, value);
			return ;
		}
		++i;
	}
	*env = set_my_env(*env, ft_strjoin(var, value), 0, 1);
}

char
	*take_env_var(char *var, char *addr, char **env)
{
	char				*path;
	int					cmp;
	int					i;

	i = 0;
	cmp = ft_strlen(var);
	while (env && env[i])
	{
		if (ft_strncmp(env[i], var, cmp) == 0)
		{
			if (addr)
				path = ft_strjoin(&env[i][cmp], addr);
			else
				path = ft_strdup(&env[i][cmp]);
			return (path);
		}
		++i;
	}
	return (0);
}
