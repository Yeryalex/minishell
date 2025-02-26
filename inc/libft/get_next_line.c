/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:12:32 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/26 15:33:46 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*multiple_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

static char	*fd_lector(int fd, char *buff, char *saved_text)
{
	ssize_t	bytes;
	char	*temp;

	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
			return (multiple_free(&saved_text));
		if (bytes == 0)
			return (saved_text);
		buff[bytes] = '\0';
		if (!saved_text)
			saved_text = ft_strdup("");
		if (!saved_text)
			return (multiple_free(&saved_text));
		temp = saved_text;
		saved_text = ft_strjoin(temp, buff);
		free(temp);
		temp = NULL;
		if (ft_strchr(buff, '\n'))
			return (saved_text);
	}
	return (saved_text);
}

static char	*ft_line_remover(char *line)
{
	size_t	count;
	char	*saved_text;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0')
		return (0);
	saved_text = ft_substr(line, count + 1, ft_strlen(line) - (count + 1));
	if (!saved_text)
		return (multiple_free(&saved_text));
	if (*saved_text == '\0')
	{
		free(saved_text);
		saved_text = NULL;
	}
	line[count + 1] = '\0';
	return (saved_text);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*saved_text;
	char		*line;
	char		*tmp;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (0);
	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	line = fd_lector(fd, buff, saved_text);
	free(buff);
	buff = NULL;
	if (!line)
	{
		saved_text = NULL;
		return (NULL);
	}
	saved_text = ft_line_remover(line);
	tmp = ft_strdup(line);
	free(line);
	line = tmp;
	if (!line)
		return (multiple_free(&saved_text));
	return (line);
}