/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:33:52 by yrodrigu          #+#    #+#             */
/*   Updated: 2024/12/22 11:25:09 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int ac, char **argv, char **env)
{
	t_env	*env_list;

	(void)argv;
	char	**environ;
	int		i;
	
	i = 0;
	if (!isatty(STDIN_FILENO))
	{
		perror("./minishell");
		exit(EXIT_FAILURE);
	}
	if (ac != 1)
	{
		perror("Error ./minishel without arguments");
		return (EXIT_FAILURE);
	}
<<<<<<< HEAD
	if (!env)
		environ = ft_init_env(env);
	else
	{
		environ = env;
		while (environ[i])
		{
   			printf("%s Num linea: %d\n", environ[i], i);
   			i++;
   		}
	}
=======
	env_list = ft_env_init(env);
>>>>>>> 7f28b3ae1f0acf86087ff21e16fb467bde059652
	prompt_loop();
 	return (0);
}
