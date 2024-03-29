/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 00:27:40 by cviegas           #+#    #+#             */
/*   Updated: 2024/01/30 11:21:56 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	first_child_pid(t_pipex *p, char **av, int i)
{
	if (p->is_heredoc)
		p->fd_in = p->end_heredoc[READ];
	else
	{
		p->fd_in = open(av[1], O_RDONLY);
		p->err_fd_in = strerror(errno);
		errors_handler_fd_in(p, av[1]);
	}
	if (ft_strncmp(av[1], "/dev/stdin", 10) || ft_strlen(av[1]) != 10)
		(dup2(p->fd_in, STDIN), close(p->fd_in));
	close(p->end[READ]);
	dup2(p->end[WRITE], STDOUT);
	close(p->end[WRITE]);
	store_commands(p, av, i);
	exec_in_path(p);
	clean_pipex(p);
	exit(errno);
}

void	intermediate_child_pid(t_pipex *p, char **av, int i)
{
	close(p->end[READ]);
	dup2(p->end[WRITE], STDOUT);
	close(p->end[WRITE]);
	store_commands(p, av, i);
	exec_in_path(p);
	clean_pipex(p);
	exit(errno);
}

void	last_child_pid(t_pipex *p, char **av, int i)
{
	p->fd_out = open(av[p->nb_commands + 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	p->err_fd_out = strerror(errno);
	errors_handler_fd_out(p, av[p->nb_commands + 1]);
	dup2(p->fd_out, STDOUT);
	close(p->fd_out);
	dup2(STDIN, p->end[READ]);
	close(p->end[READ]);
	close(p->end[WRITE]);
	store_commands(p, av, i);
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

	if (ac < 5)
		return (v_printfd(2,
				"./pipex [infile | here_doc LIMITER] cmd1 ... cmdn outfile\n"),
			FAILURE);
	p = init_pipex(ac, av, env);
	while (p.i < p.nb_commands - 1)
	{
		if (pipe(p.end) < 0)
			return (clean_pipex(&p), perror("Pipe"), errno);
		ppid = fork();
		if (ppid < 0)
			return (clean_pipex(&p), perror("Fork"), errno);
		if (!ppid && (p.i == 0 || (p.is_heredoc && p.i == 1)))
			first_child_pid(&p, av, p.i);
		if (!ppid && p.i == p.nb_commands - 2)
			last_child_pid(&p, av, p.i);
		if (!ppid)
			intermediate_child_pid(&p, av, p.i);
		handle_pipes_for_next_child(&p);
		p.i++;
	}
	return (parent_ppid(&p));
}
