#include "binding-util.h"
#include "fmod_bindings.h"
#ifdef AUTO_CLEAN_FMOD
#include "debugwriter.h"
#include <fmod_errors.h>
#endif

/*
? Bank bindings
? Why is RB_UNUSED_PARAM used everywhere? I have no idea!
? MKXP has them *everywhere*, and I don't know why!
?
? Most of these abuse macros and the C preprocessor to
? shrink code. You may want to read up on these macros
? first.
*/

DEF_TYPE(Bank);
/*
? Custom bank destructor
? Automatically unloads the bank when
? the bank is garbage collected from ruby
*/
Bank::~Bank()
{
    #ifdef AUTO_CLEAN_FMOD
    Debug() << "Warning: auto unloading bank (garbage collected?)";
    Debug() << "Bank unloading result: " << FMOD_ErrorString(FMOD_Studio_Bank_Unload(p));
    #endif
}

VALUE rb_cBank = Qnil;

FMOD_VALID_FUNC(FMOD_Studio_Bank, Bank);

FMOD_ID_FUNC(FMOD_Studio_Bank, Bank);

FMOD_PATH_FUNC(FMOD_Studio_Bank, Bank);

RB_METHOD(bankUnload)
{
    RB_UNUSED_PARAM;

    //? Get wrapper
    Bank *b = getPrivateData<Bank>(self);

    //? Unload bank
    FMOD_RESULT result = FMOD_Studio_Bank_Unload(b->p);

    //? Return only the result
    FMOD_RESULT_SIMPLE;
}

RB_METHOD(bankLoadSampleData)
{
    RB_UNUSED_PARAM;

    //? Get wrapper
    Bank *b = getPrivateData<Bank>(self);

    //? Load sample data
    FMOD_RESULT result = FMOD_Studio_Bank_LoadSampleData(b->p);

    //? Return only the result
    FMOD_RESULT_SIMPLE;
}

RB_METHOD(bankUnloadSampleData)
{
    RB_UNUSED_PARAM;

    //? Get wrapper
    Bank *b = getPrivateData<Bank>(self);

    //? Unload sample data
    FMOD_RESULT result = FMOD_Studio_Bank_UnloadSampleData(b->p);

    //? Return only the result
    FMOD_RESULT_SIMPLE;
}

RB_METHOD(bankGetLoadingState)
{
    RB_UNUSED_PARAM;

    //? Get wrapper
    Bank *b = getPrivateData<Bank>(self);
    FMOD_STUDIO_LOADING_STATE state;

    //? Call function
    FMOD_RESULT result = FMOD_Studio_Bank_GetLoadingState(b->p, &state);

    //? Return result & value
    FMOD_RESULT_CONVERT(state, INT2NUM);
}

RB_METHOD(bankGetSampleLoadingState)
{
    RB_UNUSED_PARAM;

    //? Get wrapper
    Bank *b = getPrivateData<Bank>(self);
    FMOD_STUDIO_LOADING_STATE state;

    //? Call function
    FMOD_RESULT result = FMOD_Studio_Bank_GetSampleLoadingState(b->p, &state);

    //? Return result & value
    FMOD_RESULT_CONVERT(state, INT2NUM);
}

RB_METHOD(bankGetStringCount)
{
    RB_UNUSED_PARAM;
    //? Get wrapper
    Bank *b = getPrivateData<Bank>(self);
    int count;

    //? Call function
    FMOD_RESULT result = FMOD_Studio_Bank_GetStringCount(b->p, &count);

    //? Return result & value
    FMOD_RESULT_CONVERT(count, INT2NUM);
}

