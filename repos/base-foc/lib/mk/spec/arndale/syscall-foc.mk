L4_CONFIG := $(call select_from_repositories,config/arndale.user)

include $(REP_DIR)/lib/mk/spec/arm/syscall-foc.inc
