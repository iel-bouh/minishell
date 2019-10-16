/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 14:27:10 by iel-bouh          #+#    #+#             */
/*   Updated: 2019/10/16 11:09:26 by iel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_not_found(char **token)
{
	ft_putstr_fd(token[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	ft_free_tab(token);
}

void	ft_ctl_c(int sig)
{
	char *pwd;

	signal(SIGINT, ft_ctl_c);
	if (g_ctl != 2)
	{
		ft_putstr_fd("\033[1;33m", 1);
		ft_putstr_fd("\n$", 1);
		pwd = getcwd(NULL, 0);
		ft_putstr_fd(pwd, 1);
		ft_putstr_fd("> ", 1);
		ft_putstr_fd("\033[0;32m", 1);
		ft_memdel((void **)&pwd);
	}
	g_ctl = 1;
	sig = g_ctl;
}

void	ft_prompot(void)
{
	char *tmp_pwd;

	ft_putstr_fd("\033[1;33m", 1);
	ft_putstr_fd("$", 1);
	tmp_pwd = getcwd(NULL, 0);
	ft_putstr_fd(tmp_pwd, 1);
	ft_memdel((void**)&tmp_pwd);
	ft_putstr_fd("> ", 1);
	ft_putstr_fd("\033[0;32m", 1);
}

int		ft_chr_exist(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
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
