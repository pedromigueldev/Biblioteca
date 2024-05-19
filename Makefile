CC=gcc
SRCDIR=src
BUILDDIR=build
PROGRAM=Biblioteca

SOURCE_F := $(wildcard $(SRCDIR)/*.c)
BUILD_F  := $(SOURCE_F:$(SRCDIR)/%.c=./$(BUILDDIR)/%.o)

all: create_dir clean start

create_dir:
ifeq ($(OS),Windows_NT)
	if not exist "$(BUILDDIR)\" mkdir $(BUILDDIR)
else
	mkdir -p $(BUILDDIR)/
endif

clean:
	rm -f $(BUILDDIR)/*.o

start: $(BUILD_F)
	$(CC) -o $(PROGRAM) $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $^ -Wall -g -std=gnu99

run:
	./$(PROGRAM)