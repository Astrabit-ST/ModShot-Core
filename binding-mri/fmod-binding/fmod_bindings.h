#ifndef FMOD_BINDINGS_H
#define FMOD_BINDINGS_H

#include "binding-util.h"
#include "common_structs.h"
#include <fmod_studio.h>

//* Bool to ruby converter
#define BOOL2RB(val) ((val) ? Qtrue : Qfalse)
#define RB2BOOL(val) (val == Qtrue)

/*
 * We use wrapper classes since we can't set the private data
 * of the ruby object using setPrivateData<Klass>(klass, self)
 * with most FMOD types (Like FMOD_STUDIO_BANK, etc) since
 * their members are not defined anywhere
 */

#define DEF_FMOD_WRAPPER(Klass, wrap_type) \
    class Klass                            \
    {                                      \
    public:                                \
        wrap_type *p;                      \
                                           \
        Klass(wrap_type *p)                \
            : p(p) {}                      \
                                           \
        ~Klass();                          \
    };

/*
* Return result macros
* These macros cover returning results of function calls in fmod
* Most functions have 2 (or should have 2) return values,
* ordered by an FMOD_RESULT and then the actual return value.
*
* FMOD_RESULT_WRAP is for when we need to wrap an FMOD struct pointer
! but the struct has no defined members (I.e FMOD_STUDIO_BANK)
*
* FMOD_RESULT_CONVERT is for when we need to convert the return value
* using a standard ruby conversion macro (like INT2NUM)
*
* FMOD_RESULT_VALUE is for when we want to add a VALUE to the
* return array.
*
* FMOD_RESULT_NO_CHECK is for when we are almost always returning a value
* and the value could be 0, it also acts like FMOD_RESULT_CONVERT
*
* FMOD_RESULT_NO_WRAP is for when we need to wrap an FMOD struct pointer,
! but the struct has defined members (I.e. FMOD_GUID)
*
* FMOD_RESULT_SIMPLE just returns the result. That's it.
*/
#define FMOD_RESULT_BASE             \
    VALUE return_ary = rb_ary_new(); \
    rb_ary_push(return_ary, INT2NUM(result));

#define FMOD_RESULT_RET return return_ary;

