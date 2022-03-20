CXXSRCS += HomePageView.cpp
CXXSRCS += HomePage.cpp

DEPPATH += --dep-path $(PAGES_DIR)/HomePage
VPATH += :$(PAGES_DIR)/HomePage

CFLAGS += "-I$(PAGES_DIR)/HomePage"