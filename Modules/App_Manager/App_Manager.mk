CSRCS += App_Manager.c 

DEPPATH += --dep-path $(MODULES_DIR)/App_Manager/
VPATH += :$(MODULES_DIR)/App_Manager/

CFLAGS += "-I$(MODULES_DIR)/App_Manager/"