/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:44:37 by cviegas           #+#    #+#             */
/*   Updated: 2023/11/08 00:24:18 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

// int	main(int ac, char **av)
// {
// 	printf("%d\n", ft_isascii('a'));
// 	if (ac == 2)
// 		printf("%d\n", ft_isascii(av[1][0]));
// }
