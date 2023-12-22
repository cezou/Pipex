/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:24:28 by cviegas           #+#    #+#             */
/*   Updated: 2023/12/19 03:11:06 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	print_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		ft_printfd(STDERR_FILENO, "%s", split[i++]);
		if (split[i])
			ft_printfd(STDERR_FILENO, " ");
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
