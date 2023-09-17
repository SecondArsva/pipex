/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:21:44 by davidga2          #+#    #+#             */
/*   Updated: 2023/09/17 23:16:59 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// Función para reventar la ejecución. vicmarti dice que no está de acuerdo
// al retornar el "errno". Con algo que no sea 0 le vale.
void	ft_error(char *str)
{
	perror(str);
	exit(errno);
}

// Función dedicada a los errores de comandos no encontrados.
void	ft_cmd_error(char *cmd)
{
	ft_printf_error("%s", cmd);
	ft_printf_error(": command not found\n");
	exit(127);
}
