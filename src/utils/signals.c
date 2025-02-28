/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:46:08 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/28 09:45:37 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

void	ft_control_c(t_utils *utils)
{
	if (g_signal == 1)
	{
		g_signal = 0;
		utils->exit_status = 130;
	}
}

void	*handle_error_ctrl_d(char *stop, int cmd_num)
{
	char	*cmd_count;

	cmd_count = ft_itoa(cmd_num);
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putstr_fd(cmd_count, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(stop, 2);
	ft_putstr_fd("')\n", 2);
	free(cmd_count);
	return (NULL);
}

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 1;
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_signal_child(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = 1;
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_init_signals(int mode)
{
	if (mode == 1)
	{
		signal(SIGINT, handle_signal_child);
		signal(SIGQUIT, handle_signal_child);
	}
	if (mode  == 0)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
	}
}
