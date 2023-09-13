/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:37:02 by davidga2          #+#    #+#             */
/*   Updated: 2023/09/13 16:52:21 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_error(char *msg);
void	ft_infile_child(char **argv, char **envp, int *pipe_fd);
void	ft_outfile_child(char **argv, char **envp, int *pipe_fd);
char	**ft_get_paths(char **envp);
void	ft_pipex(char **argv, char **envp);
void	ft_exec(char **argv, char **envp);

// Función para reventar la ejecución. vicmarti dice que no está de acuerdo
// al retornar el "errno". Con algo que no sea 0 le vale.
void	ft_error(char *msg)
{
	perror(msg);
	exit(errno);
}

// Esto va de lujo. Busca el PATH en el env y "splitea" los binaries.
// Si no existe PATH, revienta. Falta reventar el caso de envp == NULL.
char **ft_get_paths(char **envp)
{
	int i;
	char **matrix;

	i = 0;
	matrix = NULL;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i]) // Esto evita un segmantation fault en caso de no existir la variable PATH.
		ft_error("PATH dont exits in the enviroment");
	matrix = ft_split(&envp[i][5], ':');
	if (!matrix)
		ft_error("Binaries matrix reserve failed");
	return (matrix);
}

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
			ft_error("Some fd close failed in the outfile child proccess-.-.-");
		outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (outfile_fd == -1 || dup2(pipe_fd[0], STDIN_FILENO) == -1
			|| dup2(outfile_fd, STDOUT_FILENO) == -1)
			ft_error("Outfile fd creation or dup2 failed");
		if (close(pipe_fd[0]) == -1 || close(outfile_fd) == -1)
			ft_error("Some fd close failed in the output child proccess");
		ft_exec(argv, envp);
	}

}

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

// El infile_child creo que está bien. Input.
void	ft_infile_child(char **argv, char **envp, int *pipe_fd)
{
	int		infile_fd;
	pid_t	child_pid;

	child_pid = fork_error();
	if (child_pid == 0)
	{
		if (close(pipe_fd[0]) == -1)
			ft_error("Some fd close failed in the infile child proccess-.-.-");
		infile_fd = open(argv[1], O_RDONLY);
		if (infile_fd == -1 || dup2(infile_fd, STDIN_FILENO) == -1
			|| dup2(pipe_fd[1], STDOUT_FILENO == -1))
			ft_error("Infile fd creation or dup2 failed");
		if (close(infile_fd) == -1 || close(pipe_fd[1]) == -1)
			ft_error("Some fd close failed in the infile child proccess");
		ft_exec(argv, envp);
	}
//	close (pipe_fd[1]);
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
