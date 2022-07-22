#include "fmod_bindings.h"
#include "binding-util.h"
#ifdef AUTO_CLEAN_FMOD
#include "debugwriter.h"
#include <fmod_errors.h>
#endif

DEF_TYPE(EventInstance);
EventInstance::~EventInstance()
{
#ifdef AUTO_CLEAN_FMOD
    Debug() << "Warning: auto releasing event instance (garbage collected?)";
    Debug() << "Event instance release result: " << FMOD_ErrorString(FMOD_Studio_EventInstance_Release(p));
#endif
}

FMOD_VALID_FUNC(FMOD_Studio_EventInstance, EventInstance);

RB_METHOD(eventInstanceGetDescription)
{
    RB_UNUSED_PARAM;

    EventInstance *b = getPrivateData<EventInstance>(self);
    FMOD_STUDIO_EVENTDESCRIPTION *description = NULL;

    FMOD_RESULT result = FMOD_Studio_EventInstance_GetDescription(
        b->p, &description);

    FMOD_RESULT_WRAP(description, EventDescription);
}

FMOD_VOLUME_FUNC(FMOD_Studio_EventInstance, EventInstance);

RB_METHOD(eventInstanceGetPitch)
{
    RB_UNUSED_PARAM;

    EventInstance *b = getPrivateData<EventInstance>(self);
    float pitch;
    float finalpitch;

    FMOD_RESULT result = FMOD_Studio_EventInstance_GetPitch(b->p, &pitch, &finalpitch);

    FMOD_RESULT_BASE;
    if (result == FMOD_OK)
    {
        rb_ary_push(return_ary, DBL2NUM(pitch));
        rb_ary_push(return_ary, DBL2NUM(finalpitch));
    }
    FMOD_RESULT_RET;
}

