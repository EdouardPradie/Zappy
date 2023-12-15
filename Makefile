##
## EPITECH PROJECT, 2023
## Zappy/Makefile
## File description:
## Makefile
##

NAME_SERVER	=	zappy_server

NAME_GUI	=	zappy_gui

NAME_AI	=	zappy_ai

all: $(NAME_SERVER) $(NAME_GUI) $(NAME_AI)
.PHONY: all

$(NAME_SERVER):
	@make -C server
.PHONY: $(NAME_SERVER)

$(NAME_GUI)::
	yes | unzip gui/assets -d gui/assets
$(NAME_GUI)::
	cd gui && ./compile.sh --ninja
.PHONY: $(NAME_GUI)

$(NAME_AI):
	make -C./ai
.PHONY: $(NAME_AI)

debug:
	@make debug -C server
	cd gui && ./compile.sh --debug
.PHONY: debug

tests_run:
	@make tests_run -C server
	cd gui && ./compile.sh --tests
.PHONY: tests_run

clean:
	@make clean -C server
	@rm -rf ./gui/build/
.PHONY: clean

fclean: clean
	@rm -rf gui/assets
	@rm -rf $(NAME_AI) $(NAME_GUI) $(NAME_SERVER)
.PHONY: fclean

re	::	fclean
re	::	all
.PHONY: re
