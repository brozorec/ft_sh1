/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1_prototypes.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbarakov <bbarakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 18:15:24 by bbarakov          #+#    #+#             */
/*   Updated: 2015/02/06 18:12:40 by bbarakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH1_PROTOTYPES_H
# define FT_SH1_PROTOTYPES_H

char	*lookup_paths(char *var, char *name, char **env);
char	**get_paths(char *var, char **env);
char	**get_reserve_paths(void);
char	*dir_content(char *path, char *name);
int		get_cmd(char *line, char ***cmd);
void	opt_builtin(char **cmd, char ***environ, char ***saved);
char	**set_my_env(char **environ, char *str, int cmp, int flag);
void	setenv_builtin(char **cmd, char ***env, char ***saved);
void	unsetenv_builtin(char **cmd, char ***env);
void	env_builtin(char **cmd, char **env);
void	print_env(char **env);
void	exit_builtin(char **cmd, char ***env);
void	cd_builtin(char **cmd, char ***env);
void	pwd_builtin(char **env);
void	lst_init_or_free(t_cd **lst);
void	change_or_add_env_var(char *var, char *value, char ***env);
char	*take_env_var(char *var, char *addr, char **env);
int		get_options_or_take_oldpwd(char *cmd, t_cd **lst, char **env, int i);
char	*second_try(char *name, char **env);
int		get_len(char **ptr, int flag);
int		compare(char *cmd, char *env);
char	*trim_quot_marks(char *str);
void	err_msg(char *err);
void	cd_errors(t_cd **lst);
void	cd_options_err(char a);
void	exit_err(int i);

#endif
