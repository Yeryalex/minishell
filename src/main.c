/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:33:52 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/01/17 11:21:17 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int ac, char **argv, char **env)
{
	t_env	*environ;
	char	*environ2;
	int		i;
	(void)argv;
	
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
	//if (!env)
	//{
	
		environ = ft_init_env(env);
		while (environ)
		{
			printf(" Variable env propia: %s = %s\n", environ->key, environ->value);
			environ = environ->next;
		}
		environ2 = getenv(*env);
		while (environ2)
		{
			printf(" Variable env 2 getenv %c\n", environ2[0]);
			environ2++;
		}
	//}
	//else
	//{
		while (*env)
		{
			printf(" Variable env sys: %s\n", env[0]);
			env++;
		}
	//}
	//ft_print_env_list(environ);
	prompt_loop(environ);
 	return (0);
}
