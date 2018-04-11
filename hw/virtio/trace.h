/* This file is autogenerated by tracetool, do not edit. */

#ifndef TRACE_HW_VIRTIO_GENERATED_TRACERS_H
#define TRACE_HW_VIRTIO_GENERATED_TRACERS_H

#include "qemu-common.h"
#include "trace/control.h"

extern TraceEvent _TRACE_VIRTQUEUE_ALLOC_ELEMENT_EVENT;
extern TraceEvent _TRACE_VIRTQUEUE_FILL_EVENT;
extern TraceEvent _TRACE_VIRTQUEUE_FLUSH_EVENT;
extern TraceEvent _TRACE_VIRTQUEUE_POP_EVENT;
extern TraceEvent _TRACE_VIRTIO_QUEUE_NOTIFY_EVENT;
extern TraceEvent _TRACE_VIRTIO_NOTIFY_IRQFD_EVENT;
extern TraceEvent _TRACE_VIRTIO_NOTIFY_EVENT;
extern TraceEvent _TRACE_VIRTIO_SET_STATUS_EVENT;
extern TraceEvent _TRACE_VIRTIO_RNG_GUEST_NOT_READY_EVENT;
extern TraceEvent _TRACE_VIRTIO_RNG_CPU_IS_STOPPED_EVENT;
extern TraceEvent _TRACE_VIRTIO_RNG_POPPED_EVENT;
extern TraceEvent _TRACE_VIRTIO_RNG_PUSHED_EVENT;
extern TraceEvent _TRACE_VIRTIO_RNG_REQUEST_EVENT;
extern TraceEvent _TRACE_VIRTIO_RNG_VM_STATE_CHANGE_EVENT;
extern TraceEvent _TRACE_VIRTIO_BALLOON_BAD_ADDR_EVENT;
extern TraceEvent _TRACE_VIRTIO_BALLOON_HANDLE_OUTPUT_EVENT;
extern TraceEvent _TRACE_VIRTIO_BALLOON_GET_CONFIG_EVENT;
extern TraceEvent _TRACE_VIRTIO_BALLOON_SET_CONFIG_EVENT;
extern TraceEvent _TRACE_VIRTIO_BALLOON_TO_TARGET_EVENT;
extern uint16_t _TRACE_VIRTQUEUE_ALLOC_ELEMENT_DSTATE;
extern uint16_t _TRACE_VIRTQUEUE_FILL_DSTATE;
extern uint16_t _TRACE_VIRTQUEUE_FLUSH_DSTATE;
extern uint16_t _TRACE_VIRTQUEUE_POP_DSTATE;
extern uint16_t _TRACE_VIRTIO_QUEUE_NOTIFY_DSTATE;
extern uint16_t _TRACE_VIRTIO_NOTIFY_IRQFD_DSTATE;
extern uint16_t _TRACE_VIRTIO_NOTIFY_DSTATE;
extern uint16_t _TRACE_VIRTIO_SET_STATUS_DSTATE;
extern uint16_t _TRACE_VIRTIO_RNG_GUEST_NOT_READY_DSTATE;
extern uint16_t _TRACE_VIRTIO_RNG_CPU_IS_STOPPED_DSTATE;
extern uint16_t _TRACE_VIRTIO_RNG_POPPED_DSTATE;
extern uint16_t _TRACE_VIRTIO_RNG_PUSHED_DSTATE;
extern uint16_t _TRACE_VIRTIO_RNG_REQUEST_DSTATE;
extern uint16_t _TRACE_VIRTIO_RNG_VM_STATE_CHANGE_DSTATE;
extern uint16_t _TRACE_VIRTIO_BALLOON_BAD_ADDR_DSTATE;
extern uint16_t _TRACE_VIRTIO_BALLOON_HANDLE_OUTPUT_DSTATE;
extern uint16_t _TRACE_VIRTIO_BALLOON_GET_CONFIG_DSTATE;
extern uint16_t _TRACE_VIRTIO_BALLOON_SET_CONFIG_DSTATE;
extern uint16_t _TRACE_VIRTIO_BALLOON_TO_TARGET_DSTATE;
#define TRACE_VIRTQUEUE_ALLOC_ELEMENT_ENABLED 1
#define TRACE_VIRTQUEUE_FILL_ENABLED 1
#define TRACE_VIRTQUEUE_FLUSH_ENABLED 1
#define TRACE_VIRTQUEUE_POP_ENABLED 1
#define TRACE_VIRTIO_QUEUE_NOTIFY_ENABLED 1
#define TRACE_VIRTIO_NOTIFY_IRQFD_ENABLED 1
#define TRACE_VIRTIO_NOTIFY_ENABLED 1
#define TRACE_VIRTIO_SET_STATUS_ENABLED 1
#define TRACE_VIRTIO_RNG_GUEST_NOT_READY_ENABLED 1
#define TRACE_VIRTIO_RNG_CPU_IS_STOPPED_ENABLED 1
#define TRACE_VIRTIO_RNG_POPPED_ENABLED 1
#define TRACE_VIRTIO_RNG_PUSHED_ENABLED 1
#define TRACE_VIRTIO_RNG_REQUEST_ENABLED 1
#define TRACE_VIRTIO_RNG_VM_STATE_CHANGE_ENABLED 1
#define TRACE_VIRTIO_BALLOON_BAD_ADDR_ENABLED 1
#define TRACE_VIRTIO_BALLOON_HANDLE_OUTPUT_ENABLED 1
#define TRACE_VIRTIO_BALLOON_GET_CONFIG_ENABLED 1
#define TRACE_VIRTIO_BALLOON_SET_CONFIG_ENABLED 1
#define TRACE_VIRTIO_BALLOON_TO_TARGET_ENABLED 1
#include "qemu/log.h"


