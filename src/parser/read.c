/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 07:47:48 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/24 18:34:43 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	write_on_file(int fd, char *read_line)
{
	if (fd < 0)
	{
		free (read_line);
		return (-1);
	}
	if (write(fd, read_line, ft_strlen(read_line)) == -1)
	{
		free (read_line);
		return (-1);
	}
	free (read_line);
	if (write(fd, "\n", 1) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	read_and_write(char *stop, int cmds_amount, char *f_name)
{
	char	*read_line;
	int		fd;

	while (1)
	{
		read_line = readline("> ");
		if (!read_line)
		{
			handle_error_ctrl_d(stop, cmds_amount);
			return (-1);
		}
		if (!ft_strncmp(read_line, stop, ft_strlen(stop) + 1))
			break ;
		fd = ft_open_fd(f_name, O_WRONLY | O_APPEND | O_CREAT);
		if (write_on_file(fd, read_line) == -1)
			return (-1);
		close(fd);
	}
	free (read_line);
	return (0);
}

int	ft_read_to_file(char *stop, int cmds_amount, char *f_name)
{
	char	new_stop[4096];
	int		fd;

	if (!stop)
		return (-1);
	fd = ft_open_fd(f_name, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd != -1)
		close(fd);
	ft_bzero(new_stop, 4096);
	ft_strlcpy(new_stop, stop, 4096);
	free (stop);
	if (read_and_write(new_stop, cmds_amount, f_name) == -1)
		return (-1);
	return (0);
}
