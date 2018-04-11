/* This file is autogenerated by tracetool, do not edit. */

#ifndef TRACE_TARGET_PPC_GENERATED_TRACERS_H
#define TRACE_TARGET_PPC_GENERATED_TRACERS_H

#include "qemu-common.h"
#include "trace/control.h"

extern TraceEvent _TRACE_KVM_FAILED_SPR_SET_EVENT;
extern TraceEvent _TRACE_KVM_FAILED_SPR_GET_EVENT;
extern uint16_t _TRACE_KVM_FAILED_SPR_SET_DSTATE;
extern uint16_t _TRACE_KVM_FAILED_SPR_GET_DSTATE;
#define TRACE_KVM_FAILED_SPR_SET_ENABLED 1
#define TRACE_KVM_FAILED_SPR_GET_ENABLED 1
#include "qemu/log.h"


static inline void _nocheck__trace_kvm_failed_spr_set(int str, const char * msg)
{
    if (trace_event_get_state(TRACE_KVM_FAILED_SPR_SET)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log_mask(LOG_TRACE,
                      "%d@%zd.%06zd:kvm_failed_spr_set " "Warning: Unable to set SPR %d to KVM: %s" "\n",
                      getpid(),
                      (size_t)_now.tv_sec, (size_t)_now.tv_usec
                      , str, msg);
    }
}

static inline void trace_kvm_failed_spr_set(int str, const char * msg)
{
    if (true) {
        _nocheck__trace_kvm_failed_spr_set(str, msg);
    }
}

static inline void _nocheck__trace_kvm_failed_spr_get(int str, const char * msg)
{
    if (trace_event_get_state(TRACE_KVM_FAILED_SPR_GET)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log_mask(LOG_TRACE,
                      "%d@%zd.%06zd:kvm_failed_spr_get " "Warning: Unable to retrieve SPR %d from KVM: %s" "\n",
                      getpid(),
                      (size_t)_now.tv_sec, (size_t)_now.tv_usec
                      , str, msg);
    }
}

static inline void trace_kvm_failed_spr_get(int str, const char * msg)
{
    if (true) {
        _nocheck__trace_kvm_failed_spr_get(str, msg);
    }
}
#endif /* TRACE_TARGET_PPC_GENERATED_TRACERS_H */
