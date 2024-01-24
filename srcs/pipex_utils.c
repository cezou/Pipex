/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 22:11:31 by cviegas           #+#    #+#             */
/*   Updated: 2024/01/24 16:37:09 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	errors_handler_fd_in(t_pipex *p, char *file_in)
{
	if (p->fd_in == -1)
		ft_printfd(STDERR, "%s: %s\n", file_in, p->err_fd_in);
	if (p->fd_in == -1)
		exit(SUCCESS);
}

void	errors_handler_fd_out(t_pipex *p, char *file_out)
{
	if (p->fd_out == -1)
		ft_printfd(STDERR, "%s: %s\n", file_out, p->err_fd_out);
	if (p->fd_out == -1)
		exit(FAILURE);
}

t_pipex	init_pipex(int ac, char **env)
{
	t_pipex	p;

	p.cmd_args = NULL;
	p.cmd_path = NULL;
	p.whitespaces = NULL;
	p.nb_commands = ac - 2;
	p.env = env;
	p.child_wstatus = 0;
	p.i = 0;
	return (p);
}

void	store_commands(t_pipex *p, char **av, int i)
{
	p->cmd_path = parsing(p->env);
	p->whitespaces = str_whitespaces();
	if (!p->cmd_path)
		return (clean_pipex(p), exit(errno));
	if (!av[i + 2][0])
		return (clean_pipex(p), v_printfd(STDERR, "permission denied:\n"),
			exit(errno));
	p->cmd_args = malloc(sizeof(char *) * (ft_nb_mots(av[i + 2],
					p->whitespaces)));
	if (!p->cmd_args)
		return (clean_pipex(p), perror("Malloc"), exit(errno));
	p->cmd_args = ft_split_charset(av[i + 2], p->whitespaces);
	if (!p->cmd_args)
		return (clean_pipex(p), perror("Malloc"), exit(errno));
}

void	clean_pipex(t_pipex *p)
{
	if (p->whitespaces)
		free(p->whitespaces);
	if (p->cmd_path)
		free_split(p->cmd_path);
	if (p->cmd_args)
		free_split(p->cmd_args);
	close(p->end[READ]);
	close(p->end[WRITE]);
}
