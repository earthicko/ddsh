FILE_LIBENVMAN	= \
				t_enventry \
				exit_stat_manager \
				envmanager_getenvp \
				envmanager_init \
				envmanager_setval \
				envmanager_utils \
				envmanager_clear \
				envmanager_getentry \
				envmanager_getval \
				envmanager_unsetval \
				envmanager_printlist \
				envmanager_addentry \
				envmanager_specialval \
				envmanager_specialval0 \
				envmanager_escape \
				envmanager_escape0 \
				envmanager_escape1 \
				envmanager_escape2 \
				envmanager_escape3 \
				envmanager

SRC_LIBENVMAN	= $(addprefix srcs/, $(addsuffix .c, $(FILE_LIBENVMAN)))
OBJ_LIBENVMAN	= $(addprefix srcs/, $(addsuffix .o, $(FILE_LIBENVMAN)))
DEP_LIBENVMAN	= $(addprefix srcs/, $(addsuffix .d, $(FILE_LIBENVMAN)))