//! Oh boy
RB_METHOD(bankGetStringInfo)
{
    //? Get the index we are using
    int index;
    rb_get_args(argc, argv, "i", &index RB_ARG_END);

    //? Get wrapper
    Bank *b = getPrivateData<Bank>(self);
    //? Set up variables, guid and path are intentionally null
    //? so we don't allocate memory for them if the function is
    //? unsuccessful
    int retrieved;
    char *path = NULL;
    FMOD_GUID guid;

    FMOD_RESULT result = FMOD_Studio_Bank_GetStringInfo(
        b->p, index, NULL, NULL, 0, &retrieved);

    //? If function was successful
    if (result == FMOD_OK)
    {
        //? Allocate memory for the string like in GetPath
        path = new char[retrieved];
        //? Create the GUID
        guid = FMOD_GUID();

        //? Finally call the function for real
        //? Oh boy that was horrible
        result = FMOD_Studio_Bank_GetStringInfo(
            b->p, index, &guid, path, retrieved, &retrieved);
    }

    //? Not many functions need more than 1 return value
    //? and the functions that do are specialized, so no
    //? fancy macro here unfortunately
    FMOD_RESULT_BASE;
    if (path)
    {
        VALUE return_val = fmodFMOD_GUID2rb(guid);
        rb_ary_push(return_ary, return_val);
        rb_ary_push(return_ary, rb_str_new_cstr(path));
    }
    //? Hell is over!
    FMOD_RESULT_RET;
}

FMOD_USERDATA_FUNC(FMOD_Studio_Bank, Bank);

RB_METHOD(bankGetVCACount)
{
    RB_UNUSED_PARAM;
    //? Get wrapper
    Bank *b = getPrivateData<Bank>(self);
    int count;

    //? Call function
    FMOD_RESULT result = FMOD_Studio_Bank_GetVCACount(b->p, &count);

    //? Return result & value
    FMOD_RESULT_CONVERT(count, INT2NUM);
}

//! HERE BE DRAGONS
RB_METHOD(bankGetVCAList)
{
    RB_UNUSED_PARAM;

    //? Get wrapper
    Bank *b = getPrivateData<Bank>(self);

    //? Find size of array we need (because we need to allocate memory)
    //? I absolutely hate doing this kind of process but y'know what
    //? whatever it works
    int count;
    FMOD_STUDIO_VCA **array = NULL;
    FMOD_RESULT result = FMOD_Studio_Bank_GetVCACount(b->p, &count);

    if (result == FMOD_OK)
    {
        //? Allocate array (god i hate this)
        array = new FMOD_STUDIO_VCA *[count];

        result = FMOD_Studio_Bank_GetVCAList(
            b->p, array, count, NULL);
    }

    FMOD_RESULT_BASE;
    if (array && result == FMOD_OK)
    {
        //? Convert the vca array to a ruby array, painfully
        VALUE vca_ary = rb_ary_new();
        //? Iterate over all elements in the array
        //? May potentially crash if the amount of elements
        //? is different from count
        for (int i = 0; i < count; i++)
        {
            //? Convert VCA and add it to the array
            VALUE ele = rb_obj_alloc(rb_cVCA);
            setPrivateData(ele, new VCA(array[i]));
            rb_ary_push(vca_ary, ele);
        }
        //? Add the result array and we are done!
        //? This likely memory leaks I think, but we'll see
        rb_ary_push(return_ary, vca_ary);
        delete array; //? This shouldn't free the elements?
    }
    FMOD_RESULT_RET;
}

RB_METHOD(bankGetBusCount)
{
    RB_UNUSED_PARAM;
    Bank *b = getPrivateData<Bank>(self);
    int count;

    FMOD_RESULT result = FMOD_Studio_Bank_GetBusCount(b->p, &count);

    FMOD_RESULT_CONVERT(count, INT2NUM);
}

