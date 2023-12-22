/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:33:49 by cviegas           #+#    #+#             */
/*   Updated: 2023/12/15 23:01:57 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTFD_H
# define FT_PRINTFD_H
# include <unistd.h>

int	ft_printfd(int fd, const char *s, ...);

int	ft_putunsigned_fd(unsigned int n, int fd);
int	ft_putaddr_fd(void *addr, int fd);
int	ft_puthexa_min_fd(unsigned long long hexa, int fd);
int	ft_puthexa_max_fd(unsigned long long hexa, int fd);

#endif