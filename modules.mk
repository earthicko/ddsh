LIB_DIR				= ${PWD}/modules

ifeq ($(OSNAME),Linux)
	ifeq ($(shell [ -d "/data/data/com.termux/files/usr" ] && echo 1), 1)
		LIBREADLINE_DIR		= /data/data/com.termux/files/usr/lib
		LIBREADLINE			= $(LIBREADLINE_DIR)/libreadline.so
		LINK_LIBREADLINE	= -L$(LIBREADLINE_DIR) -lreadline
		INC_DIR_LIBREADLINE	= -I/data/data/com.termux/files/usr/include
	else
		LIBREADLINE_DIR		= /usr/lib/x86_64-linux-gnu
		LIBREADLINE			= $(LIBREADLINE_DIR)/libreadline.a
		LINK_LIBREADLINE	= -L$(LIBREADLINE_DIR) -lreadline
		INC_DIR_LIBREADLINE	= -I/usr/include
	endif
else ifeq ($(OSNAME),Darwin)
	LIBREADLINE_DIR		= $(LIB_DIR)/readline
	LIBREADLINE			= $(LIBREADLINE_DIR)/lib/libreadline.a
	LINK_LIBREADLINE	= -L$(LIBREADLINE_DIR)/lib -lreadline
	INC_DIR_LIBREADLINE	= -I$(LIBREADLINE_DIR)/include
endif

LIBFT_DIR			= $(LIB_DIR)/libft
LIBFT				= $(LIBFT_DIR)/libft.a
LINK_LIBFT			= -L$(LIBFT_DIR)
INC_DIR_LIBFT		= -I$(LIBFT_DIR)/includes

LDLIBS				= \
					$(LIBFT) \

LDFLAGS				= \
					$(LINK_LIBREADLINE) \
					$(LINK_LIBFT) \

INC_DIR				= -I. -I${PWD}/includes \
					$(INC_DIR_LIBREADLINE) \
					$(INC_DIR_LIBFT) \

include $(LIBFT_DIR)/filelist.mk

ABS_SRC_LIBFT = $(addprefix $(LIBFT_DIR)/, $(SRC_LIBFT))

export ACFLAGS
export INC_DIR

ifeq ($(OSNAME),Darwin)
$(LIBREADLINE):
	./modules/make_symlink_readline.sh
endif

$(LIBFT): $(ABS_SRC_LIBFT)
	git submodule update --remote $(LIBFT_DIR)
	@make -j4 -C $(LIBFT_DIR)/
