/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:16:38 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/10 09:28:18 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*static void	ft_handle_exit(t_utils *utils, char *input, char **env)
{
	ft_putstr_fd("exit\n", 1);
	free(input);
	ft_free_array(env);
	ft_free_utils(utils);
	rl_clear_history();
	//exit(EXIT_SUCCESS);
}*/

static void ft_cleanup(t_utils *utils, char **env, char *input, t_tokens *commands, t_cmds *cmd)
{
	if (utils)
		ft_free_utils(utils);
	if (env)
		ft_free_array(env);
	if (input)
		free(input);
	if (cmd)
		ft_free_cmd(cmd);
	if (commands)
		ft_free_tokens(&commands);
	rl_clear_history();
}

static int	ft_process_input(char *input, t_tokens **commands, t_cmds **cmd, char *path, t_utils *utils)
{
	*commands = ft_lexer_input(input);
	if (!*commands)
		return (ft_free_tokens(commands), free(input), 0);
	*cmd = ft_parser(*commands, path, utils);
	if (!cmd)
		return (ft_free_tokens(commands), free(input), 0);
	return (1);
}

/*void	prompt_loop(t_utils *utils, char *path)
{
	char		*input;
	t_tokens	*commands;
	t_cmds		*cmd;
	char		**env;
	
	input = NULL;
	cmd = NULL;
	commands = NULL;

	ft_init_signals();
	env = ft_list_to_char(utils->environ);
	while (utils->exit_status == -1)
	{
		if (utils->status == 0)
		{
			ft_free_array(env);
			break;
		}
		input = read_input(env);
		if (!input)
		{
			//ft_handle_exit(utils, input, env);
			//ft_free_array(env);
			free(input);
				//free(path);
			//rl_clear_history();
			break ;
		}		
		if (!ft_process_input(input, &commands, &cmd, path, utils))
		{
			
			ft_free_tokens(&commands);
			continue;;
		}
		if (cmd && env)
			ft_executor(cmd, utils, env);
		ft_free_cmd(cmd);
		ft_free_tokens(&commands);
	}
	ft_free_utils(utils);
	ft_free_array(env);
	rl_clear_history();
}
*/
void	prompt_loop(t_utils *utils, char *path)
{
	char		*input;
	t_tokens	*commands;
	t_cmds		*cmd;
	char		**env;
	input = NULL;
	cmd = NULL;
	commands = NULL;
	env = ft_list_to_char(utils->environ);
	if (env)
	{
		while (1)
		{
			//if (utils->status == 0)
				//continue;
			input = read_input(env);
			if (input == NULL)
			{
				ft_putstr_fd("exit\n", 1);
				break;
			}
			if (input[0] == '\0')
			{
				free(input);
				continue;
			}
			if (!ft_process_input(input, &commands, &cmd, path, utils))
			{
				//utils->status = 0;
				continue;
			}
			ft_free_tokens(&commands);
			if (cmd && env)
				ft_executor(cmd, utils, env);
			ft_free_cmd(cmd);
		}
	}
	ft_cleanup(utils, env, input, commands, cmd);
}