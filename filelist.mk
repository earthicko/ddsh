DRIVER_FILENAME		= srcs/prompt/prompt_main
DRIVER_SRC			= $(addsuffix .c, $(DRIVER_FILENAME))
DRIVER_OBJ			= $(addsuffix .o, $(DRIVER_FILENAME))
DRIVER_DEP			= $(addsuffix .d, $(DRIVER_FILENAME))

FILENAME			= \
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