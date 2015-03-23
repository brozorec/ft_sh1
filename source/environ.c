/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 16:46:13 by bbarakov          #+#    #+#             */
/*   Updated: 2015/03/23 17:12:37 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"
#include "ft_sh1_prototypes.h"

void		change_or_add_env_var(char *var, char *value, char ***env)
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

char		*take_env_var(char *var, char *addr, char **env)
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
	int					i;
	int					j;
	int					len;
	char				**env;

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
		ft_str3del(environ);
	return (env);
}
