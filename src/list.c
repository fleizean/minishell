/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:10:21 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/01 15:59:58 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	**add_list(char **str, t_list **mini)
{
	int		i;
	t_list	*new;

	i = 0;
	while (str[i])
	{
		new = ft_lstnew(str[i]);
		ft_lstadd_back(mini, new);
		i++;
	}
	return (mini);
}
