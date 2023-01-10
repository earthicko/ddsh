################################ FILENAMES #####################################
FILE_LIBPARSER	= \
				t_node \
				parse_util \
				parse_map_setter \
				parse_io_file \
				parse_io_redirect \
				parse_simple_command \
				parse_cmd_element \
				parse_io_here \
				parse_pipe_sequence \
				parse_terminal \
				parser

SRC_LIBPARSER	= $(addprefix srcs/, $(addsuffix .c, $(FILE_LIBPARSER)))
OBJ_LIBPARSER	= $(addprefix srcs/, $(addsuffix .o, $(FILE_LIBPARSER)))
DEP_LIBPARSER	= $(addprefix srcs/, $(addsuffix .d, $(FILE_LIBPARSER)))
