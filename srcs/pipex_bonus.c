/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 00:27:40 by cviegas           #+#    #+#             */
/*   Updated: 2023/12/19 03:11:17 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_pid(t_pipex *p, char **av)
{
	dup2(p->fd_in, STDIN);
	dup2(p->end[WRITE], STDOUT);
	close(p->end[READ]);
	close(p->fd_in);
	store_commands(p, av);
	exec_in_path(p, 0);
	clean_pipex(p);
	close(p->end[WRITE]);
	exit(errno);
}

void	parent_ppid(t_pipex *p, char **av)
{
	waitpid(-1, &p->child_wstatus, 0);
	dup2(p->fd_out, STDOUT);
	dup2(p->end[READ], STDIN);
	close(p->end[WRITE]);
	store_commands(p, av);
	exec_in_path(p, 1);
	clean_pipex(p);
	close(p->end[READ]);
	exit(errno);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	p;
	pid_t	ppid;

	if (ac < 5)
		return (ft_printfd(2, "./pipex infile cmd1 ... cmdn outfile\n"), 1);
	p = init_pipex(ac, av, env);
	if (pipe(p.end) < 0)
		return (clean_pipex(&p), perror("Pipe"), errno);
	ppid = fork();
	if (ppid < 0)
		return (clean_pipex(&p), perror("Fork"), errno);
	if (!ppid)
		child_pid(&p, av);
	else
		parent_ppid(&p, av);
	close(p.fd_out);
}
