/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 15:29:46 by bbarakov          #+#    #+#             */
/*   Updated: 2015/01/28 19:58:38 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_sh1.h"

void			lst_init_or_free(t_cd *lst)
{
	if (lst == 0)
	{
		lst = (t_cd *)malloc(sizeof(*lst));
		lst->opt_l = 0;
		lst->opt_p = 0;
		lst->name = 0;
		lst->path = 0;
	}
	else
	{
		free(lst->path);
		free(lst->name);
		free(lst);
	}
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

