#include "binding-util.h"
#include "fmod_bindings.h"

VALUE rb_mFMOD = Qnil;
VALUE rb_mFMOD_Core = Qnil;

void fmodCoreBindingInit() {
    rb_mFMOD = rb_define_module("FMOD");
    rb_mFMOD_Core = rb_define_module_under(rb_mFMOD, "Core");

    bindFmodCoreStructs();
    bindFmodSystem();
}
