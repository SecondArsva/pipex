/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:37:02 by davidga2          #+#    #+#             */
/*   Updated: 2023/09/14 20:34:46 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
// Esto es un caos. Spliteo PATH, los argumentos del comando del infile y,
// en principio, tras ello tocaría ejecutar el comando. Pero ni idea de como
// gestionar los errores.
void	ft_exec(char **argv, char **envp)
{
	int		i;
	char	**binaries;
	char	**cmd;
	char	*cmd_path;

	i = 0;
	binaries = ft_get_paths(envp);
	cmd = ft_split(argv[3], ' ');
	while (binaries[i])
	{
		if (access(binaries[i], F_OK) != -1)
		{
			cmd_path = ft_strdoublejoin(binaries[i], "/", cmd[0]);
			if (!cmd_path)
				ft_error("Double join failed");
			if (access(cmd_path, X_OK) != -1)
			{
				printf("this is the path:%s\n", cmd_path);
				if (execve(cmd_path, cmd, envp) == -1)
					ft_error("Command execution failed.");
			}
		}
		i++;
	}
	ft_error("No se pudo acceder a los directorios binarios");
}*/

// Esto va de lujo. Busca el PATH en el env y "splitea" los binaries.
// Si no existe PATH, revienta. Falta reventar el caso de envp == NULL.
// Revisa el compartamiento de samusanc con el PATH unseteado.
char **ft_get_paths(char **envp)
{
	int i;
	char **matrix;

	i = -1;
	matrix = NULL;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 4))
		i++;
	if (!envp[i]) // Esto evita un segmantation fault en caso de no existir la variable PATH.
		ft_error("PATH dont exits in the enviroment");
	matrix = ft_split(&envp[i][4], ':');
	if (!matrix)
		ft_error("Binaries matrix reserve failed");
	return (matrix);
}

// En construcción. Equivale al padre.
void ft_pipex(char **argv, char **envp)
{
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		ft_error("La vinculación de fd en la creación del pipe ha fallado");
	ft_infile_child(argv, envp, pipe_fd);
	ft_outfile_child(argv, envp, pipe_fd);
	if (close(pipe_fd[0]) == -1 || close(pipe_fd[1]) == -1)
		ft_error("Parent cant close some pipe_fd");
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
}

// En construcción.
int	main(int argc, char **argv, char **envp)
{
	if (argc == 5)
		ft_pipex(argv, envp);
	else
		return (1);
	return (0);
}
