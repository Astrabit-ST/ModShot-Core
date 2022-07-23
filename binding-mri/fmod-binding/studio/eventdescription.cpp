#include "fmod_bindings.h"
#include "binding-util.h"
#include "debugwriter.h"

DEF_TYPE(EventDescription);
EventDescription::~EventDescription()
{
}

VALUE rb_cEventDescription = Qnil;

FMOD_VALID_FUNC(FMOD_Studio_EventDescription, EventDescription);

FMOD_ID_FUNC(FMOD_Studio_EventDescription, EventDescription);

FMOD_PATH_FUNC(FMOD_Studio_EventDescription, EventDescription);

RB_METHOD(descriptionGetParameterCount)
{
    RB_UNUSED_PARAM;

    EventDescription *b = getPrivateData<EventDescription>(self);
    int count;

    FMOD_RESULT result = FMOD_Studio_EventDescription_GetParameterDescriptionCount(
        b->p, &count);

    FMOD_RESULT_CONVERT(count, INT2NUM);
}

RB_METHOD(descriptionGetParameterIndex)
{
    int index;
    rb_get_args(argc, argv, "i", &index RB_ARG_END);

    EventDescription *b = getPrivateData<EventDescription>(self);
    FMOD_STUDIO_PARAMETER_DESCRIPTION description = FMOD_STUDIO_PARAMETER_DESCRIPTION();

    FMOD_RESULT result = FMOD_Studio_EventDescription_GetParameterDescriptionByIndex(
        b->p, index, &description);

    FMOD_RESULT_NO_WRAP(description, FMOD_STUDIO_PARAMETER_DESCRIPTION);
}

RB_METHOD(descriptionGetParameterName)
{
    char *name;
    rb_get_args(argc, argv, "z", &name RB_ARG_END);

    EventDescription *b = getPrivateData<EventDescription>(self);
    FMOD_STUDIO_PARAMETER_DESCRIPTION description = FMOD_STUDIO_PARAMETER_DESCRIPTION();

    FMOD_RESULT result = FMOD_Studio_EventDescription_GetParameterDescriptionByName(
        b->p, name, &description);

    FMOD_RESULT_NO_WRAP(description, FMOD_STUDIO_PARAMETER_DESCRIPTION);
}

RB_METHOD(descriptionGetParameterID)
{
    VALUE rb_id;
    rb_get_args(argc, argv, "o", &rb_id RB_ARG_END);

    FMOD_STUDIO_PARAMETER_ID id = rb2FMOD_STUDIO_PARAMETER_ID(rb_id);
    EventDescription *b = getPrivateData<EventDescription>(self);
    FMOD_STUDIO_PARAMETER_DESCRIPTION description = FMOD_STUDIO_PARAMETER_DESCRIPTION();

    FMOD_RESULT result = FMOD_Studio_EventDescription_GetParameterDescriptionByID(
        b->p, id, &description);

    FMOD_RESULT_NO_WRAP(description, FMOD_STUDIO_PARAMETER_DESCRIPTION);
}

RB_METHOD(descriptionGetParameterLabelIndex)
{
    int index;
    int labelindex;
    rb_get_args(argc, argv, "ii", &index, &labelindex RB_ARG_END);

    EventDescription *b = getPrivateData<EventDescription>(self);
    char *label = NULL;
    int retrieved;

    FMOD_RESULT result = FMOD_Studio_EventDescription_GetParameterLabelByIndex(
        b->p, index, labelindex, NULL, 0, &retrieved);
    if (result == FMOD_OK)
    {
        label = new char[retrieved];

        result = FMOD_Studio_EventDescription_GetParameterLabelByIndex(
            b->p, index, labelindex, label, retrieved, &retrieved);
    }

    FMOD_RESULT_CONVERT(label, rb_str_new_cstr);
}

RB_METHOD(descriptionGetParameterLabelName)
{
    char *name;
    int labelindex;
    rb_get_args(argc, argv, "zi", &name, &labelindex RB_ARG_END);

    EventDescription *b = getPrivateData<EventDescription>(self);
    char *label = NULL;
    int retrieved;

    FMOD_RESULT result = FMOD_Studio_EventDescription_GetParameterLabelByName(
        b->p, name, labelindex, NULL, 0, &retrieved);
    if (result == FMOD_OK)
    {
        label = new char[retrieved];

        result = FMOD_Studio_EventDescription_GetParameterLabelByName(
            b->p, name, labelindex, label, retrieved, &retrieved);
    }

    FMOD_RESULT_CONVERT(label, rb_str_new_cstr);
}

