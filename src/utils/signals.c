/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:46:08 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/12 13:43:26 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

void	sigquit_handler(int signal)
{
	(void)signal;
	ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
}

int	event(void)
{
	return (EXIT_SUCCESS);
}

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
		g_signal = 1;
		//exit(130);
	}
}

void	ft_init_signals(void)
{
	struct sigaction	sa;

	rl_event_hook = event;
	sa.sa_flags = 0;
	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	rl_catch_signals = 1;
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