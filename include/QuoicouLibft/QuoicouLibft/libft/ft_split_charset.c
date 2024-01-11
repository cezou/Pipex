/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:37:54 by cviegas           #+#    #+#             */
/*   Updated: 2023/12/11 23:37:09 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "first_libft.h"

static int	is_sep(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static int	lenbsep(char *s, char *charset, int indice_s)
{
	int	i;

	i = 0;
	while (!is_sep(s[indice_s], charset) && s[indice_s])
	{
		indice_s++;
		i++;
	}
	return (i);
}

static int	ft_nb_mots(char *str, char *charset)
{
	int	i;
	int	nb_mots;

	i = 0;
	nb_mots = 0;
	while (str[i])
	{
		if (is_sep(str[i], charset))
			nb_mots++;
		i++;
	}
	return (nb_mots + 1);
}

char	**if_str_null(char *str)
{
	char	**ret;

	ret = malloc(sizeof (char *) * 2);
	ret[0] = ft_strdup(str);
	ret[1] = 0;
	return (ret);
}

char	**ft_split_charset(char *str, char *charset)
{
	char	**ret;
	int		i;
	int		j;
	int		k;

	if (!str)
		return (NULL);
	ret = ft_calloc(sizeof(char *) * (ft_nb_mots(str, charset) + 1), 1);
	k = 0;
	j = 0;
	while (str[j])
	{
		if (lenbsep(str, charset, j) > 0)
		{
			ret[k] = ft_calloc((lenbsep(str, charset, j) + 1)
					* sizeof(char), 1);
			i = 0;
			while (lenbsep(str, charset, j) > 0)
				ret[k][i++] = str[j++];
			k++;
		}
		else
			j++;
	}
	return (ret);
}

// void	afficherTableauStrings(char **tableau)
// {
// 	int	i;

// 	i = 0;
// 	while (tableau[i])
// 	{
// 		printf("%s\n", tableau[i]);
// 		i++;
// 	}
// }

// void	free_splitter(char **s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		free(s[i]);
// 		i++;
// 	}
// 	free(s);
// }

// int	main(int ac, char **av)
// {
// 	if (ac != 3)
// 		printf("Erreur");
// 	else
// 	{	char **squid = ft_split_charset(av[1], av[2]);
// 		afficherTableauStrings(squid);
// 		free_splitter(squid);
// 	}
// 	return (0);
// }