RB_METHOD(bankGetBusList)
{
    RB_UNUSED_PARAM;

    Bank *b = getPrivateData<Bank>(self);

    int count;
    FMOD_STUDIO_BUS **array = NULL;
    FMOD_RESULT result = FMOD_Studio_Bank_GetBusCount(b->p, &count);

    if (result == FMOD_OK)
    {
        array = new FMOD_STUDIO_BUS *[count];

        result = FMOD_Studio_Bank_GetBusList(
            b->p, array, count, NULL);
    }

    FMOD_RESULT_BASE;
    if (array && result == FMOD_OK)
    {
        VALUE bus_ary = rb_ary_new();

        for (int i = 0; i < count; i++)
        {
            VALUE ele = rb_obj_alloc(rb_cBus);
            setPrivateData(ele, new Bus(array[i]));
            rb_ary_push(bus_ary, ele);
        }

        rb_ary_push(return_ary, bus_ary);
        delete array;
    }
    FMOD_RESULT_RET;
}

RB_METHOD(bankGetEventCount)
{
    RB_UNUSED_PARAM;
    Bank *b = getPrivateData<Bank>(self);
    int count;

    FMOD_RESULT result = FMOD_Studio_Bank_GetEventCount(b->p, &count);

    FMOD_RESULT_CONVERT(count, INT2NUM);
}

RB_METHOD(bankGetEventList)
{
    RB_UNUSED_PARAM;

    Bank *b = getPrivateData<Bank>(self);

    int count;
    FMOD_STUDIO_EVENTDESCRIPTION **array = NULL;
    FMOD_RESULT result = FMOD_Studio_Bank_GetEventCount(b->p, &count);

    if (result == FMOD_OK)
    {
        array = new FMOD_STUDIO_EVENTDESCRIPTION *[count];

        result = FMOD_Studio_Bank_GetEventList(
            b->p, array, count, NULL);
    }

    FMOD_RESULT_BASE;
    if (array && result == FMOD_OK)
    {
        VALUE event_ary = rb_ary_new();

        for (int i = 0; i < count; i++)
        {
            VALUE ele = rb_obj_alloc(rb_cEventDescription);
            setPrivateData(ele, new EventDescription(array[i]));
            rb_ary_push(event_ary, ele);
        }

        rb_ary_push(return_ary, event_ary);
        delete array;
    }
    FMOD_RESULT_RET;
}

FMOD_EQUAL_FUNC(Bank);

void bindFmodStudioBank()
{
    rb_cBank = rb_define_class_under(rb_mFMOD_Studio, "Bank", rb_cObject);
    rb_define_alloc_func(rb_cBank, classAllocate<&BankType>);
    _rb_define_method(rb_cBank, "initialize", fmodErrorInit);
    _rb_define_method(rb_cBank, "==", fmodEqual);

    _rb_define_method(rb_cBank, "is_valid", fmodIsValid);
    _rb_define_method(rb_cBank, "get_id", fmodGetID);
    _rb_define_method(rb_cBank, "get_path", fmodGetPath);
    _rb_define_method(rb_cBank, "unload", bankUnload);
    _rb_define_method(rb_cBank, "load_sample_data", bankLoadSampleData);
    _rb_define_method(rb_cBank, "unload_sample_data", bankUnloadSampleData);
    _rb_define_method(rb_cBank, "get_loading_state", bankGetLoadingState);
    _rb_define_method(rb_cBank, "get_sample_loading_state", bankGetSampleLoadingState);
    _rb_define_method(rb_cBank, "get_string_count", bankGetStringCount);
    _rb_define_method(rb_cBank, "get_string_info", bankGetStringInfo);
    _rb_define_method(rb_cBank, "get_user_data", fmodGetUserData);
    _rb_define_method(rb_cBank, "set_user_data", fmodSetUserData);
    _rb_define_method(rb_cBank, "get_vca_count", bankGetVCACount);
    _rb_define_method(rb_cBank, "get_vca_list", bankGetVCAList);
    _rb_define_method(rb_cBank, "get_bus_count", bankGetBusCount);
    _rb_define_method(rb_cBank, "get_bus_list", bankGetBusList);
    _rb_define_method(rb_cBank, "get_event_count", bankGetEventCount);
    _rb_define_method(rb_cBank, "get_event_list", bankGetEventList);
}
