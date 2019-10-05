/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 15:20:40 by iel-bouh          #+#    #+#             */
/*   Updated: 2019/10/04 13:11:15 by iel-bouh         ###   ########.fr       */
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
	else if (ft_built_env(tokens, key_val) == 0)
		return (0);
	else if (ft_strequ(tokens[0], "exit"))
	{
		return (2);
	}
	else
		return (1);
}

int		ft_built_env(char **tokens, t_env **key_val)
{
	if (ft_strequ(tokens[0], "env"))
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
	return (1);
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
