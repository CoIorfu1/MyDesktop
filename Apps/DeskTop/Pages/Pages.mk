include $(PAGES_DIR)/HomePage/HomePage.mk
include $(PAGES_DIR)/Brightness/Brightness.mk

CXXSRCS += AppFactory.cpp

DEPPATH += --dep-path $(PAGES_DIR)
VPATH += :$(PAGES_DIR)

CFLAGS += "-I$(PAGES_DIR)"

