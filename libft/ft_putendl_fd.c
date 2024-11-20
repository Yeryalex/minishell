/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:47:15 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/02/08 19:07:31 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	len;
	size_t	i;

	if (s)
	{
		i = 0;
		len = ft_strlen(s);
		while (i < len)
			write(fd, &s[i++], 1);
		write(fd, "\n", 1);
	}
}