RB_METHOD(descriptionGetParameterLabelID)
{
    VALUE rb_id;
    int labelindex;
    rb_get_args(argc, argv, "oi", &rb_id, &labelindex RB_ARG_END);

    FMOD_STUDIO_PARAMETER_ID id = rb2FMOD_STUDIO_PARAMETER_ID(rb_id);
    EventDescription *b = getPrivateData<EventDescription>(self);
    char *label = NULL;
    int retrieved;

    FMOD_RESULT result = FMOD_Studio_EventDescription_GetParameterLabelByID(
        b->p, id, labelindex, NULL, 0, &retrieved);
    if (result == FMOD_OK)
    {
        label = new char[retrieved];

        result = FMOD_Studio_EventDescription_GetParameterLabelByID(
            b->p, id, labelindex, label, retrieved, &retrieved);
    }

    FMOD_RESULT_CONVERT(label, rb_str_new_cstr);
}

RB_METHOD(descriptionGetUserCount)
{
    RB_UNUSED_PARAM;

    EventDescription *b = getPrivateData<EventDescription>(self);
    int count;

    FMOD_RESULT result = FMOD_Studio_EventDescription_GetUserPropertyCount(
        b->p, &count);

    FMOD_RESULT_CONVERT(count, INT2NUM);
}

RB_METHOD(descriptionGetUserIndex)
{
    int index;
    rb_get_args(argc, argv, "i", &index RB_ARG_END);

    EventDescription *b = getPrivateData<EventDescription>(self);
    FMOD_STUDIO_USER_PROPERTY property = FMOD_STUDIO_USER_PROPERTY();

    FMOD_RESULT result = FMOD_Studio_EventDescription_GetUserPropertyByIndex(
        b->p, index, &property);

    FMOD_RESULT_NO_WRAP(property, FMOD_STUDIO_USER_PROPERTY);
}

RB_METHOD(descriptionGetUser)
{
    char *name;
    rb_get_args(argc, argv, "z", &name RB_ARG_END);

    EventDescription *b = getPrivateData<EventDescription>(self);
    FMOD_STUDIO_USER_PROPERTY property = FMOD_STUDIO_USER_PROPERTY();

    FMOD_RESULT result = FMOD_Studio_EventDescription_GetUserProperty(
        b->p, name, &property);

    FMOD_RESULT_NO_WRAP(property, FMOD_STUDIO_USER_PROPERTY);
}

RB_METHOD(descriptionGetLength)
{
    RB_UNUSED_PARAM;

    EventDescription *b = getPrivateData<EventDescription>(self);
    int length;

    FMOD_RESULT result = FMOD_Studio_EventDescription_GetLength(
        b->p, &length);

    FMOD_RESULT_CONVERT(length, INT2NUM);
}

RB_METHOD(descriptionGetMinMax)
{
    RB_UNUSED_PARAM;

    EventDescription *b = getPrivateData<EventDescription>(self);
    float min;
    float max;

    FMOD_RESULT result = FMOD_Studio_EventDescription_GetMinMaxDistance(
        b->p, &min, &max);

    FMOD_RESULT_BASE;
    if (result == FMOD_OK)
    {
        rb_ary_push(return_ary, DBL2NUM(min));
        rb_ary_push(return_ary, DBL2NUM(max));
    }
    FMOD_RESULT_RET;
}

RB_METHOD(descriptionIsSnapshot)
{
    RB_UNUSED_PARAM;

    EventDescription *b = getPrivateData<EventDescription>(self);
    FMOD_BOOL isSnapshot;

    FMOD_RESULT result = FMOD_Studio_EventDescription_IsSnapshot(
        b->p, &isSnapshot);

    FMOD_RESULT_CONVERT(isSnapshot, BOOL2RB);
}

RB_METHOD(descriptionIsOneshot)
{
    RB_UNUSED_PARAM;

    EventDescription *b = getPrivateData<EventDescription>(self);
    FMOD_BOOL isOneshot;

    FMOD_RESULT result = FMOD_Studio_EventDescription_IsOneshot(
        b->p, &isOneshot);

    FMOD_RESULT_CONVERT(isOneshot, BOOL2RB);
}

