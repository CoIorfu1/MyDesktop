export G++ := arm-buildroot-linux-gnueabihf-g++
export CC := arm-buildroot-linux-gnueabihf-gcc
export LVGL_DIR_NAME ?= lvgl
export LVGL_DIR ?= ${shell cd ../Utils && pwd}
export MODULES_DIR ?= ${shell cd ../../Modules && pwd}
export PAGES_DIR ?= ${shell cd ./Pages && pwd}
export HAL_DIR ?= ${shell cd ./HAL && pwd}
export DP_DIR ?= ${shell cd ./DataProc && pwd}

export CFLAGS ?= -O3 -g0 -I$(LVGL_DIR)/  -Wall -Wshadow -Wundef -Wmissing-prototypes -Wno-discarded-qualifiers -Wall -Wextra -Wno-unused-function -Wno-error=strict-prototypes -Wpointer-arith -fno-strict-aliasing -Wno-error=cpp -Wuninitialized -Wmaybe-uninitialized -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits -Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wno-cast-qual -Wunreachable-code -Wno-switch-default -Wreturn-type -Wmultichar -Wformat-security -Wno-ignored-qualifiers -Wno-error=pedantic -Wno-sign-compare -Wno-error=missing-prototypes -Wdouble-promotion -Wclobbered -Wdeprecated -Wempty-body -Wtype-limits -Wshift-negative-value -Wstack-usage=2048 -Wno-unused-value -Wno-unused-parameter -Wno-missing-field-initializers -Wuninitialized -Wmaybe-uninitialized -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits -Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wpointer-arith -Wno-cast-qual -Wmissing-prototypes -Wunreachable-code -Wno-switch-default -Wreturn-type -Wmultichar -Wno-discarded-qualifiers -Wformat-security -Wno-ignored-qualifiers -Wno-sign-compare \
	-I ~/100ask_imx6ull-sdk/ToolChain/arm-buildroot-linux-gnueabihf_sdk-buildroot/arm-buildroot-linux-gnueabihf/sysroot/usr/include -I ~/100ask_imx6ull-sdk/ToolChain/arm-buildroot-linux-gnueabihf_sdk-buildroot/arm-buildroot-linux-gnueabihf/sysroot/usr/lib/dbus-1.0/include
export LDFLAGS ?= -lm -ldbus-1 -lpthread
BIN = MyBrightness

#Collect the files to compile
MAINSRC = ./main.cpp
CXXSRCS ?= ./App.cpp

include $(LVGL_DIR)/Utils.mk
include $(MODULES_DIR)/Modules.mk
include $(PAGES_DIR)/Pages.mk
include $(DP_DIR)/DataProc.mk
include $(HAL_DIR)/HAL.mk


OBJEXT ?= .o

AOBJS = $(ASRCS:.S=$(OBJEXT))
COBJS = $(CSRCS:.c=$(OBJEXT))
CXXOBJS = $(CXXSRCS:.cpp=$(OBJEXT))

MAINOBJ = $(MAINSRC:.cpp=$(OBJEXT))

SRCS =  $(CSRCS) $(CXXSRC) $(MAINSRC)
OBJS =  $(AOBJS) $(COBJS) $(CXXOBJS)

all: default

%.o: %.c
	$(CC)  $(CFLAGS) -c $< -o $@
	@echo "CC $<"

%.o: %.cpp
	$(G++)  $(CFLAGS) -c $< -o $@
	@echo "G++ $<"
    
default:  $(AOBJS) $(COBJS) $(CXXOBJS) $(MAINOBJ)
	$(G++) -o $(BIN) $(MAINOBJ) $(AOBJS) $(COBJS) $(CXXOBJS) $(LDFLAGS)
	mkdir -p ./obj ./bin
	mv *.o ./obj
	mv $(BIN) ./bin/

clean: 
	rm -f $(BIN) $(AOBJS) $(COBJS) $(CXXOBJS) $(MAINOBJ) ./bin/* ./obj/*
	