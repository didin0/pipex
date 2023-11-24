/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:20:21 by mabbadi           #+#    #+#             */
/*   Updated: 2023/11/24 17:57:42 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft/libft.h"

void	freetab(char **str);
char	**getcmd(char **argv, int i);
char	*getenvpath(char **env);
char	*getpath(char **cmd, char **env);

#endif