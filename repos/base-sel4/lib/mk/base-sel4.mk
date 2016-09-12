include $(BASE_DIR)/lib/mk/base.inc

SRC_CC += capability_space.cc
SRC_CC += thread_start.cc thread_init.cc
SRC_CC += thread_no_execution_time.cc
SRC_CC += cache.cc

LIBS += syscall-sel4 base-sel4-common
