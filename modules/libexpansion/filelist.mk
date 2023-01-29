FILE_LIBEXPANSION	= \
					expansion_word_split \
					expansion_word_split_utils \
					expansion_compose_quotes \
					expansion_compose_envvar \
					expansion_compose_str \
					expansion_utils \
					expansion_tokens \
					expansion_tilde \
					expansion_interface \
					expansion \

SRC_LIBEXPANSION	= $(addprefix srcs/, $(addsuffix .c, $(FILE_LIBEXPANSION)))
OBJ_LIBEXPANSION	= $(addprefix srcs/, $(addsuffix .o, $(FILE_LIBEXPANSION)))
DEP_LIBEXPANSION	= $(addprefix srcs/, $(addsuffix .d, $(FILE_LIBEXPANSION)))
