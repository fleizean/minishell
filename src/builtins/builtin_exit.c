/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 02:00:12 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 02:00:13 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

static int	valid_number(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	parse_exit_code(char *s)
{
	int	i;
	int	neg;
	int	val;

	i = 0;
	neg = (s[0] == '-');
	if (s[0] == '+' || s[0] == '-')
		i++;
	val = 0;
	while (s[i])
	{
		val = (val * 10 + (s[i] - '0')) % 256;
		i++;
	}
	if (neg)
		val = (256 - val) % 256;
	return (val);
}

int	builtin_exit(char **argv, t_shell *shell)
{
	if (argv[1] && argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->exit_status = 1;
		return (1);
	}
	if (!argv[1])
		exit(shell->exit_status);
	if (!valid_number(argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	exit(parse_exit_code(argv[1]));
}
