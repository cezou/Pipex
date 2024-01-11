/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cezou <cezou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 00:27:40 by cviegas           #+#    #+#             */
/*   Updated: 2024/01/08 17:32:08 by cezou            ###   ########.fr       */
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

// void	parent_ppid(t_pipex *p, char **av)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < p->nb_commands - 1)
// 		waitpid(-1, &p->child_wstatus, 0);
// 	close(p->end[WRITE]);
// 	clean_pipex(p);
// 	close(p->end[READ]);
// 	close(p->fd_out);
// 	exit(errno);
// }

void	first_child_pid(t_pipex *p, char **av)
{
	p->is_first = false;
	dup2(p->fd_in, STDIN);
	dup2(p->end[WRITE], STDOUT);
	close(p->end[READ]);
	close(p->fd_in);
	store_commands(p, av);
	exec_in_path(p, 0);
	clean_pipex(p);
	ft_printfd(2, "failed\n");
	close(p->end[WRITE]);
	exit(errno);
}

void	last_child_pid(t_pipex *p, char **av)
{
	close(p->end[READ]);
	dup2(p->fd_out, STDOUT);
	dup2(p->end[READ], STDIN);
	store_commands(p, av);
	exec_in_path(p, p->nb_commands - 2);
	clean_pipex(p);
	ft_printfd(2, "failed\n");
	close(p->end[WRITE]);
	exit(errno);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	p;
	pid_t	ppid;
	size_t	i;

	i = 0;
	if (ac < 5)
		return (ft_printfd(2, "./pipex infile cmd1 ... cmdn outfile\n"), 1);
	p = init_pipex(ac, av, env);
	if (pipe(p.end) < 0)
		return (clean_pipex(&p), perror("Pipe"), errno);
	while (i < p.nb_commands)
	{
		if (i == p.nb_commands - 2)
			p.is_last = true;
		ppid = fork();
		if (ppid < 0)
			return (clean_pipex(&p), perror("Fork"), errno);
		if (!ppid && i == 0)
		{
			ft_printfd(2, "FIRST\n");
			first_child_pid(&p, av);
		}
		if (!ppid && p.is_last)
		{
			ft_printfd(2, "LAST\n");
			last_child_pid(&p, av);
		}
		else
			wait(NULL);
		i++;
	}
}
