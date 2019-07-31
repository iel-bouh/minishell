/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 15:20:40 by iel-bouh          #+#    #+#             */
/*   Updated: 2019/07/31 18:24:00 by iel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else if (ft_strequ(tokens[0], "env"))
	{
		ft_put_env(*key_val);
		return (0);
	}
	else if (ft_strequ(tokens[0], "unsetenv"))
	{
		ft_unsetenv(key_val, tokens[1]);
		return (0);
	}
	else if (ft_strequ(tokens[0], "setenv"))
	{
		if (tokens[1])
			ft_setenv(key_val, tokens);
		else
			ft_put_env(*key_val);
		return (0);
	}
	else if (ft_strequ(tokens[0], "exit"))
	{
		return (2);
	}
	else
		return (1);
}

void	ft_cd(char **tokens, t_env **key_val)
{
	struct stat buf;
	int	i;

	i = 1;
	while (tokens[i])
	{
		if (i > 1)
		{
			ft_putstr("cd: string not in pwd: ");
			ft_putendl(tokens[1]);
			return ;
		}
		i++;
	}
	if (i == 1)
	{
		ft_change_env(key_val, "OLDPWD", getcwd(NULL, 0));
		chdir(ft_value(*key_val ,"HOME"));
	}
	else if (ft_strequ(tokens[1], "-"))
	{
		chdir(ft_value(*key_val, "OLDPWD"));
		ft_change_env(key_val, "OLDPWD", ft_value(*key_val ,"PWD"));
	}
	else if (lstat(tokens[1], &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
		{
			ft_change_env(key_val, "OLDPWD", getcwd(NULL, 0));
			chdir(tokens[1]);
		}
		else
		{
			ft_putstr("cd : not a directory: ");
			ft_putendl(tokens[1]);
		}
	}
	else
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(tokens[1]);
		return ;
	}
	ft_change_env(key_val, "PWD", getcwd(NULL, 0));
}

void	ft_list_env(t_env *key_val)
{
	while (key_val != NULL)
	{
		ft_putstr(key_val->key);
		ft_putchar('=');
		ft_putendl(key_val->value);
		key_val = key_val->next;
	}
}

void	ft_setenv(t_env **key_val, char **token)
{
	if (!ft_change_env(key_val, token[1], token[2]))
	{
		ft_add_path(&(token[1]), key_val);
	}
}

int	ft_change_env(t_env **key_val, char *key, char *val)
{
	t_env *tmp;

	tmp = *key_val;
	while (tmp)
	{
		if (ft_strequ(tmp->key, key))
		{
			ft_memdel((void **)&(tmp->value));
			if (val)
				tmp->value = ft_strdup(val);
			else
				tmp->value = ft_strdup("\0");
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_unsetenv(t_env **key_val, char *key)
{
	t_env *tmp;
	t_env *tmp_prev;

	tmp = *key_val;
	while (tmp)
	{
		if (ft_strequ(tmp->key, key))
		{
			tmp_prev->next = tmp->next;
			ft_memdel((void **)&(tmp->value));
			ft_memdel((void **)&(tmp->key));
			return ;
		}
		tmp_prev = tmp;
		tmp = tmp->next;
	}
}

void	ft_echo(char **str)
{
	while (*str)
	{
		ft_putstr(*str);
		ft_putchar(' ');
		str++;
	}
	ft_putchar('\n');
}
