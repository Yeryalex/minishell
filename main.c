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

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int main()
{
    char *line;

    // Mostrar el prompt al usuario y leer la línea de entrada
    line = readline("Ingresa una línea de texto: ");

    // Imprimir la línea de entrada
    printf("La línea ingresada es: %s\n", line);

    // Liberar la memoria asignada para la línea de entrada
    free(line);

    return 0;
}
