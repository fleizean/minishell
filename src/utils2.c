/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:22:35 by fyurtsev          #+#    #+#             */
/*   Updated: 2022/12/15 12:14:05 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isonlyecho(char *s)
{
	char	**tmp;
	int		i;

	tmp = ft_split(s, ' ');
	if (!ft_islower(tmp[0], "echo", 5) && !tmp[1])
	{
		ft_putchar_fd('\n', 1);
		ft_free_str(tmp);
		return (0);
	}
	i = 0;
	while (tmp[i])
		i++;
	while (--i)
	{
		if (ft_strncmp(tmp[i], "-n", 3))
		{
			ft_free_str(tmp);
			return (1);
		}
	}
	if (tmp)
		ft_free_str(tmp);
	return (0);
}

void	no_input_redir(int fd)
{
	ft_putstr_fd("no heredoc input\n", 2);
	g_list.exit_status = 1;
	close(fd);
}

void	here_doc2(char *file, char *eof)
{
	char	*line;
	int		flags;
	int		fd;

	flags = O_RDWR | O_CREAT | O_TRUNC;
	line = ft_strdup("");
	fd = open(file, flags, 0777);
	while (ft_strcmp(line, eof))
	{
		if (line)
			free(line);
		line = readline("heredoc> ");
		if (!line)
			no_input_redir(fd);		
		if (line && ft_strcmp(line, eof))
			ft_putstrendl_fd(line, fd);
		else
			break ;
	}
	if (line)
		free(line);
}
