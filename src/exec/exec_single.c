/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 01:59:50 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/27 01:59:51 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../internal.h"

int	is_builtin_name(const char *name)
{
	if (!name)
		return (0);
	return (ft_strcmp((char *)name, "echo") == 0
		|| ft_strcmp((char *)name, "cd") == 0
		|| ft_strcmp((char *)name, "pwd") == 0
		|| ft_strcmp((char *)name, "export") == 0
		|| ft_strcmp((char *)name, "unset") == 0
		|| ft_strcmp((char *)name, "env") == 0
		|| ft_strcmp((char *)name, "exit") == 0);
}

int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	char	*name;
	int		status;

	name = cmd->argv[0];
	if (ft_strcmp(name, "echo") == 0)
		status = builtin_echo(cmd->argv);
	else if (ft_strcmp(name, "cd") == 0)
		status = builtin_cd(cmd->argv, shell);
	else if (ft_strcmp(name, "pwd") == 0)
		status = builtin_pwd(cmd->argv);
	else if (ft_strcmp(name, "export") == 0)
		status = builtin_export(cmd->argv, shell);
	else if (ft_strcmp(name, "unset") == 0)
		status = builtin_unset(cmd->argv, shell);
	else if (ft_strcmp(name, "env") == 0)
		status = builtin_env(cmd->argv, shell);
	else
		status = builtin_exit(cmd->argv, shell);
	shell->exit_status = status;
	return (status);
}

void	exec_external(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	int		errcode;

	path = resolve_path(cmd->argv[0], shell->env, &errcode);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		if (errcode == 126)
			ft_putstr_fd(": Permission denied\n", 2);
		else
			ft_putstr_fd(": command not found\n", 2);
		exit(errcode);
	}
	execve(path, cmd->argv, shell->env);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->argv[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	free(path);
	exit(126);
}
