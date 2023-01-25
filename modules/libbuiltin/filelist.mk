FILE_LIBBUILTIN	= \
					builtin_utils \
					builtin_cd \
					builtin_echo \
					builtin_export \
					builtin_declare \
					builtin_pwd \
					builtin_unset \
					builtin_exit \
					builtin_dot

SRC_LIBBUILTIN	= $(addprefix srcs/, $(addsuffix .c, $(FILE_LIBBUILTIN)))
OBJ_LIBBUILTIN	= $(addprefix srcs/, $(addsuffix .o, $(FILE_LIBBUILTIN)))
DEP_LIBBUILTIN	= $(addprefix srcs/, $(addsuffix .d, $(FILE_LIBBUILTIN)))
