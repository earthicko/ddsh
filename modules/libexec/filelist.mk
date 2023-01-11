################################ FILENAMES #####################################
FILE_LIBEXEC	= \

SRC_LIBEXEC	= $(addprefix srcs/, $(addsuffix .c, $(FILE_LIBEXEC)))
OBJ_LIBEXEC	= $(addprefix srcs/, $(addsuffix .o, $(FILE_LIBEXEC)))
DEP_LIBEXEC	= $(addprefix srcs/, $(addsuffix .d, $(FILE_LIBEXEC)))
