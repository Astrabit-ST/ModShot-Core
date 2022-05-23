#include "etc-binding-util.h"
#include "etc-internal.h"
#include "binding-util.h"
#include "sharedstate.h"

DEF_TYPE(Vec2);
DEF_TYPE(Vec4);

ATTR_FLOAT_RW(Vec2, X);
ATTR_FLOAT_RW(Vec2, Y);

ATTR_FLOAT_RW(Vec4, X);
ATTR_FLOAT_RW(Vec4, Y);
ATTR_FLOAT_RW(Vec4, Z);
ATTR_FLOAT_RW(Vec4, W);

EQUAL_FUN(Vec2);
EQUAL_FUN(Vec4);

INIT_FUN_2(Vec2, float, "ff", 0);
INIT_FUN(Vec4, float, "ffff", 0);
INIT_FUN_2(Vec2i, int, "ii", 0);

SET_FUN_2(Vec2, float, "ff", 0);
SET_FUN(Vec4, float, "ffff", 0);

RB_METHOD(Vec2Stringify)
{
    RB_UNUSED_PARAM;

    Vec2 *v = getPrivateData<Vec2>(self);

    return rb_sprintf("(%f, %f)", v->x, v->y);
}

RB_METHOD(Vec4Stringify)
{
    RB_UNUSED_PARAM;

    Vec4 *v = getPrivateData<Vec4>(self);

    return rb_sprintf("(%f, %f, %f, %f)", v->x, v->y, v->z, v->w);
}

INITCOPY_FUN(Vec2);
INITCOPY_FUN(Vec4);

void etc_internalBindingInit()
{
    VALUE klass;

    INIT_BIND_SERIALIZELESS(Vec2);

    RB_ATTR_RW(Vec2, X, x);
    RB_ATTR_RW(Vec2, Y, y);

    INIT_BIND_SERIALIZELESS(Vec4);

    RB_ATTR_RW(Vec4, X, x);
    RB_ATTR_RW(Vec4, Y, y);
    RB_ATTR_RW(Vec4, Z, z);
    RB_ATTR_RW(Vec4, W, w);
}