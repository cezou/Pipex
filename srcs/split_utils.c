/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:24:28 by cviegas           #+#    #+#             */
/*   Updated: 2024/01/23 19:51:15 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
