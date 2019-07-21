/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 12:12:30 by iel-bouh          #+#    #+#             */
/*   Updated: 2018/10/30 12:14:59 by iel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "./libft/libft.h"
# define BUFF_SIZE 5

typedef struct	s_lst
{
	int				fd;
	char			*lines;
	struct s_lst	*next;
}				t_lst;

int				get_next_line(const int fd, char **line);

#endif
