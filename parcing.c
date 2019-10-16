/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 20:16:03 by iel-bouh          #+#    #+#             */
/*   Updated: 2019/10/16 11:08:46 by iel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_split_quote(char **line)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while ((**line == ' ' || **line == '\t') && **line != '\0')
		(*line)++;
	tmp = *line;
	while (*tmp != '\0')
	{
		if (*tmp == '"')
			i++;
		else if (*tmp == '\'')
			j++;
		else if ((*tmp == ' ' || *tmp == '\t')
					&& ((i % 2) == 0 && (j % 2) == 0))
			*tmp = -1;
		tmp++;
	}
	return (1);
}

char	ft_first(char *str)
{
	while (*str)
	{
		if (*str == '"')
			return ('"');
		if (*str == '\'')
			return ('\'');
		str++;
	}
	return ('"');
}

void	ft_rm_quote(char **token)
{
	char	**split;
	char	*tmp;
	int		i;

	i = 0;
	split = ft_strsplit(*token, ft_first(*token));
	ft_memdel((void **)&(*token));
	while (split[i])
	{
		if (*token)
		{
			tmp = ft_strjoin(*token, split[i++]);
			ft_memdel((void **)&(*token));
			*token = tmp;
			ft_memdel((void **)&tmp);
		}
		else
			*token = ft_strdup(split[i++]);
	}
	ft_free_tab(split);
}

void	ft_dolar(char **str, t_env *key_val)
{
	char	*tmp;
	int		count;

	count = 0;
	tmp = *str;
	while (*tmp != '\0')
	{
		if (*tmp == '$')
		{
			ft_extract_expand(str, ++tmp, key_val, count);
			tmp = *str;
		}
		tmp++;
		count++;
	}
}

void	ft_expand(char **token, t_env *key_val)
{
	while (*token)
	{
		ft_tilde(token, key_val);
		ft_dolar(token, key_val);
		ft_rm_quote(token);
		token++;
	}
}
