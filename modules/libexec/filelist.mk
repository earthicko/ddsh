################################ FILENAMES #####################################
FILE_LIBEXEC	= build_exec	\
				  build_exec_utils	\
				  do_redir	\
				  executor	\
				  executor_builtin	\
				  executor_child_exec	\
				  free_build_fail	\
				  units_destroy	\

SRC_LIBEXEC	= $(addprefix srcs/, $(addsuffix .c, $(FILE_LIBEXEC)))
OBJ_LIBEXEC	= $(addprefix srcs/, $(addsuffix .o, $(FILE_LIBEXEC)))
DEP_LIBEXEC	= $(addprefix srcs/, $(addsuffix .d, $(FILE_LIBEXEC)))
