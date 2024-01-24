/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 22:13:37 by cviegas           #+#    #+#             */
/*   Updated: 2024/01/24 14:59:15 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "QuoicouLibft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <unistd.h>
# define WRITE 1
# define READ 0
# define STDIN STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO
# define SUCCESS EXIT_SUCCESS
# define FAILURE EXIT_FAILURE

// Splits:
void		free_split(char **split);
void		print_split(char **split);
char		*str_whitespaces(void);

// Path & Exec
char		*join_cmd(char *s1, char *s2);
char		*join_path(char const *s1, char const *s2);
char		**parsing(char **env);

// Pipex:

typedef struct s_pipex
{
	bool	is_first;
	bool	is_last;
	pid_t	ppid;
	char	**cmd_args;
	char	**cmd_path;
	char	**env;
	char	*err_fd_in;
	char	*err_fd_out;
	int		fd_in;
	int		fd_out;
	int		nb_commands;
	int		end[2];
	int		child_wstatus;
	char	*whitespaces;
}			t_pipex;

t_pipex		init_pipex(int ac, char **av, char **env);
void		clean_pipex(t_pipex *p);
void		errors_holder_fd_out(t_pipex *p, char *file_out);
void		errors_holder_fd_in(t_pipex *p, char *file_in);
void		store_commands(t_pipex *p, char **av, int i);
void		exec_in_path(t_pipex *p);
void		exec_in_path_old(char **path, char **cmd_args, char **env);

#endif