//! We use alloc since it skirts around initializing the object
#define FMOD_RESULT_WRAP(val, wrap)                  \
    FMOD_RESULT_BASE                                 \
    if (result == FMOD_OK)                           \
    {                                                \
        VALUE return_val = rb_obj_alloc(rb_c##wrap); \
        setPrivateData(return_val, new wrap(val));   \
        rb_ary_push(return_ary, return_val);         \
    }                                                \
    FMOD_RESULT_RET

#define FMOD_RESULT_CONVERT(val, convert)      \
    FMOD_RESULT_BASE                           \
    if (result == FMOD_OK)                     \
    {                                          \
        rb_ary_push(return_ary, convert(val)); \
    }                                          \
    FMOD_RESULT_RET

#define FMOD_RESULT_NO_CHECK(val, convert) \
    FMOD_RESULT_BASE                       \
    rb_ary_push(return_ary, convert(val)); \
    FMOD_RESULT_RET

#define FMOD_RESULT_VALUE(val)        \
    FMOD_RESULT_BASE                  \
    if (result == FMOD_OK)            \
    {                                 \
        rb_ary_push(return_ary, val); \
    }                                 \
    FMOD_RESULT_RET

//! We can delete the val (and want to) since it's always a newly
//! allocated struct that this is used for
//! If we don't, and the function did not return ok, we risk a
//! memory leak
#define FMOD_RESULT_NO_WRAP(val, klass)           \
    FMOD_RESULT_BASE                              \
    if (result == FMOD_OK)                        \
    {                                             \
        VALUE return_val = fmod##klass##2rb(val); \
        rb_ary_push(return_ary, return_val);      \
    }                                             \
                                                  \
    FMOD_RESULT_RET

#define FMOD_RESULT_SIMPLE \
    FMOD_RESULT_BASE       \
    FMOD_RESULT_RET

DEF_FMOD_WRAPPER(System, FMOD_SYSTEM)
DECL_TYPE(System);

DEF_FMOD_WRAPPER(StudioSystem, FMOD_STUDIO_SYSTEM);
DECL_TYPE(StudioSystem);

//? Define wrapper for Bank
DEF_FMOD_WRAPPER(Bank, FMOD_STUDIO_BANK);
//? Define ruby data type for Bank
DECL_TYPE(Bank);

DEF_FMOD_WRAPPER(VCA, FMOD_STUDIO_VCA);
DECL_TYPE(VCA);

DEF_FMOD_WRAPPER(Bus, FMOD_STUDIO_BUS);
DECL_TYPE(Bus);

DEF_FMOD_WRAPPER(EventDescription, FMOD_STUDIO_EVENTDESCRIPTION);
DECL_TYPE(EventDescription);

DEF_FMOD_WRAPPER(EventInstance, FMOD_STUDIO_EVENTINSTANCE);
DECL_TYPE(EventInstance);

DEF_FMOD_WRAPPER(CommandReplay, FMOD_STUDIO_COMMANDREPLAY);
DECL_TYPE(CommandReplay);

// * Modules and classes to be defined under
extern VALUE rb_mFMOD;
extern VALUE rb_mFMOD_Core;
extern VALUE rb_mFMOD_Studio;
extern VALUE rb_cSystem;
extern VALUE rb_cGUID;
DEFINE_CONVERT_FUNC(FMOD_GUID);
extern VALUE rb_c3D_Attributes;
DEFINE_CONVERT_FUNC(FMOD_3D_ATTRIBUTES);
extern VALUE rb_cVector;
DEFINE_CONVERT_FUNC(FMOD_VECTOR);
extern VALUE rb_cCreateSoundExInfo;
DEFINE_CONVERT_FUNC(FMOD_CREATESOUNDEXINFO);
extern VALUE rb_cCPUUsage;
DEFINE_CONVERT_FUNC(FMOD_CPU_USAGE);

extern VALUE rb_cStudioSystem;
extern VALUE rb_cBank;
extern VALUE rb_cVCA;
extern VALUE rb_cBus;
extern VALUE rb_cMemoryUsage;
DEFINE_CONVERT_FUNC(FMOD_STUDIO_MEMORY_USAGE);
extern VALUE rb_cEventDescription;
extern VALUE rb_cParameterID;
DEFINE_CONVERT_FUNC(FMOD_STUDIO_PARAMETER_ID);
extern VALUE rb_cParameterDescription;
DEFINE_CONVERT_FUNC(FMOD_STUDIO_PARAMETER_DESCRIPTION);
extern VALUE rb_cUserProperty;
DEFINE_CONVERT_FUNC(FMOD_STUDIO_USER_PROPERTY);
extern VALUE rb_cEventInstance;
extern VALUE rb_cCommandReplay;
extern VALUE rb_cCommandInfo;
DEFINE_CONVERT_FUNC(FMOD_STUDIO_COMMAND_INFO);
extern VALUE rb_cAdvancedSettings;
DEFINE_CONVERT_FUNC(FMOD_STUDIO_ADVANCEDSETTINGS);
extern VALUE rb_cSoundInfo;
DEFINE_CONVERT_FUNC(FMOD_STUDIO_SOUND_INFO);
extern VALUE rb_cStudioCPUUsage;
DEFINE_CONVERT_FUNC(FMOD_STUDIO_CPU_USAGE);
extern VALUE rb_cBufferUsage;
DEFINE_CONVERT_FUNC(FMOD_STUDIO_BUFFER_USAGE);
extern VALUE rb_cBufferInfo;
DEFINE_CONVERT_FUNC(FMOD_STUDIO_BUFFER_INFO);

void bindFmodStudioBank();
void bindFmodStudioSystem();
void bindFmodStudioStructs();
void bindFmodStudioVCA();
void bindFmodStudioBus();
void bindFmodStudioEventDescription();
void bindFmodStudioEventInstance();
void bindFmodStudioCommandReplay();

void bindFmodSystem();
void bindFmodCoreStructs();

inline RB_METHOD(fmodErrorInit)
{
    rb_raise(rb_eException, "You cannot instantiate this class directly.");

    return Qnil;
}

//? These functions are common, so we share them
//? in the header
#define FMOD_USERDATA_FUNC(func_base, type)                 \
    RB_METHOD(fmodGetUserData)                              \
    {                                                       \
        RB_UNUSED_PARAM;                                    \
                                                            \
        type *b = getPrivateData<type>(self);               \
        VALUE data;                                         \
                                                            \
        FMOD_RESULT result = func_base##_GetUserData(       \
            b->p, (void **)&data);                          \
                                                            \
        FMOD_RESULT_BASE;                                   \
        if (data)                                           \
        {                                                   \
            rb_ary_push(return_ary, data);                  \
        }                                                   \
        FMOD_RESULT_RET;                                    \
    }                                                       \
    RB_METHOD(fmodSetUserData)                              \
    {                                                       \
        VALUE arg;                                          \
        rb_get_args(argc, argv, "o", &arg RB_ARG_END);      \
                                                            \
        rb_iv_set(self, "userdata_dont_touch_please", arg); \
                                                            \
        type *b = getPrivateData<type>(self);               \
                                                            \
        FMOD_RESULT result = func_base##_SetUserData(       \
            b->p, (void *)arg);                             \
                                                            \
        FMOD_RESULT_SIMPLE;                                 \
    }

