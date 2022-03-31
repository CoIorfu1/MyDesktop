CXXSRCS += PM_Anim.cpp
CXXSRCS += PM_Base.cpp
CXXSRCS += PM_Router.cpp
CXXSRCS += PM_State.cpp

DEPPATH += --dep-path $(LVGL_DIR)/PageManager
VPATH += :$(LVGL_DIR)/PageManager

CFLAGS += "-I$(LVGL_DIR)/PageManager"