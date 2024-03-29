NAME	= ddsh
RC_NAME	= .ddshrc

all: $(NAME)

${HOME}/bin/$(NAME): $(NAME)
	mkdir -p ${HOME}/bin
	cp $(NAME) ${HOME}/bin/$(NAME)

${HOME}/$(RC_NAME): ddshrc_example
	cp ddshrc_example ${HOME}/$(RC_NAME)

install: ${HOME}/bin/$(NAME) ${HOME}/$(RC_NAME)

uninstall:
	$(RM) ${HOME}/$(NAME)
	$(RM) ${HOME}/$(RC_NAME)

include target_system.mk
include	modules.mk
include	filelist.mk

CFLAGS	= -Wall -Werror -Wextra -MMD -MP $(ACFLAGS) $(INC_DIR) $(DEFINES)

$(NAME): $(LDLIBS) $(OBJ) $(DRIVER_OBJ) $(LIBREADLINE)
	$(CC) $(CFLAGS) $(OBJ) $(DRIVER_OBJ) $(LDFLAGS) $(LDLIBS) -o $@

test_lexer: $(LDLIBS) $(OBJ) $(TEST_OBJ) tests/test_lexer.o
	$(CC) $(CFLAGS) $(LDLIBS) $(OBJ) $(TEST_OBJ) tests/test_lexer.o -o $@ $(LDFLAGS)

test_parser: $(LDLIBS) $(OBJ) $(TEST_OBJ) tests/test_parser.o
	$(CC) $(CFLAGS) $(LDLIBS) $(OBJ) $(TEST_OBJ) tests/test_parser.o -o $@ $(LDFLAGS)

test_envmanager: $(LDLIBS) $(OBJ) $(TEST_OBJ) tests/test_envmanager.o
	$(CC) $(CFLAGS) $(LDLIBS) $(OBJ) $(TEST_OBJ) tests/test_envmanager.o -o $@ $(LDFLAGS)

test_heredoc: $(LDLIBS) $(OBJ) $(TEST_OBJ) tests/test_heredoc.o
	$(CC) $(CFLAGS) $(LDLIBS) $(OBJ) $(TEST_OBJ) tests/test_heredoc.o -o $@ $(LDFLAGS)

test_expansion: $(LDLIBS) $(OBJ) $(TEST_OBJ) tests/test_expansion.o
	$(CC) $(CFLAGS) $(LDLIBS) $(OBJ) $(TEST_OBJ) tests/test_expansion.o -o $@ $(LDFLAGS)

test_exec: $(LDLIBS) $(OBJ) $(TEST_OBJ) tests/test_exec.o
	$(CC) $(CFLAGS) $(LDLIBS) $(OBJ) $(TEST_OBJ) tests/test_exec.o -o $@ $(LDFLAGS)

test_strutils: $(LDLIBS) $(OBJ) $(TEST_OBJ) tests/test_strutils.o
	$(CC) $(CFLAGS) $(LDLIBS) $(OBJ) $(TEST_OBJ) tests/test_strutils.o -o $@ $(LDFLAGS)

clean:
	$(RM) $(OBJ) $(DEP)
	$(RM) $(DRIVER_OBJ) $(DRIVER_DEP)
	$(RM) $(TESTER_OBJ) $(TESTER_DEP)
	$(RM) $(TEST_OBJ) $(TEST_DEP)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TESTER_FILENAME)
	@make fclean -C $(LIBFT_DIR)

re:
	@make fclean
	@make all

.PHONY: all clean fclean re install uninstall
