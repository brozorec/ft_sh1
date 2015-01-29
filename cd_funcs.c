/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_funcs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 15:29:46 by bbarakov          #+#    #+#             */
/*   Updated: 2015/01/29 16:47:46 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_sh1.h"

void			lst_init_or_free(t_cd **lst)
{
	if (*lst == 0)
	{
		*lst = (t_cd *)malloc(sizeof(t_cd));
		(*lst)->opt_l = 0;
		(*lst)->opt_p = 0;
		(*lst)->name = 0;
		(*lst)->path = 0;
	}
	else
	{
		free((*lst)->path);
		free((*lst)->name);
		free(*lst);
	}
}

char 			*second_try(char *name, char **env)
{
	char 			**tab_paths;
	char 			*path;
	char 			*new_path;
	char 			*truncated;
	int				i;

	if ((tab_paths = get_paths("CDPATH=", env)) == 0)
		return (0);
	if ((path = lookup_paths(tab_paths, name)) != 0)
	{
		ft_strdel(tab_paths);
		return (path);
	}
	truncated = ft_strdup(ft_strchr(name, '/'));
	i = ft_strlen(name) - ft_strlen(truncated);
	ft_bzero(&name[i], ft_strlen(truncated));
	if ((path = lookup_paths(tab_paths, name)) != 0)
	{
		new_path = ft_strjoin(path, truncated);
		free(truncated);
		ft_strdel(tab_paths);
		return (new_path);
	}
	return (0);
}

void			change_or_add_env_var(char *var, char *value, char ***env)
{
	int			i;
	int			cmp;

	i = 0;
	cmp = ft_strlen(var);
	while ((*env)[i])
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

char 			*take_home_or_oldpwd(char *var, char *addr, char **env)
{
	char 			*path;
	int				cmp;
	int				i;

	i = 0;
	cmp = ft_strlen(var);
	while (env[i])
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

