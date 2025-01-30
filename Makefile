# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akurochk <akurochk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 13:21:16 by akurochk          #+#    #+#              #
#    Updated: 2025/01/30 14:37:45 by akurochk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# the name of the binary
NAME =	ircserv

# sources needed to compile
SRC =	main.cpp \
		Client.cpp \
		Channel.cpp \
		Server.cpp \
		ServerCommands.cpp \
		ServerPrint.cpp \
		cmdCAP.cpp \
		cmdNICK.cpp \
		cmdPASS.cpp \
		cmdPING.cpp \
		cmdUSER.cpp \
		cmdWHOIS.cpp

# path of sources
PATH_SRCS =	./srcs

# pathe of includes
INCLUDES =	./includes/

# flags for compilation
CXXFLAGS =	-Wall -Wextra -Werror -std=c++98

# compiler used
CXX =		c++

##########################################

SRCS =		$(addprefix $(PATH_SRCS)/,$(SRC))
OBJ =		$(addprefix $(OBJ_DIR)/,$(SRC:.cpp=.o))
OBJ_DIR =	.obj

all: $(NAME)

$(OBJ_DIR)/%.o: $(PATH_SRCS)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -I $(INCLUDES) $(OBJ) -o $(NAME)
	@chmod 777 $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)
	@rm -rf .vscode

re: fclean all

run:	re
		clear
		./ircserv 1234 4545

.PHONY: all clean fclean re run
