/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:16:38 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/28 22:21:23 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tokens	*ft_free_in_input(t_tokens *lexer, t_tokens *node)
{
	ft_free_tokens(&lexer);
	ft_free_tokens(&node);
	return (NULL);
}

int	ft_print_syntax_error(t_tokens *temp)
{
	printf("minishell: syntax error near unexpected ");
	printf("token `%s'\n", temp->value);
	return (0);
}

static void	ft_handle_exit(t_utils *utils, char *input)
{
	int		_exit;

	_exit = utils->exit_status;
	free(input);
	ft_free_array(utils->env_in_char);
	ft_free_utils(utils);
	rl_clear_history();
	ft_putstr_fd("exit\n", 1);
	exit(_exit);
}

static int	ft_process_input(char *input, t_tokens **commands,
		t_cmds **cmd, t_utils *utils)
{
	*commands = ft_lexer_input(input, utils);
	if (!*commands)
		return (ft_free_tokens(commands), free(input), 0);
	*cmd = ft_parser(*commands, utils);
	if (!cmd)
		return (ft_free_tokens(commands), free(input), 0);
	return (1);
}

void	prompt_loop(t_utils *utils)
{
	char		*input;
	t_tokens	*commands;
	t_cmds		*cmd;

	input = NULL;
	cmd = NULL;
	commands = NULL;
	ft_control_c(utils);
	while (1)
	{
		ft_init_signals(0);
		if (utils->status == 0)
			break ;
		utils->path_to_input = ft_get_paths_from_env(utils->environ);
		input = read_input(utils->env_in_char, utils);
		if (!input)
			ft_handle_exit(utils, input);
		if (!ft_process_input(input, &commands, &cmd, utils))
			continue ;
		ft_executor(cmd, utils, utils->env_in_char);
		//ft_free_array(utils->env_in_char);
		ft_auxiliar_free(cmd, input, commands);
		utils->cmds_amount++;

	}
	ft_free_array(utils->env_in_char);
	rl_clear_history();
}
