# ----------------------------
# Makefile Options
# WARNING - THIS IS A MAKEFILE, ENSURE YOUR EDITOR KNOWS NOT TO SWAP TABS FOR SPACES
# OR YOU WILL BREAK THIS IN SUBTLE AND CONFUSING WAYS
# ----------------------------

##############################################################################
# EDIT THIS PART

# The name of your final executable
NAME = agon-template
DESCRIPTION = "Agon Light C Template"

CFLAGS = -Wall -Wextra -Oz -DDEBUG
CXXFLAGS = -Wall -Wextra -Oz

# SET WHERE YOUR EMULATOR IS
EMULATOR_DIR=../fab-agon-emulator
EMULATOR_BIN=fab-agon-emulator
EMULATOR_FLAGS=--scale 2000
# WHERE THE SD CARD IS LOCATED IN THE EMULATOR
EMULATOR_SDCARD=~/.agon-sdcard
# WHERE THE REAL SD CARD IS WHEN MOUNTED
SD_CARD=/media/james/H1N_SD

# THIS WILL ONE DAY BE PART OF A CONFIG FILE
FONT_CHAR_WIDTH=8
FONT_CHAR_HEIGHT=8
MAP_BITMAP_START_ID=1000
FONT_BITMAP_START_ID=2000

##############################################################################
# DON'T EDIT BELOW HERE
DIST=dist
IMAGES=data/images
FONTS=data/fonts
TILES=data/tiles
PNG2RGB=tools/png2rgb.py
MAKE_TILEMAP=tools/make_tilemap.py
MAKE_FONT=tools/make_font.py
COMPRESSED = NO
VERSION_FILE = src/version.h
DOXYFILE = Doxyfile
DOXYGEN = doxygen
UPDATE_DOXYFILE_SCRIPT = tools/update_doxyfile.py
# ----------------------------
# DON'T EDIT THIS, IT IS PURE EVIL, THERE ARE TAB CHARACTERS IN HERE

include $(shell cedev-config --makefile)

.PHONY: dist emulate dist_sd inst_emu inst_sd images tiles fonts assets distclean docs update_doxyfile

emulate: inst_emu
	cd $(EMULATOR_DIR) && ./$(EMULATOR_BIN) $(EMULATOR_FLAGS)

images: $(wildcard $(IMAGES)/*)
	mkdir -p $(DIST)/$(NAME)/images
	@for file in $^; do \
		echo "Processing $$file into $(DIST)/$(NAME)/images"; \
		$(PNG2RGB) $$file $(DIST)/$(NAME)/images; \
    done

tiles: $(wildcard $(TILES)/*.tmx)
	mkdir -p $(DIST)/$(NAME)/tiles
	@for file in $^; do \
		echo "Processing $$file into $(DIST)/$(NAME)/tiles"; \
		$(MAKE_TILEMAP) $$file $(DIST)/$(NAME)/tiles $(MAP_BITMAP_START_ID); \
    done

fonts: $(wildcard $(FONTS)/*)
	mkdir -p $(DIST)/$(NAME)/fonts
	@for file in $^; do \
		echo "Processing $$file into $(DIST)/$(NAME)/fonts"; \
		$(MAKE_FONT) $$file $(DIST)/$(NAME)/fonts $(FONT_CHAR_WIDTH) $(FONT_CHAR_HEIGHT) $(FONT_BITMAP_START_ID); \
    done

assets: fonts tiles images

distclean: clean
	rm -rf $(DIST)

dist: assets all
	mkdir -p $(DIST)/$(NAME)
	echo "cd $(NAME)" > $(DIST)/autoexec.txt
	echo "load $(TARGETBIN)" >> $(DIST)/autoexec.txt
	echo "run" >> $(DIST)/autoexec.txt
	cp $(BINDIR)/$(TARGETBIN) $(DIST)/$(NAME)

inst_emu: dist
	mkdir -p $(EMULATOR_SDCARD)/$(NAME)
	cp -a $(DIST)/$(NAME) $(EMULATOR_SDCARD)
	cp $(DIST)/autoexec.txt $(EMULATOR_SDCARD)

inst_sd: dist
	mkdir -p $(SD_CARD)/$(NAME)
	cp -a $(DIST)/$(NAME) $(SD_CARD)
	cp $(DIST)/autoexec.txt $(SD_CARD)

docs: update_doxyfile
	$(DOXYGEN) $(DOXYFILE)

# Target to update the Doxyfile with the project version
update_doxyfile: $(UPDATE_DOXYFILE_SCRIPT) $(VERSION_FILE)
	$(UPDATE_DOXYFILE_SCRIPT)