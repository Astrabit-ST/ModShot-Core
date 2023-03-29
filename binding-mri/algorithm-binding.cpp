#include "algorithm.h"
#include "binding-util.h"

RB_METHOD(algorithmPointDistance)
{
    double x1, y1, x2,  y2;
    rb_get_args(argc, argv, "ffff", &x1, &y1, &x2, &y2 RB_ARG_END);

    return DBL2NUM(point_distance(x1, y1, x2, y2));
}

RB_METHOD(algorithmCircleDistance)
{
    double x1, y1, x2,  y2, radius;
    rb_get_args(argc, argv, "fffff", &x1, &y1, &x2, &y2, &radius RB_ARG_END);

    return DBL2NUM(point_distance(x1, y1, x2, y2));
}

RB_METHOD(algorithmRectangleDistance)
{
    double x1, y1, x2,  y2, width, height;
    rb_get_args(argc, argv, "fffff", &x1, &y1, &x2, &y2, &width, &height RB_ARG_END);

    return DBL2NUM(rectangle_distance(x1, y1, x2, y2, width, height));
}

void algorithmBindingInit() 
{
    VALUE module = rb_define_module("Algorithm");
    _rb_define_module_function(module, "point_distance", algorithmPointDistance);
    _rb_define_module_function(module, "circle_distance", algorithmCircleDistance);
    _rb_define_module_function(module, "rectangle_distance", algorithmRectangleDistance);
}