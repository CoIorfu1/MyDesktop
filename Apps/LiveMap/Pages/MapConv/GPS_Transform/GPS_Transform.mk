CSRCS += GPS_Transform.c

DEPPATH += --dep-path $(PAGES_DIR)/MapConv/GPS_Transform
VPATH += :$(PAGES_DIR)/MapConv/GPS_Transform

CFLAGS += "-I$(PAGES_DIR)/MapConv/GPS_Transform"