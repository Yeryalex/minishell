/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:08:28 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/01/24 11:20:21 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"


/*
char	*ft_get_path(char *path, char *cmd)
{
	char	**path_dir;
	char	*path_to_exec;
	char	*tmp;
	int		i;

	path_dir = ft_split(path, ':');
	if (!path_dir)
		return NULL;
	i = 0;
	while(path_dir[i])
	{
		path_to_exec = ft_strjoin(path_dir[i], "/");
		if (!path_to_exec)
			return (ft_free_array(path_dir), NULL);
		tmp = ft_strjoin(path_to_exec, cmd);
		if (!tmp)
			return (ft_free_array(path_dir), free(path_to_exec), NULL);
		free(path_to_exec);
		path_to_exec = tmp;
		if (access(path_to_exec, F_OK | X_OK) == 0)
			break ;
		free(path_to_exec);
		i++;
	}
	return (ft_free_array(path_dir), path_to_exec);	
}
*/

/*
void print_struct(t_commands *lst)
{
	while (lst)
	{
		if (lst->prev)
		{
    		printf("Struct content->prev = %i\n", lst->prev->id);
		}
		else
    		printf("first content->prev node is NULL\n");
		printf("struct content %i\n", lst->id);
		if (lst->next)
		    printf("struct content->next = %i\n", lst->next->id);
		else
    		printf("last content->next node is NULL\n");
		lst = lst->next;
	}
}
*/

void	ft_dup_close(t_cmds *cmd, int prev_read, int *fd)
{
	if (cmd->prev)
	{
		dup2(prev_read, STDIN_FILENO);
		close(prev_read);
	}
	if (cmd->next)
	{
		dup2(fd[1], STDOUT_FILENO);;
		close(fd[1]);	
	}
}

int	ft_forking(t_cmds *cmd, int	prev_read, int *fd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_dup_close(cmd, prev_read, fd);
		execve(cmd->full_path, cmd->cmd_array, env);
		exit(1);
	}
	return (1);
}

void	ft_reset_read_end(t_cmds *current, int *prev_read, int *fd)
{
	if (current->next)
		close(fd[1]);
	if (current->prev)
		close(*prev_read);
	if (current && current->next)
		*prev_read = fd[0];
}

/*
int	ft_is_builtin(t_commands *cmd, t_utils *utils)
{
	int i;

	i = 0;
	while (utils->builtins[i])
	{
		if (!ft_strncmp(cmd->cmd[0], utils->builtins[i], 
					ft_strlen(utils->builtins[i] + 1)))
			return (1);
		i++;
	}
	return (0);
}

void	ft_call_builtin()
{

}

void	ft_exec_builtin(t_commands *cmd, t_utils *utils, int fd)
{
	(void)utils;
	if (!ft_strncmp(cmd->cmd[0], "echo", 5))
		ft_echo(cmd, fd);
}
*/

void	ft_executor(t_cmds *current, t_utils *utils, char **env)
{
	int	fd[2];
	int	prev_read;
	int	i;
	
	(void)utils;
	i = 0;
	prev_read = -1;

	while (current)
    {
    	if (current->next && pipe(fd) == -1)
		{
            perror("error in pipe\n");
			return ;
        }
		if (current->cmd_array && current->cmd_array[0])
		{
		/*	if (ft_is_builtin(current, utils))
			{
				printf("%s is builtin\n", current->cmd[0]);
				ft_exec_builtin(current, utils, fd[1]);
			}
			else	*/
        	i += ft_forking(current, prev_read, fd, env);
        	ft_reset_read_end(current, &prev_read, fd);
		}
		current = current->next;
     }
 
     printf("Number of process = %i\n", i);
     while (i-- > 0)
     {
         wait(NULL);
     }
}


/*
int main(int argc, char **argv, char **env)
{
	(void)argc, (void)argv;
	t_commands	*cmd;
	t_commands	*cmd2;
	t_commands	*cmd3;
	t_commands	*cmd4;
	t_utils		*utils;
	char		*path_value;

	path_value = getenv("PATH");

	cmd = ft_newlst();
	cmd2 = ft_newlst();
	cmd3 = ft_newlst();
	cmd4 = ft_newlst();
	utils = (t_utils *)malloc(sizeof(t_utils));
	if (!utils)
		return (0);

	init_cmds(cmd);
	init_cmds2(cmd2);
	init_cmds3(cmd3);
	init_cmds4(cmd4);

	cmd->full_PATH = ft_get_path(path_value, "ls");
	cmd2->full_PATH = ft_get_path(path_value, "wc");
	cmd3->full_PATH = ft_get_path(path_value, "grep");
	cmd4->full_PATH = ft_get_path(path_value, "wc");

//	ft_lstadd_back(&cmd, cmd2);
//	ft_lstadd_back(&cmd, cmd3);
//	ft_lstadd_back(&cmd, cmd4);
	
	init_utils(utils);


	ft_executor(cmd, utils, env);


	ft_free(cmd);
	ft_free(cmd2);
	ft_free(cmd3);
	ft_free(cmd4);
	free(utils);
	
	return (0);
}
*/
