#include <stdint.h>

static inline uint64_t read_cntfrq(void) {
    uint64_t val;
    asm volatile("mrs %0, CNTFRQ_EL0" : "=r"(val));
    return val;
}

static inline void write_cntp_tval(uint64_t val) {
    asm volatile("msr CNTP_TVAL_EL0, %0" :: "r"(val));
}

static inline void write_cntp_ctl(uint64_t val) {
    asm volatile("msr CNTP_CTL_EL0, %0" :: "r"(val));
}

void timer_init() {
    uint64_t freq = read_cntfrq();
    write_cntp_tval(freq);   // 1초
    write_cntp_ctl(1);       // Enable=1, IMASK=0
}