RB_METHOD(descriptionIsStream)
{
    RB_UNUSED_PARAM;

    EventDescription *b = getPrivateData<EventDescription>(self);
    FMOD_BOOL isStream;

    FMOD_RESULT result = FMOD_Studio_EventDescription_IsStream(
        b->p, &isStream);

    FMOD_RESULT_CONVERT(isStream, BOOL2RB);
}

RB_METHOD(descriptionIs3D)
{
    RB_UNUSED_PARAM;

    EventDescription *b = getPrivateData<EventDescription>(self);
    FMOD_BOOL is3D;

    FMOD_RESULT result = FMOD_Studio_EventDescription_Is3D(
        b->p, &is3D);

    FMOD_RESULT_CONVERT(is3D, BOOL2RB);
}

RB_METHOD(descriptionDopplerEnabled)
{
    RB_UNUSED_PARAM;

    EventDescription *b = getPrivateData<EventDescription>(self);
    FMOD_BOOL isDopplerEnabled;

    FMOD_RESULT result = FMOD_Studio_EventDescription_IsDopplerEnabled(
        b->p, &isDopplerEnabled);

    FMOD_RESULT_CONVERT(isDopplerEnabled, BOOL2RB);
}

RB_METHOD(descriptionHasSustainPoint)
{
    RB_UNUSED_PARAM;

    EventDescription *b = getPrivateData<EventDescription>(self);
    FMOD_BOOL hasSustainPoint;

    FMOD_RESULT result = FMOD_Studio_EventDescription_HasSustainPoint(
        b->p, &hasSustainPoint);

    FMOD_RESULT_CONVERT(hasSustainPoint, BOOL2RB);
}

RB_METHOD(descriptionCreateInstance)
{
    RB_UNUSED_PARAM;

    EventDescription *b = getPrivateData<EventDescription>(self);
    FMOD_STUDIO_EVENTINSTANCE *instance = NULL;

    FMOD_RESULT result = FMOD_Studio_EventDescription_CreateInstance(
        b->p, &instance);

    FMOD_RESULT_WRAP(instance, EventInstance);
}

RB_METHOD(descriptionGetInstanceCount)
{
    RB_UNUSED_PARAM;

    EventDescription *b = getPrivateData<EventDescription>(self);
    int count;

    FMOD_RESULT result = FMOD_Studio_EventDescription_GetInstanceCount(
        b->p, &count);

    FMOD_RESULT_CONVERT(count, INT2NUM);
}

RB_METHOD(descriptionGetInstanceList)
{
    RB_UNUSED_PARAM;

    EventDescription *b = getPrivateData<EventDescription>(self);
    FMOD_STUDIO_EVENTINSTANCE **array = NULL;
    int count;

    FMOD_RESULT result = FMOD_Studio_EventDescription_GetInstanceCount(
        b->p, &count);


    if (result == FMOD_OK) {
        array = new FMOD_STUDIO_EVENTINSTANCE*[count];
        result = FMOD_Studio_EventDescription_GetInstanceList(
            b->p, array, count, NULL);
    }

    FMOD_RESULT_BASE;
    if (array && result == FMOD_OK)
    {
        VALUE instance_ary = rb_ary_new();

        for (int i = 0; i < count; i++)
        {
            VALUE ele = rb_obj_alloc(rb_cEventInstance);
            setPrivateData(ele, new EventInstance(array[i]));
            rb_ary_push(instance_ary, ele);
        }

        rb_ary_push(return_ary, instance_ary);
        delete array;
    }
    FMOD_RESULT_RET;
}

