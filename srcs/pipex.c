/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cezou <cezou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 00:27:40 by cviegas           #+#    #+#             */
/*   Updated: 2024/01/06 23:30:29 by cezou            ###   ########.fr       */
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
	wait(NULL);
	dup2(p->fd_out, STDOUT);
	close(p->end[WRITE]);
	dup2(p->end[READ], STDIN);
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

	if (ac != 5)
		return ((void)ft_printfd(STDERR, "./pipex infile cmd1 cmd2 outfile\n"),
			FAILURE);
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
