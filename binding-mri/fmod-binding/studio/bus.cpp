#include "fmod_bindings.h"
#include "binding-util.h"
#include "debugwriter.h"

DEF_TYPE(Bus);
Bus::~Bus()
{
    // Debug() << "Warning: Bus deconstructed (garbage collected?)";
}

VALUE rb_cBus = Qnil;

FMOD_VALID_FUNC(FMOD_Studio_Bus, Bus);

FMOD_ID_FUNC(FMOD_Studio_Bus, Bus);

FMOD_PATH_FUNC(FMOD_Studio_Bus, Bus);

FMOD_VOLUME_FUNC(FMOD_Studio_Bus, Bus);

FMOD_PAUSED_FUNC(FMOD_Studio_Bus, Bus);

RB_METHOD(busStopAllEvents)
{
    int mode;
    rb_get_args(argc, argv, "i", &mode RB_ARG_END);

    Bus *b = getPrivateData<Bus>(self);

    FMOD_RESULT result = FMOD_Studio_Bus_StopAllEvents(
        b->p, (FMOD_STUDIO_STOP_MODE)mode);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(busGetPortIndex)
{
    RB_UNUSED_PARAM;

    Bus *b = getPrivateData<Bus>(self);
    unsigned long long port;

    FMOD_RESULT result = FMOD_Studio_Bus_GetPortIndex(
        b->p, &port);

    FMOD_RESULT_CONVERT(port, ULL2NUM);
}

RB_METHOD(busSetPortIndex)
{
    unsigned long long port;
    VALUE rb_port;
    rb_get_args(argc, argv, "o", &port RB_ARG_END);
    port = NUM2ULL(rb_port); //? Hack since mkxp doesn't support ull's from rb_get_args

    Bus *b = getPrivateData<Bus>(self);

    FMOD_RESULT result = FMOD_Studio_Bus_SetPortIndex(
        b->p, port);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(busLockChannelGroup)
{
    RB_UNUSED_PARAM;
    Bus *b = getPrivateData<Bus>(self);

    FMOD_RESULT result = FMOD_Studio_Bus_LockChannelGroup(
        b->p);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(busUnlockChannelGroup)
{
    RB_UNUSED_PARAM;
    Bus *b = getPrivateData<Bus>(self);

    FMOD_RESULT result = FMOD_Studio_Bus_UnlockChannelGroup(
        b->p);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(busGetChannelGroup) {
    // TODO
}

FMOD_CPU_USAGE_FUNC(FMOD_Studio_Bus, Bus);
FMOD_MEMORY_USAGE_FUNC(FMOD_Studio_Bus, Bus);

FMOD_EQUAL_FUNC(Bus);

void bindFmodStudioBus()
{
    rb_cBus = rb_define_class_under(rb_mFMOD_Studio, "Bus", rb_cObject);
    rb_define_alloc_func(rb_cBus, classAllocate<&BusType>);
    _rb_define_method(rb_cBus, "initialize", fmodErrorInit);
    _rb_define_method(rb_cBus, "==", fmodEqual);

    _rb_define_method(rb_cBus, "is_valid", fmodIsValid);
    _rb_define_method(rb_cBus, "get_id", fmodGetID);
    _rb_define_method(rb_cBus, "get_path", fmodGetPath);
    _rb_define_method(rb_cBus, "get_volume", fmodGetVolume);
    _rb_define_method(rb_cBus, "set_volume", fmodSetVolume);
    _rb_define_method(rb_cBus, "get_paused", fmodGetPaused);
    _rb_define_method(rb_cBus, "set_paused", fmodSetPaused);
    _rb_define_method(rb_cBus, "stop_all_events", busStopAllEvents);
    _rb_define_method(rb_cBus, "get_port_index", busGetPortIndex);
    _rb_define_method(rb_cBus, "set_port_index", busSetPortIndex);
    _rb_define_method(rb_cBus, "lock_channelgroup", busLockChannelGroup);
    _rb_define_method(rb_cBus, "unlock_channelgroup", busUnlockChannelGroup);
    _rb_define_method(rb_cBus, "get_channelgroup", busGetChannelGroup);
    _rb_define_method(rb_cBus, "get_cpu_usage", fmodGetCPUUsage);
    _rb_define_method(rb_cBus, "get_memory_usage", fmodGetMemoryUsage);
}
