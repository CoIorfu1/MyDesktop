CXXSRCS += DataProc.cpp
CXXSRCS += DP_Ap3216c.cpp

DEPPATH += --dep-path $(DP_DIR)
VPATH += :$(DP_DIR)

CFLAGS += "-I$(DP_DIR)"