CSRCS += Dbus_Server.c 

DEPPATH += --dep-path $(MODULES_DIR)/Dbus_Server/
VPATH += :$(MODULES_DIR)/Dbus_Server/

CFLAGS += "-I$(MODULES_DIR)/Dbus_Server/"