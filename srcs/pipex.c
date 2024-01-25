/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 00:27:40 by cviegas           #+#    #+#             */
/*   Updated: 2024/01/25 12:16:48 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	first_pid(t_pipex *p, char **av)
{
	p->fd_in = open(av[1], O_RDONLY);
	p->err_fd_in = strerror(errno);
	errors_handler_fd_in(p, av[1]);
	dup2(p->fd_in, STDIN);
	close(p->fd_in);
	dup2(p->end[WRITE], STDOUT);
	close(p->end[READ]);
	close(p->end[WRITE]);
	store_commands(p, av, 0);
	exec_in_path(p);
	clean_pipex(p);
	exit(errno);
}

void	second_pid(t_pipex *p, char **av)
{
	p->fd_out = open(av[p->nb_commands + 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	p->err_fd_out = strerror(errno);
	errors_handler_fd_out(p, av[p->nb_commands + 1]);
	dup2(p->fd_out, STDOUT);
	close(p->fd_out);
	dup2(p->end[READ], STDIN);
	close(p->end[WRITE]);
	close(p->end[READ]);
	store_commands(p, av, 1);
	exec_in_path(p);
	clean_pipex(p);
	exit(errno);
}

int	parent_ppid(t_pipex *p)
{
	clean_pipex(p);
	while (errno != ECHILD)
		wait(&p->child_wstatus);
	return (WEXITSTATUS(p->child_wstatus));
}

int	main(int ac, char **av, char **env)
{
	t_pipex	p;
	pid_t	ppid;

	if (ac != 5)
		return (v_printfd(STDERR, "./pipex infile cmd1 cmd2 outfile\n"),
			FAILURE);
	p = init_pipex(ac, av, env);
	if (pipe(p.end) < 0)
		return (clean_pipex(&p), perror("Pipe"), errno);
	ppid = fork();
	if (ppid < 0)
		return (clean_pipex(&p), perror("Fork"), errno);
	if (!ppid)
		first_pid(&p, av);
	ppid = fork();
	if (ppid < 0)
		return (clean_pipex(&p), perror("Fork"), errno);
	if (!ppid)
		second_pid(&p, av);
	return (parent_ppid(&p));
}
