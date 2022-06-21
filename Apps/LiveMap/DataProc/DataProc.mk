CXXSRCS += DataProc.cpp
CXXSRCS += DP_GPS.cpp

DEPPATH += --dep-path $(DP_DIR)
VPATH += :$(DP_DIR)

CFLAGS += "-I$(DP_DIR)"