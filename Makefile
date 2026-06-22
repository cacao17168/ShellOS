MAIN = kernel/main/main.c
REGSCRIPT = kernel/main/registry_generate.py

PYTHON = python3.12
CONF = kernel/main/commands.cfg
REGFILE = kernel/main/registry.c

HASHTABLE = kernel/hashtable/hash_table.c

INCLUDES = -Ikernel/filesystem -Ikernel/main -Ikernel/usersystem -Ibootloader -Ikernel/hashtable

FLAGS = -g -O0

NAME = "ShellOS.bin"

all: reggen compile

compile: $(MAIN)
	gcc -o $(NAME) $(INCLUDES) $(FLAGS) $(MAIN) $(HASHTABLE)
	
reggen: $(REGSCRIPT)
	$(PYTHON) $(REGSCRIPT) $(CONF) > $(REGFILE)
