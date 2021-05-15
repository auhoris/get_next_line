# Bin
name			= get_next_line.a

# Directories
srcdir			= srcs
bonusdir		= bonus
objdir			= objs
incdir			= includes

# Files
sources			= $(wildcard $(srcdir)/*.c)
bonuses			= $(wildcard $(bonusdir)/*.c)
inclds			= $(wildcard $(incdir)/*.h)
objects			= $(sources:$(srcdir)/%.c=$(objdir)/%.o)
objsbonus		= $(bonuses:$(bonusdir)/%.c=$(objdir)/%.o)

# Flags and linkers
cc				= gcc
cflags			= -Wall -Werror -Wextra
dbgf			= -g
sanitize		= -fsanitize=address

# Additional libraries
# NONE

# Utils
rm				= rm -rf


all:			 $(name)

$(name):		$(objects)
				ar rcs $@ $^
				@echo "\033[0;32m"$@" compiled"

bonus:			$(objsbonus) $(objects)
				ar rcs $(name) $^
				@echo "\033[0;32m"$(name)" compiled with bonus\033[0m"

$(objdir)/%.o: $(srcdir)/%.c Makefile $(inclds)
				@mkdir -p $(objdir)
				$(cc) $(cflags) -c $< -o $@
				@echo "Compiled "$<" successfully!"

$(objdir)/%.o: $(bonusdir)/%.c Makefile $(inclds)
				@mkdir -p $(objdir)
				$(cc) $(cflags) -c $< -o $@
				@echo "Compiled "$<" successfully!"

clean:
				$(rm) $(objdir)

fclean:			clean
				$(rm) $(name)

re:				fclean all


.PHONY:			clean fclean re all
.SILENT:		$(name) $(objects) $(objsbonus) bonus
