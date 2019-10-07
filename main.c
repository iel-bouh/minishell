/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 14:51:08 by iel-bouh          #+#    #+#             */
/*   Updated: 2019/10/07 12:51:31 by iel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>

int g_ctl;

void	ft_cl_sc(void)
{
	char *env;
	char *str;

	env = getenv("TERM");
	//errro handling
	tgetent(NULL, env);
	str = tgetstr("cl", NULL);
	ft_putstr(str);
}

void	ft_key_mode(void)
{
	char *env;
	char *str;

	env = getenv("TERM");
	//errro handling

	tgetent(NULL, env);
	str = tgetstr("ks", NULL);
	ft_putstr(str);
}
int		main(int argc, char **argv, char **env)
{
	t_env	*key_val;

	key_val = NULL;
	argv = NULL;
	argc = 0;
	ft_cl_sc();
	signal(SIGINT, ft_ctl_c);
	ft_env_var(env, &key_val);
	if (!ft_launch(&key_val))
	{
		ft_putstr_fd("\033[0m", 1);
		ft_free_key(&key_val);
		return (0);
	}
	ft_putstr_fd("\033[0m", 1);
	ft_free_key(&key_val);
	return (0);
}

static struct termios stored;

void echo_off(void)
{
    struct termios new;
    tcgetattr(0,&stored);
    memcpy(&new, &stored, sizeof(struct termios));
    new.c_lflag &= (~ECHO);
	//new.c_lflag &= (~ICANON);
	//new.c_cc[VTIME] = 0;
   // new.c_cc[VMIN] = 1;
    tcsetattr(0,TCSANOW,&new);
	g_ctl = 0;
    return;
}

int		ft_launch(t_env **key_val)
{
	char	*line;
	int		size;
	char	*tmp_line;


	size = 0;

	while (1)
	{
		(g_ctl == 0) ? ft_prompot() : (g_ctl = 1);
		line = (char *)malloc(sizeof(char) * 1024);
		//ft_key_mode();
		tmp_line = line;
		while (read(0, tmp_line, 1))
		{
			if (*tmp_line == EOF || *tmp_line == '\n')
			{
				size++;
				break;
			}
			char *env = getenv("TERM");
			//errro handling
			tgetent(NULL, env);
			char *left= tgetstr("kl", NULL);
			if (ft_strequ(tmp_line, left))
				ft_putstr(left);
			if (ft_strequ(tmp_line, "\n"))
				break;
			tmp_line++;
			size++;
		}
		//echo_off();
		line[size] = '\0';
		tmp_line = ft_strtrim(line);
		ft_memdel((void **)&line);
		line = tmp_line;
		if (size > 1)
		{
			if (ft_launch_command(line, key_val) == 0)
				return (0);
		}
		else if (size == 0)
		{
			ft_putendl("logout");
			exit(0);
		}
		g_ctl = 0;
	}
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

	if (path)
	{
		while (*path != NULL)
		{
			dirp = opendir(*path);
			if (dirp == NULL)
				return (NULL);
			while ((dp = readdir(dirp)))
			{
				if (ft_strequ(dp->d_name, exec))
				{
					tmp = ft_strjoin(*path, "/");
					closedir(dirp);
					return (tmp);
				}
			}
			closedir(dirp);
			path++;
		}
	}
	return (NULL);
}

int		ft_launch_command(char *line, t_env **key_val)
{
	int		i;
	char	**command;
	char	**cmd_tmp;

	i = 0;
	command = ft_strsplit(line, ';');
	ft_memdel((void **)&line);
	cmd_tmp = command;
	while (*cmd_tmp)
	{
		if (!ft_parce_exec(*cmd_tmp++, key_val))
		{
			while (command[i])
			{
				free(command[i]);
				i++;
			}
			free(command);
			return (0);
		}
	}
	ft_free_tab(command);
	return (1);
}