static inline void _nocheck__trace_virtqueue_alloc_element(void * elem, size_t sz, unsigned in_num, unsigned out_num)
{
    if (trace_event_get_state(TRACE_VIRTQUEUE_ALLOC_ELEMENT)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log_mask(LOG_TRACE,
                      "%d@%zd.%06zd:virtqueue_alloc_element " "elem %p size %zd in_num %u out_num %u" "\n",
                      getpid(),
                      (size_t)_now.tv_sec, (size_t)_now.tv_usec
                      , elem, sz, in_num, out_num);
    }
}

static inline void trace_virtqueue_alloc_element(void * elem, size_t sz, unsigned in_num, unsigned out_num)
{
    if (true) {
        _nocheck__trace_virtqueue_alloc_element(elem, sz, in_num, out_num);
    }
}

static inline void _nocheck__trace_virtqueue_fill(void * vq, const void * elem, unsigned int len, unsigned int idx)
{
    if (trace_event_get_state(TRACE_VIRTQUEUE_FILL)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log_mask(LOG_TRACE,
                      "%d@%zd.%06zd:virtqueue_fill " "vq %p elem %p len %u idx %u" "\n",
                      getpid(),
                      (size_t)_now.tv_sec, (size_t)_now.tv_usec
                      , vq, elem, len, idx);
    }
}

static inline void trace_virtqueue_fill(void * vq, const void * elem, unsigned int len, unsigned int idx)
{
    if (true) {
        _nocheck__trace_virtqueue_fill(vq, elem, len, idx);
    }
}

static inline void _nocheck__trace_virtqueue_flush(void * vq, unsigned int count)
{
    if (trace_event_get_state(TRACE_VIRTQUEUE_FLUSH)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log_mask(LOG_TRACE,
                      "%d@%zd.%06zd:virtqueue_flush " "vq %p count %u" "\n",
                      getpid(),
                      (size_t)_now.tv_sec, (size_t)_now.tv_usec
                      , vq, count);
    }
}

static inline void trace_virtqueue_flush(void * vq, unsigned int count)
{
    if (true) {
        _nocheck__trace_virtqueue_flush(vq, count);
    }
}

static inline void _nocheck__trace_virtqueue_pop(void * vq, void * elem, unsigned int in_num, unsigned int out_num)
{
    if (trace_event_get_state(TRACE_VIRTQUEUE_POP)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log_mask(LOG_TRACE,
                      "%d@%zd.%06zd:virtqueue_pop " "vq %p elem %p in_num %u out_num %u" "\n",
                      getpid(),
                      (size_t)_now.tv_sec, (size_t)_now.tv_usec
                      , vq, elem, in_num, out_num);
    }
}

static inline void trace_virtqueue_pop(void * vq, void * elem, unsigned int in_num, unsigned int out_num)
{
    if (true) {
        _nocheck__trace_virtqueue_pop(vq, elem, in_num, out_num);
    }
}

static inline void _nocheck__trace_virtio_queue_notify(void * vdev, int n, void * vq)
{
    if (trace_event_get_state(TRACE_VIRTIO_QUEUE_NOTIFY)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log_mask(LOG_TRACE,
                      "%d@%zd.%06zd:virtio_queue_notify " "vdev %p n %d vq %p" "\n",
                      getpid(),
                      (size_t)_now.tv_sec, (size_t)_now.tv_usec
                      , vdev, n, vq);
    }
}

static inline void trace_virtio_queue_notify(void * vdev, int n, void * vq)
{
    if (true) {
        _nocheck__trace_virtio_queue_notify(vdev, n, vq);
    }
}

