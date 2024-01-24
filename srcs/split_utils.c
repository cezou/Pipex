/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:24:28 by cviegas           #+#    #+#             */
/*   Updated: 2024/01/24 14:49:59 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// Creates a String (char *) with all whitespaces
// (to use it with split charset after)
char	*str_whitespaces(void)
{
	char	*whitespaces;
	size_t	i;

	whitespaces = malloc(sizeof(char) * 7);
	if (!whitespaces)
		return (NULL);
	i = 0;
	while (i < 5)
	{
		whitespaces[i] = i + 9;
		i++;
	}
	whitespaces[i++] = ' ';
	whitespaces[i] = 0;
	return (whitespaces);
}

void	print_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		ft_printfd(STDERR, "%s", split[i++]);
		if (split[i])
			ft_printfd(STDERR, " ");
	}
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}
