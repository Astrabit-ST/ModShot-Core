#include "binding-util.h"
#include "fmod_bindings.h"
#ifdef AUTO_CLEAN_FMOD
#include "debugwriter.h"
#include <fmod_errors.h>
#endif

DEF_TYPE(System);
System::~System() {
    #ifdef AUTO_CLEAN_FMOD
    Debug() << "Warning: auto releasing system (garbage collected?)";
    Debug() << "System release result: " << FMOD_ErrorString(FMOD_System_Release(p));
    #endif
}

VALUE rb_cSystem = Qnil;

void bindFmodSystem() {
    rb_cSystem = rb_define_class_under(rb_mFMOD_Core, "System", rb_cObject);
    rb_define_alloc_func(rb_cSystem, classAllocate<&SystemType>);
}
