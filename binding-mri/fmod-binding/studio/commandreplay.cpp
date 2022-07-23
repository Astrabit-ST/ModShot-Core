#include "fmod_bindings.h"
#include "binding-util.h"
#ifdef AUTO_CLEAN_FMOD
#include "debugwriter.h"
#include <fmod_errors.h>
#endif

DEF_TYPE(CommandReplay);
CommandReplay::~CommandReplay()
{
#ifdef AUTO_CLEAN_FMOD
    Debug() << "Warning: auto releasing command replay (garbage collected?)";
    Debug() << "Command replay release result: " << FMOD_ErrorString(FMOD_Studio_CommandReplay_Release(p));
#endif
}

VALUE rb_cCommandReplay = Qnil;

FMOD_VALID_FUNC(FMOD_Studio_CommandReplay, CommandReplay);

RB_METHOD(commandReplayGetSystem)
{
    RB_UNUSED_PARAM;

    CommandReplay *b = getPrivateData<CommandReplay>(self);
    FMOD_STUDIO_SYSTEM *system;

    FMOD_RESULT result = FMOD_Studio_CommandReplay_GetSystem(b->p, &system);

    FMOD_RESULT_WRAP(system, StudioSystem);
}

RB_METHOD(commandReplayGetLength)
{
    RB_UNUSED_PARAM;

    CommandReplay *b = getPrivateData<CommandReplay>(self);
    float length;

    FMOD_RESULT result = FMOD_Studio_CommandReplay_GetLength(b->p, &length);

    FMOD_RESULT_CONVERT(length, DBL2NUM);
}

RB_METHOD(commandReplayGetCommandCount)
{
    RB_UNUSED_PARAM;

    CommandReplay *b = getPrivateData<CommandReplay>(self);
    int count;

    FMOD_RESULT result = FMOD_Studio_CommandReplay_GetCommandCount(b->p, &count);

    FMOD_RESULT_CONVERT(count, INT2NUM);
}

RB_METHOD(commandReplayGetCommandInfo)
{
    int index;
    rb_get_args(argc, argv, "i", &index RB_ARG_END);

    CommandReplay *b = getPrivateData<CommandReplay>(self);
    FMOD_STUDIO_COMMAND_INFO info = FMOD_STUDIO_COMMAND_INFO();

    FMOD_RESULT result = FMOD_Studio_CommandReplay_GetCommandInfo(b->p, index, &info);

    FMOD_RESULT_NO_WRAP(info, FMOD_STUDIO_COMMAND_INFO);
}

RB_METHOD(commandReplayGetCommandString)
{
    int index;
    rb_get_args(argc, argv, "i", &index RB_ARG_END);

    CommandReplay *b = getPrivateData<CommandReplay>(self);

    //! WHY DOES THIS FUNCTION ACT DIFFERNTLY!?!?!?!
    int length = 256;
    char *path = new char[length];

    FMOD_RESULT result = FMOD_Studio_CommandReplay_GetCommandString(b->p, index, path, length);

    //! Make string longer while it's too short
    while (result == FMOD_ERR_TRUNCATED)
    {
        delete path;
        length *= 2;
        path = new char[length];
        result = FMOD_Studio_CommandReplay_GetCommandString(b->p, index, path, length);
    }

    if (result != FMOD_OK)
        delete path; //! Normally the string would never be allocated if the function didn't return ok
                     //! but here since we ALWAYS allocate the string we need to free it
                     //! This also would not normally be a problem with other functions since they
                     //! usually take in a statically allocated argument, but here since it's a string,
                     //! we need to free it.

    //! This also means that the string is too long, but that's fine since ruby controls the string now
    FMOD_RESULT_CONVERT(path, rb_str_new_cstr);
}

RB_METHOD(commandReplayGetCommandAtTime) {
    float time;
    rb_get_args(argc, argv, "f", &time RB_ARG_END);

    CommandReplay *b = getPrivateData<CommandReplay>(self);
    int index;

    FMOD_RESULT result = FMOD_Studio_CommandReplay_GetCommandAtTime(b->p, time, &index);

    FMOD_RESULT_CONVERT(index, INT2NUM);
}

