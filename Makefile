FONT_RED := $(shell tput setaf 1)
FONT_GREEN := $(shell tput setaf 2)
FONT_YELLOW := $(shell tput setaf 3)
FONT_PURPLE := $(shell tput setaf 4)
FONT_PINK := $(shell tput setaf 5)
FONT_CYAN := $(shell tput setaf 6)
FONT_GRAY := $(shell tput setaf 7)
FONT_BLACK := $(shell tput setaf 8)
FONT_BOLD := $(shell tput bold)
FONT_RESET := $(shell tput sgr0)

COMPILER=g++
OPTIONS=-std=c++17 -Wall -Wfatal-errors -Wextra -Wpedantic -fmessage-length=80 -fno-diagnostics-show-option -fstack-protector-all -g -O3 -Walloc-zero -Walloca -Wctor-dtor-privacy -Wduplicated-cond -Wno-unused-parameter -Wduplicated-branches -Werror -Winit-self -Wlogical-op -Wold-style-cast -Wshadow -Wunused-const-variable=1 -Wzero-as-null-pointer-constant
COMPILE=$(COMPILER) $(OPTIONS)
BINARY=cipher
OBJECTS=cipher.o file.o arguments.o crypto.o
HEADERS=file.h arguments.h
$(BINARY): $(OBJECTS)
	@echo "$(FONT_GREEN)Built and output to $(FONT_RED)./$(BINARY)$(FONT_RESET)"
	@$(COMPILE) -o $@ $^ 

cipher.o: cipher.cpp
	@echo "$(FONT_CYAN)Bulding $@$(FONT_RESET)"
	@$(COMPILE) -c $<

file.o: file.cpp #file.h
	@echo "$(FONT_CYAN)Bulding $@$(FONT_RESET)"
	@$(COMPILE) -c $<

arguments.o: arguments.cpp #arguments.h
	@echo "$(FONT_CYAN)Bulding $@$(FONT_RESET)"
	@$(COMPILE) -c $<

crypto.o: crypto.cpp #crypto.h
	@echo "$(FONT_CYAN)Bulding $@$(FONT_RESET)"
	@$(COMPILE) -c $<
#%.o: %.cpp
#	@echo "$(FONT_CYAN)Bulding $@$(FONT_RESET)"
#	@$(COMPILE) -c $^

#$(OBJECTS): $(HEADERS)

clean:
	@echo "$(FONT_RED)Cleaning directory...$(FONT_RESET)"
	@rm -f $(OBJECTS) $(BINARY)

b-enc: # for testing
	./cipher B input.txt a keyfile E

b-dec:
	./cipher B a output.txt keyfile D

s-enc:
	./cipher S input.txt a keyfile E

s-dec:
	./cipher S a output.txt keyfile D

diff:
	diff -qs input.txt output.txt

print-test:
	@printf "$(FONT_RED)red$(FONT_RESET)\n"
	@printf "$(FONT_GREEN)green$(FONT_RESET)\n"
	@printf "$(FONT_YELLOW)yellow$(FONT_RESET)\n"
	@printf "$(FONT_PURPLE)purple$(FONT_RESET)\n"
	@printf "$(FONT_PINK)pink$(FONT_RESET)\n"
	@printf "$(FONT_CYAN)cyan$(FONT_RESET)\n"
	@printf "$(FONT_GRAY)gray$(FONT_RESET)\n"
	@printf "$(FONT_BLACK)black$(FONT_RESET)\n"
	@printf "$(FONT_BOLD)bold$(FONT_RESET)\n"