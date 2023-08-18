DRIVER_FILENAME		= srcs/prompt/prompt_main
DRIVER_SRC			= $(addsuffix .c, $(DRIVER_FILENAME))
DRIVER_OBJ			= $(addsuffix .o, $(DRIVER_FILENAME))
DRIVER_DEP			= $(addsuffix .d, $(DRIVER_FILENAME))

FILENAME			= \
					builtin/utils \
					builtin/cd \
					builtin/echo \
					builtin/export \
					builtin/declare \
					builtin/pwd \
					builtin/unset \
					builtin/exit \
					builtin/dot \
					envmanager/t_enventry \
					envmanager/exit_stat_manager \
					envmanager/getenvp \
					envmanager/init \
					envmanager/setval \
					envmanager/utils \
					envmanager/clear \
					envmanager/getentry \
					envmanager/getval \
					envmanager/unsetval \
					envmanager/printlist \
					envmanager/addentry \
					envmanager/specialval \
					envmanager/specialval0 \
					envmanager/escape \
					envmanager/escape0 \
					envmanager/escape1 \
					envmanager/escape2 \
					envmanager/escape3 \
					envmanager/envmanager \
					executor/io_manager \
					executor/pipeseq_fork \
					executor/pipeseq_fork_utils \
					executor/pipeseq \
					executor/simplecom \
					executor/simplecom_extern \
					executor/redirs \
					executor/executor \
					expansion/word_split \
					expansion/word_split_utils \
					expansion/compose_quotes \
					expansion/compose_envvar \
					expansion/compose_str \
					expansion/utils \
					expansion/tokens \
					expansion/tilde \
					expansion/interface \
					expansion/expansion \
					heredoc/clear \
					heredoc/filename \
					heredoc/interface \
					heredoc/read \
					heredoc/heredocmanager \
					parser/t_node \
					parser/t_node_utils \
					parser/util \
					parser/map_setter \
					parser/io_file \
					parser/io_redirect \
					parser/simple_command \
					parser/cmd_element \
					parser/io_here \
					parser/pipe_sequence \
					parser/terminal \
					parser/parser \
					prompt/prompt_steps \
					prompt/prompt_cosmetic \
					strutils/pchararr \
					strutils/pchararr_utils \
					strutils/remove_quotes \
					strutils/is_valid_str \
					strutils/find_exec \
					strutils/find_exec_from_path \
					signal/signal_set_state \
					signal/signal_handler

SRC					= $(addprefix srcs/, $(addsuffix .c, $(FILENAME)))
OBJ					= $(addprefix srcs/, $(addsuffix .o, $(FILENAME)))
DEP					= $(addprefix srcs/, $(addsuffix .d, $(FILENAME)))

TEST_FILENAME		= \
					print_nodes \
					print_tokens
TEST_SRC			= $(addprefix tests/, $(addsuffix .c, $(TEST_FILENAME)))
TEST_OBJ			= $(addprefix tests/, $(addsuffix .o, $(TEST_FILENAME)))
TEST_DEP			= $(addprefix tests/, $(addsuffix .d, $(TEST_FILENAME)))

TESTER_FILENAME		= \
					test_lexer \
					test_parser \
					test_envmanager \
					test_heredoc \
					test_expansion \
					test_exec \
					test_strutils

TESTER_OBJ			= $(addprefix tests/, $(addsuffix .o, $(TESTER_FILENAME)))
TESTER_DEP			= $(addprefix tests/, $(addsuffix .d, $(TESTER_FILENAME)))

-include			$(DEP)