#include "update_req.h"
#include "dtypes.h"
#include "helperfuncs.h"
#include <iostream>
#include <stdlib.h>
#include "verilated.h"

 // this function is tb specific currently. Maybe adapt top level SoCs s.t. this can be put into meta repo?
void _update_req(const std::unique_ptr<Module> &module, tick_req_t *ret){
    static uint32_t curr_float_req_dump_id = 0;
    static uint32_t curr_int_req_dump_id = 1;
    static uint32_t curr_regstream_dump_id = 0;
    if ((module->mmio_req_o & 1) == 1 && (module->mmio_we_o & 1) == 1) {
        if ((module->mmio_addr_o & 0x7FFFFFFFULL) == 0x60000000ULL) {
            if (ret->type != REQ_NONE)
              std::cerr << "WARNING: Missed a request during a batch of ticks." << std::endl;
            ret->type = REQ_STOP;
            } 
            else if ((module->mmio_addr_o & 0x7FFFFFFFULL) == 0x60000010ULL) {
                if (ret->type != REQ_NONE)
                    std::cerr << "WARNING: Missed a request during a batch of ticks." << std::endl;
                assert(module->mmio_strb_o == 0xFF);
                ret->type = REQ_INTREGDUMP;
                ret->id = curr_int_req_dump_id++;
                ret->content = module->mmio_wdata_o;
                #ifdef TAINT_EN
                ret->content_t0 =  module->mmio_wdata_o_t0;
                #endif
            } 
            else if ((module->mmio_addr_o & 0x7FFFFFFFULL) == 0x60000018ULL) {
                if (ret->type != REQ_NONE)
                    std::cerr << "WARNING: Missed a request during a batch of ticks." << std::endl;
                assert(module->mmio_strb_o == 0xFF);
                ret->type = REQ_FLOATREGDUMP;
                ret->id = curr_float_req_dump_id++;
                ret->content = module->mmio_wdata_o;
                #ifdef TAINT_EN
                ret->content_t0 =  module->mmio_wdata_o_t0;
                #endif
            }
            else if ((module->mmio_addr_o & 0x7FFFFFFFULL) == 0x60000020ULL) {
                if (ret->type != REQ_NONE)
                    std::cerr << "WARNING: Missed a request during a batch of ticks." << std::endl;
                assert(module->mmio_strb_o == 0xFF);
                ret->type = REQ_REGSTREAM;
                ret->id = curr_regstream_dump_id++;
                ret->content = module->mmio_wdata_o;
                #ifdef TAINT_EN
                ret->content_t0 =  module->mmio_wdata_o_t0;
                #endif
            }

        }
    #ifdef PRINT_TAINT_BUS
    if(module->mem_rdata_o_t0) std::cout << "Taint on memory bus detected!\n";
    #endif // PRINT_TAINT_BUS
}
