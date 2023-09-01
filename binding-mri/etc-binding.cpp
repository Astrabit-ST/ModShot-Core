/*
** etc-binding.cpp
**
** This file is part of mkxp.
**
** Copyright (C) 2013 Jonas Kulla <Nyocurio@gmail.com>
**
** mkxp is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 2 of the License, or
** (at your option) any later version.
**
** mkxp is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with mkxp.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "etc.h"
#include "binding-util.h"
#include "serializable-binding.h"
#include "sharedstate.h"
#include "etc-binding-util.h"

DEF_TYPE(Color);
DEF_TYPE(Tone);
DEF_TYPE(Rect);

ATTR_DOUBLE_RW(Color, Red)
ATTR_DOUBLE_RW(Color, Green)
ATTR_DOUBLE_RW(Color, Blue)
ATTR_DOUBLE_RW(Color, Alpha)

ATTR_DOUBLE_RW(Tone, Red)
ATTR_DOUBLE_RW(Tone, Green)
ATTR_DOUBLE_RW(Tone, Blue)
ATTR_DOUBLE_RW(Tone, Gray)

ATTR_INT_RW(Rect, X)
ATTR_INT_RW(Rect, Y)
ATTR_INT_RW(Rect, Width)
ATTR_INT_RW(Rect, Height)

EQUAL_FUN(Color)
EQUAL_FUN(Tone)
EQUAL_FUN(Rect)

INIT_FUN(Color, double, "fff|f", 255)
INIT_FUN(Tone, double, "fff|f", 0)
INIT_FUN(Rect, int, "iiii", 0)

SET_FUN(Color, double, "fff|f", 255)
SET_FUN(Tone, double, "fff|f", 0)
SET_FUN(Rect, int, "iiii", 0)

RB_METHOD(rectEmpty)
{
	RB_UNUSED_PARAM;
	Rect *r = getPrivateData<Rect>(self);
	r->empty();
	return self;
}

RB_METHOD(ColorStringify)
{
	RB_UNUSED_PARAM;

	Color *c = getPrivateData<Color>(self);

	return rb_sprintf("(%f, %f, %f, %f)",
	                  c->red, c->green, c->blue, c->alpha);
}

RB_METHOD(ToneStringify)
{
	RB_UNUSED_PARAM;

	Tone *t = getPrivateData<Tone>(self);

	return rb_sprintf("(%f, %f, %f, %f)",
	                  t->red, t->green, t->blue, t->gray);
}

RB_METHOD(RectStringify)
{
	RB_UNUSED_PARAM;

	Rect *r = getPrivateData<Rect>(self);

	return rb_sprintf("(%d, %d, %d, %d)",
	                  r->x, r->y, r->width, r->height);
}

MARSH_LOAD_FUN(Color)
MARSH_LOAD_FUN(Tone)
MARSH_LOAD_FUN(Rect)

INITCOPY_FUN(Tone)
INITCOPY_FUN(Color)
INITCOPY_FUN(Rect)

void
etcBindingInit()
{
	VALUE klass;

	INIT_BIND(Color);

	RB_ATTR_RW(Color, Red, red);
	RB_ATTR_RW(Color, Green, green);
	RB_ATTR_RW(Color, Blue, blue);
	RB_ATTR_RW(Color, Alpha, alpha);

	INIT_BIND(Tone);

	RB_ATTR_RW(Tone, Red, red);
	RB_ATTR_RW(Tone, Green, green);
	RB_ATTR_RW(Tone, Blue, blue);
	RB_ATTR_RW(Tone, Gray, gray);

	INIT_BIND(Rect);

	RB_ATTR_RW(Rect, X, x);
	RB_ATTR_RW(Rect, Y, y);
	RB_ATTR_RW(Rect, Width, width);
	RB_ATTR_RW(Rect, Height, height);
	_rb_define_method(klass, "empty", rectEmpty);
}
