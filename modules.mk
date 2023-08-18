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

LIBEXPANSION_DIR	= $(LIB_DIR)/libexpansion
LIBEXPANSION		= $(LIBEXPANSION_DIR)/libexpansion.a
LINK_LIBEXPANSION	= -L$(LIBEXPANSION_DIR)
INC_DIR_LIBEXPANSION= -I$(LIBEXPANSION_DIR)/includes

LIBHEREDOC_DIR		= $(LIB_DIR)/libheredoc
LIBHEREDOC			= $(LIBHEREDOC_DIR)/libheredoc.a
LINK_LIBHEREDOC		= -L$(LIBHEREDOC_DIR)
INC_DIR_LIBHEREDOC	= -I$(LIBHEREDOC_DIR)/includes

LIBBUILTIN_DIR		= $(LIB_DIR)/libbuiltin
LIBBUILTIN			= $(LIBBUILTIN_DIR)/libbuiltin.a
LINK_LIBBUILTIN		= -L$(LIBBUILTIN_DIR)
INC_DIR_LIBBUILTIN	= -I$(LIBBUILTIN_DIR)/includes

LIBEXEC_DIR			= $(LIB_DIR)/libexec
LIBEXEC				= $(LIBEXEC_DIR)/libexec.a
LINK_LIBEXEC		= -L$(LIBEXEC_DIR)
INC_DIR_LIBEXEC		= -I$(LIBEXEC_DIR)/includes

LDLIBS				= \
					$(LIBLEXER) \
					$(LIBEXPANSION) \
					$(LIBHEREDOC) \
					$(LIBEXEC) \
					$(LIBBUILTIN)\
					$(LIBFT)
LDFLAGS				= \
					$(LINK_LIBREADLINE) \
					$(LINK_LIBFT) \
					$(LINK_LIBLEXER) \
					$(LINK_LIBEXPANSION) \
					$(LINK_LIBHEREDOC) \
					$(LINK_LIBBUILTIN) \
					$(LINK_LIBEXEC)
INC_DIR				= -I. -I${PWD}/includes \
					$(INC_DIR_LIBREADLINE) \
					$(INC_DIR_LIBFT) \
					$(INC_DIR_LIBLEXER) \
					$(INC_DIR_LIBEXPANSION) \
					$(INC_DIR_LIBHEREDOC) \
					$(INC_DIR_LIBBUILTIN) \
					$(INC_DIR_LIBEXEC)

include $(LIBFT_DIR)/filelist.mk
include $(LIBLEXER_DIR)/filelist.mk
include $(LIBEXPANSION_DIR)/filelist.mk
include $(LIBHEREDOC_DIR)/filelist.mk
include $(LIBBUILTIN_DIR)/filelist.mk
include $(LIBEXEC_DIR)/filelist.mk

ABS_SRC_LIBFT = $(addprefix $(LIBFT_DIR)/, $(SRC_LIBFT))
ABS_SRC_LIBLEXER = $(addprefix $(LIBLEXER_DIR)/, $(SRC_LIBLEXER))
ABS_SRC_LIBEXPANSION = $(addprefix $(LIBEXPANSION_DIR)/, $(SRC_LIBEXPANSION))
ABS_SRC_LIBHEREDOC = $(addprefix $(LIBHEREDOC_DIR)/, $(SRC_LIBHEREDOC))
ABS_SRC_LIBBUILTIN = $(addprefix $(LIBBUILTIN_DIR)/, $(SRC_LIBBUILTIN))
ABS_SRC_LIBEXEC = $(addprefix $(LIBEXEC_DIR)/, $(SRC_LIBEXEC))

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

$(LIBEXPANSION): $(ABS_SRC_LIBEXPANSION)
	@make -j4 -C $(LIBEXPANSION_DIR)/

$(LIBHEREDOC): $(ABS_SRC_LIBHEREDOC)
	@make -j4 -C $(LIBHEREDOC_DIR)/

$(LIBBUILTIN): $(ABS_SRC_LIBBUILTIN)
	@make -j4 -C $(LIBBUILTIN_DIR)/

$(LIBEXEC): $(ABS_SRC_LIBEXEC)
	@make -j4 -C $(LIBEXEC_DIR)\
