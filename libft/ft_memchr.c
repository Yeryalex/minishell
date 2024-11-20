/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:54:25 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/01/29 11:39:35 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, int n)
{
	unsigned char	*str;
	int				i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return (&str[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	*s1;
	char	*s2;
	char	*s3;

	s1 = "";
	s2 = "ajhahajahahjhn";
	s3 = "123123456";
	printf("Testeando s1 Test1  ");
	if (ft_memchr(s1, 'x', 0) == NULL)
		printf("Passed");
	else	printf("Failed");
	printf("\nTesteando s2 Tes2  ");
	if (ft_memchr(s2, 'y', 1) == NULL)
		printf("Passed");
	else	printf("Failed");
	printf("\n Testendo s3, test3  ");
	if (ft_memchr(s3, 'f', 12) == NULL)
		printf("Passed");
	printf("\n");
	return (0);
}*/
