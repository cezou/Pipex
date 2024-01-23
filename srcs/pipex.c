/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 00:27:40 by cviegas           #+#    #+#             */
/*   Updated: 2024/01/23 19:26:52 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	first_pid(t_pipex *p, char **av)
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

void	second_pid(t_pipex *p, char **av)
{
	dup2(p->fd_out, STDOUT);
	close(p->fd_out);
	close(p->end[WRITE]);
	dup2(p->end[READ], STDIN);
	store_commands(p, av);
	exec_in_path(p, 1);
	clean_pipex(p);
	close(p->end[READ]);
	exit(errno);
}

int	parent_ppid(t_pipex *p, pid_t pid)
{
	while ("squidgame")
	{
		if (wait(&p->child_wstatus) == pid)
		{
		}
		else
		{
			break ;
		}
	}
	return (WEXITSTATUS(p->child_wstatus));
}

int	main(int ac, char **av, char **env)
{
	t_pipex	p;
	pid_t	ppid;

	if (!env)
		return (v_printfd(STDERR, "Env not found"), FAILURE);
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
	return (parent_ppid(&p, ppid));
}
