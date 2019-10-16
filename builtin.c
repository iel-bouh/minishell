/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 15:20:40 by iel-bouh          #+#    #+#             */
/*   Updated: 2019/10/16 11:07:47 by iel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_echo(char **str)
{
	int i;

	i = 0;
	if (ft_strequ(*str, "-n"))
	{
		i = 1;
		str++;
	}
	while (*str)
	{
		ft_putstr(*str++);
		if (*str)
			ft_putchar(' ');
	}
	if (i == 0)
		ft_putchar('\n');
}

int		ft_built_env(char **tokens, t_env **key_val)
{
	int i;

	i = 0;
	if (ft_strequ(tokens[0], "env"))
	{
		ft_put_env(*key_val);
		return (0);
	}
	else if (ft_strequ(tokens[0], "unsetenv"))
	{
		while (tokens[i])
			ft_unsetenv(key_val, tokens[i++]);
		return (0);
	}
	else if (ft_strequ(tokens[0], "setenv"))
	{
		if (tokens[1])
			ft_setenv(key_val, tokens);
		return (0);
	}
	return (1);
}

int		ft_builtin(char **tokens, t_env **key_val)
{
	if (ft_strequ(tokens[0], "cd"))
	{
		ft_cd(tokens, key_val);
		return (0);
	}
	else if (ft_strequ(tokens[0], "echo"))
	{
		ft_echo(&(tokens[1]));
		return (0);
	}
	else if (ft_built_env(tokens, key_val) == 0)
		return (0);
	else if (ft_strequ(tokens[0], "exit"))
	{
		return (2);
	}
	else
		return (1);
}
