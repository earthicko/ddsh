LIB_DIR				= ${PWD}/modules

ifeq ($(OSNAME),Linux)
	LIBREADLINE_DIR		= /usr/lib/x86_64-linux-gnu
	LIBREADLINE			= $(LIBREADLINE_DIR)/libreadline.a
	LINK_LIBREADLINE	= -L$(LIBREADLINE_DIR) -lreadline
	INC_DIR_LIBREADLINE	= -I/usr/include
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

LIBLEXER_DIR		= $(LIB_DIR)/liblexer
LIBLEXER			= $(LIBLEXER_DIR)/liblexer.a
LINK_LIBLEXER		= -L$(LIBLEXER_DIR)
INC_DIR_LIBLEXER	= -I$(LIBLEXER_DIR)/includes

LDLIBS				= \
					$(LIBLEXER) \
					$(LIBFT)
LDFLAGS				= \
					$(LINK_LIBREADLINE) \
					$(LINK_LIBFT) \
					$(LINK_LIBLEXER)
INC_DIR				= -I. -I${PWD}/includes \
					$(INC_DIR_LIBREADLINE) \
					$(INC_DIR_LIBFT) \
					$(INC_DIR_LIBLEXER) \

include $(LIBFT_DIR)/filelist.mk
include $(LIBLEXER_DIR)/filelist.mk

ABS_SRC_LIBFT = $(addprefix $(LIBFT_DIR)/, $(SRC_LIBFT))
ABS_SRC_LIBLEXER = $(addprefix $(LIBLEXER_DIR)/, $(SRC_LIBLEXER))

export ACFLAGS
export INC_DIR

ifeq ($(OSNAME),Darwin)
$(LIBREADLINE):
	./modules/make_symlink_readline.sh
endif

$(LIBFT): $(ABS_SRC_LIBFT)
	git submodule update --remote $(LIBFT_DIR)
	@make -j4 -C $(LIBFT_DIR)/

$(LIBLEXER): $(ABS_SRC_LIBLEXER)
	@make -j4 -C $(LIBLEXER_DIR)/
