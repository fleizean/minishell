/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 02:01:43 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 02:01:43 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

static char	*read_command_line(t_shell *shell)
{
	char	*prompt;
	char	*line;

	setup_parent_signals();
	prompt = build_prompt();
	g_signal = 0;
	line = readline(prompt);
	free(prompt);
	if (!line)
	{
		ft_putstr_fd("exit\n", 1);
		exit(shell->exit_status);
	}
	if (g_signal == SIGINT)
		shell->exit_status = 130;
	if (line[0])
		add_history(line);
	return (line);
}

static void	process_line(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;
	int		syntax_err;

	tokens = tokenize(line, &syntax_err);
	free(line);
	if (syntax_err || !tokens)
		return ;
	if (check_syntax(tokens, shell))
	{
		free_tokens(tokens);
		return ;
	}
	cmds = build_pipeline(tokens, shell);
	free_tokens(tokens);
	if (process_heredocs(cmds, shell) == 0)
		run_pipeline(cmds, shell);
	free_cmds(cmds);
}

void	shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = read_command_line(shell);
		process_line(line, shell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argv;
	if (argc > 1)
	{
		ft_putstr_fd("minishell: too many arguments\n", 2);
		return (1);
	}
	init_shell();
	shell.env = env_copy(envp);
	shell.exit_status = 0;
	shell_loop(&shell);
	return (shell.exit_status);
}
