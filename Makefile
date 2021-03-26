##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

################################################################################
# Config Vars
NAME					=	r-type
BUILD_DIR				=	build

#################################################
# Client
CLIENT_BIN				=	r-type_client
CLIENT_DIR				=	client

#################################################
# Server
SERVER_BIN				=	r-type_server
SERVER_DIR				=	server

################################################################################
.DEFAULT: all

all: $(NAME)

$(NAME): setup-build-tree server client

################################################################################
# SERVER RULES
server:
	cmake $(OPTIONS) -B $(BUILD_DIR)
	@$(MAKE) -j `nproc` --no-print-directory -C $(BUILD_DIR) $(SERVER_BIN)
	cp $(BUILD_DIR)/bin/$(SERVER_BIN) .

server_fclean:
	@$(RM) -r $(SERVER_BIN)

################################################################################
# CLIENTS RULES
client:
	cmake $(OPTIONS) -B $(BUILD_DIR)
	@$(MAKE) -j `nproc` --no-print-directory -C $(BUILD_DIR) $(CLIENT_BIN)
	cp $(BUILD_DIR)/bin/$(CLIENT_BIN) .

client_fclean:
	@$(RM) -r $(CLIENT_BIN)

################################################################################
# OTHERS RULES

setup-build-tree:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && conan install ..
	cmake -B $(BUILD_DIR)


mouli-install: fclean
	-conan remote add tech-repo https://api.bintray.com/conan/epitech/public-conan
	-conan remote add public-repo https://api.bintray.com/conan/bincrafters/public-conan
	@mkdir -p $(BUILD_DIR) && cd $(BUILD_DIR) && conan install .. --build=missing

clean:
	@$(RM) -r $(BUILD_DIR)

fclean: clean server_fclean client_fclean
	@$(RM) -r $(BUILD_DIR) $(CRITERION_BIN)

re: fclean all

.PHONY: all $(NAME) server client mouli
.PHONY: server_fclean client_fclean clean fclean r