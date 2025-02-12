/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:46:08 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/12 11:40:21 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

/* esta es un desarrollo mas seguro de la memoria*/


void	signal_ctrl_c(void)
{
	struct sigaction	ctrl_c;

	ctrl_c.sa_handler = handle_sigint;
	ctrl_c.sa_flags = SA_RESTART;
	sigemptyset(&ctrl_c.sa_mask);
	sigaction(SIGINT, &ctrl_c, NULL);
}

void	signal_ctrl_backslash(void)
{
	struct sigaction	ctrl_back_slash;

	ctrl_back_slash.sa_handler = SIG_IGN;
	ctrl_back_slash.sa_flags = SA_RESTART;
	sigemptyset(&ctrl_back_slash.sa_mask);
	sigaction(SIGQUIT, &ctrl_back_slash, NULL);
}

void	handle_sigint(int sig_num)
{
	if (sig_num == SIGINT)
	{
		g_exit = 0;
		write(1, "\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	*handle_error_ctrl_d(char *stop, int cmds_amount)
{
	char	*cmds_count;

	cmds_count = ft_itoa(cmds_amount);
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putstr_fd(cmds_count, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(stop, 2);
	ft_putstr_fd("')\n", 2);
	free(cmds_count);
	return (NULL);
}

void	ft_init_signals(void)
{
	g_exit = 1;
	signal_ctrl_backslash();
	signal_ctrl_c();
}

