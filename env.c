/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:37:11 by iel-bouh          #+#    #+#             */
/*   Updated: 2019/07/17 14:28:28 by iel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_add_path(char **lines, t_env **key_val)
{
	t_env *element;
	t_env *tmp;

	element = (t_env *)malloc(sizeof(t_env));
	if (!element)
		return (0);
	element->key = ft_strdup(*(lines++));
	element->value = ft_strdup(*lines);
	element->next = NULL;
	tmp = *key_val;
	if (!(*key_val))
	{
		*key_val = element;
		return (0);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = element;
	return (0);
}

void	ft_env_var(char **env, t_env **key_val)
{
	char	**tmp;

	while (*env)
	{
		tmp = ft_strsplit(*env, '=');
		ft_add_path(tmp, key_val);
		env++;
	}
}

void	ft_put_env(t_env *env)
{
	while (env != NULL)
	{
		ft_putstr(env->key);
		ft_putchar('=');
		ft_putendl(env->value);
		env = env->next;
	}
}

char	*ft_value(t_env *key_val, char *key)
{
	while (key_val)
	{
		if (ft_strequ(key_val->key, key))
			return (key_val->value);
		key_val = key_val->next;
	}
	return (NULL);
}
