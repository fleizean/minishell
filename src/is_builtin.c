/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:10:26 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/13 18:42:27 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *tmp)
{
	if (tmp[0] == '\0')
		return (0);
	if (is_echo(tmp))
		return (1);
	else if (!ft_islower(tmp, "cd", 3))
		return (2);
	else if (!ft_islower(tmp, "pwd", 4))
		return (3);
	else if (!ft_islower(tmp, "export", 7))
		return (4);
	else if (!ft_islower(tmp, "unset", 6))
		return (5);
	else if (!ft_islower(tmp, "env", 4))
	{
		g_list.exit_status = 127;
		return (6);
	}
	else if (!ft_islower(tmp, "exit", 5))
		return (7);
	return (0);
}

void	exec_builtin(char *str)
{
	char	*tmp;
	int		i;

	tmp = ft_strtrim(str, " ");
	i = is_builtin(tmp);
	if (i == 1)
		echo_canalizer(str);
	else if (i == 2)
		mini_cd(tmp);
	else if (i == 3)
		print_dir();
	else if (i == 4)
		export_handle(tmp);
	else if (i == 5)
		unset_handle(tmp);
	else if (i == 6)
		printenv();
	else if (i == 7)
		exit(0);
	free (tmp);
}
