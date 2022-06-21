CXXSRCS += TileConv.cpp

DEPPATH += --dep-path $(PAGES_DIR)/TileConv
VPATH += :$(PAGES_DIR)/TileConv

CFLAGS += "-I$(PAGES_DIR)/TileConv"