CXXSRCS += HAL.cpp
CXXSRCS += HAL_Ap3216c.cpp

DEPPATH += --dep-path $(HAL_DIR)
VPATH += :$(HAL_DIR)

CFLAGS += "-I$(HAL_DIR)"