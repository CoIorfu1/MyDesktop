include $(PAGES_DIR)/LiveMap/LiveMap.mk
include $(PAGES_DIR)/MapConv/MapConv.mk
include $(PAGES_DIR)/TileConv/TileConv.mk

CXXSRCS += AppFactory.cpp

DEPPATH += --dep-path $(PAGES_DIR)
VPATH += :$(PAGES_DIR)

CFLAGS += "-I$(PAGES_DIR)"