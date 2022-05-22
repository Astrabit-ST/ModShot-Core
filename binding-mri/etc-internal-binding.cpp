#include "etc-binding-util.h"
#include "etc-internal.h"
#include "binding-util.h"
#include "sharedstate.h"

DEF_TYPE(Vec2);
DEF_TYPE(Vec4);
DEF_TYPE(Vec2i);

ATTR_FLOAT_RW(Vec2, X);
ATTR_FLOAT_RW(Vec2, Y);

ATTR_FLOAT_RW(Vec4, X);
ATTR_FLOAT_RW(Vec4, Y);
ATTR_FLOAT_RW(Vec4, Z);
ATTR_FLOAT_RW(Vec4, W);

ATTR_INT_RW(Vec2i, X);
ATTR_INT_RW(Vec2i, Y);

EQUAL_FUN(Vec2);
EQUAL_FUN(Vec4);
EQUAL_FUN(Vec2i);

INIT_FUN_2(Vec2, float, "ff", 0);
INIT_FUN(Vec4, float, "ffff", 0);
INIT_FUN_2(Vec2i, int, "ii", 0);

SET_FUN_2(Vec2, float, "ff", 0);
SET_FUN(Vec4, float, "ffff", 0);
SET_FUN_2(Vec2i, int, "ii", 0);

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

RB_METHOD(Vec2iStringify)
{
    RB_UNUSED_PARAM;

    Vec2i *v = getPrivateData<Vec2i>(self);

    return rb_sprintf("(%d, %d)", v->x, v->y);
}

INITCOPY_FUN(Vec2);
INITCOPY_FUN(Vec4);
INITCOPY_FUN(Vec2i);

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

    INIT_BIND_SERIALIZELESS(Vec2i);

    RB_ATTR_RW(Vec2i, X, x);
    RB_ATTR_RW(Vec2i, Y, y);
}