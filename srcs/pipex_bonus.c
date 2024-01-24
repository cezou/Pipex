/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 00:27:40 by cviegas           #+#    #+#             */
/*   Updated: 2024/01/24 15:24:00 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// void	child_pid(t_pipex *p, char **av, size_t i)
// {

// 	if (!p->is_last)
// 		dup2(p->end[WRITE], STDOUT);
// 	else
// 		dup2(p->fd_out, STDOUT);
// 	if (!p->is_first)
// 	{
// 		close(p->end[WRITE]);
// 		dup2(p->end[READ], STDIN);
// 		close(p->end[READ]);
// 	}
// 	else
// 	{
// 		dup2(p->fd_in, STDIN);
// 		close(p->fd_in);
// 		p->is_first = false;
// 	}
// 	close(p->end[READ]);
// 	store_commands(p, av);
// 	exec_in_path(p, i);
// 	clean_pipex(p);
// 	close(p->end[WRITE]);
// 	exit(errno);
// }

void	first_child_pid(t_pipex *p, char **av, int i)
{
	p->fd_in = open(av[1], O_RDONLY);
	p->err_fd_in = strerror(errno);
	errors_holder_fd_in(p, av[1]);
	dup2(p->fd_in, STDIN);
	close(p->fd_in);
	close(p->end[READ]);
	dup2(p->end[WRITE], STDOUT);
	store_commands(p, av, i);
	exec_in_path(p);
	clean_pipex(p);
	close(p->end[WRITE]);
	exit(errno);
}

void	last_child_pid(t_pipex *p, char **av, int i)
{
	p->fd_out = open(av[p->nb_commands + 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	p->err_fd_out = strerror(errno);
	errors_holder_fd_out(p, av[p->nb_commands + 1]);
	dup2(p->fd_out, STDOUT);
	close(p->fd_out);
	close(p->end[WRITE]);
	dup2(p->end[READ], STDIN);
	store_commands(p, av, i);
	exec_in_path(p);
	clean_pipex(p);
	close(p->end[READ]);
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
	int		i;

	i = 0;
	if (ac < 5)
		return (v_printfd(STDERR, "./pipex infile cmd1 ... cmdn outfile\n"), 1);
	p = init_pipex(ac, av, env);
	if (pipe(p.end) < 0)
		return (clean_pipex(&p), perror("Pipe"), errno);
	while (i < p.nb_commands - 1)
	{
		if (i == p.nb_commands - 2)
			p.is_last = true;
		ppid = fork();
		if (ppid < 0)
			return (clean_pipex(&p), perror("Fork"), errno);
		if (!ppid && i == 0)
			first_child_pid(&p, av, i);
		if (!ppid && p.is_last)
			last_child_pid(&p, av, i);
		p.is_first = false;
		i++;
	}
	return (parent_ppid(&p));
}
