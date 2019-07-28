/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:37:11 by iel-bouh          #+#    #+#             */
/*   Updated: 2019/07/28 19:24:57 by iel-bouh         ###   ########.fr       */
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
		while (*tmp)
			free(*(tmp++));
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

char	**ft_env_change(t_env *key_val)
{
	char	**env_tmp;
	t_env	*tmp;
	int		len;
	char	**tmp1;

	len = 0;
	tmp = key_val;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	if (!(env_tmp = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	tmp1 = env_tmp;
	while (key_val)
	{
		char *fr = ft_strjoin(key_val->key, "=");
		*env_tmp = ft_strjoin(fr, key_val->value);
		free(fr);
		env_tmp++;
		key_val = key_val->next;
	}
	env_tmp = NULL;
	return (tmp1);
}