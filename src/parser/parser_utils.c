/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:27:04 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/24 08:32:20 by rbuitrag         ###   ########.fr       */
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

void	filename(char *name)
{
	int		fd;
	int		i;
	char	tmp;

	i = 0;
	while (i < 3)
	{
		fd = open("/dev/urandom", O_RDONLY);
		if (fd < 0)
			free (name);
		if (read(fd, &tmp, 1) != 1)
		{
			close (fd);
			free (name);
		}
		close (fd);
		name[i] = (tmp % 26) + 'a';
		i++;
	}
}

/*char	*ft_random_filename(void)
{
	char			*name;

	name = (char *)malloc(3 + 1 * sizeof(char));
	if (!name)
		return (free(name), NULL);
	filename(name);
	name[3] = '\0';
	if (!access((const char *)name, F_OK))
	{
		free(name);
		name = ft_random_filename();
	}
	name = ft_strjoin(ft_strdup("tmp_file"), name);
	if (!name)
		return (free(name), NULL);
	return (name);
}*/

char	*ft_random_filename(void)
{
	char	*name;
	char	*prefix;
	char	*final_name;

	// 🔹 Reservar memoria para el nombre
	name = (char *)malloc(4 * sizeof(char));
	if (!name)
		return (NULL);
	filename(name);
	name[3] = '\0';

	// 🔹 Si el archivo ya existe, liberar `name` y generar otro
	if (!access((const char *)name, F_OK))
	{
		free(name);
		return (ft_random_filename());
	}

	// 🔹 Crear el nombre final con prefijo "tmp_file"
	prefix = ft_strdup("tmp_file");
	if (!prefix)
		return (free(name), NULL);

	final_name = ft_strjoin(prefix, name);
	free(name);
	free(prefix); // 🔹 Liberar `prefix` después de usarlo

	if (!final_name)
		return (NULL);

	return (final_name);
}
