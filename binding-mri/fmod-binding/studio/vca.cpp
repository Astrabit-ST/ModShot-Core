#include "binding-util.h"
#include "fmod_bindings.h"
#include "debugwriter.h"

DEF_TYPE(VCA);
VCA::~VCA()
{
    // Debug() << "Warning: VCA deconstructed (garbage collected?)";
}

VALUE rb_cVCA = Qnil;

FMOD_VALID_FUNC(FMOD_Studio_VCA, VCA);

FMOD_ID_FUNC(FMOD_Studio_VCA, VCA);

FMOD_PATH_FUNC(FMOD_Studio_VCA, VCA);

FMOD_VOLUME_FUNC(FMOD_Studio_VCA, VCA);

FMOD_EQUAL_FUNC(VCA);

void bindFmodStudioVCA()
{
    rb_cVCA = rb_define_class_under(rb_mFMOD_Studio, "VCA", rb_cObject);
    rb_define_alloc_func(rb_cVCA, classAllocate<&VCAType>);
    _rb_define_method(rb_cVCA, "initialize", fmodErrorInit);
    _rb_define_method(rb_cVCA, "==", fmodEqual);

    _rb_define_method(rb_cVCA, "is_valid", fmodIsValid);
    _rb_define_method(rb_cVCA, "get_id", fmodGetID);
    _rb_define_method(rb_cVCA, "get_path", fmodGetPath);
    _rb_define_method(rb_cVCA, "get_volume", fmodGetVolume);
    _rb_define_method(rb_cVCA, "set_volume", fmodSetVolume);
}
