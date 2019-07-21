/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:49:08 by iel-bouh          #+#    #+#             */
/*   Updated: 2019/07/18 13:55:46 by iel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_key(t_env **key_val)
{
	t_env *tmp;

	while (key_val)
	{
		tmp = (*key_val)->next;
		ft_memdel((void **)&((*key_val)->key));
		ft_memdel((void **)&((*key_val)->value));
		ft_memdel((void **)key_val);
		*key_val = tmp;
	}
}
