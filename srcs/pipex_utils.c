/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 22:11:31 by cviegas           #+#    #+#             */
/*   Updated: 2024/01/23 19:56:50 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	errors_holder_fd(t_pipex *p, char *file_in, char *file_out)
{
	if (p->fd_in == -1)
		ft_printfd(STDERR, "%s: %s\n", file_in, p->err_fd_in);
	if (p->fd_out == -1)
		ft_printfd(STDERR, "%s: %s\n", file_out, p->err_fd_out);
	if (p->fd_in == -1)
		exit(SUCCESS);
	if (p->fd_out == -1)
		exit(FAILURE);
}

t_pipex	init_pipex(int ac, char **av, char **env)
{
	t_pipex	p;

	p.cmd_args = NULL;
	p.cmd_path = NULL;
	p.fd_in = open(av[1], O_RDONLY);
	p.err_fd_in = strerror(errno);
	p.fd_out = open(av[ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	p.err_fd_out = strerror(errno);
	errors_holder_fd(&p, av[1], av[ac - 1]);
	p.nb_commands = ac - 2;
	p.env = env;
	p.is_first = true;
	p.is_last = false;
	p.child_wstatus = 0;
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
	close(p->fd_in);
	close(p->fd_out);
}
