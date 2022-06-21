CXXSRCS += LiveMapView.cpp
CXXSRCS += LiveMapModel.cpp
CXXSRCS += LiveMap.cpp

DEPPATH += --dep-path $(PAGES_DIR)/LiveMap
VPATH += :$(PAGES_DIR)/LiveMap

CFLAGS += "-I$(PAGES_DIR)/LiveMap"