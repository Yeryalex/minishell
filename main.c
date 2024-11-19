/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:33:52 by yrodrigu          #+#    #+#             */
/*   Updated: 2024/11/19 20:05:53 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int main()
{
    char *line;

    line = readline("\033[95mminishell42\033[92m$\033[0m ");

    printf("La línea ingresada es: %s\n", line);

    free(line);

    return 0;
}
