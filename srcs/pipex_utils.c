/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 22:11:31 by cviegas           #+#    #+#             */
/*   Updated: 2024/01/24 14:17:39 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	errors_holder_fd_in(t_pipex *p, char *file_in)
{
	if (p->fd_in == -1)
		ft_printfd(STDERR, "%s: %s\n", file_in, p->err_fd_in);
	if (p->fd_in == -1)
		exit(SUCCESS);
}

void	errors_holder_fd_out(t_pipex *p, char *file_out)
{
	if (p->fd_out == -1)
		ft_printfd(STDERR, "%s: %s\n", file_out, p->err_fd_out);
	if (p->fd_out == -1)
		exit(FAILURE);
}

t_pipex	init_pipex(int ac, char **av, char **env)
{
	t_pipex	p;

	p.cmd_args = NULL;
	p.cmd_path = NULL;
	p.nb_commands = ac - 2;
	p.env = env;
	p.is_first = true;
	p.is_last = false;
	p.child_wstatus = 0;
	(void)av;
	return (p);
}

void	store_commands(t_pipex *p, char **av)
{
	int	i;

	p->cmd_path = parsing(p->env);
	if (!p->cmd_path)
		return (clean_pipex(p), exit(errno));
	p->cmd_args = malloc(sizeof(char **) * (p->nb_commands + 1));
	if (!p->cmd_args)
		return (clean_pipex(p), perror("Malloc"), exit(errno));
	i = 0;
	while (i < p->nb_commands)
	{
		p->cmd_args[i] = ft_split(av[i + 2], ' ');
		if (!p->cmd_args[i])
			return (clean_pipex(p), perror("Malloc"), exit(errno));
		i++;
	}
	p->cmd_args[i] = NULL;
}

void	clean_pipex(t_pipex *p)
{
	int	i;

	if (p->cmd_path)
		free_split(p->cmd_path);
	if (p->cmd_args)
	{
		i = 0;
		while (p->cmd_args[i])
		{
			free_split(p->cmd_args[i]);
			i++;
		}
		free(p->cmd_args);
	}
	close(p->end[READ]);
	close(p->end[WRITE]);
}
