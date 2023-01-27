FILE_LIBEXEC	= \
				io_manager \
				exec_pipeseq_fork \
				exec_pipeseq_fork_utils \
				exec_pipeseq \
				exec_simplecom \
				exec_simplecom_extern \
				exec_redirs \
				executor

SRC_LIBEXEC	= $(addprefix srcs/, $(addsuffix .c, $(FILE_LIBEXEC)))
OBJ_LIBEXEC	= $(addprefix srcs/, $(addsuffix .o, $(FILE_LIBEXEC)))
DEP_LIBEXEC	= $(addprefix srcs/, $(addsuffix .d, $(FILE_LIBEXEC)))
