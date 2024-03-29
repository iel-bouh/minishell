/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 14:04:46 by hastid            #+#    #+#             */
/*   Updated: 2018/10/13 14:54:58 by iel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		word_count(char *s, char c)
{
	int		i;
	int		is_word;

	i = 0;
	is_word = 0;
	while (*s)
	{
		if (is_word == 0 && *s != c)
		{
			is_word = 1;
			i++;
		}
		else if (is_word == 1 && *s == c)
			is_word = 0;
		s++;
	}
	return (i);
}

static int		word_len(char *s, char c)
{
	int		len;

	len = 0;
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	int		w_count;
	char	**str;
	int		i;

	if (!s)
		return (NULL);
	w_count = word_count((char *)s, c);
	str = (char **)malloc((w_count + 1) * sizeof(char*));
	i = 0;
	if (!str)
		return (NULL);
	while (w_count--)
	{
		while (*s == c && *s != '\0')
			s++;
		str[i] = ft_strsub((char *)s, 0, word_len((char *)s, c));
		if (!str[i])
			return (NULL);
		s = s + word_len((char *)s, c);
		i++;
	}
	str[i] = NULL;
	return (str);
}
