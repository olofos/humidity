V=@

SHELL=/bin/bash
C_SOURCES := main.c vector.c spi.c spi-flash.c spi-flash-cbuf.c uart.c i2c.c systick.c shtc3.c shtc3-crc.c adc.c rfm69.c rfm69-hal.c rtc.c pretty-print.c measurement.c debug.c
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

OBJ := $(C_SOURCES:%.c=$(OBJDIR)/%.o) $(ASM_SOURCES:%.s=$(OBJDIR)/%.o)
DEPS := $(C_SOURCES:%.c=$(DEPDIR)/%.d)
SRC := C_SOURCES ASM_SOURCES

VPATH := src/ ../common/src/

SOURCES_TST = $(wildcard $(TSTDIR)/*.c)

AR = arm-none-eabi-ar
CC = arm-none-eabi-gcc
NM = arm-none-eabi-nm
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
JLINK = JLinkExe

CFLAGS = -g -mthumb -mcpu=cortex-m0plus -march=armv6-m -mlittle-endian -nostartfiles --specs=nano.specs --specs=nosys.specs \
	 -std=gnu99 -Os \
	 -Wpointer-arith -Wundef -Wall -Wextra -Wimplicit-function-declaration -Wredundant-decls -Wstrict-prototypes -Wshadow  \
	 -fno-common \
	 $(INCLUDES)

LDFILE = ld/stm32l031K6Tx.ld

LDFLAGS = $(CFLAGS) -T$(LDFILE) -Wl,-Map=$(BINDIR)/$(TARGET).map,--cref

INCLUDES := $(INCLUDES)
INCLUDES += -I$(CURDIR)/include
INCLUDES += -I$(CURDIR)/../common/include

TST_CC = gcc
TST_WRAP =
TST_CFLAGS = -Wall -I$(SRCDIR) -ggdb -fsanitize=address -fno-omit-frame-pointer --coverage $(TST_WRAP) -DUNIT_TESTING=1

TST_RESULTS = $(patsubst $(TSTDIR)/test_%.c,$(TSTRESDIR)/test_%.txt,$(SOURCES_TST))
TST_DEPS = $(TSTDEPDIR)/*.d

.PHONY: all bin flash clean erase test build_dirs lss

all: build_dirs $(BINDIR)/$(TARGET).elf $(BINDIR)/$(TARGET).bin

lss: $(BINDIR)/$(TARGET).lss

-include $(DEPS)
-include $(TST_DEPS)

$(TSTBINDIR)/test_package-handler: $(TSTOBJDIR)/pretty-print.o

$(OBJDIR)/%.o : %.c
	@echo CC $@
	$(V)$(CC) $(CFLAGS) -c $< -o $@
	$(V)$(CC) -MM -MT $@ $(CFLAGS) $< > $(DEPDIR)/$*.d

$(OBJDIR)/%.o : %.s
	@echo CC $@
	$(V)$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/$(TARGET).elf : $(OBJ)
	@echo LINKING $@
	$(V)$(CC) $^ $(LDFLAGS) -o $@

$(BINDIR)/$(TARGET).elf : $(OBJDIR)/$(TARGET).elf $(OBJDIR)/$(TARGET).sum
	@echo COPYING $@
	$(V)$(OBJCOPY) --update-section .checksum=$(OBJDIR)/$(TARGET).sum $(OBJDIR)/$(TARGET).elf $(BINDIR)/$(TARGET).elf

%.hex : %.elf
	@echo CREATING HEX IMAGE $@
	$(V)$(OBJCOPY) --gap-fill 0xFF -O ihex $< $(@)

$(OBJDIR)/$(TARGET).bin : $(OBJDIR)/$(TARGET).elf
	@echo CREATING IMAGE $@
	$(V)$(OBJCOPY) --gap-fill 0xFF -O binary $< $(@)

$(BINDIR)/$(TARGET).bin : $(BINDIR)/$(TARGET).elf
	@echo CREATING IMAGE $@
	$(V)$(OBJCOPY) --gap-fill 0xFF -O binary $< $(@)

%.lss : %.elf
	@echo DUMPING $@
	$(V)$(OBJDUMP) -h -S $< > $@

%.sum : %.bin
	@echo CREATING CHECKSUM $@
	$(V)printf '%X' $$(( 0x$$(b2sum -l 64 -b $< | cut -d' ' -f1) & ~(1 << 63)))  | xxd -r -p - > $@

flash: $(BINDIR)/$(TARGET).bin
	@echo Flashing
	$(V)$(JLINK) -commanderscript scripts/flash.jlink

erase:
	@echo Not implemented

test: build_dirs $(TST_RESULTS)
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
	@echo Cleaning
	$(V)-rm -f $(OBJ) $(TSTOBJDIR)/*.o $(TSTBINDIR)/test_* $(TSTRESDIR)/*.txt $(DEPDIR)/*.d $(BINDIR)/* $(OBJDIR)/*

.PRECIOUS: $(TSTBINDIR)/test_%
.PRECIOUS: $(DEPDIR)/%.d
.PRECIOUS: $(OBJDIR)/%.o
.PRECIOUS: $(TSTRESDIR)/%.txt
.PRECIOUS: $(TSTOBJDIR)/%.o
