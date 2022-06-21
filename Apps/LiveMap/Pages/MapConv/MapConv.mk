include $(PAGES_DIR)/MapConv/GPS_Transform/GPS_Transform.mk
include $(PAGES_DIR)/MapConv/TileSystem/TileSystem.mk

CXXSRCS += MapConv.cpp

DEPPATH += --dep-path $(PAGES_DIR)/MapConv
VPATH += :$(PAGES_DIR)/MapConv

CFLAGS += "-I$(PAGES_DIR)/MapConv"