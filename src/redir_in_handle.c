/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:06:21 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/13 13:21:05 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_doc(char *file, char *eof)
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
	close(fd);
	if (line)
		free(line);
}

void	mixed_redir2(char *str, char *temp, int fd)
{
	int		fdd;
	int		stdout_copy;

	stdout_copy = dup(1);
	fdd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0777);
	dup2(fdd, 1);
	close(fdd);
	execute_dir(temp, fd, 0);
	dup2(stdout_copy, 1);
	close(stdout_copy);
}

void	mixed_redir(char *str, char *temp, int fd)
{
	int		fdd;
	int		stdout_copy;

	stdout_copy = dup(1);
	fdd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(fdd, 1);
	close(fdd);
	execute_dir(temp, fd, 0);
	dup2(stdout_copy, 1);
	close(stdout_copy);
}

void	redir_in_handle(char **str, int i)
{
	char	*file;
	int		fd;
	char	*temp;

	temp = sub_redir(str, i);
	file = ft_strdup(str[i + 1]);
	fd = open(file, O_RDONLY, 0777);
	if (str[i + 2] && str[i + 2][0] == '>')
	{
		if (str[i + 2][1] || str[i + 2][1] == '>')
			mixed_redir2(str[i + 3], temp, fd);
		else
			mixed_redir(str[i + 3], temp, fd);
	}	
	else
		execute_dir(temp, fd, 0);
	free (file);
	free (temp);
}

void	redir2_in_handle(char **str, int i)
{
	int		fd;
	char	*eof;
	char	*temp;

	temp = sub_redir(str, i);
	if (str[i + 2] && str[i + 2][0] == '>')
	{
		eof = ft_strdup(str[i + 1]);
		here_doc2("b.txt", eof);
		fd = open("b.txt", O_RDONLY, 0777);
		mixed_redir(str[i + 3], temp, fd);
	}	
	else
	{
		eof = ft_strdup(str[i + 1]);
		here_doc(TMP_FILE, eof);
		fd = open(TMP_FILE, O_RDONLY, 0777);
		execute_dir(temp, fd, 0);
	}
	if (eof[0] != '\0')
		free(eof);
	if (temp[0] != '\0')
		free(temp);
}
