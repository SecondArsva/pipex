/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 03:05:27 by davidga2          #+#    #+#             */
/*   Updated: 2023/09/17 22:11:39 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// Esto determina si la ruta es absoluta, relativa, o ninguna de las dos.
// En caso de ser absoluta o relativa el path se tomará del argv
// correspondiente al comando y en caso de que no sea ninguna de las dos,
// el path se tomará de los directorios binarios albergados en la variable
// de entorno PATH.
int	ft_path_type(char *cmd_argv)
{
	int path_type;

	path_type = 0;
	if (ft_strncmp(cmd_argv, "/", 1) == 0 || ft_strncmp(cmd_argv, "./", 2) == 0
		|| ft_strncmp(cmd_argv, "../", 3) == 0)
	{
		//ft_printf("The path is absolute or relative.\n");
		path_type = 1;
	}
	else
	{
		//ft_printf("The path its a binary file.\n");
		path_type = 2;
	}
	return (path_type);
}

// Esto va de lujo. Busca el PATH en el env y "splitea" los binaries.
// Si no existe PATH, debería reventar. Falta reventar el caso de envp == NULL.
// Revisa el compartamiento de samusanc con el PATH unseteado.
char **ft_get_paths(char **envp)
{
	int i;
	char **matrix;

	i = 0;
	matrix = NULL;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
	{
		//ft_printf("-; %s\n", envp[i]);
		i++;
	}
	//ft_printf("-; %s\n", envp[i]);
	if (!envp[i]) // Esto evita un segmantation fault en caso de no existir la variable PATH.
		ft_error("PATH dont exits in the enviroment");
	matrix = ft_split(&envp[i][4], ':');
	if (!matrix)
		ft_error("Binaries matrix reserve failed");
	return (matrix);
}

// Esta función hace uso de la variable de entorno PATH para obtener el directorio binario
// correcto en el que se encuentre el comando.
char	*ft_get_correct_binary_path(char *cmd, char **envp)
{
	char	*correct_path;
	char	**binaries;
	int		i;

	correct_path = NULL;
	binaries = ft_get_paths(envp);
	i = 0;
	if (!binaries)
		ft_error("Binaries matrix creation failed");
	while (binaries[i])
	{
		correct_path = ft_strdoublejoin(binaries[i], "/", cmd);
		if (!correct_path)
			ft_error("Double join failed");
		if (access(correct_path, X_OK) == 0)
		{
			//ft_printf("CP. %s\n", correct_path);
			return (correct_path);
		}
		i++;
	}
	ft_error("Command not found");
	return (NULL);
}

void	ft_exec(char *cmd_argv, char **envp)
{
	char **cmd;
	char *path;

	cmd = ft_split(cmd_argv, ' ');
	if (!cmd)
		ft_error("Command matrix creation failed");
	if (ft_path_type(cmd_argv) == 1)
		path = cmd[0];
	else if (ft_path_type(cmd_argv) == 2)
		path = ft_get_correct_binary_path(cmd[0], envp);
	if (execve(path, cmd, envp) == -1)
		ft_error("Command execution failed");
}
