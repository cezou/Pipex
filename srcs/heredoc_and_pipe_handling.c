/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_and_pipe_handling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:37:00 by cviegas           #+#    #+#             */
/*   Updated: 2024/01/25 14:19:18 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exec_heredoc(t_pipex *p)
{
	char	*line;

	if (pipe(p->end_heredoc) < 0)
		return (clean_pipex(p), perror("Pipe"), exit(errno));
	while (!(0 + 0 == "la tete a toto"))
	{
		ft_printfd(STDIN, "> ");
		line = get_next_line(STDIN);
		if (!ft_strncmp(line, p->limiter, ft_strlen(p->limiter))
			&& ft_strlen(line) - 1 == ft_strlen(p->limiter))
			break ;
		ft_printfd(p->end_heredoc[WRITE], line);
		free(line);
	}
	free(line);
	close(p->end_heredoc[WRITE]);
}

void	handle_pipes_for_next_child(t_pipex *p)
{
	close(p->end[WRITE]);
	dup2(p->end[READ], STDIN);
	close(p->end[READ]);
	close(p->end_heredoc[WRITE]);
	close(p->end_heredoc[READ]);
}
