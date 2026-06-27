/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 02:00:07 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 02:00:07 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

int	builtin_pwd(char **argv)
{
	char	cwd[2048];

	(void)argv;
	if (!getcwd(cwd, sizeof(cwd)))
	{
		ft_putstr_fd("minishell: pwd: error retrieving current directory\n",
			2);
		return (1);
	}
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}
