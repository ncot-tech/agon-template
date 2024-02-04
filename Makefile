# ----------------------------
# Makefile Options
# ----------------------------

NAME = agon-light-test
DESCRIPTION = "Test for the Agon Light C Compiler"
COMPRESSED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

EMULATOR_DIR=/home/james/Development/fab-agon-emulator
EMULATOR_BIN=fab-agon-emulator
EMULATOR_FLAGS=--scale 2000
SD_CARD=/media/james/H1N_SD
# ----------------------------

include $(shell cedev-config --makefile)

.PHONY: emulate inst_emu inst_sd

autoexec.txt: all
	echo "cd $(NAME)" > $(BINDIR)/autoexec.txt
	echo "load $(TARGETBIN)" >> $(BINDIR)/autoexec.txt
	echo "run" >> $(BINDIR)/autoexec.txt

inst_emu: $(BINDIR)/$(TARGETBIN)
	mkdir -p $(EMULATOR_DIR)/sdcard/$(NAME)
	cp $(BINDIR)/$(TARGETBIN) $(EMULATOR_DIR)/sdcard/$(NAME)
	cp $(BINDIR)/autoexec.txt $(EMULATOR_DIR)/sdcard

inst_sd: $(BINDIR)/$(TARGETBIN)
	mkdir -p $(SD_CARD)/$(NAME)
	cp $(BINDIR)/$(TARGETBIN) $(SD_CARD)/$(NAME)
	cp $(BINDIR)/autoexec.txt $(SD_CARD)

emulate: autoexec.txt inst_emu
	gnome-terminal --working-directory=$(EMULATOR_DIR) -- ./$(EMULATOR_BIN) $(EMULATOR_FLAGS)