static inline void _nocheck__trace_virtio_notify_irqfd(void * vdev, void * vq)
{
    if (trace_event_get_state(TRACE_VIRTIO_NOTIFY_IRQFD)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log_mask(LOG_TRACE,
                      "%d@%zd.%06zd:virtio_notify_irqfd " "vdev %p vq %p" "\n",
                      getpid(),
                      (size_t)_now.tv_sec, (size_t)_now.tv_usec
                      , vdev, vq);
    }
}

static inline void trace_virtio_notify_irqfd(void * vdev, void * vq)
{
    if (true) {
        _nocheck__trace_virtio_notify_irqfd(vdev, vq);
    }
}

static inline void _nocheck__trace_virtio_notify(void * vdev, void * vq)
{
    if (trace_event_get_state(TRACE_VIRTIO_NOTIFY)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log_mask(LOG_TRACE,
                      "%d@%zd.%06zd:virtio_notify " "vdev %p vq %p" "\n",
                      getpid(),
                      (size_t)_now.tv_sec, (size_t)_now.tv_usec
                      , vdev, vq);
    }
}

static inline void trace_virtio_notify(void * vdev, void * vq)
{
    if (true) {
        _nocheck__trace_virtio_notify(vdev, vq);
    }
}

static inline void _nocheck__trace_virtio_set_status(void * vdev, uint8_t val)
{
    if (trace_event_get_state(TRACE_VIRTIO_SET_STATUS)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log_mask(LOG_TRACE,
                      "%d@%zd.%06zd:virtio_set_status " "vdev %p val %u" "\n",
                      getpid(),
                      (size_t)_now.tv_sec, (size_t)_now.tv_usec
                      , vdev, val);
    }
}

static inline void trace_virtio_set_status(void * vdev, uint8_t val)
{
    if (true) {
        _nocheck__trace_virtio_set_status(vdev, val);
    }
}

static inline void _nocheck__trace_virtio_rng_guest_not_ready(void * rng)
{
    if (trace_event_get_state(TRACE_VIRTIO_RNG_GUEST_NOT_READY)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log_mask(LOG_TRACE,
                      "%d@%zd.%06zd:virtio_rng_guest_not_ready " "rng %p: guest not ready" "\n",
                      getpid(),
                      (size_t)_now.tv_sec, (size_t)_now.tv_usec
                      , rng);
    }
}

static inline void trace_virtio_rng_guest_not_ready(void * rng)
{
    if (true) {
        _nocheck__trace_virtio_rng_guest_not_ready(rng);
    }
}

static inline void _nocheck__trace_virtio_rng_cpu_is_stopped(void * rng, int size)
{
    if (trace_event_get_state(TRACE_VIRTIO_RNG_CPU_IS_STOPPED)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log_mask(LOG_TRACE,
                      "%d@%zd.%06zd:virtio_rng_cpu_is_stopped " "rng %p: cpu is stopped, dropping %d bytes" "\n",
                      getpid(),
                      (size_t)_now.tv_sec, (size_t)_now.tv_usec
                      , rng, size);
    }
}

static inline void trace_virtio_rng_cpu_is_stopped(void * rng, int size)
{
    if (true) {
        _nocheck__trace_virtio_rng_cpu_is_stopped(rng, size);
    }
}

static inline void _nocheck__trace_virtio_rng_popped(void * rng)
{
    if (trace_event_get_state(TRACE_VIRTIO_RNG_POPPED)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log_mask(LOG_TRACE,
                      "%d@%zd.%06zd:virtio_rng_popped " "rng %p: elem popped" "\n",
                      getpid(),
                      (size_t)_now.tv_sec, (size_t)_now.tv_usec
                      , rng);
    }
}

static inline void trace_virtio_rng_popped(void * rng)
{
    if (true) {
        _nocheck__trace_virtio_rng_popped(rng);
    }
}

static inline void _nocheck__trace_virtio_rng_pushed(void * rng, size_t len)
{
    if (trace_event_get_state(TRACE_VIRTIO_RNG_PUSHED)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log_mask(LOG_TRACE,
                      "%d@%zd.%06zd:virtio_rng_pushed " "rng %p: %zd bytes pushed" "\n",
                      getpid(),
                      (size_t)_now.tv_sec, (size_t)_now.tv_usec
                      , rng, len);
    }
}

static inline void trace_virtio_rng_pushed(void * rng, size_t len)
{
    if (true) {
        _nocheck__trace_virtio_rng_pushed(rng, len);
    }
}

static inline void _nocheck__trace_virtio_rng_request(void * rng, size_t size, unsigned quota)
{
    if (trace_event_get_state(TRACE_VIRTIO_RNG_REQUEST)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log_mask(LOG_TRACE,
                      "%d@%zd.%06zd:virtio_rng_request " "rng %p: %zd bytes requested, %u bytes quota left" "\n",
                      getpid(),
                      (size_t)_now.tv_sec, (size_t)_now.tv_usec
                      , rng, size, quota);
    }
}

