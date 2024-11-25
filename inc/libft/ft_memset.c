/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:00:54 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/01/14 17:40:20 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t count)
{
	size_t	i;
	char	*a;

	i = 0;
	a = dest;
	while (i < count)
	{
		a[i] = (unsigned char)c;
		i++;
	}
	return (dest);
}
