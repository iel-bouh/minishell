/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 20:16:03 by iel-bouh          #+#    #+#             */
/*   Updated: 2019/07/19 19:30:20 by iel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_quote(char *lines)
{
	int		i;

	i = 0;

	i += ft_count(lines, '\'');
	i += ft_count(lines, '\"');
	if ((i % 2) == 0)
		return (1);
	return (-1);
}

int	ft_count(char *line, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (line[j] != '\0')
	{
		if ((('"' == c) && ((line[j] == c)
				&& line[j - 1] != '\\')) || (c == '\'' && line[j] == c))
			i++;
		j++;
	}
	return (i);
}

int	ft_split_quote(char **line)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	if (ft_check_quote(*line) == 1)
	{
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
				*tmp = '1';
			tmp++;
		}
		return (1);
	}
	else
	{
		ft_putendl("quote error");
		return (-1);
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

/*void	ft_rm_quote(char **token)
{
	char *tmp;
	int start;
	int end;
	int one;
	int two;
	char *cp;

	one = 0;
	two = 0;
	start = 0;
	end = 0;
	tmp = *token;
	cp = (char *)malloc(sizeof(char) * ft_strlen(*token));
	while (*tmp != '\0')
	{
		if (*tmp == '"' && (one % 2) == 0)
		{
			cp = ft_strncat(cp, *token, start);
			*token += start + 1;
			two++;
			start = 0;
		}
		else if (*tmp == '\'' && (two % 2) == 0)
		{
			cp = ft_strncat(cp, *token, start);
			*token += start + 1;
			start = 0;
			one++;
		}
		else
			start++;
		tmp++;
	}
	cp = ft_strncat(cp, *(token), start);
	*token = cp;
}*/

char ft_first(char *str)
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
	char **tmp;


	tmp = ft_strsplit(*token, ft_first(*token));
	ft_memdel((void **)&(*token));
	while (*tmp)
	{
		if (*token)
			*token = ft_strjoin(*token, *tmp);
		else
			*token = ft_strdup(*tmp);
		tmp++;
	}

}

