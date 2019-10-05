/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 13:22:33 by iel-bouh          #+#    #+#             */
/*   Updated: 2019/10/02 10:45:47 by iel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_find_expand(char *tmp, t_env *key_val, char **str)
{
	int		q;
	int		dq;
	int		count;

	q = 0;
	dq = 0;
	count = 0;
	if (*tmp == '"' && (q % 2 == 0))
	{
		count++;
		dq++;
	}
	else if (*tmp == '\'' && (dq % 2 == 0))
	{
		count++;
		q++;
	}
	else if (*tmp == '$' && (q % 2 == 0))
	{
		ft_extract_expand(str, tmp, key_val, count);
		return ;
	}
	else
		count++;
}

void	ft_extract_expand(char **str, char *tmp, t_env *key_val, int count)
{
	char	*param;
	char	*head_tmp;

	param = ft_param(&tmp);
	ft_para_expand(param, &tmp, key_val);
	ft_memdel((void **)&param);
	head_tmp = ft_strsub(*str, 0, count);
	ft_memdel((void **)str);
	*str = ft_strjoin(head_tmp, tmp);
	ft_memdel((void **)&head_tmp);
	ft_memdel((void **)&tmp);
}

char	*ft_param(char **str)
{
	int		count;
	char	*tmp;

	tmp = *str;
	count = 0;
	while (**str != '\0' && **str != '"' && **str != '\''
				&& **str != '\t' && **str != ' ' && **str != '/')
	{
		count++;
		(*str)++;
	}
	if (**str == '\0')
		return (strdup(tmp));
	else
		return (ft_strsub(tmp, 0, count));
}

void	ft_para_expand(char *param, char **rest, t_env *key_val)
{
	char *expand;

	if ((expand = ft_get_param(param, key_val)))
	{
		if (*rest)
		{
			*rest = ft_strjoin(expand, *rest);
			ft_memdel((void **)&expand);
		}
		else
			*rest = expand;
	}
	else
		*rest = ft_strdup(*rest);
}

char	*ft_get_param(char *param, t_env *key_val)
{
	while (key_val)
	{
		if (ft_strequ(key_val->key, ((&param[1]))))
			return (strdup(key_val->value));
		key_val = key_val->next;
	}
	return (NULL);
}
