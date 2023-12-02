# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/11 16:34:15 by mabbadi           #+#    #+#              #
#    Updated: 2023/12/02 16:07:23 by mabbadi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc
FLAGS = -Wall -Wextra -Werror -g3

# Liste des fichiers source
SOURCES := main.c \
					utils.c \
					errandfree.c \
		   $(wildcard Libft/*.c) \

# Liste des fichiers d'en-tête
HEADERS :=	$(wildcard *.h) \
		   		$(wildcard Libft/*.h)

# Génération de la liste des fichiers objets
OBJECTS := $(SOURCES:.c=.o)

# Règle pour la compilation des fichiers source en fichiers objets
%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -Iincludes -c $< -o $@

# Règle pour la création de l'exécutable
$(NAME): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
