
#include "../../inc/minishell.h"

void	ft_wait_for_childs(int i, int *exit_status)
{
	int	exit;

	exit = 0;
	while (i-- > 0)
	{
		wait(&exit);
		if (WIFSIGNALED(exit))
		{
			*exit_status = 128 + WTERMSIG(exit);
			if (WTERMSIG(exit) == SIGQUIT)
				ft_putstr_fd("Quit (core dumped)\n", 2);
			else if (WTERMSIG(exit) == SIGINT)
			{
				g_signal = 1;
				ft_putstr_fd("\n", 2);
			}
		}
		else if (WIFEXITED(exit))
		{
			*exit_status = WEXITSTATUS(exit);
		}
	}
}