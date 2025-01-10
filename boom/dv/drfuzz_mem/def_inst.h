#ifndef DEF_INST
#define DEF_INST

#define INST "drfuzz_mem"

// enable taints
#define TAINT_EN
#define SEED 0

#define CHECK_REG_REQ
#define DUMP_FINAL_REGVALS
#define DUMP_REGSTREAM_VALS
#define SINGLE_FUZZ // only runs a single fuzzing round with seed for testing of taint propagation

#define PRINT_REG_REQ // prints register requests
#define CHECK_REG_REQ // compares register values to spike simulation
#define CHECK_GOT_STOP_REQ

#endif // DEF_INST