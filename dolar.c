/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 13:22:33 by iel-bouh          #+#    #+#             */
/*   Updated: 2019/07/19 19:28:59 by iel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_dolar(char **str, t_env *key_val)
{
	int		q;
	int		dq;
	int		count;
	char	*tmp;
	char	*tmp1;


	q = 0;
	dq = 0;
	count = 0;
	tmp = ft_strdup(*str);
	while (**str != '\0')
	{
		if (**str == '"' && (q % 2 == 0))
		{
			count++;
			dq++;
		}
		else if (**str == '\'' && (dq % 2 == 0))
		{
			count++;
			q++;
		}
		else if (**str == '$' && (q % 2 == 0))
		{
			tmp1 = ft_param(str);
			ft_para_expand(tmp1, str, key_val);
			*str = ft_strjoin(ft_strsub(tmp, 0, count), *str);
			return ;
		}
		else
			count++;
		(*str)++;
	}
	*str = tmp;
}

char	*ft_param(char **str)
{
	int		count;
	char	*tmp;

	tmp = ft_strdup(*str);
	count = 0;
	while (**str != '\0' && **str != '"' && **str != '\''
				&& **str != '\t' && **str != ' ')
	{
		count++;
		(*str)++;
	}
	if (**str == '\0')
		return (tmp);
	else
		return (ft_strsub(tmp, 0, count));
}

void	ft_para_expand(char *param, char **rest, t_env *key_val)
{
	char *expand;

	if ((expand = ft_get_param(param, key_val)))
	{
		if (*rest)
			*rest = ft_strjoin(expand, *rest);
		else
			*rest = expand;
	}

}

char	*ft_get_param(char *param, t_env *key_val)
{
	while (key_val)
	{
		if (ft_strequ(key_val->key, ((&param[1]))))
			return (key_val->value);
		key_val = key_val->next;
	}
	return (NULL);
}
