APP = test
APP_SRCS += test.c
APP_CFLAGS += -O3 -g -Werror
APP_LDFLAGS +=

IMAGE1=$(CURDIR)/../../samples/imgTest0.pgm
JPG_IMAGE1=$(CURDIR)/imgTest0.jpg

# Include GAP_LIB/JPEG
CONFIG_GAP_LIB_JPEG = 1

PLPBRIDGE_FLAGS += -f $(IMAGE1) -jtag
override runner_args += --config-opt=flash/fs/files=$(IMAGE1) --config-opt=flash/fs/files=$(JPG_IMAGE1)

include $(RULES_DIR)/pmsis_rules.mk
