V=@

C_SOURCES := main.c rfm69.c rfm69-hal.c db.c sqlite3.c

SRCDIR := src
OBJDIR := obj
DEPDIR := .deps


CFLAGS = -g -O2 -Wall -Iinclude/
LDFLAGS = $(CFLAGS) -lgpiod -lpthread -ldl

CC = gcc

SRC := $(C_SOURCES:%.c=$(SRCDIR)/%.c) $(ASM_SOURCES:%.s=$(SRCDIR)/%.s)
OBJ := $(C_SOURCES:%.c=$(OBJDIR)/%.o) $(ASM_SOURCES:%.s=$(OBJDIR)/%.o)
DEPS := $(C_SOURCES:%.c=$(DEPDIR)/%.d)

BUILD_DIRS := $(OBJDIR) $(DEPDIR)

.PHONY: all clean build_dirs

all: build_dirs humidity-gateway

-include $(DEPS)

humidity-gateway: $(OBJ)
	@echo LINKING $@
	$(V)$(CC) $^ $(LDFLAGS) -o $@

build_dirs:
	$(V)mkdir -p $(BUILD_DIRS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@echo CC $@
	$(V)$(CC) $(CFLAGS) -c $< -o $@
	$(V)$(CC) -MM -MT $@ $(CFLAGS) $< > $(DEPDIR)/$*.d

clean:
	@echo CLEANING
	$(V)rm humidity-gateway $(OBJ)
