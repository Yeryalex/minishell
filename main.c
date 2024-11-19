/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:33:52 by yrodrigu          #+#    #+#             */
/*   Updated: 2024/11/06 17:34:52 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*#include "minishell.h"

int	main()
{
	printf("I am the begining of MINISHELL\n");
	return (0);
}*/
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int main()
{
    char *line;
    int i;
    for(i = 0; i < 5; i++) {
        line = readline("Ingresa una línea de texto: ");
        add_history(line);
    }
    while(1) {
        line = readline("Ingresa una línea de texto (o presiona ctrl + c para salir): ");
        if(line != NULL) {
            printf("La línea ingresada es: %s\n", line);
        } else {
            break;
        }
    }
    return 0;
}
