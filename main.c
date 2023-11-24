/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:23:39 by mabbadi           #+#    #+#             */
/*   Updated: 2023/11/24 18:29:11 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	char **cmd = getcmd(argv, 1);
	char *path = getpath(cmd, env);
	int fd[2];
	pid_t pid;


	// AFFICHAGE
	int i = 0;
	while(cmd[i])
	{
		printf("args %d : <%s> | ",i, cmd[i]);
		i++;
	}
	printf("\npath : %s", path);
	// END

	freetab(cmd);
	free(path);
	return (0);
}