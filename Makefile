# Colors
RED		= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[0;33m
CYAN	= \033[0;36m
BLUE	= \033[0;34m
PURPLE	= \033[0;35m
NC		= \033[0m # No Color

NAME					= cub3D

CC						= cc
CFLAGS					= -Wall -Wextra -Werror -g  #-fsanitize=address

# ===== MLX42 & GLFW LIBRARIES 

LIBMLX					= $(HOME)/MLX42
MLX_INCLUDE				= $(HOME)/MLX42/include/MLX42
MLX_LIB					= $(HOME)/MLX42/build/libmlx42.a
GLFW_INCLUDE			= $(HOME)/.brew/include
GLFW_LIB				= $(HOME)/.brew/lib

HEADERS					= -I ./inc -I $(MLX_INCLUDE) -I $(GLFW_INCLUDE)

HEADER_FILES			= inc/cub3d.h

LIBS					= $(MLX_LIB) -L $(GLFW_LIB) -lglfw -framework OpenGL -framework IOKit -framework Cocoa


SRCS					= \
	src/main.c \
	src/main_utils.c \
	src/animation/anim_0.c \
	src/animation/anim_1.c \
	src/animation/anim_2.c \
	src/animation/anim_3.c \
	src/animation/anim_4.c \
	src/animation/anim_5.c \
	src/engine/init_game.c \
	src/engine/init_setup_1.c \
	src/engine/init_setup_2.c \
	src/engine/input.c \
	src/engine/input_utils.c \
	src/engine/movement.c \
	src/engine/keys.c \
	src/engine/math_utils.c \
	src/engine/raycasting.c \
	src/engine/raycasting_utils.c \
	src/engine/rendering.c \
	src/engine/render_anim_1.c \
	src/engine/render_anim_2.c \
	src/engine/rendering_utils.c \
	src/engine/textures.c \
	src/engine/textures_utils_1.c \
	src/engine/textures_utils_2.c \
	src/parsing/parse_file.c \
	src/parsing/parse_file_content_1.c \
	src/parsing/parse_file_content_2.c \
	src/parsing/parse_file_content_3.c \
	src/parsing/parse_map_1.c \
	src/parsing/parse_map_2.c \
	src/parsing/parse_map_3.c \
	src/parsing/parse_rgb_1.c \
	src/parsing/parse_rgb_3.c \
	src/parsing/parse_textures_1.c \
	src/parsing/parse_textures_2.c \
	src/parsing/validate_map_1.c \
	src/parsing/validate_map_2.c \
	src/parsing/validate_map_3.c \
	src/parsing/validate_map_4.c \
	src/parsing/validate_map_5.c \
	src/utils/error.c \
	src/utils/utils_1.c \
	src/utils/utils_2.c \
	src/utils/utils_3.c \
	src/utils/utils_4.c \
	src/utils/utils_5.c \
	src/utils/free.c

OBJS					= ${SRCS:.c=.o}

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
	@printf "${YELLOW}🏗️   riel-fas ssallami  ${NC}\n"
	@printf "${YELLOW}📋 Project: Cub3D - Raycasting Game Engine${NC}\n"
	@printf "\n"

$(NAME): compile_msg $(OBJS)
	@printf "${GREEN}🔗 Linking objects to create $(NAME)...${NC}\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@printf "${GREEN}✅ $(NAME) successfully compiled!${NC}\n"
	@printf "${CYAN}🚀 Ready to explore the 3D world!${NC}\n"

%.o: %.c $(HEADER_FILES)
	@printf "${GREEN}🔨 Compiling $<...${NC}\n"
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

compile_msg:
	@printf "${CYAN}🏗️  Compiling source files...${NC}\n"

clean:
	@printf "${YELLOW}🧹 Removing object files...${NC}\n"
	@rm -rf $(OBJS) $(OBJS_BONUS)
	@printf "${YELLOW}✨ Object files cleaned!${NC}\n"

fclean: clean
	@printf "${YELLOW}🗑️  Removing executable...${NC}\n"
	@rm -rf $(NAME) $(BONUS)
	@printf "${YELLOW}🧽 Complete cleanup finished!${NC}\n"

re: fclean all

.PHONY: all bonus clean fclean re banner 



# # Development utilities
# debug: CFLAGS += -fsanitize=address -g3
# debug: $(NAME)
# 	@printf "${PURPLE}🐛 Debug version compiled with AddressSanitizer${NC}\n"

# test: $(NAME)
# 	@printf "${CYAN}🧪 Running basic tests...${NC}\n"
# 	@if [ -f "test.cub" ]; then \
# 		printf "${GREEN}Testing with test.cub...${NC}\n"; \
# 		./$(NAME) test.cub; \
# 	else \
# 		printf "${RED}❌ test.cub not found!${NC}\n"; \
# 	fi

# norm:
# 	@printf "${BLUE}📏 Checking norminette...${NC}\n"
# 	@norminette src inc | grep -v "OK!" || printf "${GREEN}✅ All files are norm compliant!${NC}\n"

# help:
# 	@printf "${CYAN}📖 Available targets:${NC}\n"
# 	@printf "${YELLOW}  all${NC}      - Build the project\n"
# 	@printf "${YELLOW}  bonus${NC}    - Build with bonus features\n"
# 	@printf "${YELLOW}  clean${NC}    - Remove object files\n"
# 	@printf "${YELLOW}  fclean${NC}   - Remove object files and executable\n"
# 	@printf "${YELLOW}  re${NC}       - Rebuild everything\n"
# 	@printf "${YELLOW}  debug${NC}    - Build with debug flags and AddressSanitizer\n"
# 	@printf "${YELLOW}  test${NC}     - Run basic tests\n"
# 	@printf "${YELLOW}  norm${NC}     - Check norm compliance\n"
# 	@printf "${YELLOW}  help${NC}     - Show this help message\n"

# debug test norm help compile_msg





# $(BONUS): compile_msg $(OBJS_BONUS)
# 	@printf "${GREEN}🔗 Linking objects to create $(BONUS)...${NC}\n"
# 	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBS) -o $(BONUS)
# 	@printf "${GREEN}✅ $(BONUS) successfully compiled!${NC}\n"
# 	@printf "${CYAN}🚀 Ready to explore the 3D world with bonus features!${NC}\n"
