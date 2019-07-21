/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 13:23:33 by iel-bouh          #+#    #+#             */
/*   Updated: 2019/07/19 19:20:40 by iel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_prefix(char **str)
{
	char	*tmp;
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	count = 0;
	if (**str)
	{
		tmp = ft_strdup(*str);
		while (**str != '\0')
		{
			if (**str == '"')
				i++;
			else if (**str == '\'')
				j++;
			else if (**str == '/' && ((i % 2) == 0 && (j % 2) == 0))
			{
				break ;
			}
			count++;
			(*str)++;
		}
		if (**str == '\0')
			return (tmp);
		if (count)
		{
			char *tmp1 = ft_strsub(tmp, 0, count);
			ft_memdel((void **)&tmp);
			return (tmp1);
		}
	}
	return (NULL);
}

void	ft_tilde(char **str, t_env *key_val)
{
	char *tmp;
	char *prefix;
	char *tmp1;

	tmp = *str;
	if (*(tmp++) != '~')
		return ;
	prefix = ft_prefix(&tmp);
	if (prefix)
	{
		if (!ft_strchr(prefix, '"') && !ft_strchr(prefix, '\''))
		{
			if (ft_search_dir("/Users", prefix))
			{
				ft_memdel((void **)str);
				*str = ft_strjoin("/Users/", ft_strjoin(prefix, tmp));
				ft_memdel((void **)&prefix);
			}
			ft_memdel((void **)&prefix);
			return ;
		}
		ft_memdel((void **)&prefix);
		return ;
	}
	tmp = strdup(tmp);
	tmp1 = ft_value(key_val, "HOME");
	ft_memdel((void **)str);
	*str = ft_strjoin(tmp1, tmp);
	ft_memdel((void **)&tmp);
}

int		ft_search_dir(char *path, char *exec)
{
	DIR				*dirp;
	struct dirent	*dp;
	char			*tmp;

	while (*path != '\0')
	{
		dirp = opendir(path);
		if (dirp == NULL)
			return (0);
		while ((dp = readdir(dirp)))
		{
			if (ft_strequ(dp->d_name, exec))
				return (1);
		}
		path++;
	}
	return (0);
}
