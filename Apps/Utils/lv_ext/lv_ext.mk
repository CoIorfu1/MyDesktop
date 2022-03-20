CXXSRCS += lv_anim_timeline_wrapper.cpp

DEPPATH += --dep-path $(LVGL_DIR)/lv_ext
VPATH += :$(LVGL_DIR)/lv_ext

CFLAGS += "-I$(LVGL_DIR)/lv_ext"