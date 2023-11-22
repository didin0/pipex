/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:23:39 by mabbadi           #+#    #+#             */
/*   Updated: 2023/11/22 14:29:26 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **getcmd(char **argv)
{
	char **args = ft_split(argv[1], ' ');
	return args;
}

char *getpath(char **env)
{
	int i = 0;
	
	while(env[i])
	{
		if(ft_strncmp(env[i], "PATH", 4) == 0)
		{
			return (env[i]);
		}
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **env)
{
// int i = 0;
// 	while(env[i]){
// 		printf("%d : %s\n", i, env[i]);
// 	i++;
// 	}
	printf("%d", ft_strncmp(env[19], "PATH", 4));
	return (0);
}