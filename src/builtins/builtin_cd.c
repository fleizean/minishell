/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 02:07:49 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 02:07:50 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

static void	print_cd_error(char *target)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(target, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

static char	*pick_target(char **argv, t_shell *shell)
{
	if (!argv[1] || ft_strcmp(argv[1], "~") == 0)
		return (env_get(shell->env, "HOME"));
	return (argv[1]);
}

static int	do_chdir(char *target, t_shell *shell)
{
	char	cwd[2048];
	char	*oldpwd;

	if (!getcwd(cwd, sizeof(cwd)))
		cwd[0] = '\0';
	oldpwd = ft_strdup(cwd);
	if (chdir(target) != 0)
	{
		print_cd_error(target);
		shell->exit_status = 1;
		free(oldpwd);
		return (1);
	}
	env_set(&shell->env, "OLDPWD", oldpwd);
	free(oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		env_set(&shell->env, "PWD", cwd);
	shell->exit_status = 0;
	return (0);
}

int	builtin_cd(char **argv, t_shell *shell)
{
	char	*target;

	if (argv[1] && argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		shell->exit_status = 1;
		return (1);
	}
	target = pick_target(argv, shell);
	if (!target)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		shell->exit_status = 1;
		return (1);
	}
	return (do_chdir(target, shell));
}
