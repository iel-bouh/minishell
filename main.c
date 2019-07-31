/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 14:51:08 by iel-bouh          #+#    #+#             */
/*   Updated: 2019/07/31 04:01:43 by iel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_ctl;

int		main(int argc, char **argv, char **env)
{
	t_env	*key_val;

	key_val = NULL;
	argv = NULL;
	argc = 0;
	signal(SIGINT, ft_ctl_c);
	ft_env_var(env, &key_val);
	if (!ft_launch(key_val))
	{
		ft_putstr_fd("\033[0m", 1);
		return (0);
	}
	ft_free_key(&key_val);
	ft_putstr_fd("\033[0m", 1);
	return (0);

}

void	ft_ctl_c(int sig)
{
	signal(SIGINT, ft_ctl_c);
	if (g_ctl != 2)
	{
		ft_putstr_fd("\033[1;33m", 1);
		ft_putstr_fd("\n$", 1);
		ft_putstr_fd(getcwd(NULL, 0), 1);
		ft_putstr_fd("> ", 1);
		ft_putstr_fd("\033[0;32m", 1);
	}
	g_ctl = 1;
	sig = g_ctl;
}

int	ft_launch(t_env *key_val)
{
	char	*line;
	char	**command;
	char	**cmd_tmp;
	int		ch;

	while (1)
	{
		if (g_ctl == 0)
		{
			ft_putstr_fd("\033[1;33m", 1);
			ft_putstr_fd("$", 1);
			ft_putstr_fd(getcwd(NULL, 0), 1);
			ft_putstr_fd("> ", 1);
			ft_putstr_fd("\033[0;32m", 1);
		}
		ch = get_next_line(1, &line); //freee it 
		if (ch)
		{
			command = ft_strsplit(line, ';');
			cmd_tmp = command;
			while (*command)
			{
				if (!ft_parce_exec(*command++, &key_val))
				{
					ft_memdel((void **)&line);
					while (*cmd_tmp)
						free(*(cmd_tmp++));
					return (0);
				}
			}
		}
		else
		{
			ft_putendl("logout");
			exit(0);
		}
		g_ctl = 0;
	}
}

char	**ft_path_var(char **env)
{
	char *path;
	char **bin_path;
	char *tmp;

	while (*env != NULL)
	{
		if ((path = ft_strstr(*env, "PATH")))
		{
			tmp = ft_strchr(path, '=');
			path = tmp + 1;
			bin_path = ft_strsplit(path, ':');
			return (bin_path);
		}
		env++;
	}
	return (NULL);
}

char	**ft_path_split(char *path)
{
	char **bin_path;

	if (path)
	{
		bin_path = ft_strsplit(path, ':');
		return (bin_path);
	}
	return (NULL);
}

char	*ft_path_check(char **path, char *exec)
{
	DIR				*dirp;
	struct dirent	*dp;
	char			*tmp;

	while (*path)
	{
		dirp = opendir(*path);
		if (dirp == NULL)
			return (NULL);
		while ((dp = readdir(dirp)))
		{
			if (ft_strequ(dp->d_name, exec))
			{
				tmp = ft_strjoin(*path, "/");
				return (tmp);
			}
		}
		path++;
	}
	return (NULL);
}

int		ft_parce_exec(char *line, t_env **key_val)
{
	pid_t	pid;
	char	**tmp1;
	int		build;
	char	*path;

	line = ft_strtrim(line);
	tmp1 = ft_strsplit(line, ' ');
	ft_expand(tmp1, *key_val);
	if ((build = ft_builtin(tmp1, key_val)) == 1)
	{
		g_ctl = 2;
		pid = fork();
		if (pid < 0)
			perror("error: ");
		if (pid == 0)
		{
			if (!ft_strchr(tmp1[0], '/') &&
					(path = ft_path_check(ft_path_split(
						ft_value(*key_val, "PATH")), tmp1[0])))
			{
				tmp1[0] = ft_strjoin(path, tmp1[0]);
				if (access(tmp1[0], X_OK) == 0)
				{
					execve(tmp1[0], tmp1, ft_env_change(*key_val));
				}
				else
				{
					ft_putstr_fd(tmp1[0], 2);
					ft_putendl_fd(": Permission denied", 2);
				}
			}
			if (ft_strchr(tmp1[0], '/'))
			{
				if (access(tmp1[0], X_OK) == 0)
					execve(tmp1[0], tmp1, ft_env_change(*key_val));
				else
				{
					ft_putstr_fd(tmp1[0], 2);
					ft_putendl_fd(": Permission denied", 2);
				}
			}
			else if (!path)
			{
				ft_putstr_fd("-bash: ", 2);
				ft_putstr_fd(tmp1[0], 2);
				ft_putstr_fd(": command not found\n", 2);
			}
			exit(0);
		}
	}
	else if (build == 2)
		return (0);
	wait(0);
	return (1);
}
