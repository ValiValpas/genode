#
# Z3 solver library
#

include $(REP_DIR)/lib/mk/z3.inc

# transforms files
SRC_CC = dl_transforms.cpp \
	dl_mk_unfold.cpp \
	dl_mk_unbound_compressor.cpp \
	dl_mk_subsumption_checker.cpp \
	dl_mk_slice.cpp \
	dl_mk_separate_negated_tails.cpp \
	dl_mk_scale.cpp \
	dl_mk_rule_inliner.cpp \
	dl_mk_quantifier_instantiation.cpp \
	dl_mk_quantifier_abstraction.cpp \
	dl_mk_magic_symbolic.cpp \
	dl_mk_magic_sets.cpp \
	dl_mk_loop_counter.cpp \
	dl_mk_karr_invariants.cpp \
	dl_mk_interp_tail_simplifier.cpp \
	dl_mk_filter_rules.cpp \
	dl_mk_coi_filter.cpp \
	dl_mk_coalesce.cpp \
	dl_mk_bit_blast.cpp \
	dl_mk_backwards.cpp \
	dl_mk_array_blast.cpp

LIBS = stdcxx z3-muz z3-hilbert z3-dataflow gmp

vpath %.cpp $(Z3_DIR)/src/muz/transforms
