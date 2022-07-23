#ifndef ETC_BINDING_UTIL_H
#define ETC_BINDING_UTIL_H

#define INIT_BIND(Klass) \
{ \
	klass = rb_define_class(#Klass, rb_cObject); \
	rb_define_alloc_func(klass, classAllocate<&Klass##Type>); \
	rb_define_class_method(klass, "_load", Klass##Load); \
	serializableBindingInit<Klass>(klass); \
	_rb_define_method(klass, "initialize", Klass##Initialize); \
	_rb_define_method(klass, "initialize_copy", Klass##InitializeCopy); \
	_rb_define_method(klass, "set", Klass##Set); \
	_rb_define_method(klass, "==", Klass##Equal); \
	_rb_define_method(klass, "===", Klass##Equal); \
	_rb_define_method(klass, "eql?", Klass##Equal); \
	_rb_define_method(klass, "to_s", Klass##Stringify); \
	_rb_define_method(klass, "inspect", Klass##Stringify); \
}

#define INIT_BIND_SERIALIZELESS(Klass) \
{ \
	klass = rb_define_class(#Klass, rb_cObject); \
	rb_define_alloc_func(klass, classAllocate<&Klass##Type>); \
	_rb_define_method(klass, "initialize", Klass##Initialize); \
	_rb_define_method(klass, "initialize_copy", Klass##InitializeCopy); \
	_rb_define_method(klass, "set", Klass##Set); \
	_rb_define_method(klass, "==", Klass##Equal); \
	_rb_define_method(klass, "===", Klass##Equal); \
	_rb_define_method(klass, "eql?", Klass##Equal); \
	_rb_define_method(klass, "to_s", Klass##Stringify); \
	_rb_define_method(klass, "inspect", Klass##Stringify); \
}

#define MRB_ATTR_R(Class, attr) mrb_define_method(mrb, klass, #attr, Class##Get_##attr, MRB_ARGS_NONE())
#define MRB_ATTR_W(Class, attr) mrb_define_method(mrb, klass, #attr "=", Class##Set_##attr, MRB_ARGS_REQ(1))
#define MRB_ATTR_RW(Class, attr) { MRB_ATTR_R(Class, attr); MRB_ATTR_W(Class, attr); }

#define RB_ATTR_R(Klass, Attr, attr) _rb_define_method(klass, #attr, Klass##Get##Attr)
#define RB_ATTR_W(Klass, Attr, attr) _rb_define_method(klass, #attr "=", Klass##Set##Attr)
#define RB_ATTR_RW(Klass, Attr, attr) \
	{ RB_ATTR_R(Klass, Attr, attr); RB_ATTR_W(Klass, Attr, attr); }

#define SET_FUN(Klass, param_type, param_t_s, last_param_def) \
	RB_METHOD(Klass##Set) \
	{ \
		Klass *k = getPrivateData<Klass>(self); \
		if (argc == 1) \
		{ \
			VALUE otherObj = argv[0]; \
			Klass *other = getPrivateDataCheck<Klass>(otherObj, Klass##Type); \
			*k = *other; \
		} \
		else \
		{ \
			param_type p1, p2, p3, p4 = last_param_def; \
			rb_get_args(argc, argv, param_t_s, &p1, &p2, &p3, &p4 RB_ARG_END); \
			k->set(p1, p2, p3, p4); \
		} \
		return self; \
	}

#define SET_FUN_2(Klass, param_type, param_t_s, last_param_def) \
	RB_METHOD(Klass##Set) \
	{ \
		Klass *k = getPrivateData<Klass>(self); \
		if (argc == 1) \
		{ \
			VALUE otherObj = argv[0]; \
			Klass *other = getPrivateDataCheck<Klass>(otherObj, Klass##Type); \
			*k = *other; \
		} \
		else \
		{ \
			param_type p1, p2 = last_param_def; \
			rb_get_args(argc, argv, param_t_s, &p1, &p2 RB_ARG_END); \
			k->set(p1, p2); \
		} \
		return self; \
	}

#define INIT_FUN(Klass, param_type, param_t_s, last_param_def) \
	RB_METHOD(Klass##Initialize) \
	{ \
		Klass *k; \
		if (argc == 0) \
		{ \
			k = new Klass(); \
		} \
		else \
		{ \
			param_type p1, p2, p3, p4 = last_param_def; \
			rb_get_args(argc, argv, param_t_s, &p1, &p2, &p3, &p4 RB_ARG_END); \
			k = new Klass(p1, p2, p3, p4); \
		} \
		setPrivateData(self, k); \
		return self; \
	}

#define INIT_FUN_2(Klass, param_type, param_t_s, last_param_def) \
	RB_METHOD(Klass##Initialize) \
	{ \
		Klass *k; \
		if (argc == 0) \
		{ \
			k = new Klass(); \
		} \
		else \
		{ \
			param_type p1, p2 = last_param_def; \
			rb_get_args(argc, argv, param_t_s, &p1, &p2 RB_ARG_END); \
			k = new Klass(p1, p2); \
		} \
		setPrivateData(self, k); \
		return self; \
	}

#define EQUAL_FUN(Klass) \
	RB_METHOD(Klass##Equal) \
	{ \
		Klass *p = getPrivateData<Klass>(self); \
		VALUE otherObj; \
		Klass *other; \
		rb_get_args(argc, argv, "o", &otherObj RB_ARG_END); \
		if (rgssVer >= 3) \
			if (!rb_typeddata_is_kind_of(otherObj, &Klass##Type)) \
				return Qfalse; \
		other = getPrivateDataCheck<Klass>(otherObj, Klass##Type); \
		return rb_bool_new(*p == *other); \
	}

#define ATTR_RW(Klass, Attr, arg_type, arg_t_s, value_fun) \
	RB_METHOD(Klass##Get##Attr) \
	{ \
		RB_UNUSED_PARAM \
		Klass *p = getPrivateData<Klass>(self); \
		return value_fun(p->get##Attr()); \
	} \
	RB_METHOD(Klass##Set##Attr) \
	{ \
		Klass *p = getPrivateData<Klass>(self); \
		arg_type arg; \
		rb_get_args(argc, argv, arg_t_s, &arg RB_ARG_END); \
		p->set##Attr(arg); \
		return *argv; \
	}

#define ATTR_DOUBLE_RW(Klass, Attr) ATTR_RW(Klass, Attr, double, "f", rb_float_new)
#define ATTR_FLOAT_RW(Klass, Attr) ATTR_RW(Klass, Attr, float, "f", rb_float_new)
#define ATTR_INT_RW(Klass, Attr)   ATTR_RW(Klass, Attr, int, "i", rb_fix_new)

#endif