################################ FILENAMES #####################################
FILE_LIBHEREDOC	= \
				heredoc_filename \
				heredoc_read \
				heredocmanager

SRC_LIBHEREDOC	= $(addprefix srcs/, $(addsuffix .c, $(FILE_LIBHEREDOC)))
OBJ_LIBHEREDOC	= $(addprefix srcs/, $(addsuffix .o, $(FILE_LIBHEREDOC)))
DEP_LIBHEREDOC	= $(addprefix srcs/, $(addsuffix .d, $(FILE_LIBHEREDOC)))