static inline void trace_virtio_rng_request(void * rng, size_t size, unsigned quota)
{
    if (true) {
        _nocheck__trace_virtio_rng_request(rng, size, quota);
    }
}

static inline void _nocheck__trace_virtio_rng_vm_state_change(void * rng, int running, int state)
{
    if (trace_event_get_state(TRACE_VIRTIO_RNG_VM_STATE_CHANGE)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log_mask(LOG_TRACE,
                      "%d@%zd.%06zd:virtio_rng_vm_state_change " "rng %p: state change to running %d state %d" "\n",
                      getpid(),
                      (size_t)_now.tv_sec, (size_t)_now.tv_usec
                      , rng, running, state);
    }
}

static inline void trace_virtio_rng_vm_state_change(void * rng, int running, int state)
{
    if (true) {
        _nocheck__trace_virtio_rng_vm_state_change(rng, running, state);
    }
}

static inline void _nocheck__trace_virtio_balloon_bad_addr(uint64_t gpa)
{
    if (trace_event_get_state(TRACE_VIRTIO_BALLOON_BAD_ADDR)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log_mask(LOG_TRACE,
                      "%d@%zd.%06zd:virtio_balloon_bad_addr " "%"PRIx64 "\n",
                      getpid(),
                      (size_t)_now.tv_sec, (size_t)_now.tv_usec
                      , gpa);
    }
}

static inline void trace_virtio_balloon_bad_addr(uint64_t gpa)
{
    if (true) {
        _nocheck__trace_virtio_balloon_bad_addr(gpa);
    }
}

static inline void _nocheck__trace_virtio_balloon_handle_output(const char * name, uint64_t gpa)
{
    if (trace_event_get_state(TRACE_VIRTIO_BALLOON_HANDLE_OUTPUT)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log_mask(LOG_TRACE,
                      "%d@%zd.%06zd:virtio_balloon_handle_output " "section name: %s gpa: %"PRIx64 "\n",
                      getpid(),
                      (size_t)_now.tv_sec, (size_t)_now.tv_usec
                      , name, gpa);
    }
}

static inline void trace_virtio_balloon_handle_output(const char * name, uint64_t gpa)
{
    if (true) {
        _nocheck__trace_virtio_balloon_handle_output(name, gpa);
    }
}

static inline void _nocheck__trace_virtio_balloon_get_config(uint32_t num_pages, uint32_t actual)
{
    if (trace_event_get_state(TRACE_VIRTIO_BALLOON_GET_CONFIG)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log_mask(LOG_TRACE,
                      "%d@%zd.%06zd:virtio_balloon_get_config " "num_pages: %d actual: %d" "\n",
                      getpid(),
                      (size_t)_now.tv_sec, (size_t)_now.tv_usec
                      , num_pages, actual);
    }
}

static inline void trace_virtio_balloon_get_config(uint32_t num_pages, uint32_t actual)
{
    if (true) {
        _nocheck__trace_virtio_balloon_get_config(num_pages, actual);
    }
}

static inline void _nocheck__trace_virtio_balloon_set_config(uint32_t actual, uint32_t oldactual)
{
    if (trace_event_get_state(TRACE_VIRTIO_BALLOON_SET_CONFIG)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log_mask(LOG_TRACE,
                      "%d@%zd.%06zd:virtio_balloon_set_config " "actual: %d oldactual: %d" "\n",
                      getpid(),
                      (size_t)_now.tv_sec, (size_t)_now.tv_usec
                      , actual, oldactual);
    }
}

static inline void trace_virtio_balloon_set_config(uint32_t actual, uint32_t oldactual)
{
    if (true) {
        _nocheck__trace_virtio_balloon_set_config(actual, oldactual);
    }
}

static inline void _nocheck__trace_virtio_balloon_to_target(uint64_t target, uint32_t num_pages)
{
    if (trace_event_get_state(TRACE_VIRTIO_BALLOON_TO_TARGET)) {
        struct timeval _now;
        gettimeofday(&_now, NULL);
        qemu_log_mask(LOG_TRACE,
                      "%d@%zd.%06zd:virtio_balloon_to_target " "balloon target: %"PRIx64" num_pages: %d" "\n",
                      getpid(),
                      (size_t)_now.tv_sec, (size_t)_now.tv_usec
                      , target, num_pages);
    }
}

static inline void trace_virtio_balloon_to_target(uint64_t target, uint32_t num_pages)
{
    if (true) {
        _nocheck__trace_virtio_balloon_to_target(target, num_pages);
    }
}
#endif /* TRACE_HW_VIRTIO_GENERATED_TRACERS_H */
