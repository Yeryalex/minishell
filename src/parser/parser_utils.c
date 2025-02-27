/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:27:04 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/27 14:05:33 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_addlast_pnode(t_cmds **list, t_cmds *node)
{
	t_cmds	*current_node;

	if (!*list)
	{
		*list = node;
		return ;
	}
	current_node = *list;
	while (current_node->next)
		current_node = current_node->next;
	current_node->next = node;
	node->prev = current_node;
}

/* Libera un array de cadenas y devuelve NULL */
void	*free_cmd_array(char **cmd_array)
{
	int	i;

	if (!cmd_array)
		return (NULL);
	i = 0;
	while (cmd_array[i])
	{
		free(cmd_array[i]);
		cmd_array[i] = NULL;
		i++;
	}
	free(cmd_array);
	return (NULL);
}

/*char	*ft_random_filename(void)
{
	char	*name;
	int		fd;
	char	tmp;
	int		i;

	name = (char *)malloc(12 * sizeof(char));
	if (!name)
		return (NULL);
	ft_strlcpy(name, "tmp_file_", 9);
	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (free(name), NULL);
	i = 8;
	while (i < 11)
	{
		if (read(fd, &tmp, 1) != 1)
		{
			close(fd);
			return (free(name), NULL);
		}
		name[i] = (tmp % 26) + 'a';
		i++;
	}
	close(fd);
	name[11] = '\0';
	return (name);
}
*/

static int	ft_fill_random_chars(char *name, int fd)
{
	int		i;
	char	tmp;

	i = 8;
	while (i < 11)
	{
		if (read(fd, &tmp, 1) != 1)
		{
			close(fd);
			free(name);
			return (0);
		}
		name[i] = (tmp % 26) + 'a';
		i++;
	}
	return (1);
}

char	*ft_random_filename(void)
{
	char	*name;
	int		fd;

	name = (char *)malloc(12 * sizeof(char));
	if (!name)
		return (NULL);
	ft_strlcpy(name, "tmp_file_", 9);
	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0 || !ft_fill_random_chars(name, fd))
		return (NULL);
	close(fd);
	name[11] = '\0';
	return (name);
}
