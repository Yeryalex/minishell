/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:33:52 by yrodrigu          #+#    #+#             */
/*   Updated: 2024/11/20 10:51:15 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
