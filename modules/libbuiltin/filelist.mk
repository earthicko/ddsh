################################ FILENAMES #####################################
FILE_LIBBUILTIN	= \
					builtin_echo \
					builtin_pwd \
					builtin_unset

SRC_LIBBUILTIN	= $(addprefix srcs/, $(addsuffix .c, $(FILE_LIBBUILTIN)))
OBJ_LIBBUILTIN	= $(addprefix srcs/, $(addsuffix .o, $(FILE_LIBBUILTIN)))
DEP_LIBBUILTIN	= $(addprefix srcs/, $(addsuffix .d, $(FILE_LIBBUILTIN)))
