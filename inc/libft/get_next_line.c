/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:12:32 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/25 18:00:16 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_ptr(void **ptr)
{
	free (*ptr);
	*ptr = NULL;
}

static char	*ft_get_remind(char *buffer, char *line)
{
	int		len;
	int		i;
	int		j;
	char	*remind;

	if (!line)
	{
		free (buffer);
		return (NULL);
	}
	i = 0;
	while (line[i])
		++i;
	len = ft_strlen(&buffer[i]) + 1;
	remind = (char *)malloc(sizeof(char) * len);
	if (!remind)
		return (free(buffer), NULL);
	j = 0;
	while (buffer[i])
		remind[j++] = buffer[i++];
	remind[j] = '\0';
	free (buffer);
	if (ft_strlen(remind) == 0)
		ft_free_ptr ((void **)&remind);
	return (remind);
}

static char	*ft_get_line(char *buffer)
{
	char	*line;
	char	*end;
	int		len;
	int		i;

	end = ft_strchr(buffer, '\n');
	if (!end)
		return (ft_strdup(buffer));
	len = (end - buffer) + 2;
	line = (char *)malloc(sizeof(char) * len);
	if (!line)
		return (NULL);
	i = 0;
	while (&buffer[i] != end + 1)
	{
		line[i] = buffer[i];
		++i;
	}
	line[i] = '\0';
	if (ft_strlen(line) == 0)
		return (NULL);
	return (line);
}

static char	*ft_read_file(char *buffer, int fd)
{
	char	*read_buf;
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		read_buf = (char *)malloc((sizeof(char) * BUFFER_SIZE) + 1);
		if (!read_buf)
			return (free(buffer), NULL);
		ft_bzero(read_buf, BUFFER_SIZE + 1);
		bytes_read = read(fd, read_buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free (read_buf);
			free (buffer);
			return (NULL);
		}
		buffer = ft_strjoin(buffer, read_buf);
		if (ft_strchr(buffer, '\n') || buffer == NULL)
			break ;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[70000];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = (char *)malloc(sizeof(char) * 1);
		if (!buffer[fd])
			return (NULL);
		buffer[fd][0] = '\0';
	}
	buffer[fd] = ft_read_file(buffer[fd], fd);
	if (!buffer[fd])
		return (NULL);
	if (ft_strlen(buffer[fd]) == 0)
	{
		free (buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	line = ft_get_line(buffer[fd]);
	buffer[fd] = ft_get_remind(buffer[fd], line);
	return (line);
}
/*
int	main(void)
{
	int	fd;

	fd = open("prueba.txt", O_RDONLY);
	if (fd == -1)
	{
		perror ("open");
		exit(EXIT_FAILURE);
	}
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	close(fd);
	return (0);
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open("prueba.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file");
		return (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		count++;
		printf("[%d]:%s\n", count, line);
		free(line);
		line = NULL;
	}
	close(fd);
		return (0);
}
*/