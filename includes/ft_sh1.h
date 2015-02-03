/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 15:51:32 by bbarakov          #+#    #+#             */
/*   Updated: 2015/02/03 19:22:58 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH1_H
# define FT_SH1_H

# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include "get_next_line.h"
# include <stdio.h> // don't forget it
# include <errno.h> // don't forget it

typedef struct 			s_cd
{
	int					opt_l;
	int					opt_p;
	char 				*name;
	char 				*path;
	char 				*input;
	char 				*saved_path;
	char 				new_dir[4096];
	char 				old_dir[4096];
}						t_cd;

typedef struct 			s_env
{
	int 				opt_i;
	char 				**new_env;
	char 				**new_cmd;
	char 				*prog_name;
}						t_env;

char		*lookup_paths(char *var, char *name, char **env);
char		**get_paths(char *var, char **env);
char		*dir_content(char *path, char *name);
void		opt_builtin(char **cmd, char ***environ);
char		**set_my_env(char **environ, char *str, int cmp, int flag);
void		setenv_builtin(char **cmd, char ***env);
void		unsetenv_builtin(char **cmd, char ***env);
void		env_builtin(char **cmd, char **env);
void		print_env(char **env);
void		exit_builtin(char **env);
void		cd_builtin(char **cmd, char ***env);
void		pwd_builtin(char **env);
void		lst_init_or_free(t_cd **lst);
void		change_or_add_env_var(char *var, char *value, char ***env);
char 		*take_env_var(char *var, char *addr, char **env);
int 		get_options_or_take_oldpwd(char *cmd, t_cd **lst, char **env, int i);
char 		*second_try(char *name, char **env);
int			get_len(char **ptr, int flag);
int			compare(char *cmd, char *env);
void		err_msg(char *err);
void		cd_errors(t_cd **lst);
void		cd_options_err(char a);
void		exit_err(int i);

#endif
