#include "binding-util.h"
#include "sharedstate.h"
#include "fmod_bindings.h"

#include <fmod_studio.h>
#include <iostream>

VALUE rb_mFMOD_Studio = Qnil;

void fmodStudioBindingInit()
{
    rb_mFMOD_Studio = rb_define_module_under(rb_mFMOD, "Studio");

    bindFmodStudioSystem();
    bindFmodStudioStructs();
    bindFmodStudioBank();
    bindFmodStudioVCA();
    bindFmodStudioBus();
    bindFmodStudioEventDescription();
    bindFmodStudioEventInstance();
}
