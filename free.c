/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:49:08 by iel-bouh          #+#    #+#             */
/*   Updated: 2019/09/30 14:25:16 by iel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_key(t_env **key_val)
{
	t_env *tmp;

	tmp = NULL;
	while (*key_val)
	{
		tmp = (*key_val)->next;
		ft_memdel((void **)&((*key_val)->key));
		ft_memdel((void **)&((*key_val)->value));
		free(*key_val);
		*key_val = tmp;
	}
}

void	ft_free_tab(char **tab)
{
	int i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			ft_memdel((void **)&(tab[i++]));
		}
		free(tab);
	}
}
