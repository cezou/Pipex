/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:25:46 by cviegas           #+#    #+#             */
/*   Updated: 2024/01/24 15:00:15 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exec_in_path(t_pipex *p)
{
	char	*path_full;
	size_t	i;

	i = 0;
	while (p->cmd_path[i])
	{
		path_full = join_path(p->cmd_path[i], p->cmd_args[0]);
		if (!path_full)
			return (clean_pipex(p), perror("Malloc"), exit(errno));
		execve(path_full, p->cmd_args, p->env);
		free(path_full);
		i++;
	}
	print_split(p->cmd_args);
	ft_printfd(STDERR, ": command not found\n");
	clean_pipex(p);
	exit(127);
}

char	*join_path(char const *s1, char const *s2)
{
	size_t	i;
	char	*join;

	i = -1;
	if (!s1 || !s2)
		return (NULL);
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!join)
		return (NULL);
	while (s1[++i])
		join[i] = s1[i];
	join[i] = '/';
	while (s2[++i - ft_strlen(s1) - 1])
		join[i] = s2[i - ft_strlen(s1) - 1];
	join[i] = 0;
	return (join);
}

char	*join_cmd(char *s1, char *s2)
{
	size_t	i;
	char	*join;

	i = -1;
	if (!s1 || !s2)
		return (NULL);
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 3));
	if (!join)
		return (NULL);
	while (s1[++i])
		join[i] = s1[i];
	join[i] = ' ';
	while (s2[++i - ft_strlen(s1) - 1])
		join[i] = s2[i - ft_strlen(s1) - 1];
	join[i] = 0;
	return (join);
}

char	**parsing(char **env)
{
	char	**path;
	char	*raw_path;
	int		i;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			raw_path = ft_substr(env[i], 5, strlen(env[i]) - 5);
			if (!raw_path)
				return (perror("Malloc"), NULL);
			path = ft_split(raw_path, ':');
			if (!raw_path)
				return (free(raw_path), perror("Malloc"), NULL);
			free(raw_path);
			break ;
		}
		i++;
	}
	if (!path)
		return (v_printfd(STDERR, "Missing PATH\n"), exit(127), NULL);
	return (path);
}
