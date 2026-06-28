SOURCES = kernel/main/main.c kernel/hashtable/hash_table.c kernel/filesystem/filesystem.c
REGSCRIPT = kernel/main/registry_generate.py

PYTHON = python3.12
CONF = kernel/main/commands.cfg
REGFILE = kernel/main/registry.c

INCLUDES = -Ikernel/filesystem -Ikernel/main -Ikernel/usersystem -Ibootloader -Ikernel/hashtable

FLAGS = -g -O0

LIBS = -lm

NAME = "ShellOS.bin"

all: reggen compile

compile: $(MAIN)
	gcc -o $(NAME) $(INCLUDES) $(FLAGS) $(SOURCES) $(LIBS)
	
reggen: $(REGSCRIPT)
	$(PYTHON) $(REGSCRIPT) $(CONF) > $(REGFILE)
