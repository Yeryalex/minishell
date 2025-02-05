/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:46:08 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/05 13:19:03 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

/*void	ft_ctr_c(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		//exit(130);
	}
}

		g_signal = 0;
		utils->exit_status = 130;
	}
}*/

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
	/*if (g_status == 0)
	{
		g_status = 2;
		rl_done = 1;
	}
	else
	{*/
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
		//exit(130);
	}
	//}
	//(void)signal;
}

void	init_signals(void)
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
