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
CAM_PATH		= ${SRC_PATH}camera/
EVENT_PATH		= ${SRC_PATH}event/
INTSEC_PATH		= ${SRC_PATH}intersection/
MATH_PATH		= ${SRC_PATH}math/
REND_PATH		= ${SRC_PATH}rendering/


LIBFT_PATH		= ${LIB_PATH}libft/
LIBFT_INC_PATH	= ${LIBFT_PATH}include/
LIBFT_FILE		= libft.a
LIBFT_NAME		= ${LIBFT_PATH}${LIBFT_FILE}


MINILIBX_PATH	= ${LIB_PATH}minilibx/
MINILIBX_FILE	= libmlx_Linux.a
MLX_NAME		= ${MINILIBX_PATH}${MINILIBX_FILE}


CC				= cc
DEBUG_SYMBOLS	= -g3
CFLAGS			= -Wall -Wextra -Werror


# "-l<file>" instructs the linker to add a specific library by its name.
#            the linker will consider the "lib" prefix and ".a"/".so" sufix.
#            e.g. "-lft" links against "libft.a" or "libft.so".
#            note: this flag can't have a space in between, it's
#                  processed as a single token
#
# "-lXext"      links against the "libXext" library, an extension for
#               the X11 windowing system. It's a dependency of minilibx
#
# "-lX11"       links against the "libX11" library. Provides the core functions
#               of the X11 windowing system
#
# "-lm"         links against "libm.a", the math library
#
# "-lmlx_Linux" links against "libmlx_Linux.a"
#
# additional notes: minilibx is a lightweight library that relies on X11
#                   for graphical rendering. "-lXext -lX11" are dependencies
#                   of minilibx that provide the underlying graphical
#                   functionality. "-lmlx -lmlx_Linux" are specific to
#                   minilibx itself
ADD_LIBS		= -lmlx_Linux -lXext -lX11 -lm


LINKER_FLAGS	= -L ${MINILIBX_PATH} ${ADD_LIBS}


INCLUDE_LIBFT	= -I ${LIBFT_INC_PATH}
INCLUDE_MLX		= -I ${MINILIBX_PATH}
INCLUDE			= -I ${INC_PATH} ${INCLUDE_LIBFT} ${INCLUDE_MLX}


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


ROOT_SRC_FILES	=	rt_main.c
CAM_SRC_FILES	=	rt_get_camera_axes.c \
					rt_get_camera_ray.c \
					rt_get_viewport_point.c
EVENT_SRC_FILES	=	rt_handlers.c
INTSEC_SRC_FILES	=	rt_find_closest_cylinder.c \
						rt_find_closest_object.c \
						rt_find_closest_plane.c \
						rt_find_closest_sphere.c \
						rt_get_side_normal.c \
						rt_intersect_caps.c \
						rt_intersect_cylinder.c \
						rt_plane.c \
						rt_solve_side_quadratic.c \
						rt_sphere.c \
						rt_transform_ray.c \
						rt_within_height.c
MATH_SRC_FILES	=	rt_add_vector.c \
					rt_dotprod_of.c \
					rt_get_mag.c \
					rt_get_sqmag.c \
					rt_multiply_vector.c \
					rt_negate_vector.c \
					rt_normalize_vector.c \
					rt_ray.c \
					rt_subtract_vector.c
REND_SRC_FILES	=	rt_destroy.c \
					rt_destroy_scene.c \
					rt_init.c \
					rt_init_mock.c \
					rt_put_pxl.c \
					rt_render.c
ROOT_SRCS		= $(addprefix ${SRC_PATH}, ${ROOT_SRC_FILES})
CAM_SRCS		= $(addprefix ${CAM_PATH}, ${CAM_SRC_FILES})
EVENT_SRCS		= $(addprefix ${EVENT_PATH}, ${EVENT_SRC_FILES})
INTSEC_SRCS		= $(addprefix ${INTSEC_PATH}, ${INTSEC_SRC_FILES})
MATH_SRCS		= $(addprefix ${MATH_PATH}, ${MATH_SRC_FILES})
REND_SRCS		= $(addprefix ${REND_PATH}, ${REND_SRC_FILES})
SRC_FILES		=	${ROOT_SRCS} \
					${CAM_SRCS} \
					${EVENT_SRCS} \
					${INTSEC_SRCS} \
					${MATH_SRCS} \
					${REND_SRCS} 


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


${NAME}: ${LIBFT_NAME} ${MLX_NAME} ${OBJ_FILES}
	@${CC} ${CFLAGS} ${OBJ_FILES} ${LIBFT_NAME} -o ${NAME} ${LINKER_FLAGS}
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


sanitize: ${LIBFT_NAME} ${MLX_NAME} ${OBJ_FILES}
	@${CC} ${CFLAGS} ${SANITIZE_FLAGS} ${OBJ_FILES} ${LIBFT_NAME} -o ${NAME} ${LINKER_FLAGS}
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


${MLX_NAME}:
	@make -sC ${MINILIBX_PATH}


${LIBFT_NAME}:
	@make -sC ${LIBFT_PATH}


${LIB_DELETE}:
	@make -sC ${LIBFT_PATH} delete_library


${LIB_CLEAN}:
	@make -sC ${LIBFT_PATH} clean
	@make -sC ${MINILIBX_PATH} clean


${LIB_FCLEAN}:
	@make -sC ${LIBFT_PATH} fclean
	@make -sC ${MINILIBX_PATH} clean


${LIB_RE}:
	@make -sC ${LIBFT_PATH} re


.PHONY: ${STD_PHONY} ${DEBUG_PHONY} ${LIB_PHONY}
