/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:00:50 by iel-bouh          #+#    #+#             */
/*   Updated: 2019/09/30 14:38:39 by iel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_parce_exec(char *line, t_env **key_val)
{
	char	**token;
	int		build;

	token = ft_command_expand(line, key_val);
	if ((build = ft_builtin(token, key_val)) == 1)
	{
		if (ft_path_bin(token, key_val) == 1)
		{
			return (1);
		}
	}
	else if (build == 2)
	{
		ft_free_tab(token);
		return (0);
	}
	else
		ft_free_tab(token);
	return (1);
}

void	ft_path_exec(char **token, t_env **key_val)
{
	int		pid;
	char	**tmp_env;

	if (access(token[0], X_OK) == 0)
	{
		pid = fork();
		if (pid < 0)
			perror("error: ");
		if (pid == 0)
		{
			tmp_env = ft_env_change(*key_val);
			execve(token[0], token, tmp_env);
			ft_free_tab(tmp_env);
			exit(0);
		}
	}
	else
	{
		ft_putstr_fd(token[0], 2);
		ft_putendl_fd(": Permission denied", 2);
	}
	ft_free_tab(token);
}

void	ft_bin_exec(char **token, char *path, t_env **key_val)
{
	int		pid;
	char	*tmp;
	char	**tmp_env;

	tmp = token[0];
	token[0] = ft_strjoin(path, token[0]);
	ft_memdel((void **)&tmp);
	if (access(token[0], X_OK) == 0)
	{
		if ((pid = fork()) < 0)
			perror("error: ");
		if (pid == 0)
		{
			tmp_env = ft_env_change(*key_val);
			execve(token[0], token, tmp_env);
			ft_free_tab(tmp_env);
			exit(0);
		}
	}
	else
	{
		ft_putstr_fd(token[0], 2);
		ft_putendl_fd(": Permission denied", 2);
	}
	ft_free_tab(token);
}

char	**ft_command_expand(char *line, t_env **key_val)
{
	char	**token;
	char	*line_tmp;

	line_tmp = ft_strtrim(line);
	ft_split_quote(&line_tmp);
	token = ft_strsplit(line_tmp, -1);
	ft_memdel((void **)&line_tmp);
	ft_expand(token, *key_val);
	return (token);
}

int		ft_path_bin(char **token, t_env **key_val)
{
	char	*path;
	char	**path_tmp;

	g_ctl = 2;
	if (ft_chr_exist(token[0], '/'))
	{
		ft_path_exec(token, key_val);
		wait(0);
		return (1);
	}
	path_tmp = ft_path_split(ft_value(*key_val, "PATH"));
	path = ft_path_check(path_tmp, token[0]);
	if (path != NULL)
		ft_bin_exec(token, path, key_val);
	else if (path == NULL)
		ft_not_found(token);
	else
		ft_free_tab(token);
	if (path)
		ft_memdel((void **)&path);
	ft_free_tab(path_tmp);
	wait(0);
	return (0);
}
