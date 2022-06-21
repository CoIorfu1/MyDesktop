CXXSRCS += HAL.cpp
CXXSRCS += HAL_GPS.cpp

DEPPATH += --dep-path $(HAL_DIR)
VPATH += :$(HAL_DIR)

CFLAGS += "-I$(HAL_DIR)"