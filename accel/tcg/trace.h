/* This file is autogenerated by tracetool, do not edit. */

#ifndef TRACE_ACCEL_TCG_GENERATED_TRACERS_H
#define TRACE_ACCEL_TCG_GENERATED_TRACERS_H

#include "qemu-common.h"
#include "trace/control.h"

extern TraceEvent _TRACE_EXEC_TB_EVENT;
extern TraceEvent _TRACE_EXEC_TB_NOCACHE_EVENT;
extern TraceEvent _TRACE_EXEC_TB_EXIT_EVENT;
extern TraceEvent _TRACE_TRANSLATE_BLOCK_EVENT;
extern uint16_t _TRACE_EXEC_TB_DSTATE;
extern uint16_t _TRACE_EXEC_TB_NOCACHE_DSTATE;
extern uint16_t _TRACE_EXEC_TB_EXIT_DSTATE;
extern uint16_t _TRACE_TRANSLATE_BLOCK_DSTATE;
#define TRACE_EXEC_TB_ENABLED 0
#define TRACE_EXEC_TB_NOCACHE_ENABLED 0
#define TRACE_EXEC_TB_EXIT_ENABLED 0
#define TRACE_TRANSLATE_BLOCK_ENABLED 1
#include "qemu/log.h"


static inline void _nocheck__trace_exec_tb(void * tb, uintptr_t pc)
{
}

static inline void trace_exec_tb(void * tb, uintptr_t pc)
{
    if (true) {
        _nocheck__trace_exec_tb(tb, pc);
    }
}

static inline void _nocheck__trace_exec_tb_nocache(void * tb, uintptr_t pc)
{
}

static inline void trace_exec_tb_nocache(void * tb, uintptr_t pc)
{
    if (true) {
        _nocheck__trace_exec_tb_nocache(tb, pc);
    }
}

static inline void _nocheck__trace_exec_tb_exit(void * last_tb, unsigned int flags)
{
}

static inline void trace_exec_tb_exit(void * last_tb, unsigned int flags)
{
    if (true) {
        _nocheck__trace_exec_tb_exit(last_tb, flags);
    }
}

static inline void _nocheck__trace_translate_block(void * tb, uintptr_t pc, uint8_t * tb_code)
{
    if (trace_event_get_state(TRACE_TRANSLATE_BLOCK)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log_mask(LOG_TRACE,
                      "%d@%zd.%06zd:translate_block " "tb:%p, pc:0x%"PRIxPTR", tb_code:%p" "\n",
                      getpid(),
                      (size_t)_now.tv_sec, (size_t)_now.tv_usec
                      , tb, pc, tb_code);
    }
}

static inline void trace_translate_block(void * tb, uintptr_t pc, uint8_t * tb_code)
{
    if (true) {
        _nocheck__trace_translate_block(tb, pc, tb_code);
    }
}
#endif /* TRACE_ACCEL_TCG_GENERATED_TRACERS_H */
