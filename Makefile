# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jonnavar <marvin@42.fr>                    +#+  +:+       +#+         #
#        igenez-y <igenez-y@student.42madrid.com> +#+#+#+#+#+   +#+            #
#    Created: 2025/12/15 23:05:07 by jonnavar          #+#    #+#              #
#    Updated: 2025/12/16 17:17:22 by jonnavar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


## VARIABLE DECLARATIONS ##
###########################


NAME			= miniRT


INC_PATH		= ./include/
OBJ_PATH		= ./object/
SRC_PATH	    = ./src/


LIB_PATH		= ./lib/
LIBFT_PATH		= ${LIB_PATH}libft/
LIBFT_INC_PATH	= ${LIBFT_PATH}include/
LIBFT_FILE		= libft.a
LIBFT_NAME		= ${LIBFT_PATH}${LIBFT_FILE}


CC				= cc
DEBUG_SYMBOLS	= -g3
CFLAGS			= -Wall -Wextra -Werror
INCLUDE_LIBFT	= -I ${LIBFT_INC_PATH}
# include "libm.a" static library
# (/usr/lib/libm.a)
# contains the object files of math library 
# that are used in the project
INCLUDE_MATH	= -lm
INCLUDE			= -I ${INC_PATH} ${INCLUDE_LIBFT}


# both "-g" or "-g3" flags can be used.
# "-g3" includes everything included with "-g", but with 
# additional information to debug preprocessor directives
SANITIZE_FLAGS	= -fsanitize=address
# "--track-origin=yes" tracks the origin of uninitialized values
# "-s" display a summary of the results directly in the terminal
# "--leak-check=full" enable detailed memory leak detection, and 
#                     report every possible memory leak
VALGRIND_FLAGS	= --track-origins=yes -s --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all


LIB_DELETE		= lib_delete_library
LIB_CLEAN		= lib_clean
LIB_FCLEAN		= lib_fclean
LIB_RE			= lib_re


STD_PHONY		= all clean fclean re bonus help
DEBUG_PHONY		= sanitize valgrind gdb
LIB_PHONY		= ${LIB_DELETE} ${LIB_CLEAN} ${LIB_FCLEAN} ${LIB_RE}


ROOT_SRC_FILES	= rt_main.c
ROOT_SRCS		= $(addprefix ${SRC_PATH}, ${ROOT_SRC_FILES})
SRC_FILES		= ${ROOT_SRCS}


# "patsubst": pattern substitution
# parameters: pattern, replacement, text
#
# pattern: the pattern to match. Supports wildcards
# replacement: the string to replace the pattern with. By using wildcards, 
#              Make keeps the original text matched by the same 
#              wildcard in the pattern
# text: the list of strings on which the substitution will be performed
OBJ_FILES		= ${patsubst ${SRC_PATH}%.c, ${OBJ_PATH}%.o, ${SRC_FILES}}


CREATE_PATH		= mkdir -p
DELETE_FILE		= rm -f
DELETE_PATH		= rm -fr


## RULES ##
###########


all: ${NAME}


# "$@" refers to the target (%.o)
# "$<" refers to the dependency (%.c)
${OBJ_PATH}%.o: ${SRC_PATH}%.c
	@${CREATE_PATH} $(dir $@)
	@${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@


${NAME}: ${LIBFT_NAME} ${OBJ_FILES}
	@${CC} ${CFLAGS} ${OBJ_FILES} ${LIBFT_NAME} -o ${NAME}
	@echo "The program \"${NAME}\" has been compiled."


clean: ${LIB_CLEAN}
	@${DELETE_FILE} ${OBJ_FILES}
	@${DELETE_PATH} ${OBJ_PATH}
	@echo "The objects of program \"${NAME}\" have been deleted."


fclean: ${LIB_CLEAN} ${LIB_DELETE} clean
	@${DELETE_FILE} ${LIBFT_NAME}
	@${DELETE_FILE} ${NAME}
	@echo "The program \"${NAME}\" has been deleted."


re: fclean all


sanitize: ${LIBFT_NAME} ${OBJ_FILES}
	@${CC} ${CFLAGS} ${SANITIZE_FLAGS} ${OBJ_FILES} ${LIBFT_NAME} -o ${NAME}
	@echo "C compiler's sanitizer has been added to debug memory issues."


valgrind:
	@valgrind ${VALGRIND_FLAGS} ./${NAME}


gdb:
	@gdb ./${NAME}


help:
	@echo "Available targets:"
	@echo "    all            - Build the project (default)"
	@echo "    clean          - Remove object files"
	@echo "    fclean         - Remove object files and the executable"
	@echo "    re             - Rebuild the project"
	@echo "    sanitize       - Build with address sanitizer for debugging"
	@echo "    valgrind       - Run the program with valgrind"
	@echo "    gdb            - Run the program with gdb"


# library rules
# #############


${LIBFT_NAME}:
	@make -sC ${LIBFT_PATH}


${LIB_DELETE}:
	@make -sC ${LIBFT_PATH} delete_library


${LIB_CLEAN}:
	@make -sC ${LIBFT_PATH} clean


${LIB_FCLEAN}:
	@make -sC ${LIBFT_PATH} fclean


${LIB_RE}:
	@make -sC ${LIBFT_PATH} re


.PHONY: ${STD_PHONY} ${DEBUG_PHONY} ${LIB_PHONY}
