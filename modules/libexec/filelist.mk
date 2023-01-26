FILE_LIBEXEC	= \
				io_manager \
				t_execunit/t_exec_arg \
				t_execunit/t_exec_pipeseq \
				t_execunit/t_exec_redir \
				t_execunit/t_exec_simplecom \
				t_execunit/t_exec_simplecom_utils \
				t_execunit/t_list_utils \
				exec_pipeseq \
				exec_redirs \
				exec_simplecom_builtin \
				exec_simplecom_forked \
				executor

SRC_LIBEXEC	= $(addprefix srcs/, $(addsuffix .c, $(FILE_LIBEXEC)))
OBJ_LIBEXEC	= $(addprefix srcs/, $(addsuffix .o, $(FILE_LIBEXEC)))
DEP_LIBEXEC	= $(addprefix srcs/, $(addsuffix .d, $(FILE_LIBEXEC)))
