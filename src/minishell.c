/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:10:15 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/13 18:45:19 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_shell(void)
{
	char	*username;

	printf(RED
		"███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n"
		"████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n"
		"██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n"
		"██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n"
		"██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n"
		"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n"
		"                         😈 🔥 🌪  ⭐️ "
		"developed by fyurtsev & eyagiz" GREEN);
	username = getenv("USER");
	printf("\n\n\nUSER is: @%s\n", username);
}

void	init_env(char **envp)
{
	int		i;

	g_list.env = (char **)malloc(sizeof(char *) * env_len(envp) + 1);
	i = 0;
	while (envp[i])
	{
		g_list.env[i] = ft_strdup(envp[i]);
		i++;
	}
}

char	*rl_gets(char *str, const char *prompt)
{
	char	*tmp;

	if (str)
	{
		free(str);
		str = NULL;
	}
	str = readline(prompt);
	tmp = ft_strtrim(str, " ");
	if (str && *str)
		add_history(str);
	free(str);
	return (tmp);
}

void	takeinput(void)
{
	char	*prompt;
	char	*input;

	input = NULL;
	while (1)
	{
		run_signals(1);
		prompt = create_prompt();
		input = rl_gets(input, prompt);
		if (input)
		{
			command_router(input);
			free(prompt);
		}
		else
			run_signals(3);
	}
}

int	main(int ac, char **av, char **env)
{
	if (ac > 1 || av[1])
	{
		printf(RED"Too many arguments.\n");
		exit(1);
	}
	init_shell();
	g_list.exit_status = 0;
	init_env(env);
	takeinput();
	return (0);
}
