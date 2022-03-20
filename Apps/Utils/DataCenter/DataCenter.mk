CXXSRCS += Account.cpp
CXXSRCS += DataCenter.cpp
CXXSRCS += PingPongBuffer.cpp

DEPPATH += --dep-path $(LVGL_DIR)/DataCenter
VPATH += :$(LVGL_DIR)/DataCenter

CFLAGS += "-I$(LVGL_DIR)/DataCenter"