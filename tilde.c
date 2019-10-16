/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 13:23:33 by iel-bouh          #+#    #+#             */
/*   Updated: 2019/10/16 11:09:18 by iel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_prefix(char **str)
{
	char	*tmp;
	char	*tmp1;
	int		count;

	count = 0;
	if (**str)
	{
		tmp = *str;
		while (**str != '\0')
		{
			if (**str == '/')
				break ;
			count++;
			(*str)++;
		}
		if (**str == '\0')
			return (ft_strdup(tmp));
		if (count)
		{
			tmp1 = ft_strsub(tmp, 0, count);
			return (tmp1);
		}
	}
	return (NULL);
}

int		ft_search_dir(char *path, char *exec)
{
	DIR				*dirp;
	struct dirent	*dp;

	while (*path != '\0')
	{
		dirp = opendir(path);
		if (dirp == NULL)
			return (0);
		while ((dp = readdir(dirp)))
		{
			if (ft_strequ(dp->d_name, exec))
			{
				closedir(dirp);
				return (1);
			}
		}
		closedir(dirp);
		path++;
	}
	return (0);
}

int		ft_prefix_join(char *prefix, char **str, char *tmp)
{
	char *join_tmp;

	if (ft_search_dir("/Users", prefix))
	{
		ft_memdel((void **)str);
		join_tmp = ft_strjoin(prefix, tmp);
		*str = ft_strjoin("/Users/", join_tmp);
		ft_memdel((void **)&join_tmp);
		return (1);
	}
	return (0);
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
		ft_prefix_join(prefix, str, tmp);
		ft_memdel((void **)&prefix);
		return ;
	}
	tmp = strdup(tmp);
	tmp1 = ft_value(key_val, "HOME");
	ft_memdel((void **)str);
	if (tmp1 != NULL)
		*str = ft_strjoin(tmp1, tmp);
	else
		*str = ft_strdup(tmp);
	ft_memdel((void **)&tmp);
}
