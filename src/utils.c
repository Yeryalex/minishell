/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:59:53 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/11/26 16:51:34 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Modificacion para que no haya problema, revisar si es necesario
char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s);
	if (len > n)
		len = n;
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, len);
	dup[len] = '\0';
	return (dup);
}

void	free_tokens(t_tokens *head)
{
	t_tokens	*temp;

	while (head)
	{
		temp = head->next;
		free(head->value);
		free(head);
		head = temp;
	}
}
