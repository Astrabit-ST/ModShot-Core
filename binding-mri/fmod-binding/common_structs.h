#ifndef COMMON_STRUCTS_H
#define COMMON_STRUCTS_H

#include "binding-util.h"

#define DEFINE_CONVERT_FUNC(type)                      \
    VALUE fmod##type##2rb(type p); \
    type rb2##type(VALUE self);

#define DECLARE_FMOD2RB(type, klass)           \
    VALUE fmod##type##2rb(type p) \
    {                                          \
        VALUE self = rb_obj_alloc(klass);

#define FMOD2RB(path, convert) \
    rb_iv_set(self, "@" #path, convert(p.path));

#define FMOD2RB_NAME(name, path, convert) \
    rb_iv_set(self, "@" #name, convert(p.path));

#define FMOD2RB_CAST(name, path, cast, convert) \
    rb_iv_set(self, "@" #name, convert((cast)p.path));

#define FMOD2RB_STRUCT(path, type) \
    rb_iv_set(self, "@" #path, fmod##type##2rb(p.path));

#define FMOD2RB_STRUCT_NAME(name, path, type) \
    rb_iv_set(self, "@" #name, fmod##type##2rb(p.path));

#define FMOD2RB_END \
    return self;    \
    }

#define DECLARE_RB2FMOD(type, klass) \
    type rb2##type(VALUE self)       \
    {                                \
        type p = type();

#define RB2FMOD(path, convert) \
    p.path = convert(rb_iv_get(self, "@" #path));

#define RB2FMOD_NAME(name, path, convert) \
    p.path = convert(rb_iv_get(self, "@" #name));

#define RB2FMOD_CAST(name, path, cast, convert) \
    p.path = (cast)convert(rb_iv_get(self, "@" #name));

#define RB2FMOD_STRUCT(path, type) \
    p.path = rb2##type(rb_iv_get(self, "@" #path));

#define RB2FMOD_END \
    return p;       \
    }

#define ATTR(klass, name) \
    rb_define_attr(klass, #name, 1, 1);

#endif
