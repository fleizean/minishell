/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:03:09 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/13 14:11:05 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	restore_prompt(int sig)
{
	g_list.exit_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

static void	back_slash(int sig)
{
	g_list.exit_status = 131;
	ft_putnstr("Quit (core dumped)\n", 1);
	(void)sig;
}

void	run_signals(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, back_slash);
	}
	if (sig == 3)
	{
		printf(RED
			"You terminated the program with exit signal!\n");
		exit(0);
	}
}
