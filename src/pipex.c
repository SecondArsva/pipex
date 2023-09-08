/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:37:02 by davidga2          #+#    #+#             */
/*   Updated: 2023/09/08 05:52:26 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_error(char *msg);
void	ft_infile_child(char **argv, char **envp, int *pipe_fd);
void	ft_outfile_child(char **argv, char **binaries, char **envp);
char	**ft_get_paths(char **envp);
void	ft_pipex(char **argv, char **envp);
void	ft_exec(char binaries, char **cmd, char **envp);

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
	mtx = NULL;
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
void	ft_exec(char binaries, char **envp)
{
	char	**binaries;
	char	**cmd;

	binaries = ft_get_paths(envp);
	cmd = argv[2];
	while (binaries[i])
	{
		if (access(binaries[i], F_OK) != -1)
		{
			//nesecitaria hacer un join que pasarle al acces X_OK
			if (access(ft_strjoin(binaries[i], ft_strjoin("/", cmd[0])), F_OK) != -1)
				execve(binaries[i], cmd, envp);
		}
		else
			ft_error("No se pudo acceder a los directorios binarios");
		i++;
	}
}

// El infile_child creo que está bien.
void	ft_infile_child(char **argv, char **envp, int *pipe_fd)
{
	int		infile_fd;
	pid_t	child_pid;

	infile_fd = open(argv[1], O_RDONLY);
	child_pid = fork();
	if (child_pid < 0 || infile_fd < 0)
		ft_error("Infile fd open or infile child creation proccess failed");
	if (child_pid == 0)
	{
		if (dup2(infile_fd, STDIN_FILENO) < 0
			|| dup2(pipe_fd[0], STDOUT_FILENO < 0)
			ft_error("dup2 failed on its execution changing fds");
		ft_exec(argv, envp);
	}
}

// En construcción. Equivale al padre.
void ft_pipex(char **argv, char **envp)
{
	//int		outfile_fd;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		ft_error("La vinculación de fd en la creación del pipe ha fallado");
	//outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	ft_infile_child(argv, envp, pipe_fd);
}

// En construcción.
int	main(int argc, char **argv, char **envp)
{
	if (argc == 3)
		ft_pipex(argv, envp);
	else
		return (1);
	return (0);
}
