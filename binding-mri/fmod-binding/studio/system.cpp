#include "binding-util.h"
#include "fmod_bindings.h"
#ifdef AUTO_CLEAN_FMOD
#include "debugwriter.h"
#include <fmod_errors.h>
#endif

DEF_TYPE(StudioSystem);
StudioSystem::~StudioSystem()
{
    #ifdef AUTO_CLEAN_FMOD
    Debug() << "Warning: auto releasing studio system (garbage collected?)";
    Debug() << "Studio system release result: " << FMOD_ErrorString(FMOD_Studio_System_Release(p));
    #endif
}

FMOD_VALID_FUNC(FMOD_Studio_System, StudioSystem);

RB_METHOD(systemSetAdvancedSettings) {
    VALUE rb_settings;
    rb_get_args(argc, argv, "o", &rb_settings);

    FMOD_STUDIO_ADVANCEDSETTINGS settings = rb2FMOD_STUDIO_ADVANCEDSETTINGS(rb_settings);
    StudioSystem *b = getPrivateData<StudioSystem>(self);

    FMOD_RESULT result = FMOD_Studio_System_SetAdvancedSettings(b->p, &settings);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(systemGetAdvancedSettings) {
    RB_UNUSED_PARAM;

    FMOD_STUDIO_ADVANCEDSETTINGS settings = FMOD_STUDIO_ADVANCEDSETTINGS();
    StudioSystem *b = getPrivateData<StudioSystem>(self);

    FMOD_RESULT result = FMOD_Studio_System_GetAdvancedSettings(b->p, &settings);

    FMOD_RESULT_NO_WRAP(settings, FMOD_STUDIO_ADVANCEDSETTINGS);
}

//! Need to define custom new function because Ruby
//! does not allow for custom return values from initialize.
RB_METHOD(systemNew) {
    int maxchannels;
    int studioflags;
    int flags;
    rb_get_args(argc, argv, "iii", &maxchannels, &studioflags, &flags RB_ARG_END);

    FMOD_STUDIO_SYSTEM *system = NULL;
    FMOD_RESULT result = FMOD_Studio_System_Create(&system, FMOD_VERSION);

    if (result == FMOD_OK) {
        result = FMOD_Studio_System_Initialize(system, maxchannels, studioflags, flags, NULL);
    }

    FMOD_RESULT_BASE;
    if (result == FMOD_OK) {
        VALUE self = rb_obj_alloc(rb_cStudioSystem); //! Manually allocate the object
        setPrivateData(self, new StudioSystem(system));
        rb_ary_push(return_ary, self);
    }
    FMOD_RESULT_RET;
}

RB_METHOD(systemRelease) {
    RB_UNUSED_PARAM;

    StudioSystem *b = getPrivateData<StudioSystem>(self);

    FMOD_RESULT result = FMOD_Studio_System_Release(b->p);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(systemUpdate) {
    RB_UNUSED_PARAM;

    StudioSystem *b = getPrivateData<StudioSystem>(self);

    FMOD_RESULT result = FMOD_Studio_System_Update(b->p);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(systemGetCoreSystem) {
    RB_UNUSED_PARAM;

    StudioSystem *b = getPrivateData<StudioSystem>(self);
    FMOD_SYSTEM *system = NULL;

    FMOD_RESULT result = FMOD_Studio_System_GetCoreSystem(b->p, &system);

    FMOD_RESULT_WRAP(system, System);
}

#define GET_PATHORID \
char* pathorid; \
rb_get_args(argc, argv, "z", &pathorid RB_ARG_END);

RB_METHOD(systemGetEvent) {
    GET_PATHORID;

    StudioSystem *b = getPrivateData<StudioSystem>(self);
    FMOD_STUDIO_EVENTDESCRIPTION *event = NULL;

    FMOD_RESULT result = FMOD_Studio_System_GetEvent(b->p, pathorid, &event);

    FMOD_RESULT_WRAP(event, EventDescription);
}

RB_METHOD(systemGetBus) {
    GET_PATHORID;

    StudioSystem *b = getPrivateData<StudioSystem>(self);
    FMOD_STUDIO_BUS *bus = NULL;

    FMOD_RESULT result = FMOD_Studio_System_GetBus(b->p, pathorid, &bus);

    FMOD_RESULT_WRAP(bus, Bus);
}

RB_METHOD(systemGetVCA) {
    GET_PATHORID;

    StudioSystem *b = getPrivateData<StudioSystem>(self);
    FMOD_STUDIO_VCA *vca = NULL;

    FMOD_RESULT result = FMOD_Studio_System_GetVCA(b->p, pathorid, &vca);

    FMOD_RESULT_WRAP(vca, VCA);
}

RB_METHOD(systemGetBank) {
    GET_PATHORID;

    StudioSystem *b = getPrivateData<StudioSystem>(self);
    FMOD_STUDIO_BANK *bank = NULL;

    FMOD_RESULT result = FMOD_Studio_System_GetBank(b->p, pathorid, &bank);

    FMOD_RESULT_WRAP(bank, Bank);
}

#define GET_ID \
VALUE rb_id; \
rb_get_args(argc, argv, "o", &rb_id RB_ARG_END); \
FMOD_GUID id = rb2FMOD_GUID(rb_id);

RB_METHOD(systemGetEventByID) {
    GET_ID;

    StudioSystem *b = getPrivateData<StudioSystem>(self);
    FMOD_STUDIO_EVENTDESCRIPTION *event = NULL;

    FMOD_RESULT result = FMOD_Studio_System_GetEventByID(b->p, &id, &event);

    FMOD_RESULT_WRAP(event, EventDescription);
}

RB_METHOD(systemGetBusByID) {
    GET_ID;

    StudioSystem *b = getPrivateData<StudioSystem>(self);
    FMOD_STUDIO_BUS *bus = NULL;

    FMOD_RESULT result = FMOD_Studio_System_GetBusByID(b->p, &id, &bus);

    FMOD_RESULT_WRAP(bus, Bus);
}

RB_METHOD(systemGetVCAByID) {
    GET_ID;

    StudioSystem *b = getPrivateData<StudioSystem>(self);
    FMOD_STUDIO_VCA *vca = NULL;

    FMOD_RESULT result = FMOD_Studio_System_GetVCAByID(b->p, &id, &vca);

    FMOD_RESULT_WRAP(vca, VCA);
}

RB_METHOD(systemGetBankByID) {
    GET_ID;

    StudioSystem *b = getPrivateData<StudioSystem>(self);
    FMOD_STUDIO_BANK *bank = NULL;

    FMOD_RESULT result = FMOD_Studio_System_GetBankByID(b->p, &id, &bank);

    FMOD_RESULT_WRAP(bank, Bank);
}

RB_METHOD(systemGetSoundInfo) {
    char* key;
    rb_get_args(argc, argv, "z", &key RB_ARG_END);

    StudioSystem *b = getPrivateData<StudioSystem>(self);
    FMOD_STUDIO_SOUND_INFO info = FMOD_STUDIO_SOUND_INFO();

    FMOD_RESULT result = FMOD_Studio_System_GetSoundInfo(b->p, key, &info);

    FMOD_RESULT_NO_WRAP(info, FMOD_STUDIO_SOUND_INFO);
}

RB_METHOD(systemGetParameterDescriptionName) {
    char* name;
    rb_get_args(argc, argv, "z", &name RB_ARG_END);

    StudioSystem *b = getPrivateData<StudioSystem>(self);
    FMOD_STUDIO_PARAMETER_DESCRIPTION description = FMOD_STUDIO_PARAMETER_DESCRIPTION();

    FMOD_RESULT result = FMOD_Studio_System_GetParameterDescriptionByName(b->p, name, &description);

    FMOD_RESULT_NO_WRAP(description, FMOD_STUDIO_PARAMETER_DESCRIPTION);
}

RB_METHOD(systemGetParameterDescriptionID) {
    VALUE rb_id;
    rb_get_args(argc, argv, "o", &rb_id RB_ARG_END);

    FMOD_STUDIO_PARAMETER_ID id = rb2FMOD_STUDIO_PARAMETER_ID(rb_id);
    StudioSystem *b = getPrivateData<StudioSystem>(self);
    FMOD_STUDIO_PARAMETER_DESCRIPTION description = FMOD_STUDIO_PARAMETER_DESCRIPTION();

    FMOD_RESULT result = FMOD_Studio_System_GetParameterDescriptionByID(b->p, id, &description);

    FMOD_RESULT_NO_WRAP(description, FMOD_STUDIO_PARAMETER_DESCRIPTION);
}

RB_METHOD(systemGetParameterLabelByName) {
    char* name;
    int labelindex;
    rb_get_args(argc, argv, "zi", &name, &labelindex RB_ARG_END);

    StudioSystem *b = getPrivateData<StudioSystem>(self);
    char* label = NULL;
    int retrieved;

    FMOD_RESULT result = FMOD_Studio_System_GetParameterLabelByName(b->p, name, labelindex, NULL, 0 , &retrieved);

    if (result == FMOD_OK) {
        label = new char[retrieved];

        result = FMOD_Studio_System_GetParameterLabelByName(b->p, name, labelindex, label, retrieved, &retrieved);
    }

    FMOD_RESULT_CONVERT(label, rb_str_new_cstr);
}

RB_METHOD(systemGetParameterLabelByID) {
    VALUE rb_id;
    int labelindex;
    rb_get_args(argc, argv, "zoi", &rb_id, &labelindex RB_ARG_END);

    FMOD_STUDIO_PARAMETER_ID id = rb2FMOD_STUDIO_PARAMETER_ID(rb_id);
    StudioSystem *b = getPrivateData<StudioSystem>(self);
    char* label = NULL;
    int retrieved;

    FMOD_RESULT result = FMOD_Studio_System_GetParameterLabelByID(b->p, id, labelindex, NULL, 0 , &retrieved);

    if (result == FMOD_OK) {
        label = new char[retrieved];

        result = FMOD_Studio_System_GetParameterLabelByID(b->p, id, labelindex, label, retrieved, &retrieved);
    }

    FMOD_RESULT_CONVERT(label, rb_str_new_cstr);
}

#define RETURN_PARAMETER                              \
    FMOD_RESULT_BASE;                                 \
    if (result == FMOD_OK)                            \
    {                                                 \
        rb_ary_push(return_ary, DBL2NUM(value));      \
        rb_ary_push(return_ary, DBL2NUM(finalvalue)); \
    }                                                 \
    FMOD_RESULT_RET;

RB_METHOD(systemGetParameterByID) {
    VALUE rb_id;
    rb_get_args(argc, argv, "o", &rb_id RB_ARG_END);

    FMOD_STUDIO_PARAMETER_ID id = rb2FMOD_STUDIO_PARAMETER_ID(rb_id);
    StudioSystem *b = getPrivateData<StudioSystem>(self);
    float value, finalvalue;

    FMOD_RESULT result = FMOD_Studio_System_GetParameterByID(b->p, id, &value, &finalvalue);

    RETURN_PARAMETER;
}

RB_METHOD(systemSetParameterByID) {
    VALUE rb_id;
    float value;
    bool ignoreseekspeed;
    rb_get_args(argc, argv, "ofb", &rb_id, &value, &ignoreseekspeed RB_ARG_END);

    FMOD_STUDIO_PARAMETER_ID id = rb2FMOD_STUDIO_PARAMETER_ID(rb_id);
    StudioSystem *b = getPrivateData<StudioSystem>(self);
    FMOD_RESULT result = FMOD_Studio_System_SetParameterByID(
        b->p, id, value, (FMOD_BOOL) ignoreseekspeed);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(systemSetParameterByIDWithLabel) {
    VALUE rb_id;
    char* label;
    bool ignoreseekspeed;
    rb_get_args(argc, argv, "ozfb", &rb_id, &label, &ignoreseekspeed RB_ARG_END);

    FMOD_STUDIO_PARAMETER_ID id = rb2FMOD_STUDIO_PARAMETER_ID(rb_id);
    StudioSystem *b = getPrivateData<StudioSystem>(self);
    FMOD_RESULT result = FMOD_Studio_System_SetParameterByIDWithLabel(
        b->p, id, label, (FMOD_BOOL) ignoreseekspeed);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(systemSetParametersByIDs) {
    VALUE rb_ids;
    VALUE rb_values;
    bool ignoreseekspeed;
    rb_get_args(argc, argv, "oob", &rb_ids, &rb_values, &ignoreseekspeed RB_ARG_END);

    if (rb_array_len(rb_values) != rb_array_len(rb_ids))
    {
        rb_raise(rb_eArgError, "Array lengths must match");
    }
    int count = rb_array_len(rb_values);

    float* values = new float[count];
    FMOD_STUDIO_PARAMETER_ID* ids = new FMOD_STUDIO_PARAMETER_ID[count];
    for (int i = 0; i < count; i++)
    {
        ids[i] = rb2FMOD_STUDIO_PARAMETER_ID(rb_ary_entry(rb_ids, i));
        values[i] = NUM2DBL(rb_ary_entry(rb_values, i));
    }

    StudioSystem *b = getPrivateData<StudioSystem>(self);
    FMOD_RESULT result = FMOD_Studio_System_SetParametersByIDs(
        b->p, ids, values, count, (FMOD_BOOL) ignoreseekspeed);

    delete[] ids;
    delete[] values;
    FMOD_RESULT_SIMPLE;
}

RB_METHOD(systemGetParameterByName) {
    char* name;
    rb_get_args(argc, argv, "z", &name RB_ARG_END);

    StudioSystem *b = getPrivateData<StudioSystem>(self);
    float value, finalvalue;

    FMOD_RESULT result = FMOD_Studio_System_GetParameterByName(b->p, name, &value, &finalvalue);

    RETURN_PARAMETER;
}

RB_METHOD(systemSetParameterByName) {
    char* name;
    float value;
    bool ignoreseekspeed;
    rb_get_args(argc, argv, "zfb", &name, &value, &ignoreseekspeed RB_ARG_END);

    StudioSystem *b = getPrivateData<StudioSystem>(self);
    FMOD_RESULT result = FMOD_Studio_System_SetParameterByName(
        b->p, name, value, (FMOD_BOOL) ignoreseekspeed);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(systemSetParameterByNameWithLabel) {
    char* name;
    char* label;
    bool ignoreseekspeed;
    rb_get_args(argc, argv, "zzb", &name, &label, &ignoreseekspeed RB_ARG_END);

    StudioSystem *b = getPrivateData<StudioSystem>(self);
    FMOD_RESULT result = FMOD_Studio_System_SetParameterByNameWithLabel(
        b->p, name, label, (FMOD_BOOL) ignoreseekspeed);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(systemLookupID) {
    char* path;
    rb_get_args(argc, argv, "z", &path RB_ARG_END);

    StudioSystem *b = getPrivateData<StudioSystem>(self);
    FMOD_GUID id = FMOD_GUID();
    FMOD_RESULT result = FMOD_Studio_System_LookupID(b->p, path, &id);

    FMOD_RESULT_NO_WRAP(id, FMOD_GUID);
}

RB_METHOD(systemLookupPath) {
    VALUE rb_id;
    rb_get_args(argc, argv, "o", &rb_id RB_ARG_END);

    FMOD_GUID id = rb2FMOD_GUID(rb_id);
    StudioSystem *b = getPrivateData<StudioSystem>(self);
    char* path = NULL;
    int retrieved;

    FMOD_RESULT result = FMOD_Studio_System_LookupPath(b->p, &id, NULL, 0, &retrieved);

    if (result == FMOD_OK)
    {
        path = new char[retrieved];
        result = FMOD_Studio_System_LookupPath(b->p, &id, path, retrieved, &retrieved);
    }

    FMOD_RESULT_CONVERT(path, rb_str_new_cstr);
}

RB_METHOD(systemGetNumListeners) {
    RB_UNUSED_PARAM;

    StudioSystem *b = getPrivateData<StudioSystem>(self);
    int numlisteners;

    FMOD_RESULT result = FMOD_Studio_System_GetNumListeners(b->p, &numlisteners);

    FMOD_RESULT_CONVERT(numlisteners, INT2NUM);
}

RB_METHOD(systemSetNumListeners) {
    int numlisteners;
    rb_get_args(argc, argv, "i", &numlisteners RB_ARG_END);

    StudioSystem *b = getPrivateData<StudioSystem>(self);

    FMOD_RESULT result = FMOD_Studio_System_SetNumListeners(b->p, numlisteners);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(systemGetListenerAttributes) {
    int listener;
    rb_get_args(argc, argv, "i", &listener RB_ARG_END);

    StudioSystem *b = getPrivateData<StudioSystem>(self);
    FMOD_3D_ATTRIBUTES attributes = FMOD_3D_ATTRIBUTES();
    FMOD_VECTOR attenuationposition = FMOD_VECTOR();

    FMOD_RESULT result = FMOD_Studio_System_GetListenerAttributes(b->p, listener, &attributes, &attenuationposition);

    FMOD_RESULT_BASE;
    if (result == FMOD_OK) {
        rb_ary_push(return_ary, fmodFMOD_3D_ATTRIBUTES2rb(attributes));
        rb_ary_push(return_ary, fmodFMOD_VECTOR2rb(attenuationposition));
    }
    FMOD_RESULT_RET;
}

RB_METHOD(systemSetListenerAttributes) {
    int listener;
    VALUE rb_attributes, rb_attenuationposition;
    rb_get_args(argc, argv, "ioo", &listener, &rb_attributes, &rb_attenuationposition RB_ARG_END);

    StudioSystem *b = getPrivateData<StudioSystem>(self);
    FMOD_3D_ATTRIBUTES attributes = rb2FMOD_3D_ATTRIBUTES(rb_attributes);
    FMOD_VECTOR attenuationposition = rb2FMOD_VECTOR(rb_attenuationposition);

    FMOD_RESULT result = FMOD_Studio_System_SetListenerAttributes(b->p, listener, &attributes, &attenuationposition);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(systemGetListenerWeight) {
    int listener;
    rb_get_args(argc, argv, "i", &listener RB_ARG_END);

    StudioSystem *b = getPrivateData<StudioSystem>(self);
    float weight;

    FMOD_RESULT result = FMOD_Studio_System_GetListenerWeight(b->p, listener, &weight);

    FMOD_RESULT_CONVERT(weight, DBL2NUM);
}

RB_METHOD(systemSetListenerWeight) {
    int listener;
    float weight;
    rb_get_args(argc, argv, "if", &listener, &weight RB_ARG_END);

    StudioSystem *b = getPrivateData<StudioSystem>(self);

    FMOD_RESULT result = FMOD_Studio_System_SetListenerWeight(b->p, listener, weight);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(systemLoadBankFile) {
    const char* filename;
    int flags;

    rb_get_args(argc, argv, "zi", &filename, &flags RB_ARG_END);

    StudioSystem *b = getPrivateData<StudioSystem>(self);

    //? Initialize bank as a NULL pointer
    FMOD_STUDIO_BANK* bank = NULL;
    //? Load bank
    FMOD_RESULT result = FMOD_Studio_System_LoadBankFile(
        b->p, filename, flags, &bank
    );

    //? Wrap bank result and return it
    FMOD_RESULT_WRAP(bank, Bank);
}

RB_METHOD(systemLoadBankMemory) {
    char* buffer;
    int flags;
    rb_get_args(argc, argv, "zi", &buffer, &flags RB_ARG_END);
    int length = strlen(buffer); //! Unsafe bad very bad

    StudioSystem *b = getPrivateData<StudioSystem>(self);
    FMOD_STUDIO_BANK *bank = NULL;

    FMOD_RESULT result = FMOD_Studio_System_LoadBankMemory(
        b->p, buffer, length, FMOD_STUDIO_LOAD_MEMORY, flags, &bank
    );

    FMOD_RESULT_WRAP(bank, Bank);
}

RB_METHOD(systemLoadBankCustom) {
    // TODO
}

RB_METHOD(systemRegisterPlugin) {
    // TODO
}

RB_METHOD(systemUnregisterPlugin) {
    char* name;
    rb_get_args(argc, argv, "z", &name RB_ARG_END);

    StudioSystem *b = getPrivateData<StudioSystem>(self);

    FMOD_RESULT result = FMOD_Studio_System_UnregisterPlugin(b->p, name);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(systemUnloadAll) {
    RB_UNUSED_PARAM;

    StudioSystem *b = getPrivateData<StudioSystem>(self);

    FMOD_RESULT result = FMOD_Studio_System_UnloadAll(b->p);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(systemFlushCommands) {
    RB_UNUSED_PARAM;

    StudioSystem *b = getPrivateData<StudioSystem>(self);

    FMOD_RESULT result = FMOD_Studio_System_FlushCommands(b->p);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(systemFlushSampleLoading) {
    RB_UNUSED_PARAM;

    StudioSystem *b = getPrivateData<StudioSystem>(self);

    FMOD_RESULT result = FMOD_Studio_System_FlushSampleLoading(b->p);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(systemStartCommandCapture) {
    char* filename;
    int flags;

    rb_get_args(argc, argv, "zi", &filename, &flags RB_ARG_END);

    StudioSystem *b = getPrivateData<StudioSystem>(self);

    FMOD_RESULT result = FMOD_Studio_System_StartCommandCapture(b->p, filename, flags);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(systemStopCommandCapture) {
    RB_UNUSED_PARAM;

    StudioSystem *b = getPrivateData<StudioSystem>(self);

    FMOD_RESULT result = FMOD_Studio_System_StopCommandCapture(b->p);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(systemLoadCommandReplay) {
    char* filename;
    int flags;

    rb_get_args(argc, argv, "zi", &filename, &flags RB_ARG_END);

    StudioSystem *b = getPrivateData<StudioSystem>(self);

    FMOD_STUDIO_COMMANDREPLAY *replay = NULL;

    FMOD_RESULT result = FMOD_Studio_System_LoadCommandReplay(
        b->p, filename, flags, &replay
    );

    FMOD_RESULT_WRAP(replay, CommandReplay);
}

RB_METHOD(systemGetBankCount) {
    RB_UNUSED_PARAM;

    StudioSystem *b = getPrivateData<StudioSystem>(self);

    int count;
    FMOD_RESULT result = FMOD_Studio_System_GetBankCount(b->p, &count);

    FMOD_RESULT_CONVERT(count, INT2NUM);
}

RB_METHOD(systemGetBankList) {
    RB_UNUSED_PARAM;

    StudioSystem *b = getPrivateData<StudioSystem>(self);

    int count;
    FMOD_STUDIO_BANK **array = NULL;
    FMOD_RESULT result = FMOD_Studio_System_GetBankCount(b->p, &count);

    if (result == FMOD_OK)
    {
        array = new FMOD_STUDIO_BANK *[count];

        result = FMOD_Studio_System_GetBankList(
            b->p, array, count, NULL);
    }

    FMOD_RESULT_BASE;
    if (array && result == FMOD_OK)
    {
        VALUE bank_ary = rb_ary_new();

        for (int i = 0; i < count; i++)
        {
            VALUE ele = rb_obj_alloc(rb_cBank);
            setPrivateData(ele, new Bank(array[i]));
            rb_ary_push(bank_ary, ele);
        }

        rb_ary_push(return_ary, bank_ary);
        delete array;
    }
    FMOD_RESULT_RET;
}

RB_METHOD(systemGetParameterDescriptionCount) {
    RB_UNUSED_PARAM;

    StudioSystem *b = getPrivateData<StudioSystem>(self);

    int count;
    FMOD_RESULT result = FMOD_Studio_System_GetParameterDescriptionCount(b->p, &count);

    FMOD_RESULT_CONVERT(count, INT2NUM);
}

RB_METHOD(systemGetParameterDescriptionList) {
    RB_UNUSED_PARAM;

    StudioSystem *b = getPrivateData<StudioSystem>(self);

    int count;
    FMOD_STUDIO_PARAMETER_DESCRIPTION *array = NULL;
    FMOD_RESULT result = FMOD_Studio_System_GetParameterDescriptionCount(b->p, &count);

    if (result == FMOD_OK)
    {
        array = new FMOD_STUDIO_PARAMETER_DESCRIPTION[count];

        result = FMOD_Studio_System_GetParameterDescriptionList(
            b->p, array, count, NULL);
    }

    FMOD_RESULT_BASE;
    if (array && result == FMOD_OK)
    {
        VALUE param_ary = rb_ary_new();

        for (int i = 0; i < count; i++)
        {
            VALUE ele = fmodFMOD_STUDIO_PARAMETER_DESCRIPTION2rb(array[i]);
            rb_ary_push(param_ary, ele);
        }

        rb_ary_push(return_ary, param_ary);
        delete[] array;
    }
    FMOD_RESULT_RET;
}

RB_METHOD(systemGetCPUUsage) {
    RB_UNUSED_PARAM;

    StudioSystem *b = getPrivateData<StudioSystem>(self);

    FMOD_STUDIO_CPU_USAGE usage = FMOD_STUDIO_CPU_USAGE();
    FMOD_CPU_USAGE core_usage = FMOD_CPU_USAGE();
    FMOD_RESULT result = FMOD_Studio_System_GetCPUUsage(b->p, &usage, &core_usage);

    FMOD_RESULT_BASE;
    if (result == FMOD_OK) {
        rb_ary_push(return_ary, fmodFMOD_STUDIO_CPU_USAGE2rb(usage));
        rb_ary_push(return_ary, fmodFMOD_CPU_USAGE2rb(core_usage));
    }
    FMOD_RESULT_RET;
}

RB_METHOD(systemGetBufferUsage) {
    RB_UNUSED_PARAM;

    StudioSystem *b = getPrivateData<StudioSystem>(self);

    FMOD_STUDIO_BUFFER_USAGE usage = FMOD_STUDIO_BUFFER_USAGE();
    FMOD_RESULT result = FMOD_Studio_System_GetBufferUsage(b->p, &usage);

    FMOD_RESULT_NO_WRAP(usage, FMOD_STUDIO_BUFFER_USAGE);
}

RB_METHOD(systemSetCallback) {
    // TODO
}

FMOD_USERDATA_FUNC(FMOD_Studio_System, StudioSystem);

FMOD_MEMORY_USAGE_FUNC(FMOD_Studio_System, StudioSystem);

FMOD_EQUAL_FUNC(StudioSystem);

VALUE rb_cStudioSystem = Qnil;

void bindFmodStudioSystem() {
    rb_cStudioSystem = rb_define_class_under(rb_mFMOD_Studio, "System", rb_cObject);
    rb_define_alloc_func(rb_cStudioSystem, classAllocate<&StudioSystemType>);
    _rb_define_method(rb_cStudioSystem, "==", fmodEqual);

    _rb_define_module_function(rb_cStudioSystem, "new", systemNew);
    _rb_define_method(rb_cStudioSystem, "is_valid", fmodIsValid);
    _rb_define_method(rb_cStudioSystem, "set_advanced_settings", systemSetAdvancedSettings);
    _rb_define_method(rb_cStudioSystem, "get_advanced_settings", systemGetAdvancedSettings);
    _rb_define_method(rb_cStudioSystem, "release", systemRelease);
    _rb_define_method(rb_cStudioSystem, "update", systemUpdate);
    _rb_define_method(rb_cStudioSystem, "get_core_system", systemGetCoreSystem);
    _rb_define_method(rb_cStudioSystem, "get_event", systemGetEvent);
    _rb_define_method(rb_cStudioSystem, "get_bus", systemGetBus);
    _rb_define_method(rb_cStudioSystem, "get_vca", systemGetVCA);
    _rb_define_method(rb_cStudioSystem, "get_bank", systemGetBank);
    _rb_define_method(rb_cStudioSystem, "get_event_by_id", systemGetEventByID);
    _rb_define_method(rb_cStudioSystem, "get_bus_by_id", systemGetBusByID);
    _rb_define_method(rb_cStudioSystem, "get_vca_by_id", systemGetVCAByID);
    _rb_define_method(rb_cStudioSystem, "get_bank_by_id", systemGetBankByID);
    _rb_define_method(rb_cStudioSystem, "get_sound_info", systemGetSoundInfo);
    _rb_define_method(rb_cStudioSystem, "get_parameter_description_by_name", systemGetParameterDescriptionName);
    _rb_define_method(rb_cStudioSystem, "get_parameter_description_by_id", systemGetParameterDescriptionID);
    _rb_define_method(rb_cStudioSystem, "get_parameter_label_by_name", systemGetParameterLabelByName);
    _rb_define_method(rb_cStudioSystem, "get_parameter_label_by_id", systemGetParameterLabelByID);
    _rb_define_method(rb_cStudioSystem, "get_parameter_by_id", systemGetParameterByID);
    _rb_define_method(rb_cStudioSystem, "set_parameter_by_id", systemSetParameterByID);
    _rb_define_method(rb_cStudioSystem, "set_parameter_by_id_with_label", systemSetParameterByIDWithLabel);
    _rb_define_method(rb_cStudioSystem, "set_parameters_by_ids", systemSetParametersByIDs);
    _rb_define_method(rb_cStudioSystem, "get_parameter_by_name", systemGetParameterByName);
    _rb_define_method(rb_cStudioSystem, "set_parameter_by_name", systemSetParameterByName);
    _rb_define_method(rb_cStudioSystem, "set_parameter_by_name_with_label", systemSetParameterByNameWithLabel);
    _rb_define_method(rb_cStudioSystem, "lookup_id", systemLookupID);
    _rb_define_method(rb_cStudioSystem, "lookup_path", systemLookupPath);
    _rb_define_method(rb_cStudioSystem, "get_num_listeners", systemGetNumListeners);
    _rb_define_method(rb_cStudioSystem, "set_num_listeners", systemSetNumListeners);
    _rb_define_method(rb_cStudioSystem, "get_listener_attributes", systemGetListenerAttributes);
    _rb_define_method(rb_cStudioSystem, "set_listener_attributes", systemSetListenerAttributes);
    _rb_define_method(rb_cStudioSystem, "get_listener_weight", systemGetListenerWeight);
    _rb_define_method(rb_cStudioSystem, "set_listener_weight", systemSetListenerWeight);
    _rb_define_method(rb_cStudioSystem, "load_bank_file", systemLoadBankFile);
    _rb_define_method(rb_cStudioSystem, "load_bank_memory", systemLoadBankMemory);
    _rb_define_method(rb_cStudioSystem, "load_bank_custom", systemLoadBankCustom);
    _rb_define_method(rb_cStudioSystem, "register_plugin", systemRegisterPlugin);
    _rb_define_method(rb_cStudioSystem, "unregister_plugin", systemUnregisterPlugin);
    _rb_define_method(rb_cStudioSystem, "unload_all", systemUnloadAll);
    _rb_define_method(rb_cStudioSystem, "flush_commands", systemFlushCommands);
    _rb_define_method(rb_cStudioSystem, "flush_sample_loading", systemFlushSampleLoading);
    _rb_define_method(rb_cStudioSystem, "start_command_capture", systemStartCommandCapture);
    _rb_define_method(rb_cStudioSystem, "stop_command_capture", systemStopCommandCapture);
    _rb_define_method(rb_cStudioSystem, "load_command_replay", systemLoadCommandReplay);
    _rb_define_method(rb_cStudioSystem, "get_bank_count", systemGetBankCount);
    _rb_define_method(rb_cStudioSystem, "get_bank_list", systemGetBankList);
    _rb_define_method(rb_cStudioSystem, "get_parameter_description_count", systemGetParameterDescriptionCount);
    _rb_define_method(rb_cStudioSystem, "get_parameter_description_list", systemGetParameterDescriptionList);
    _rb_define_method(rb_cStudioSystem, "get_cpu_usage", systemGetCPUUsage);
    _rb_define_method(rb_cStudioSystem, "get_buffer_usage", systemGetBufferUsage);
    _rb_define_method(rb_cStudioSystem, "set_callback", systemSetCallback);
    _rb_define_method(rb_cStudioSystem, "set_user_data", fmodSetUserData);
    _rb_define_method(rb_cStudioSystem, "get_user_data", fmodGetUserData);
    _rb_define_method(rb_cStudioSystem, "get_memory_usage", fmodGetMemoryUsage);
}
