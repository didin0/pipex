/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:23:39 by mabbadi           #+#    #+#             */
/*   Updated: 2023/11/28 17:35:08 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void child(int fd[2], char **argv, char **env)
{
	close(fd[0]);

	int infile = open(argv[1], O_RDONLY, 0777);
		if (infile < 0)
	{
		close(fd[1]);
		exit(errno);
	}
	char **cmd = getcmd(argv, 2);
	char *path = getpath(cmd, env);
	
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execve(path, cmd, NULL);
	close(infile);
}

void parent(int fd[2], char **argv, char **env)
{
	close(fd[1]);
	int outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0666);
	char **cmd2 = getcmd(argv, 3);
	char *path2 = getpath(cmd2, env);
	if (outfile < 0)
	{
		close(fd[0]);
		exit(errno);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[0]);
	execve(path2, cmd2, NULL);
	close(outfile);
}

int	main(int argc, char **argv, char **env)
{
	int fd[2];
	pid_t pid1;
	if (pipe(fd) < 0)
		return (1);
	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
		child(fd, argv, env);
	parent(fd, argv, env);\
	waitpid(pid1, NULL, 0);
	return (0);
}