RB_METHOD(commandReplaySetBankPath) {
    char* path;
    rb_get_args(argc, argv, "z", &path RB_ARG_END);

    CommandReplay *b = getPrivateData<CommandReplay>(self);

    FMOD_RESULT result = FMOD_Studio_CommandReplay_SetBankPath(b->p, path);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(commandReplayStart) {
    RB_UNUSED_PARAM;

    CommandReplay *b = getPrivateData<CommandReplay>(self);

    FMOD_RESULT result = FMOD_Studio_CommandReplay_Start(b->p);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(commandReplayStop) {
    RB_UNUSED_PARAM;

    CommandReplay *b = getPrivateData<CommandReplay>(self);

    FMOD_RESULT result = FMOD_Studio_CommandReplay_Stop(b->p);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(commandReplaySeekToTime) {
    float time;
    rb_get_args(argc, argv, "f", &time RB_ARG_END);

    CommandReplay *b = getPrivateData<CommandReplay>(self);

    FMOD_RESULT result = FMOD_Studio_CommandReplay_SeekToTime(b->p, time);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(commandReplaySeekToCommand) {
    int index;
    rb_get_args(argc, argv, "i", &index RB_ARG_END);

    CommandReplay *b = getPrivateData<CommandReplay>(self);

    FMOD_RESULT result = FMOD_Studio_CommandReplay_SeekToCommand(b->p, index);

    FMOD_RESULT_SIMPLE;
}

FMOD_PAUSED_FUNC(FMOD_Studio_CommandReplay, CommandReplay);

RB_METHOD(commandReplayGetPlaybackState) {
    RB_UNUSED_PARAM;

    CommandReplay *b = getPrivateData<CommandReplay>(self);

    FMOD_STUDIO_PLAYBACK_STATE state;

    FMOD_RESULT result = FMOD_Studio_CommandReplay_GetPlaybackState(b->p, &state);

    FMOD_RESULT_CONVERT(state, INT2NUM);
}

RB_METHOD(commandReplayGetCurrentCommand) {
    RB_UNUSED_PARAM;

    CommandReplay *b = getPrivateData<CommandReplay>(self);

    int index;
    float time;

    FMOD_RESULT result = FMOD_Studio_CommandReplay_GetCurrentCommand(b->p, &index, &time);

    FMOD_RESULT_BASE;
    if (result == FMOD_OK) {
        rb_ary_push(return_ary, INT2NUM(index));
        rb_ary_push(return_ary, DBL2NUM(time));
    }
    FMOD_RESULT_RET;
}

RB_METHOD(commandReplayRelease) {
    RB_UNUSED_PARAM;

    CommandReplay *b = getPrivateData<CommandReplay>(self);

    FMOD_RESULT result = FMOD_Studio_CommandReplay_Release(b->p);

    FMOD_RESULT_SIMPLE;
}

RB_METHOD(commandReplaySetFrameCallback) {
    // TODO
}

RB_METHOD(commandReplaySetLoadBankCallback) {
    // TODO
}

RB_METHOD(commandReplaySetCreateInstanceCallback) {
    // TODO
}

FMOD_USERDATA_FUNC(FMOD_Studio_CommandReplay, CommandReplay);

FMOD_EQUAL_FUNC(CommandReplay);

void bindFmodStudioCommandReplay()
{
    rb_cCommandReplay = rb_define_class_under(
        rb_mFMOD_Studio, "CommandReplay", rb_cObject);
    rb_define_alloc_func(rb_cCommandReplay, classAllocate<&CommandReplayType>);
    _rb_define_method(rb_cCommandReplay, "initialize", fmodErrorInit);
    _rb_define_method(rb_cCommandReplay, "==", fmodEqual);

    _rb_define_method(rb_cCommandReplay, "is_valid", fmodIsValid);
    _rb_define_method(rb_cCommandReplay, "get_system", commandReplayGetSystem);
    _rb_define_method(rb_cCommandReplay, "get_length", commandReplayGetLength);
    _rb_define_method(rb_cCommandReplay, "get_command_count", commandReplayGetCommandCount);
    _rb_define_method(rb_cCommandReplay, "get_command_info", commandReplayGetCommandInfo);
    _rb_define_method(rb_cCommandReplay, "get_command_string", commandReplayGetCommandString);
    _rb_define_method(rb_cCommandReplay, "get_command_at_time", commandReplayGetCommandAtTime);
    _rb_define_method(rb_cCommandReplay, "set_bank_path", commandReplaySetBankPath);
    _rb_define_method(rb_cCommandReplay, "start", commandReplayStart);
    _rb_define_method(rb_cCommandReplay, "stop", commandReplayStop);
    _rb_define_method(rb_cCommandReplay, "seek_to_time", commandReplaySeekToTime);
    _rb_define_method(rb_cCommandReplay, "seek_to_command", commandReplaySeekToCommand);
    _rb_define_method(rb_cCommandReplay, "get_paused", fmodGetPaused);
    _rb_define_method(rb_cCommandReplay, "set_paused", fmodSetPaused);
    _rb_define_method(rb_cCommandReplay, "get_playback_state", commandReplayGetPlaybackState);
    _rb_define_method(rb_cCommandReplay, "get_current_command", commandReplayGetCurrentCommand);
    _rb_define_method(rb_cCommandReplay, "release", commandReplayRelease);
    _rb_define_method(rb_cCommandReplay, "set_frame_callback", commandReplaySetFrameCallback);
    _rb_define_method(rb_cCommandReplay, "set_load_bank_callback", commandReplaySetLoadBankCallback);
    _rb_define_method(rb_cCommandReplay, "set_create_instance_callback", commandReplaySetCreateInstanceCallback);
    _rb_define_method(rb_cCommandReplay, "get_user_data", fmodGetUserData);
    _rb_define_method(rb_cCommandReplay, "set_user_data", fmodSetUserData);
}
