#ifndef DEF_TB
#define DEF_TB
#include "def_inst.h"

#include "Vtop_tiny_soc.h"
#include "Vtop_tiny_soc__Dpi.h"
typedef Vtop_tiny_soc Module;

#define DUT "Boom"

#define N_COV_POINTS 5716
#define N_TAINT_OUTPUTS N_COV_POINTS
#define N_ASSERTS 0

#define SINGLE_MEM
#define VSCOPE_MEM "TOP.top_tiny_soc.i_sram"
#define T_DELTA_COV_DUMP 600

#define DATA_WIDTH_BYTES_LOG2 3
#define ADDR_WIDTH_BYTES_LOG2 2

#define RELOCATE_UP 0x80000000
#define N_RESET_TICKS 50
#define N_META_RESET_TICKS 1
#define N_TICKS_AFTER_STOP 50 // Run a bit longer in case something interesting still happens

#ifdef VM_TRACE
#define TRACE_LEVEL 6
#endif  // VM_TRACE

// #define PRINT_TAINT_BUS


#endif // DEF_TB