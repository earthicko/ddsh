FILE_LIBEXEC	= \
				io_manager \
				exec_pipeseq_pipeutils \
				exec_pipeseq_usepipe \
				exec_pipeseq \
				exec_simplecom \
				exec_redirs \
				executor

SRC_LIBEXEC	= $(addprefix srcs/, $(addsuffix .c, $(FILE_LIBEXEC)))
OBJ_LIBEXEC	= $(addprefix srcs/, $(addsuffix .o, $(FILE_LIBEXEC)))
DEP_LIBEXEC	= $(addprefix srcs/, $(addsuffix .d, $(FILE_LIBEXEC)))
