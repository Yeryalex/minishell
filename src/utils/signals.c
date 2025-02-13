/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:46:08 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/13 13:10:36 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

/*void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);                                                      
	    rl_replace_line("", 0);                                                 
        rl_on_new_line();                                                       
        rl_redisplay();   
		g_exit = 130;
	}
	
}

void	ft_init_signals(void)
{
	rl_catch_signals = 1;
	signal(SIGINT, sigint_handler);                                            
    signal(SIGQUIT, SIG_IGN);	
}*/
void sigint_handler(int sig)
{
    if (sig == SIGINT)
	{ 
		
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit = 130;
		
	}
}

void ft_init_signals(void)
{
    struct sigaction sa;

      /*/ Configuramos el handler para SIGINT*/
	sa.sa_handler = sigint_handler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sa, NULL);
}

