include $(PAGES_DIR)/HomePage/HomePage.mk

CXXSRCS += AppFactory.cpp

DEPPATH += --dep-path $(PAGES_DIR)
VPATH += :$(PAGES_DIR)

CFLAGS += "-I$(PAGES_DIR)"

