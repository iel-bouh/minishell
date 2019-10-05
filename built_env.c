/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:32:12 by iel-bouh          #+#    #+#             */
/*   Updated: 2019/10/04 13:32:01 by iel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_add_path(token[1], token[2], key_val);
	}
}

int		ft_change_env(t_env **key_val, char *key, char *val)
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
				tmp->value = NULL;
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
	tmp_prev = NULL;
	while (tmp)
	{
		if (ft_strequ(tmp->key, key))
		{
			if (tmp_prev == NULL)
			{
				ft_free_head(key_val);
				return ;
			}
			tmp_prev->next = tmp->next;
			ft_memdel((void **)&(tmp->value));
			ft_memdel((void **)&(tmp->key));
			free(tmp);
			return ;
		}
		tmp_prev = tmp;
		tmp = tmp->next;
	}
}

void	ft_free_head(t_env **key_val)
{
	t_env *tmp;

	tmp = *key_val;

	*key_val = (*key_val)->next;
	ft_memdel((void **)&(tmp->value));
	ft_memdel((void **)&(tmp->key));
	free(tmp);
}
