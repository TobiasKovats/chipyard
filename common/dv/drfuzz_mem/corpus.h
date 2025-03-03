#ifndef CORPUS_H
#define CORPUS_H

#include <deque>

#include "queue.h"
#include "macros.h"
#include "testbench.h"
#ifdef DUMP_COVERAGE
#include <iostream>
#include <fstream>
#endif
// this class defines the set of queses that contain inputs and, if applied to DUT,
// the resulting outpus. That is, after fuzzing, it holds all test inputs and
// the the DUT ouputs each results in. It is initialized with some random seeds, which 
// are then permuted and if new coverage points are reached, readded to the corpus
class Corpus{
    private:
        std::deque<Queue *> qs;
        Queue *acc_queue;
        #ifdef DUMP_COVERAGE
        std::chrono::_V2::steady_clock::time_point t_last_dump;
        #endif
    public:
        Corpus();
        void dump_current_cov(Testbench *tb);
        void add_q(Queue *q);
        void accumulate_output(Queue *q);
        doutput_t *get_accumulated_output();
        Queue *pop_q();
        bool empty();
        bool is_interesting(Queue *q);
        int get_coverage_amount();
        void print_acc_coverage();
        size_t size();
        
        #ifdef TAINT_EN
        void sort_qs();
        size_t get_n_untoggled_and_untainted_mux(Queue *q);
        bool taints_all_untoggled_mux(Queue *q);
        bool taints_any_untoggled_mux(Queue *q);
        #endif // TAINT_EN

};
#endif // CORPUS_H