# ----------------------------
# Makefile Options
# ----------------------------

NAME = ${REPO_NAME_SNAKE}
DESCRIPTION = "${REPO_DESCRIPTION}"
COMPRESSED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

EMULATOR_DIR=/home/james/Development/fab-agon-emulator
EMULATOR_BIN=target/release/fab-agon-emulator
EMULATOR_FLAGS=--scale 2000
# ----------------------------

include $(shell cedev-config --makefile)

.PHONY: emulate inst

autoexec.txt: all
	echo "cd $(NAME)" > $(BINDIR)/autoexec.txt
	echo "load $(TARGETBIN)" >> $(BINDIR)/autoexec.txt
	echo "run" >> $(BINDIR)/autoexec.txt

inst: $(BINDIR)/$(TARGETBIN)
	mkdir -p $(EMULATOR_DIR)/sdcard/$(NAME)
	cp $(BINDIR)/$(TARGETBIN) $(EMULATOR_DIR)/sdcard/$(NAME)
	cp $(BINDIR)/autoexec.txt $(EMULATOR_DIR)/sdcard

emulate: autoexec.txt inst
	cd $(EMULATOR_DIR) && $(EMULATOR_DIR)/$(EMULATOR_BIN) $(EMULATOR_FLAGS)
