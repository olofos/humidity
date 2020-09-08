V=@

C_SOURCES := main.c rfm69.c rfm69-hal.c db.c sqlite3.c package-handler.c node.c

SRCDIR := src
OBJDIR := obj
DEPDIR := .deps
TSTDIR := test
TSTOBJDIR := test/obj
TSTBINDIR := test/bin
TSTDEPDIR := test/.deps
TSTRESDIR := test/results


CFLAGS = -g -O2 -Wall -Iinclude/
LDFLAGS = $(CFLAGS) -lgpiod -lpthread -ldl

CC = gcc

SRC := $(C_SOURCES:%.c=$(SRCDIR)/%.c) $(ASM_SOURCES:%.s=$(SRCDIR)/%.s)
OBJ := $(C_SOURCES:%.c=$(OBJDIR)/%.o) $(ASM_SOURCES:%.s=$(OBJDIR)/%.o)
DEPS := $(C_SOURCES:%.c=$(DEPDIR)/%.d)

BUILD_DIRS := $(OBJDIR) $(DEPDIR)
TEST_BUILD_DIRS := $(TSTRESDIR) $(TSTOBJDIR) $(TSTBINDIR) $(TSTDEPDIR)

SOURCES_TST = $(wildcard $(TSTDIR)/*.c)

TST_CC = gcc
TST_WRAP = -Wl,--wrap=time
TST_CFLAGS = -Wall -Iinclude/ -I../common/include -ggdb -fsanitize=address -fno-omit-frame-pointer --coverage $(TST_WRAP) -DUNIT_TESTING=1

TST_RESULTS = $(patsubst $(TSTDIR)/test_%.c,$(TSTRESDIR)/test_%.txt,$(SOURCES_TST))
TST_DEPS = $(TSTDEPDIR)/*.d

TST_PROGS = $(patsubst $(TSTDIR)/test_%.c,$(TSTBINDIR)/test_%,$(SOURCES_TST))


.PHONY: all clean build_dirs test_build_dirs

.PRECIOUS: $(TST_PROGS)

all: build_dirs humidity-gateway

-include $(DEPS)
-include $(TST_DEPS)

humidity-gateway: $(OBJ)
	@echo LINKING $@
	$(V)$(CC) $^ $(LDFLAGS) -o $@

test: test_build_dirs $(TST_RESULTS)
	@echo "-----------------------"
	@echo "SKIPPED:" `grep -o '\[  SKIPPED \]' $(TSTRESDIR)/*.txt|wc -l`
	@echo "-----------------------"
	@grep -s '\[  SKIPPED \]' $(TSTRESDIR)/*.txt || true
	@echo
	@echo "-----------------------"
	@echo "FAILED:" `grep -o '\[  FAILED  \]' $(TSTRESDIR)/*.txt|wc -l`
	@echo "-----------------------"
	@grep -s 'FAILED\|LINE\|ERROR' $(TSTRESDIR)/*.txt || true
	@echo
	@echo "-----------------------"
	@echo "PASSED:" `grep -o '\[       OK \]' $(TSTRESDIR)/*.txt|wc -l`
	@echo "-----------------------"
	@echo
	@! grep -s '\[  FAILED  \]' $(TSTRESDIR)/*.txt 2>&1 1>/dev/null

build_dirs:
	$(V)mkdir -p $(BUILD_DIRS)

test_build_dirs:
	$(V)mkdir -p $(TEST_BUILD_DIRS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@echo CC $@
	$(V)$(CC) $(CFLAGS) -c $< -o $@
	$(V)$(CC) -MM -MT $@ $(CFLAGS) $< > $(DEPDIR)/$*.d

$(TSTRESDIR)/%.txt: $(TSTBINDIR)/%
	@echo Running $<
	@echo
	$(V)./$< > $@ 2>&1 || true

$(TSTOBJDIR)/%.o : $(TSTDIR)/%.c
	@echo CC $@
	$(V)$(TST_CC) $(TST_CFLAGS)  $(INCLUDES) -c $< -o $@
	$(V)$(TST_CC) -MM -MT $@ $(TST_CFLAGS) $(INCLUDES) $< > $(TSTDEPDIR)/$*.d

$(TSTOBJDIR)/%.o : $(SRCDIR)/%.c
	@echo CC $@
	$(V)$(TST_CC) $(TST_CFLAGS)  $(INCLUDES) -c $< -o $@
	$(V)$(TST_CC) -MM -MT $@ $(TST_CFLAGS) $(INCLUDES) $< > $(TSTDEPDIR)/$*.d

$(TSTBINDIR)/test_%: $(TSTOBJDIR)/test_%.o $(TSTOBJDIR)/%.o
	@echo CC $@
	$(V)$(TST_CC) -o $@ $(TST_CFLAGS) $^ -lcmocka

clean:
	@echo CLEANING
	$(V)-rm -f humidity-gateway $(TSTOBJDIR)/*.o $(TSTBINDIR)/test_* $(TSTRESDIR)/*.txt $(DEPDIR)/*.d $(OBJDIR)/*
