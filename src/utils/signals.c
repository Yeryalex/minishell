/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:46:08 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/27 16:51:11 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	sigquit_handler(int signal)
{
	(void)signal;
	ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
}

int	event(void)
{
	return (EXIT_SUCCESS);
}

void	sigint_handler(int signal)
{
	if (g_status == 0)
	{
		g_status = 2;
		rl_done = 1;
	}
	else
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	(void)signal;
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
