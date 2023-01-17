################################ FILENAMES #####################################
FILE_LIBENVMAN	= \
				t_enventry \
				exit_stat_manager \
				envmanager_getenvp \
				envmanager_init \
				envmanager_setval \
				envmanager_utils \
				envmanager_clear \
				envmanager_getval \
				envmanager_unsetval \
				envmanager

SRC_LIBENVMAN	= $(addprefix srcs/, $(addsuffix .c, $(FILE_LIBENVMAN)))
OBJ_LIBENVMAN	= $(addprefix srcs/, $(addsuffix .o, $(FILE_LIBENVMAN)))
DEP_LIBENVMAN	= $(addprefix srcs/, $(addsuffix .d, $(FILE_LIBENVMAN)))
