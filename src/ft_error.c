/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:21:44 by davidga2          #+#    #+#             */
/*   Updated: 2023/09/14 20:23:28 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// Función para reventar la ejecución. vicmarti dice que no está de acuerdo
// al retornar el "errno". Con algo que no sea 0 le vale.
void	ft_error(char *msg)
{
	perror(msg);
	exit(errno);
}
