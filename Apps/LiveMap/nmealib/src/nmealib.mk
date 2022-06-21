CSRCS += context.c
CSRCS += generate.c
CSRCS += generator.c
CSRCS += gmath.c
CSRCS += info.c
CSRCS += parse.c
CSRCS += parser.c
CSRCS += sentence.c
CSRCS += time.c
CSRCS += tok.c

DEPPATH += --dep-path $(NMEA_DIR)
VPATH += :$(NMEA_DIR)

CFLAGS += "-I$(NMEA_DIR)"