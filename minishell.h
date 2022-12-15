/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:02:46 by eyagiz            #+#    #+#             */
/*   Updated: 2022/12/13 14:16:41 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <signal.h>

# define TMP_FILE "./text.txt"
# define CYAN "\001\033[1;36m\002"
# define WHITE "\001\033[0m\002"
# define GREEN "\001\033[1;32m\002"
# define RED "\033[0;31m"

typedef struct s_list
{
	void			*next;
	char			*data;
}					t_list;

typedef struct s_temp_var
{
	int		i;
	int		j;
	int		k;
	int		t;
	int		l;
	int		flag;

	char	*s;
	char	*tmp;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;
	char	*tmp5;
	char	**tmp_2ar;
}			t_temp_var;

typedef struct s_pipe_var
{
	t_list	*temp;
	pid_t	pid;
	int		*fd;
	int		i;
	int		j;
	char	**cmd;
	char	*path;
}			t_pipe_var;

typedef struct t_utils
{
	int				quote_flag;
	int				n_flag;
}			t_utils;

typedef struct s_env
{
	char			**env;
	int				exit_status;
}			t_env;

typedef struct s_redir_var
{
	char	*temp;
	int		fd;
	int		k;
	int		flags;
	char	*file;
	int		j;
	int		m;

}			t_redir_var;

t_env	g_list;

//builtin
void		exec_builtin(char *s);
int			is_builtin(char *tmp);
void		export_handle2(char *str);
void		export_handle(char *str);
void		print_dir(void);
void		printenv(void);
int			get_index(char *key);
void		export(char *var_name, char *var_val);
void		unset_handle(char *str);
void		mini_cd(char *tmp);
void		pipe_handle(char *str, int n_pipe);
int			env_len(char **envp);
void		finder_dollar_env(char *s, int *i);

//echo
void		echo_canalizer(char *str);
void		echo_handle(char *s, t_utils utils);
char		*ft_echo_substr(char *str, int start, int end);
void		sngle_quote_incheck(char *s, int *i);
void		dble_quote_incheck(char *s, int *i);
void		echo_withn(char *s);
void		echo_withoutn(char *s);
int			n_check(char *str);
int			check_quotes(char *s, t_utils utils);
int			is_echo(char *s);
int			isonlyecho(char *s);

//libft
char		**ft_split(const char *s, char c);
void		ft_putstr(char *str);
void		ft_putnstr(char *str, int n);
void		ft_lstadd_back(t_list **lst, t_list *new);
t_list		*ft_lstnew(char *str);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strtrim(char *s1, char *set);
char		*ft_substr(char *s, int start, unsigned int len);
void		ft_putchar_fd(char c, int fd);
char		*ft_strchr(const char *s, int c);
int			ft_strlen(char *str);
char		*ft_strcpy(char *dest, char *src);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strdup(char *src);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_putstr_fd(char *s, int fd);
int			ft_islower(char *s1, char *s2, int n);
int			ft_isalnum(int c);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstrendl_fd(char *s, int fd);

//minishell
void		init_shell(void);
void		init_env(char **envp);
void		takeinput(void);
void		printexport(void);
void		execsimple(char **parse);
char		*find_path(char *cmdline);
char		*find_value(char *key, char **envp);
void		execpiped(t_list **mini, int countpiped);
int			process_string(char *str);
void		ft_free_str(char **str);
void		run_signals(int sig);

//utils
char		*ft_dlr_cnv(char *s);
char		*create_prompt(void);
t_list		**add_list(char **str, t_list **mini);
int			count(char *str, char c);
void		ft_lst_free(t_list **stackA);
void		no_input_redir(int fd);

//directions
void		command_router(char *str);
void		execute_dir(char *s, int fd, int i);
void		exec_redir(char *s, int fd, int i);
int			redirect_in(char **str, int i);
int			redirect_out(char **str, int i);
void		here_doc2(char *file, char *eof);
void		exec_fork(char **s, int fd, int i);
int			check_another_redir(char **str, int i);
void		redir2_out_handle(char **str, int i);
void		redir_out_handle(char **str, int i);
void		check_dir(char *str);
void		redir2_in_handle(char **str, int i);
void		redir_in_handle(char **str, int i);
void		here_doc(char *file, char *eof);
char		*sub_redir(char **str, int i);
int			check_quotes2(char *s);
#endif