#define FMOD_VALID_FUNC(func_base, type)           \
    RB_METHOD(fmodIsValid)                         \
    {                                              \
        RB_UNUSED_PARAM;                           \
        type *b = getPrivateData<type>(self);      \
        return BOOL2RB(func_base##_IsValid(b->p)); \
    }

#define FMOD_ID_FUNC(func_base, type)                        \
    RB_METHOD(fmodGetID)                                     \
    {                                                        \
        RB_UNUSED_PARAM;                                     \
        type *b = getPrivateData<type>(self);                \
        FMOD_GUID guid = FMOD_GUID();                        \
        FMOD_RESULT result = func_base##_GetID(b->p, &guid); \
        FMOD_RESULT_NO_WRAP(guid, FMOD_GUID);                \
    }

#define FMOD_PATH_FUNC(func_base, type)                                      \
    RB_METHOD(fmodGetPath)                                                   \
    {                                                                        \
        RB_UNUSED_PARAM;                                                     \
        type *b = getPrivateData<type>(self);                                \
        int retrieved;                                                       \
        char *path = NULL;                                                   \
        FMOD_RESULT result = func_base##_GetPath(b->p, NULL, 0, &retrieved); \
        if (result == FMOD_OK)                                               \
        {                                                                    \
            path = new char[retrieved];                                      \
            result = func_base##_GetPath(b->p, path, retrieved, &retrieved); \
        }                                                                    \
                                                                             \
        FMOD_RESULT_CONVERT(path, rb_str_new_cstr);                          \
    }

#define FMOD_VOLUME_FUNC(func_base, type)                                        \
    RB_METHOD(fmodGetVolume)                                                     \
    {                                                                            \
        RB_UNUSED_PARAM;                                                         \
        type *b = getPrivateData<type>(self);                                    \
        float volume;                                                            \
        float finalvolume;                                                       \
        FMOD_RESULT result = func_base##_GetVolume(b->p, &volume, &finalvolume); \
        FMOD_RESULT_BASE;                                                        \
        if (result == FMOD_OK)                                                   \
        {                                                                        \
            rb_ary_push(return_ary, DBL2NUM(volume));                            \
            rb_ary_push(return_ary, DBL2NUM(finalvolume));                       \
        }                                                                        \
        FMOD_RESULT_RET;                                                         \
    }                                                                            \
    RB_METHOD(fmodSetVolume)                                                     \
    {                                                                            \
        float volume;                                                            \
        rb_get_args(argc, argv, "f", &volume RB_ARG_END);                        \
        type *b = getPrivateData<type>(self);                                    \
        FMOD_RESULT result = func_base##_SetVolume(b->p, volume);                \
        FMOD_RESULT_SIMPLE;                                                      \
    }

#define FMOD_PAUSED_FUNC(func_base, type)                          \
    RB_METHOD(fmodGetPaused)                                       \
    {                                                              \
        RB_UNUSED_PARAM;                                           \
        type *b = getPrivateData<type>(self);                      \
        int paused;                                                \
        FMOD_RESULT result = func_base##_GetPaused(b->p, &paused); \
        FMOD_RESULT_CONVERT(paused, BOOL2RB);                      \
    }                                                              \
    RB_METHOD(fmodSetPaused)                                       \
    {                                                              \
        bool paused;                                               \
        rb_get_args(argc, argv, "b", &paused RB_ARG_END);          \
        type *b = getPrivateData<type>(self);                      \
        FMOD_RESULT result = func_base##_SetPaused(b->p, paused);  \
        FMOD_RESULT_SIMPLE;                                        \
    }

#define FMOD_CPU_USAGE_FUNC(func_base, type)              \
    RB_METHOD(fmodGetCPUUsage)                            \
    {                                                     \
        RB_UNUSED_PARAM;                                  \
        type *b = getPrivateData<type>(self);             \
        unsigned int exclusive, inclusive;                \
        FMOD_RESULT result = func_base##_GetCPUUsage(     \
            b->p, &exclusive, &inclusive);                \
        FMOD_RESULT_BASE;                                 \
        if (result == FMOD_OK)                            \
        {                                                 \
            rb_ary_push(return_ary, UINT2NUM(exclusive)); \
            rb_ary_push(return_ary, UINT2NUM(inclusive)); \
        }                                                 \
        FMOD_RESULT_RET;                                  \
    }

#define FMOD_MEMORY_USAGE_FUNC(func_base, type)                        \
    RB_METHOD(fmodGetMemoryUsage)                                      \
    {                                                                  \
        RB_UNUSED_PARAM;                                               \
        type *b = getPrivateData<type>(self);                          \
        FMOD_STUDIO_MEMORY_USAGE usage = FMOD_STUDIO_MEMORY_USAGE();   \
        FMOD_RESULT result = func_base##_GetMemoryUsage(b->p, &usage); \
        FMOD_RESULT_NO_WRAP(usage, FMOD_STUDIO_MEMORY_USAGE);          \
    }

#define FMOD_EQUAL_FUNC(type)                                      \
    RB_METHOD(fmodEqual)                                           \
    {                                                              \
        VALUE otherObj;                                            \
        rb_get_args(argc, argv, "o", &otherObj RB_ARG_END);        \
        if (!rb_typeddata_is_kind_of(otherObj, &type##Type))       \
            return Qfalse;                                         \
        type *p = getPrivateData<type>(self);                      \
        type *b = getPrivateDataCheck<type>(otherObj, type##Type); \
        return rb_bool_new(p->p == b->p);                          \
    }

#endif
