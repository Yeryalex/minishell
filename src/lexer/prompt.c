/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:16:38 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/10 14:29:30 by rbuitrag         ###   ########.fr       */
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

static void ft_cleanup(char *input, t_tokens *commands, t_cmds *cmd)
{
	if (input)
		free(input);
	if (cmd)
		ft_free_cmd(cmd);
	if (commands)
		ft_free_tokens(&commands);
	input = NULL;
    cmd = NULL;
    commands = NULL;
}

static int	ft_process_input(char *input, t_tokens **commands, t_cmds **cmd, char *path, t_utils *utils)
{
	*commands = ft_lexer_input(input);
	if (!*commands)
		return (0);
	*cmd = ft_parser(*commands, path, utils);
	if (!*cmd)
		return (ft_free_tokens(commands), 0);
	return (1);
}


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
	if (!env)
    {
        fprintf(stderr, "minishell: error: No tables in env array\n");
		ft_free_array(env);
        return;
    }
	while (1)
	{
		if (utils->status == 0)
		{
			ft_free_array(env);
			break;
		}
		input = read_input(env);
		if (input == NULL)
		{
			//ft_putstr_fd("exit\n", STDOUT_FILENO);
			break;
		}
		if (input[0] == '\0')
		{
			free(input);
			continue;
		}
		if (!ft_process_input(input, &commands, &cmd, path, utils))
		{
			free(input);
            ft_free_tokens(&commands);
            //utils->status = 0;
			continue;
		}
		if (cmd && env)
			ft_executor(cmd, utils, env);
		ft_cleanup(input, commands, cmd);
	}
	ft_clear_lstenv(utils->environ);
	rl_clear_history();
	exit(g_exit_code);
}