RB_METHOD(descriptionLoadSampleData)
{
    RB_UNUSED_PARAM;

    EventDescription *b = getPrivateData<EventDescription>(self);
    FMOD_RESULT result = FMOD_Studio_EventDescription_LoadSampleData(
        b->p);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(descriptionUnloadSampleData)
{
    RB_UNUSED_PARAM;

    EventDescription *b = getPrivateData<EventDescription>(self);
    FMOD_RESULT result = FMOD_Studio_EventDescription_UnloadSampleData(
        b->p);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(descriptionGetSampleLoadingState)
{
    RB_UNUSED_PARAM;

    EventDescription *b = getPrivateData<EventDescription>(self);
    FMOD_STUDIO_LOADING_STATE state;

    FMOD_RESULT result = FMOD_Studio_EventDescription_GetSampleLoadingState(
        b->p, &state);

    FMOD_RESULT_CONVERT(state, INT2NUM);
}

RB_METHOD(descriptionReleaseAllInstances)
{
    RB_UNUSED_PARAM;

    EventDescription *b = getPrivateData<EventDescription>(self);
    FMOD_RESULT result = FMOD_Studio_EventDescription_ReleaseAllInstances(
        b->p);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(descriptionSetCallback)
{
    // TODO
}

FMOD_USERDATA_FUNC(FMOD_Studio_EventDescription, EventDescription);

FMOD_EQUAL_FUNC(EventDescription);

void bindFmodStudioEventDescription()
{
    rb_cEventDescription = rb_define_class_under(
        rb_mFMOD_Studio, "EventDescription", rb_cObject);
    rb_define_alloc_func(rb_cEventDescription, classAllocate<&EventDescriptionType>);
    _rb_define_method(rb_cEventDescription, "initialize", fmodErrorInit);
    _rb_define_method(rb_cEventDescription, "==", fmodEqual);

    _rb_define_method(rb_cEventDescription, "is_valid", fmodIsValid);
    _rb_define_method(rb_cEventDescription, "get_id", fmodGetID);
    _rb_define_method(rb_cEventDescription, "get_path", fmodGetPath);
    _rb_define_method(rb_cEventDescription, "get_parameter_description_count", descriptionGetParameterCount);
    _rb_define_method(rb_cEventDescription, "get_parameter_description_by_index", descriptionGetParameterIndex);
    _rb_define_method(rb_cEventDescription, "get_parameter_description_by_name", descriptionGetParameterName);
    _rb_define_method(rb_cEventDescription, "get_parameter_description_by_id", descriptionGetParameterID);
    _rb_define_method(rb_cEventDescription, "get_parameter_label_by_index", descriptionGetParameterLabelIndex);
    _rb_define_method(rb_cEventDescription, "get_parameter_label_by_name", descriptionGetParameterLabelName);
    _rb_define_method(rb_cEventDescription, "get_parameter_label_by_id", descriptionGetParameterLabelID);
    _rb_define_method(rb_cEventDescription, "get_user_property_count", descriptionGetUserCount);
    _rb_define_method(rb_cEventDescription, "get_user_property_by_index", descriptionGetUserIndex);
    _rb_define_method(rb_cEventDescription, "get_user_property", descriptionGetUser);
    _rb_define_method(rb_cEventDescription, "get_length", descriptionGetLength);
    _rb_define_method(rb_cEventDescription, "get_min_max", descriptionGetMinMax);
    _rb_define_method(rb_cEventDescription, "is_snapshot", descriptionIsSnapshot);
    _rb_define_method(rb_cEventDescription, "is_oneshot", descriptionIsOneshot);
    _rb_define_method(rb_cEventDescription, "is_stream", descriptionIsStream);
    _rb_define_method(rb_cEventDescription, "is_3d", descriptionIs3D);
    _rb_define_method(rb_cEventDescription, "is_doppler_enabled", descriptionDopplerEnabled);
    _rb_define_method(rb_cEventDescription, "has_sustain_point", descriptionHasSustainPoint);
    _rb_define_method(rb_cEventDescription, "create_instance", descriptionCreateInstance);
    _rb_define_method(rb_cEventDescription, "get_instance_count", descriptionGetInstanceCount);
    _rb_define_method(rb_cEventDescription, "get_instance_list", descriptionGetInstanceList);
    _rb_define_method(rb_cEventDescription, "load_sample_data", descriptionLoadSampleData);
    _rb_define_method(rb_cEventDescription, "unload_sample_data", descriptionUnloadSampleData);
    _rb_define_method(rb_cEventDescription, "get_sample_loading_state", descriptionGetSampleLoadingState);
    _rb_define_method(rb_cEventDescription, "release_all_instances", descriptionReleaseAllInstances);
    _rb_define_method(rb_cEventDescription, "set_callback", descriptionSetCallback);
    _rb_define_method(rb_cEventDescription, "get_user_data", fmodGetUserData);
    _rb_define_method(rb_cEventDescription, "set_user_data", fmodSetUserData);
}
