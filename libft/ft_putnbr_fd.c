/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:53:12 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/02/08 19:14:48 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_num(int n2, int fd2)
{
	int		num[10];
	int		i;
	char	print;

	i = 0;
	while (n2 > 0)
	{
		num[i] = n2 % 10;
		n2 = n2 / 10;
		i++;
	}
	i--;
	while (i >= 0)
	{
		print = num[i] + 48;
		write(fd2, &print, 1);
		i--;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0 && n > -2147483648)
	{
		write(fd, "-", 1);
		print_num(n * -1, fd);
	}
	else if (n > 0 && n <= 2147483647)
		print_num(n, fd);
	else if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
	else
		write(fd, "0", 1);
}
