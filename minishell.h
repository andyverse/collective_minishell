/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnochiza <fnochiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 20:27:43 by fnochiza          #+#    #+#             */
/*   Updated: 2022/09/05 20:28:04 by fnochiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>

# define WHITE_SPACES " \t\v\r\f"
# define PIPE 1
# define LEF_SIN_REDIR 2
# define RIGH_SIN_REDIR 3
# define LEF_DOUB_REDIR 4
# define RIGH_DOUB_REDIT 5
# define SIN_Q 1
# define DOUB_Q 2

int	g_exit_status;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef struct s_cmd
{
	char				*name;
	char				**arg;
	int					redir;
	char				*file;
	struct s_cmd		*next;
}	t_cmd;

typedef struct s_words
{
	char	*res;
	int		len;
	int		i;
	int		j;
	int		count_one;
	int		count_double;
}	t_words;

typedef struct s_split
{
	char	**split_w;
	int		words;
}	t_split;

typedef struct s_dollar
{
	char	*tmp;
	int		count_one;
	int		count_double;
	char	*rez;
	char	*head;
	char	*cmd;
	char	*tail;
}	t_dollar;

typedef struct s_exec
{
	char	*path;
	char	**path_cmd;
	char	**cmd_full;
	char	*cmd_exec;
	char	**env;
	int		pipe_num;
	int		infile;
	int		outfile;
}	t_exec;

char		*read_line(void);
void		read_envp(char **env, t_envp **envp_list);
t_envp		*envp_new(char *content);
void		envp_add_front(t_envp **lst, t_envp *new);
void		cmd_add_back(t_cmd **lst, t_cmd *new);

void		ctrl_c(int signum);
void		handle_signals(void);

int			find_sep(char c);
void		count_redirects(char *str, int *ind, int *num_words);
void		ft_count(char *str, int *ind, int *num_words);
int			count_words(char *str, int i, int words);

char		*write_redir(char *str, int *ind);
int			count_white_space(char *str);
char		*write_words(char *str, int *ind);
char		**write_split_words(char **split_w, char *str);
char		**split_by_words(char *str);

int			ft_isdelim(char *s);
int			delimetr(char *s);
void		dollar_redirect(char *str, int *num);
void		make_struct(char **arr, int *ind, t_cmd **new_cmd);

int			ft_check_eve_quotes(char *str);
int			t_check_first_end(char *str);
int			check_syntax(char *str);
int			check_double_delim(char **arr);

char		*subst_dollar(char *cmd, t_envp *envp_list);
int			replace_dollar(char **str, t_envp *envp_list);

t_split		*init_split(char *str);
t_words		*init_write_w(char *str);
t_cmd		*init_cmd(void);
t_dollar	*init_doll(void);

t_cmd		*com_new1(char *name, char **arr, int delim, char *file);
int			make_arg(char ***arg, char **arr, int i);
int			ft_new_cmd(int i, char **arr, t_cmd **new_cmd);
void		ft_struct(char **arr, t_cmd **cmd);

void		ft_copy_arr(char **arr_in, char **arr_out);
void		ft_one_name(t_cmd **cmd);
int			ft_n_words(char **arr, int i);
void		ft_empty_arr(char ***tmp, char *str);

void		free_envp_list(t_envp *envp_list);
void		free_com_list(t_cmd *cmd);
void		ft_free_com_list(t_cmd **cmd);
void		free_array(char **array);
void		ft_free(char *str);
void		free_pipe_struct(t_exec *exec);

int			print_env_declare(t_envp *envp_list);
int			var_position_in_envp(t_envp *envp_list, char *str);
int			put_value_to_envp(t_envp *envp_list, char *key, char *new_value);
char		*get_value_from_envp(t_envp *envp_list, char *str);
void		add_var_to_envp_list(t_envp **envp_list, char **array, char *str);

int			ft_export(t_cmd *cmd, t_envp **envp_list);
int			ft_unset(t_cmd *cmd, t_envp **envp_list);
void		ft_exit(t_cmd *cmd, t_envp *envp_list);
int			ft_cd(t_cmd *cmd, t_envp *envp_list);
int			ft_pwd(t_envp *envp_list);
int			ft_env(t_envp *envp_list);
int			ft_echo(t_cmd *cmd);

int			heredoc(t_cmd *cmd);
void		execute(t_cmd *cmd, t_envp **envp_list);
void		executor(t_cmd *cmd, t_envp **envp_list, t_exec *exec);
void		pipe_handler(t_cmd *cmd, t_envp **envp_list, t_exec *exec);
void		pipex(t_cmd *cmd, t_envp **envp_list, t_exec *exec);
void		get_env(t_envp *envp_list, t_exec *exec);
void		make_full_com(t_cmd *cmd, t_exec *exec);
void		check_cmd(t_cmd *cmd, t_exec *exec);
void		find_args(t_cmd *cmd, t_exec *exec);
char		*make_cmd(t_cmd *cmd, t_exec *exec);
void		redirect_handler(t_cmd *cmd, int *pipefd);

int			envsize(t_envp *lst);
int			lstsize(t_cmd *lst);
void		show_error(char *error);
int			count_array(t_cmd *cmd);
int			count_pipes(t_cmd *cmd);
void		std_out_close(int save_stdout);
void		pipe_close(t_cmd *cmd, int fd0, int fd1);
void		handle_signals2(void);
size_t		ft_strlen(const char *str);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
char		*ft_strchr(const char	*str, int c);
char		*ft_strdup(const char *s1);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strrchr(const char *str, int c);
char		**ft_split(char const *s, char c);
int			ft_isspace(char c);
char		*ft_itoa(int n);
int			ft_atoi(const char *str);
int			ft_isalpha(int ch);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
int			ft_isalnum(int ch);

#endif
