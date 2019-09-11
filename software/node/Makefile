V=@

C_SOURCES := main.c vector.c
ASM_SOURCES :=
# ASM_SOURCES :=

TARGET=node

SRCDIR := src
OBJDIR := obj
BINDIR := bin
DEPDIR := .deps
TSTDIR := test
TSTOBJDIR := test/obj
TSTBINDIR := test/bin
TSTDEPDIR := test/.deps
TSTRESDIR := test/results

BUILD_DIRS = $(OBJDIR) $(DEPDIR) $(BINDIR) $(TSTRESDIR) $(TSTOBJDIR) $(TSTBINDIR) $(TSTDEPDIR)

SRC := $(C_SOURCES:%.c=$(SRCDIR)/%.c) $(ASM_SOURCES:%.s=$(SRCDIR)/%.s)
OBJ := $(C_SOURCES:%.c=$(OBJDIR)/%.o) $(ASM_SOURCES:%.s=$(OBJDIR)/%.o)
DEPS := $(C_SOURCES:%.c=$(DEPDIR)/%.d)

SOURCES_TST = $(wildcard $(TSTDIR)/*.c)

AR = arm-none-eabi-ar
CC = arm-none-eabi-gcc
NM = arm-none-eabi-nm
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump

CFLAGS = -g -mthumb -mcpu=cortex-m0plus -march=armv6-m -mlittle-endian -nostartfiles --specs=nano.specs --specs=nosys.specs \
	 -std=gnu99 -Os \
	 -Wpointer-arith -Wundef -Wall -Wextra -Wimplicit-function-declaration -Wredundant-decls -Wstrict-prototypes -Wshadow  \
	 -fno-common \
	 $(INCLUDES)

LDFILE = ld/stm32l031K6Tx.ld

LDFLAGS = $(CFLAGS) -T$(LDFILE) -Wl,-Map=$(BINDIR)/$(TARGET).map,--cref

INCLUDES := $(INCLUDES)
INCLUDES += -I$(CURDIR)/include
INCLUDES += -I$(CURDIR)/src

TST_CC = gcc
TST_WRAP =
TST_CFLAGS = -Wall -I$(SRCDIR) -ggdb -fsanitize=address -fno-omit-frame-pointer --coverage $(TST_WRAP)

TST_RESULTS = $(patsubst $(TSTDIR)/test_%.c,$(TSTRESDIR)/test_%.txt,$(SOURCES_TST))
TST_DEPS = $(TSTDEPDIR)/*.d

.PHONY: all bin flash clean erase test build_dirs

all: build_dirs $(BINDIR)/$(TARGET).hex

-include $(DEPS)
-include $(TST_DEPS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@echo CC $@
	$(V)$(CC) $(CFLAGS) -c $< -o $@
	$(V)$(CC) -MM -MT $@ $(CFLAGS) $< > $(DEPDIR)/$*.d

$(OBJDIR)/%.o : $(SRCDIR)/%.s
	@echo CC $@
	$(V)$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR)/$(TARGET).elf : $(OBJ)
	@echo LINKING $@
	$(V)$(CC) $^ $(LDFLAGS) -o $@

%.hex : %.elf
	@echo CREATING HEX IMAGE $@
	$(V)$(OBJCOPY) -O ihex $< $(@)

flash: $(BINDIR)/$(TARGET).hex
	@echo Not implemented

erase:
	@echo Not implemented

test: build_dirs $(TST_RESULTS)
	@echo "-----------------------"
	@echo "SKIPPED:" `grep -o '\[  SKIPPED \]' $(TSTRESDIR)/*.txt|wc -l`
	@echo "-----------------------"
	@grep -s '\[  SKIPPED \]' $(TSTRESDIR)/*.txt || true
	@echo "\n-----------------------"
	@echo "FAILED:" `grep -o '\[  FAILED  \]' $(TSTRESDIR)/*.txt|wc -l`
	@echo "-----------------------"
	@grep -s 'FAILED\|LINE\|ERROR' $(TSTRESDIR)/*.txt || true
	@echo "\n-----------------------"
	@echo "PASSED:" `grep -o '\[       OK \]' $(TSTRESDIR)/*.txt|wc -l`
	@echo "-----------------------"
	@echo
	@! grep -s '\[  FAILED  \]' $(TSTRESDIR)/*.txt 2>&1 1>/dev/null

build_dirs:
	$(V)mkdir -p $(BUILD_DIRS)


$(TSTRESDIR)/%.txt: $(TSTBINDIR)/%
	@echo Running $<
	@echo
	$(V)./$< > $@ 2>&1 || true

$(TSTOBJDIR)/%.o : $(TSTDIR)/%.c
	@echo CC $@
	$(V)$(TST_CC) $(TST_CFLAGS)  $(INCLUDES) -c $< -o $@
	$(V)$(TST_CC) -MM -MT $@ $(TST_CFLAGS) $(INCLUDES) $< > $(TSTDEPDIR)$*.d

$(TSTOBJDIR)/%.o : $(SRCDIR)/%.c
	@echo CC $@
	$(V)$(TST_CC) $(TST_CFLAGS)  $(INCLUDES) -c $< -o $@
	$(V)$(TST_CC) -MM -MT $@ $(TST_CFLAGS) $(INCLUDES) $< > $(TSTDEPDIR)$*.d

$(TSTBINDIR)/test_%: $(TSTOBJDIR)/test_%.o $(TSTOBJDIR)/%.o
	@echo CC $@
	$(V)$(TST_CC) -o $@ $(TST_CFLAGS) $^ -lcmocka

clean:
	@echo Cleaning
	$(V)-rm -f $(OBJ) $(TSTOBJDIR)/*.o $(TSTBINDIR)/test_* $(TSTRESDIR)/*.txt $(DEPDIR)/*.d $(BINDIR)/*

.PRECIOUS: $(TSTBINDIR)/test_%
.PRECIOUS: $(DEPDIR)/%.d
.PRECIOUS: $(OBJDIR)/%.o
.PRECIOUS: $(TSTRESDIR)/%.txt
.PRECIOUS: $(TSTOBJDIR)/%.o
