/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:24:27 by davidga2          #+#    #+#             */
/*   Updated: 2023/09/17 19:16:18 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// Función sugerida por samusanc para gestionar la falla de la creación del
// hijo en la ejecución de la inicialización de la variabe que alberga el pid.
int fork_error(void)
{
	int i;

	i = fork();
	if (i == -1)
		ft_error("Infile child pid creation proccess failed");
	return (i);
}

// El hijo del final ha de cerrar el pipe entero. Por lo que debe hacer 3 "close()".
// Output.
void	ft_outfile_child(char **argv, char **envp, int *pipe_fd)
{
	int		outfile_fd;
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == -1)
		ft_error("Outfile child pid creation proccess failed");
	if (child_pid == 0)
	{
		if (close(pipe_fd[1]) == -1)
			ft_error("Output child failed closing the write fd pipe");
		outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (outfile_fd == -1 || dup2(pipe_fd[0], STDIN_FILENO) == -1
			|| dup2(outfile_fd, STDOUT_FILENO) == -1)
			ft_error("Outfile fd creation or dup2 failed");
		if (close(pipe_fd[0]) == -1 || close(outfile_fd) == -1)
			ft_error("Some fd close failed in the output child proccess");
		ft_exec(argv[3], envp);
	}

}

// El infile_child creo que está bien. Subproceso input.
void	ft_infile_child(char **argv, char **envp, int *pipe_fd)
{
	int		infile_fd;
	pid_t	child_pid;

	child_pid = fork_error();
	if (child_pid == 0)
	{
		if (close(pipe_fd[0]) == -1)
			ft_error("Input child failed closing the read fd pipe");
		infile_fd = open(argv[1], O_RDONLY);
		//ft_printf("dune: %i\n", infile_fd);
		if (infile_fd == -1 || dup2(infile_fd, STDIN_FILENO) == -1
			|| dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			ft_error("Infile fd creation or dup2 failed");
		if (close(infile_fd) == -1 || close(pipe_fd[1]) == -1)
			ft_error("Some fd close failed in the infile child proccess");
		ft_exec(argv[2], envp);
	}
}
