/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:09:25 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/13 14:13:35 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_dir(void)
{
	char	*pwd;
	char	buffer[2048];

	pwd = getcwd(buffer, 2048);
	g_list.exit_status = 0;
	if (!pwd)
	{
		g_list.exit_status = 1;
		ft_putstr_fd("error\n", 1);
		return ;
	}
	printf("\033[0;32m%s\033[0;39m\n", pwd);
	return ;
}
