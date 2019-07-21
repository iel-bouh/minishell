/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 13:34:47 by iel-bouh          #+#    #+#             */
/*   Updated: 2018/10/30 12:39:41 by iel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_lst	*ft_find(int fd_i, t_lst *back_up)
{
	t_lst *tmp;

	tmp = back_up;
	while (tmp)
	{
		if (tmp->fd == fd_i)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_lst	*ft_add(int fd_i, t_lst **back_up)
{
	t_lst	*new;
	char	*p;

	p = "\0";
	if ((new = ft_find(fd_i, *back_up)))
		return (new);
	if (!(new = (t_lst *)malloc(sizeof(t_lst))))
		return (NULL);
	new->fd = fd_i;
	new->next = *back_up;
	new->lines = p;
	*back_up = new;
	return (*back_up);
}

int		ft_get_line(t_lst *back_up, char **line)
{
	t_lst	*tmp;
	int		count;

	count = 0;
	tmp = back_up;
	while (((tmp->lines[count])))
	{
		if ((tmp->lines)[count] == '\n')
			break ;
		count++;
	}
	if (tmp->lines[count] == '\0')
	{
		*line = tmp->lines;
		tmp->lines = "\0";
	}
	else
	{
		*line = ft_strsub(tmp->lines, 0, count);
		tmp->lines = ft_strchr(tmp->lines, '\n') + 1;
		return (1);
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static	t_lst	*back_up;
	int				r_count;
	char			tmp[BUFF_SIZE + 1];
	t_lst			*temp;

	r_count = 0;
	if (BUFF_SIZE < 0 || (line == NULL) || read(fd, tmp, 0))
		return (-1);
	temp = ft_add(fd, &back_up);
	while ((r_count = read(fd, tmp, BUFF_SIZE)) > 0)
	{
		tmp[r_count] = '\0';
		if (!(temp->lines = ft_strjoin(temp->lines, tmp)))
			return (-1);
		if (ft_strchr(temp->lines, '\n'))
			break ;
	}
	if (ft_get_line(temp, line) == 1)
		return (1);
	if (r_count == 0 && *line[0] != '\0')
		return (1);
	return (0);
}
