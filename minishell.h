/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 18:50:35 by iel-bouh          #+#    #+#             */
/*   Updated: 2019/10/15 17:51:41 by iel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <signal.h>
# include "libft/libft.h"

int g_ctl;

typedef	struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

int					ft_launch(t_env **key_val);
char				**ft_path_var(char **env);
char				*ft_path_check(char **path, char *exec);
int					ft_count(char *line, char c);
int					ft_check_quote(char *lines);
void				ft_quote_rm(char **lines);
int					ft_split_quote(char **line);
int					ft_search_dir(char *path, char *exec);
void				ft_tilde(char **str, t_env *key_val);
void				ft_expand(char **token, t_env *key_val);
void				ft_put_env(t_env *env);
int					ft_add_path(char *line1, char *line2, t_env **key_val);
char				*ft_param(char **str);
void				ft_para_expand(char *param, char **rest, t_env *key_val);
char				*ft_get_param(char *param, t_env *key_val);
void				ft_dolar(char **str, t_env *key_val);
void				ft_rm_quote(char **token);
void				ft_cd(char **tokens, t_env **key_val);
int					ft_builtin(char **tokens, t_env **key_val);
void				ft_setenv(t_env **key_val, char **token);
void				ft_list_env(t_env *key_val);
int					ft_change_env(t_env **key_val, char *key, char *val);
void				ft_unsetenv(t_env **key_val, char *key);
void				ft_echo(char **str);
int					ft_parce_exec(char *line, t_env **key_val);
void				ft_ctl_c(int sig);
void				ft_ctl_d(int sig);
char				*ft_value(t_env *key_val, char *key);
char				**ft_path_split(char *path);
char				**ft_path_var(char **env);
void				ft_env_var(char **env, t_env **key_val);
void				ft_free_key(t_env **key_val);
char				**ft_env_change(t_env *key_val);
int					ft_chr_exist(char *str, char c);
void				ft_free_tab(char **tab);
void				ft_prompot();
int					ft_launch_command(char *line, t_env **key_val);
void				ft_path_exec(char **token, t_env **key_val);
void				ft_bin_exec(char **token, char *path, t_env **key_val);
char				**ft_command_expand(char *line, t_env **key_val);
int					ft_path_bin(char **token, t_env **key_val);
void				ft_cd_none(t_env **key_val);
void				ft_cd_old(t_env **key_val);
void				ft_cd_dir(t_env **key_val, char **tokens, struct stat buf);
int					ft_built_env(char **tokens, t_env **key_val);
void				ft_extract_expand(char **str, char *tmp, t_env *key_val,
						int count);
int					ft_prefix_join(char *prefix, char **str, char *tmp);
void				ft_find_expand(char *tmp, t_env *key_val, char **str);
int					ft_prefix_search(char **str);
void				ft_not_found(char **token);
void				ft_free_head(t_env **key_val);

#endif
