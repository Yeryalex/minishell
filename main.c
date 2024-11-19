/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:33:52 by yrodrigu          #+#    #+#             */
/*   Updated: 2024/11/19 21:36:42 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

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
