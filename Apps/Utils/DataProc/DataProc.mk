CXXSRCS += DataProc.cpp

DEPPATH += --dep-path $(LVGL_DIR)/DataProc
VPATH += :$(LVGL_DIR)/DataProc

CFLAGS += "-I$(LVGL_DIR)/DataProc"