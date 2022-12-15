/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 22:53:55 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/08 22:55:32 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_handle(char *str, int n_pipe)
{
	char	**tmp;
	t_list	**list;

	tmp = ft_split(str, '|');
	list = (t_list **)malloc(sizeof(t_list *));
	*list = NULL;
	add_list(tmp, list);
	execpiped(list, n_pipe);
	ft_free_str(tmp);
	ft_lst_free(list);
}
