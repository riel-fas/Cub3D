# Colors
RED		= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[0;33m
CYAN	= \033[0;36m
BLUE	= \033[0;34m
PURPLE	= \033[0;35m
NC		= \033[0m # No Color

NAME			=	cub3D
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -g

# MLX42 Configuration
MLX_DIR			=	$(HOME)/MLX42
MLX_FLAGS		=	-I$(MLX_DIR)/include
MLX_LIB			=	-L$(MLX_DIR)/build -lmlx42 -lglfw -framework OpenGL -framework IOKit -framework Cocoa

# Directories
SRC_DIR			=	src
INC_DIR			=	inc
OBJ_DIR			=	obj

# Source files
SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/parsing/parse_file.c \
	$(SRC_DIR)/parsing/parse_textures.c \
	$(SRC_DIR)/parsing/parse_map.c \
	$(SRC_DIR)/parsing/validate_map.c \
	$(SRC_DIR)/engine/init_game.c \
	$(SRC_DIR)/engine/textures.c \
	$(SRC_DIR)/engine/raycasting.c \
	$(SRC_DIR)/engine/rendering.c \
	$(SRC_DIR)/engine/input.c \
	$(SRC_DIR)/engine/math_utils.c \
	$(SRC_DIR)/utils/error.c \
	$(SRC_DIR)/utils/utils.c \
	$(SRC_DIR)/utils/free.c

OBJS			=	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
HEADER			=	$(INC_DIR)/cub3d.h

# Final compile flags
ALL_INCLUDES	=	$(CFLAGS) -I$(INC_DIR) $(MLX_FLAGS)

all	:	banner $(NAME)

banner:
	@printf "${BLUE}╔════════════════════════════════════════════════════════════════════════════════════╗${NC}\n"
	@printf "${BLUE}║                                                                                    ║${NC}\n"
	@printf "${RED}║                  ██████╗██╗   ██╗██████╗ ██████╗ ██████╗                           ║${NC}\n"
	@printf "${RED}║                 ██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗                          ║${NC}\n"
	@printf "${RED}║                 ██║     ██║   ██║██████╔╝ █████╔╝██║  ██║                          ║${NC}\n"
	@printf "${RED}║                 ██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║                          ║${NC}\n"
	@printf "${RED}║                 ╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝                          ║${NC}\n"
	@printf "${RED}║                  ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝                           ║${NC}\n"
	@printf "${BLUE}║                                                                                    ║${NC}\n"
	@printf "${PURPLE}║                        🌟  3D RAYCASTING ENGINE  🌟                                ║${NC}\n"
	@printf "${BLUE}║                                                                                    ║${NC}\n"
	@printf "${CYAN}║    \"Where every pixel tells a story of light and shadow...\"                        ║${NC}\n"
	@printf "${CYAN}║    \"Cast rays through the maze of your imagination...\"                             ║${NC}\n"
	@printf "${CYAN}║    \"Navigate the digital labyrinth with precision...\"                              ║${NC}\n"
	@printf "${BLUE}║                                                                                    ║${NC}\n"
	@printf "${BLUE}╚════════════════════════════════════════════════════════════════════════════════════╝${NC}\n"
	@printf "\n"
	@printf "${YELLOW}📅 Build Date: $(shell date '+%Y-%m-%d %H:%M:%S') UTC${NC}\n"
	@printf "${YELLOW}🏗️  Compiled by: 42 School Students${NC}\n"
	@printf "${YELLOW}📋 Project: Cub3D - Raycasting Game Engine${NC}\n"
	@printf "\n"

$(NAME)	:	$(OBJS)
	@printf "${GREEN}🔗 Linking objects to create $(NAME)...${NC}\n"
	@$(CC) $(ALL_INCLUDES) $(OBJS) -o $(NAME) $(MLX_LIB)
	@printf "${GREEN}✅ $(NAME) successfully compiled!${NC}\n"
	@printf "${CYAN}🚀 Ready to explore the 3D world!${NC}\n"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	@printf "${GREEN}🔨 Compiling $<...${NC}\n"
	@$(CC) $(ALL_INCLUDES) -c $< -o $@

$(OBJS): | compile_msg

compile_msg:
	@printf "${CYAN}🏗️  Compiling source files...${NC}\n"

clean	:
	@printf "${YELLOW}🧹 Removing object files...${NC}\n"
	@rm -rf $(OBJ_DIR)
	@printf "${YELLOW}✨ Object files cleaned!${NC}\n"

fclean: clean
	@printf "${YELLOW}🗑️  Removing executable...${NC}\n"
	@rm -rf $(NAME)
	@printf "${YELLOW}🧽 Complete cleanup finished!${NC}\n"

re	:	fclean all

# Development utilities
debug: CFLAGS += -fsanitize=address -g3
debug: $(NAME)
	@printf "${PURPLE}🐛 Debug version compiled with AddressSanitizer${NC}\n"

test: $(NAME)
	@printf "${CYAN}🧪 Running basic tests...${NC}\n"
	@if [ -f "test.cub" ]; then \
		printf "${GREEN}Testing with test.cub...${NC}\n"; \
		./$(NAME) test.cub; \
	else \
		printf "${RED}❌ test.cub not found!${NC}\n"; \
	fi

norm:
	@printf "${BLUE}📏 Checking norminette...${NC}\n"
	@norminette $(SRC_DIR) $(INC_DIR) | grep -v "OK!" || printf "${GREEN}✅ All files are norm compliant!${NC}\n"

help:
	@printf "${CYAN}📖 Available targets:${NC}\n"
	@printf "${YELLOW}  all${NC}      - Build the project\n"
	@printf "${YELLOW}  clean${NC}    - Remove object files\n"
	@printf "${YELLOW}  fclean${NC}   - Remove object files and executable\n"
	@printf "${YELLOW}  re${NC}       - Rebuild everything\n"
	@printf "${YELLOW}  debug${NC}    - Build with debug flags and AddressSanitizer\n"
	@printf "${YELLOW}  test${NC}     - Run basic tests\n"
	@printf "${YELLOW}  norm${NC}     - Check norm compliance\n"
	@printf "${YELLOW}  help${NC}     - Show this help message\n"

.PHONY	:	all clean fclean re banner debug test norm help compile_msg
