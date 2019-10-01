/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 15:42:55 by iel-bouh          #+#    #+#             */
/*   Updated: 2019/09/29 18:34:36 by iel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **tokens, t_env **key_val)
{
	struct stat buf;
	char		*tmp_pwd;
	char		*tmp_pwd1;

	if (!tokens[1])
		ft_cd_none(key_val);
	else if (ft_strequ(tokens[1], "-"))
		ft_cd_old(key_val);
	else if (lstat(tokens[1], &buf) == 0)
		ft_cd_dir(key_val, tokens, buf);
	else
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(tokens[1]);
		return ;
	}
	tmp_pwd = getcwd(NULL, 0);
	if (ft_change_env(key_val, "PWD", tmp_pwd) == 0)
	{
		tmp_pwd1 = getcwd(NULL, 0);
		ft_add_path("PWD", tmp_pwd1, key_val);
		ft_memdel((void **)&tmp_pwd1);
	}
	ft_memdel((void **)&tmp_pwd);
}

void	ft_cd_none(t_env **key_val)
{
	char *tmp_pwd;

	tmp_pwd = getcwd(NULL, 0);
	ft_change_env(key_val, "OLDPWD", tmp_pwd);
	ft_memdel((void **)&tmp_pwd);
	chdir(ft_value(*key_val, "HOME"));
}

void	ft_cd_old(t_env **key_val)
{
	char *old_pwd;
	char *tmp_pwd;
	char *tmp_pwd1;

	if (ft_value(*key_val, "OLDPWD") == NULL)
		return ;
	old_pwd = ft_strdup(ft_value(*key_val, "OLDPWD"));
	tmp_pwd = getcwd(NULL, 0);
	if (ft_change_env(key_val, "OLDPWD",
			tmp_pwd) == 0)
	{
		tmp_pwd1 = getcwd(NULL, 0);
		ft_add_path("OLDPWD", tmp_pwd1, key_val);
		ft_memdel((void **)&tmp_pwd1);
	}
	chdir(old_pwd);
	ft_memdel((void **)&tmp_pwd);
	ft_memdel((void **)&old_pwd);
}

void	ft_cd_dir(t_env **key_val, char **tokens, struct stat buf)
{
	char		*tmp_pwd;

	if (S_ISDIR(buf.st_mode))
	{
		tmp_pwd = getcwd(NULL, 0);
		ft_change_env(key_val, "OLDPWD", tmp_pwd);
		ft_memdel((void **)&tmp_pwd);
		chdir(tokens[1]);
	}
	else
	{
		ft_putstr("cd : not a directory: ");
		ft_putendl(tokens[1]);
	}
}
