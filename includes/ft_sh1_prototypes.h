/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1_prototypes.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 18:15:24 by bbarakov          #+#    #+#             */
/*   Updated: 2015/02/10 13:03:48 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH1_PROTOTYPES_H
# define FT_SH1_PROTOTYPES_H

void	signals(void);
char	*lookup_paths(char *var, char *name, char **env);
char	**get_paths(char *var, char **env);
t_res	*get_reserved(char **env);
char	**get_reserved_paths(void);
char	*dir_content(char *path, char *name);
int		get_cmd(char *line, char ***cmd, char **env, t_res **res);
void	opt_builtin(char **cmd, char ***environ, t_res **res);
char	**set_my_env(char **environ, char *str, int cmp, int flag);
void	setenv_builtin(char **cmd, char ***env, t_res **res);
void	unsetenv_builtin(char **cmd, char ***env);
void	env_builtin(char **cmd, char **env);
void	print_env(char **env);
void	exit_builtin(char **cmd, char ***env);
void	cd_builtin(char **cmd, char ***env, t_res **res);
void	pwd_builtin(char **env);
void	lst_init_or_free(t_cd **lst);
void	change_or_add_env_var(char *var, char *value, char ***env);
char	*take_env_var(char *var, char *addr, char **env);
int		get_options_or_take_oldpwd(char *cmd, t_cd **lst, char **env, int i);
char	*second_try(char *name, char **env);
int		check_too_many_args(t_cd *lst, char **cmd);
int		get_len(char **ptr, int flag);
int		compare(char *cmd, char *env);
char	*trim_quot_marks(char *str);
void	err_msg(char *err);
void	cd_errors(t_cd **lst);
void	cd_options_err(char a);
void	exit_err(int i);

#endif