RB_METHOD(eventInstanceSetPitch)
{
    float pitch;
    rb_get_args(argc, argv, "f", &pitch RB_ARG_END);

    EventInstance *b = getPrivateData<EventInstance>(self);

    FMOD_RESULT result = FMOD_Studio_EventInstance_SetPitch(b->p, pitch);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(eventInstanceGet3DAttributes)
{
    RB_UNUSED_PARAM;

    EventInstance *b = getPrivateData<EventInstance>(self);
    FMOD_3D_ATTRIBUTES attributes = FMOD_3D_ATTRIBUTES();

    FMOD_RESULT result = FMOD_Studio_EventInstance_Get3DAttributes(b->p, &attributes);

    FMOD_RESULT_NO_WRAP(attributes, FMOD_3D_ATTRIBUTES);
}

RB_METHOD(eventInstanceSet3DAttributes)
{
    VALUE rb_attributes;
    rb_get_args(argc, argv, "o", &rb_attributes RB_ARG_END);

    FMOD_3D_ATTRIBUTES attributes = rb2FMOD_3D_ATTRIBUTES(rb_attributes);
    EventInstance *b = getPrivateData<EventInstance>(self);

    FMOD_RESULT result = FMOD_Studio_EventInstance_Set3DAttributes(b->p, &attributes);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(eventInstanceGetListenerMask)
{
    RB_UNUSED_PARAM;

    EventInstance *b = getPrivateData<EventInstance>(self);
    unsigned int mask;

    FMOD_RESULT result = FMOD_Studio_EventInstance_GetListenerMask(b->p, &mask);

    FMOD_RESULT_CONVERT(mask, UINT2NUM);
}

RB_METHOD(eventInstanceSetListenerMask)
{
    VALUE mask;
    rb_get_args(argc, argv, "o", &mask RB_ARG_END);

    EventInstance *b = getPrivateData<EventInstance>(self);

    FMOD_RESULT result = FMOD_Studio_EventInstance_SetListenerMask(b->p, NUM2UINT(mask));

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(eventInstanceGetProperty)
{
    int index;
    rb_get_args(argc, argv, "i", &index RB_ARG_END);

    EventInstance *b = getPrivateData<EventInstance>(self);
    float value;

    FMOD_RESULT result = FMOD_Studio_EventInstance_GetProperty(
        b->p, (FMOD_STUDIO_EVENT_PROPERTY)index, &value);

    FMOD_RESULT_CONVERT(value, DBL2NUM);
}

RB_METHOD(eventInstanceSetProperty)
{
    int index;
    float value;
    rb_get_args(argc, argv, "if", &index, &value RB_ARG_END);

    EventInstance *b = getPrivateData<EventInstance>(self);

    FMOD_RESULT result = FMOD_Studio_EventInstance_SetProperty(
        b->p, (FMOD_STUDIO_EVENT_PROPERTY)index, value);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(eventInstanceGetReverbLevel)
{
    int index;
    rb_get_args(argc, argv, "i", &index RB_ARG_END);

    EventInstance *b = getPrivateData<EventInstance>(self);
    float level;

    FMOD_RESULT result = FMOD_Studio_EventInstance_GetReverbLevel(
        b->p, index, &level);

    FMOD_RESULT_CONVERT(level, DBL2NUM);
}

RB_METHOD(eventInstanceSetReverbLevel)
{
    int index;
    float level;
    rb_get_args(argc, argv, "if", &index, &level RB_ARG_END);

    EventInstance *b = getPrivateData<EventInstance>(self);

    FMOD_RESULT result = FMOD_Studio_EventInstance_SetReverbLevel(
        b->p, index, level);

    FMOD_RESULT_SIMPLE;
}

FMOD_PAUSED_FUNC(FMOD_Studio_EventInstance, EventInstance);

RB_METHOD(eventInstanceStart)
{
    RB_UNUSED_PARAM;

    EventInstance *b = getPrivateData<EventInstance>(self);

    FMOD_RESULT result = FMOD_Studio_EventInstance_Start(b->p);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(eventInstanceStop)
{
    int mode;
    rb_get_args(argc, argv, "i", &mode RB_ARG_END);

    EventInstance *b = getPrivateData<EventInstance>(self);

    FMOD_RESULT result = FMOD_Studio_EventInstance_Stop(b->p, (FMOD_STUDIO_STOP_MODE)mode);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(eventInstanceGetTimelinePosition)
{
    RB_UNUSED_PARAM;

    EventInstance *b = getPrivateData<EventInstance>(self);
    int position;

    FMOD_RESULT result = FMOD_Studio_EventInstance_GetTimelinePosition(b->p, &position);

    FMOD_RESULT_CONVERT(position, INT2NUM);
}

RB_METHOD(eventInstanceSetTimelinePosition)
{
    int position;
    rb_get_args(argc, argv, "i", &position RB_ARG_END);

    EventInstance *b = getPrivateData<EventInstance>(self);

    FMOD_RESULT result = FMOD_Studio_EventInstance_SetTimelinePosition(b->p, position);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(eventInstanceGetChannelGroup)
{
    // TODO
}

RB_METHOD(eventInstanceGetMinMaxDistance)
{
    RB_UNUSED_PARAM;

    EventInstance *b = getPrivateData<EventInstance>(self);
    float min;
    float max;

    FMOD_RESULT result = FMOD_Studio_EventInstance_GetMinMaxDistance(
        b->p, &min, &max);

    FMOD_RESULT_BASE;
    if (result == FMOD_OK)
    {
        rb_ary_push(return_ary, DBL2NUM(min));
        rb_ary_push(return_ary, DBL2NUM(max));
    }
    FMOD_RESULT_RET;
}

RB_METHOD(eventInstanceRelease)
{
    RB_UNUSED_PARAM;

    EventInstance *b = getPrivateData<EventInstance>(self);

    FMOD_RESULT result = FMOD_Studio_EventInstance_Release(b->p);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(eventInstanceIsVirtual)
{
    RB_UNUSED_PARAM;

    EventInstance *b = getPrivateData<EventInstance>(self);
    FMOD_BOOL isVirtual;

    FMOD_RESULT result = FMOD_Studio_EventInstance_IsVirtual(b->p, &isVirtual);

    FMOD_RESULT_CONVERT(isVirtual, BOOL2RB);
}

#define RETURN_PARAMETER                              \
    FMOD_RESULT_BASE;                                 \
    if (result == FMOD_OK)                            \
    {                                                 \
        rb_ary_push(return_ary, DBL2NUM(value));      \
        rb_ary_push(return_ary, DBL2NUM(finalvalue)); \
    }                                                 \
    FMOD_RESULT_RET;

RB_METHOD(eventInstanceGetParameterByName)
{
    char *name;
    rb_get_args(argc, argv, "z", &name RB_ARG_END);

    EventInstance *b = getPrivateData<EventInstance>(self);
    float value, finalvalue;

    FMOD_RESULT result = FMOD_Studio_EventInstance_GetParameterByName(
        b->p, name, &value, &finalvalue);

    RETURN_PARAMETER;
}

RB_METHOD(eventInstanceSetParameterByName)
{
    char *name;
    float value;
    bool ignoreseekspeed;
    rb_get_args(argc, argv, "zfb", &name, &value, &ignoreseekspeed RB_ARG_END);

    EventInstance *b = getPrivateData<EventInstance>(self);
    FMOD_RESULT result = FMOD_Studio_EventInstance_SetParameterByName(
        b->p, name, value, (FMOD_BOOL)ignoreseekspeed);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(eventInstanceSetParameterByNameLabel)
{
    char *name;
    char *label;
    bool ignoreseekspeed;
    rb_get_args(argc, argv, "zfb", &name, &label, &ignoreseekspeed RB_ARG_END);

    EventInstance *b = getPrivateData<EventInstance>(self);
    FMOD_RESULT result = FMOD_Studio_EventInstance_SetParameterByNameWithLabel(
        b->p, name, label, (FMOD_BOOL)ignoreseekspeed);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(eventInstanceGetParameterByID)
{
    VALUE rb_id;
    rb_get_args(argc, argv, "o", &rb_id RB_ARG_END);

    FMOD_STUDIO_PARAMETER_ID id = rb2FMOD_STUDIO_PARAMETER_ID(rb_id);
    EventInstance *b = getPrivateData<EventInstance>(self);
    float value, finalvalue;

    FMOD_RESULT result = FMOD_Studio_EventInstance_GetParameterByID(
        b->p, id, &value, &finalvalue);

    RETURN_PARAMETER;
}

RB_METHOD(eventInstanceSetParameterByID)
{
    VALUE rb_id;
    float value;
    bool ignoreseekspeed;
    rb_get_args(argc, argv, "ofb", &rb_id, &value, &ignoreseekspeed RB_ARG_END);

    FMOD_STUDIO_PARAMETER_ID id = rb2FMOD_STUDIO_PARAMETER_ID(rb_id);
    EventInstance *b = getPrivateData<EventInstance>(self);
    FMOD_RESULT result = FMOD_Studio_EventInstance_SetParameterByID(
        b->p, id, value, (FMOD_BOOL)ignoreseekspeed);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(eventInstanceSetParameterByIDLabel)
{
    VALUE rb_id;
    char *label;
    bool ignoreseekspeed;
    rb_get_args(argc, argv, "ozfb", &rb_id, &label, &ignoreseekspeed RB_ARG_END);

    FMOD_STUDIO_PARAMETER_ID id = rb2FMOD_STUDIO_PARAMETER_ID(rb_id);
    EventInstance *b = getPrivateData<EventInstance>(self);
    FMOD_RESULT result = FMOD_Studio_EventInstance_SetParameterByIDWithLabel(
        b->p, id, label, (FMOD_BOOL)ignoreseekspeed);

    FMOD_RESULT_SIMPLE;
}

//! Here be dragons
RB_METHOD(eventInstanceSetParametersByIDs)
{
    //! Get ruby arrays
    VALUE rb_ids;
    VALUE rb_values;
    bool ignoreseekspeed;
    rb_get_args(argc, argv, "oob", &rb_ids, &rb_values, &ignoreseekspeed RB_ARG_END);

    //! Check lengths are equal
    if (rb_array_len(rb_values) != rb_array_len(rb_ids))
    {
        rb_raise(rb_eArgError, "Array lengths must match");
    }
    //! Get length of arrays
    int count = rb_array_len(rb_values);

    //! Create C side arrays
    float *values = new float[count];
    FMOD_STUDIO_PARAMETER_ID *ids = new FMOD_STUDIO_PARAMETER_ID[count];
    //! Convert ruby arrays to C side arrays
    for (int i = 0; i < count; i++)
    {
        ids[i] = rb2FMOD_STUDIO_PARAMETER_ID(rb_ary_entry(rb_ids, i));
        values[i] = NUM2DBL(rb_ary_entry(rb_values, i));
    }

    //! Call the function
    EventInstance *b = getPrivateData<EventInstance>(self);
    FMOD_RESULT result = FMOD_Studio_EventInstance_SetParametersByIDs(
        b->p, ids, values, count, (FMOD_BOOL)ignoreseekspeed);

    //! Clean up
    delete[] ids;
    delete[] values;
    FMOD_RESULT_SIMPLE;
}

RB_METHOD(eventInstanceKeyOff)
{
    RB_UNUSED_PARAM;

    EventInstance *b = getPrivateData<EventInstance>(self);

    FMOD_RESULT result = FMOD_Studio_EventInstance_KeyOff(b->p);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(eventInstanceSetCallback)
{
    // TODO
}

FMOD_USERDATA_FUNC(FMOD_Studio_EventInstance, EventInstance);

FMOD_CPU_USAGE_FUNC(FMOD_Studio_EventInstance, EventInstance);

FMOD_MEMORY_USAGE_FUNC(FMOD_Studio_EventInstance, EventInstance);

FMOD_EQUAL_FUNC(EventInstance);

VALUE rb_cEventInstance = Qnil;

void bindFmodStudioEventInstance()
{
    rb_cEventInstance = rb_define_class_under(
        rb_mFMOD_Studio, "EventInstance", rb_cObject);
    rb_define_alloc_func(rb_cEventInstance, classAllocate<&EventInstanceType>);
    _rb_define_method(rb_cEventInstance, "initialize", fmodErrorInit);
    _rb_define_method(rb_cEventInstance, "==", fmodEqual);

    _rb_define_method(rb_cEventInstance, "is_valid", fmodIsValid);
    _rb_define_method(rb_cEventInstance, "get_description", eventInstanceGetDescription);
    _rb_define_method(rb_cEventInstance, "get_volume", fmodGetVolume);
    _rb_define_method(rb_cEventInstance, "set_volume", fmodSetVolume);
    _rb_define_method(rb_cEventInstance, "get_pitch", eventInstanceGetPitch);
    _rb_define_method(rb_cEventInstance, "set_pitch", eventInstanceSetPitch);
    _rb_define_method(rb_cEventInstance, "get_3d_attributes", eventInstanceGet3DAttributes);
    _rb_define_method(rb_cEventInstance, "set_3d_attributes", eventInstanceSet3DAttributes);
    _rb_define_method(rb_cEventInstance, "get_listener_mask", eventInstanceGetListenerMask);
    _rb_define_method(rb_cEventInstance, "set_listener_mask", eventInstanceSetListenerMask);
    _rb_define_method(rb_cEventInstance, "get_property", eventInstanceGetProperty);
    _rb_define_method(rb_cEventInstance, "set_property", eventInstanceSetProperty);
    _rb_define_method(rb_cEventInstance, "get_reverb_level", eventInstanceGetReverbLevel);
    _rb_define_method(rb_cEventInstance, "set_reverb_level", eventInstanceSetReverbLevel);
    _rb_define_method(rb_cEventInstance, "get_paused", fmodGetPaused);
    _rb_define_method(rb_cEventInstance, "set_paused", fmodSetPaused);
    _rb_define_method(rb_cEventInstance, "start", eventInstanceStart);
    _rb_define_method(rb_cEventInstance, "stop", eventInstanceStop);
    _rb_define_method(rb_cEventInstance, "get_timeline_position", eventInstanceGetTimelinePosition);
    _rb_define_method(rb_cEventInstance, "set_timeline_position", eventInstanceSetTimelinePosition);
    _rb_define_method(rb_cEventInstance, "get_channel_group", eventInstanceGetChannelGroup);
    _rb_define_method(rb_cEventInstance, "get_min_max_distance", eventInstanceGetMinMaxDistance);
    _rb_define_method(rb_cEventInstance, "release", eventInstanceRelease);
    _rb_define_method(rb_cEventInstance, "is_virtual", eventInstanceIsVirtual);
    _rb_define_method(rb_cEventInstance, "get_parameter_by_name", eventInstanceGetParameterByName);
    _rb_define_method(rb_cEventInstance, "set_parameter_by_name", eventInstanceSetParameterByName);
    _rb_define_method(
        rb_cEventInstance, "set_parameter_by_name_with_label", eventInstanceSetParameterByNameLabel);
    _rb_define_method(rb_cEventInstance, "get_parameter_by_id", eventInstanceGetParameterByID);
    _rb_define_method(rb_cEventInstance, "set_parameter_by_id", eventInstanceSetParameterByID);
    _rb_define_method(
        rb_cEventInstance, "set_parameter_by_id_with_label", eventInstanceSetParameterByIDLabel);
    _rb_define_method(rb_cEventInstance, "set_parameters_by_ids", eventInstanceSetParametersByIDs);
    _rb_define_method(rb_cEventInstance, "key_off", eventInstanceKeyOff);
    _rb_define_method(rb_cEventInstance, "set_callback", eventInstanceSetCallback);
    _rb_define_method(rb_cEventInstance, "get_user_data", fmodGetUserData);
    _rb_define_method(rb_cEventInstance, "set_user_data", fmodSetUserData);
    _rb_define_method(rb_cEventInstance, "get_cpu_usage", fmodGetCPUUsage);
    _rb_define_method(rb_cEventInstance, "get_memory_usage", fmodGetMemoryUsage);
}
