################################ FILENAMES #####################################
FILE_LIBLEXER	= \
				type_len \
				is_char \
				lexer_utils \
				lexer

SRC_LIBLEXER	= $(addprefix srcs/, $(addsuffix .c, $(FILE_LIBLEXER)))
OBJ_LIBLEXER	= $(addprefix srcs/, $(addsuffix .o, $(FILE_LIBLEXER)))
DEP_LIBLEXER	= $(addprefix srcs/, $(addsuffix .d, $(FILE_LIBLEXER)))
