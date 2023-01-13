################################# LIBRARIES ####################################
LIB_DIR				= modules

LINK_READLINE		= -L${HOME}/.brew/opt/readline/lib -lreadline

LIBFT_DIR			= $(LIB_DIR)/libft
LIBFT				= $(LIBFT_DIR)/libft.a
LINK_LIBFT			= -L$(LIBFT_DIR)
INC_DIR_LIBFT		= -I$(LIBFT_DIR)/includes

LIBLEXER_DIR		= $(LIB_DIR)/liblexer
LIBLEXER			= $(LIBLEXER_DIR)/liblexer.a
LINK_LIBLEXER		= -L$(LIBLEXER_DIR)
INC_DIR_LIBLEXER	= -I$(LIBLEXER_DIR)/includes

LIBPARSER_DIR		= $(LIB_DIR)/libparser
LIBPARSER			= $(LIBPARSER_DIR)/libparser.a
LINK_LIBPARSER		= -L$(LIBPARSER_DIR)
INC_DIR_LIBPARSER	= -I$(LIBPARSER_DIR)/includes

LIBHEREDOC_DIR		= $(LIB_DIR)/libheredoc
LIBHEREDOC			= $(LIBHEREDOC_DIR)/libheredoc.a
LINK_LIBHEREDOC		= -L$(LIBHEREDOC_DIR)
INC_DIR_LIBHEREDOC	= -I$(LIBHEREDOC_DIR)/includes

LIBENVMAN_DIR		= $(LIB_DIR)/libenvman
LIBENVMAN			= $(LIBENVMAN_DIR)/libenvman.a
LINK_LIBENVMAN		= -L$(LIBENVMAN_DIR)
INC_DIR_LIBENVMAN	= -I$(LIBENVMAN_DIR)/includes

LIBBUILTIN_DIR		= $(LIB_DIR)/libbuiltin
LIBBUILTIN			= $(LIBBUILTIN_DIR)/libbuiltin.a
LINK_LIBBUILTIN		= -L$(LIBBUILTIN_DIR)
INC_DIR_LIBBUILTIN	= -I$(LIBBUILTIN_DIR)/includes

LIB_ALL				= \
					$(LIBFT) \
					$(LIBLEXER) \
					$(LIBPARSER) \
					$(LIBHEREDOC) \
					$(LIBENVMAN) \
					$(LIBBUILTIN)
LINK_LIBS			= \
					$(LINK_READLINE) \
					$(LINK_LIBFT) \
					$(LINK_LIBLEXER) \
					$(LINK_LIBPARSER) \
					$(LINK_LIBHEREDOC) \
					$(LINK_LIBENVMAN) \
					$(LINK_LIBBUILTIN)
INC_DIR				= -I. -Iincludes \
					$(INC_DIR_LIBFT) \
					$(INC_DIR_LIBLEXER) \
					$(INC_DIR_LIBPARSER) \
					$(INC_DIR_LIBHEREDOC) \
					$(INC_DIR_LIBENVMAN) \
					$(INC_DIR_LIBBUILTIN)
################################# TARGETS ######################################
include $(LIBFT_DIR)/filelist.mk
include $(LIBLEXER_DIR)/filelist.mk
include $(LIBPARSER_DIR)/filelist.mk
include $(LIBHEREDOC_DIR)/filelist.mk
include $(LIBENVMAN_DIR)/filelist.mk
include $(LIBBUILTIN_DIR)/filelist.mk

ABS_SRC_LIBFT = $(addprefix $(LIBFT_DIR)/, $(SRC_LIBFT))
ABS_SRC_LIBLEXER = $(addprefix $(LIBLEXER_DIR)/, $(SRC_LIBLEXER))
ABS_SRC_LIBPARSER = $(addprefix $(LIBPARSER_DIR)/, $(SRC_LIBPARSER))
ABS_SRC_LIBHEREDOC = $(addprefix $(LIBHEREDOC_DIR)/, $(SRC_LIBHEREDOC))
ABS_SRC_LIBENVMAN = $(addprefix $(LIBENVMAN_DIR)/, $(SRC_LIBENVMAN))
ABS_SRC_LIBBUILTIN = $(addprefix $(LIBBUILTIN_DIR)/, $(SRC_LIBBUILTIN))

export ACFLAGS

$(LIBFT): $(ABS_SRC_LIBFT)
	@make -j4 -C $(LIBFT_DIR)/

$(LIBLEXER): $(ABS_SRC_LIBLEXER)
	@make -j4 -C $(LIBLEXER_DIR)/

$(LIBPARSER): $(ABS_SRC_LIBPARSER)
	@make -j4 -C $(LIBPARSER_DIR)/

$(LIBHEREDOC): $(ABS_SRC_LIBHEREDOC)
	@make -j4 -C $(LIBHEREDOC_DIR)/

$(LIBENVMAN): $(ABS_SRC_LIBENVMAN)
	@make -j4 -C $(LIBENVMAN_DIR)/

$(LIBBUILTIN): $(ABS_SRC_LIBBUILTIN)
	@make -j4 -C $(LIBBUILTIN_DIR)/
