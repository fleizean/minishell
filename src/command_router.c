/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_router.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 22:45:33 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/13 18:41:24 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	command_router(char *str)
{
	int	n_pipe;
	int	d_quote;
	int	s_quote;
	int	redir_out;
	int	redir_in;

	d_quote = count(str, '\"');
	s_quote = count(str, '\'');
	n_pipe = count(str, '|');
	redir_out = count(str, '>');
	redir_in = count(str, '<');
	if ((redir_out > 0 || redir_in > 0) && (d_quote == 0 && s_quote == 0))
		check_dir(str);
	else if ((n_pipe > 0) && (redir_out == 0 && redir_in == 0)
		&& (d_quote == 0 && s_quote == 0))
		pipe_handle(str, n_pipe);
	else if (is_builtin(str) > 0)
	{
		exec_builtin(str);
		g_list.exit_status = 0;
	}
	else
		process_string(str);
}
