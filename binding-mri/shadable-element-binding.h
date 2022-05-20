#ifndef SHADABLEBINDING_H
#define SHADABLEBIDNING_H

#include "binding-util.h"

RB_METHOD(shadableGetShaders) {

    RB_UNUSED_PARAM;

    return rb_iv_get(self, "shaders");
}

template<class C>
void shadableElementIntialize(VALUE self, C *se) {
    VALUE ary = rb_ary_new();

    rb_iv_set(self, "shaders", ary);

    se->setShaderArr(&ary);
}

void shadableElementBindingInit(VALUE klass) {
    _rb_define_method(klass, "shaders", shadableGetShaders);
}

#endif