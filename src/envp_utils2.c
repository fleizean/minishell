/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:43:53 by eyagiz            #+#    #+#             */
/*   Updated: 2022/11/30 12:40:31 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	printexport(void)
{
	int	i;

	i = 0;
	while (g_list.env[i++])
	{
		ft_putstr_fd("\033[0;32m", 1);
		if (g_list.env[i])
			ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(g_list.env[i], 1);
		ft_putstr_fd("\033[0;39m", 1);
		if (g_list.env[i])
			ft_putstr_fd("\n", 1);
	}
}
