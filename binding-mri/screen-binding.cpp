#include "etc.h"
#include "binding-util.h"
#include "binding-types.h"
#include "debugwriter.h"
#include "config.h"
#include "sharedstate.h"
#include "pipe.h"

struct ScreenImage
{
	Pipe ipc;

	ScreenImage(const char *name) : ipc()
	{
		ipc.open(name, Pipe::Write);

		// Create process
#if defined _WIN32
		WCHAR path[MAX_PATH];
		WCHAR gameFolder[MAX_PATH];
		WCHAR exePath[MAX_PATH];
		MultiByteToWideChar(CP_UTF8, 0, shState->config().game.folder.c_str(), -1, gameFolder, MAX_PATH);
		MultiByteToWideChar(CP_UTF8, 0, shState->config().paths.exeName.c_str(), -1, gameFolder, MAX_PATH);
		GetModuleFileNameW(NULL, path, MAX_PATH);
		STARTUPINFOW si;
		memset(&si, 0, sizeof(si));
		si.cb = sizeof(si);
		PROCESS_INFORMATION pi;
		std::wstring argString = std::wstring(exePath + L".exe") + L"--gameFolder \"" + gameFolder + L"\" --screenMode";
		WCHAR *args = new WCHAR[argString.size() + 1];
		memcpy(args, argString.c_str(), (argString.size() + 1) * sizeof(WCHAR));
		CreateProcessW(path, args, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		delete[] args;
#else
#if defined __linux
		char path[PATH_MAX];
		ssize_t len = readlink("/proc/self/exe", path, PATH_MAX);
		if (len == -1)
			rb_raise(rb_eRuntimeError, "Cannot determine path of running executable");
		std::string exename = std::string(path, len);
#else
#endif

		pid_t pid = fork();
		if (pid == 0)
		{
			execl(exename.c_str(), shState->config().paths.exeName.c_str(),
				  "-sn", name, 
				  "-sm", NULL);
			exit(1);
		}
#endif

		ipc.connect();
	}

	~ScreenImage()
	{
		ipc.close();
	}
};

DEF_TYPE(ScreenImage);

RB_METHOD(screenInitialize)
{
	const char *name;
	rb_get_args(argc, argv, "z", &name RB_ARG_END);

	ScreenImage *s = new ScreenImage(name);
	setPrivateData(self, s);

	return self;
}

RB_METHOD(screenFinish)
{
	RB_UNUSED_PARAM;

	ScreenImage *s = getPrivateData<ScreenImage>(self);

	s->ipc.write("END", sizeof("END"));
	s->ipc.close();

	return Qnil;
}

RB_METHOD(screenSet)
{
	RB_UNUSED_PARAM;
	const char *imageName;
	rb_get_args(argc, argv, "z", &imageName RB_ARG_END);

	ScreenImage *s = getPrivateData<ScreenImage>(self);

	s->ipc.write((std::string(imageName) + '\n').c_str(), strlen(imageName) + 1);

	return Qnil;
}

RB_METHOD(screenMove)
{
	int x, y;
	rb_get_args(argc, argv, "ii", &x, &y);

	ScreenImage *s = getPrivateData<ScreenImage>(self);

	std::string str = "MOV";
	str += std::to_string(x) + ";" + std::to_string(y) + '\n';
	s->ipc.write(str.c_str(), str.size());

	return Qnil;
}

void screenBindingInit()
{
	VALUE klass = rb_define_class("ScreenImage", rb_cObject);
	_rb_define_method(klass, "initialize", screenInitialize);
	_rb_define_method(klass, "finish", screenFinish);
	_rb_define_method(klass, "set", screenSet);
	_rb_define_method(klass, "move", screenMove);
	rb_define_alloc_func(klass, classAllocate<&ScreenImageType>);
}
