/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:23:39 by mabbadi           #+#    #+#             */
/*   Updated: 2023/11/15 17:51:34 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **getcmd(char **argv)
{
	char **args = ft_split(argv[1], ' ');
	return args;
}

int	main(int argc, char **argv, char **env)
{

	char **str = ft_split("abcd", ' ');
	printf("%s", str[0]);
	return (0);
}