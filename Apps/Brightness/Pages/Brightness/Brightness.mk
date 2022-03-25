CXXSRCS += BrightnessView.cpp
CXXSRCS += Brightness.cpp

DEPPATH += --dep-path $(PAGES_DIR)/Brightness
VPATH += :$(PAGES_DIR)/Brightness

CFLAGS += "-I$(PAGES_DIR)/Brightness"