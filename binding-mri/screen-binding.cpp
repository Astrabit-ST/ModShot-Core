#include "etc.h"
#include "binding-util.h"
#include "binding-types.h"
#include "debugwriter.h"
#include "config.h"
#include "sharedstate.h"
#include "pipe.h"

static Pipe ipc;

static void start(const char *name, bool titlebar)
{
	ipc.open("oneshot-pipe", Pipe::Write);

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
			  "-sm", titlebar ? "-stb" : NULL, NULL);
		exit(1);
	}
#endif

	ipc.connect();
}

#define GUARD_IPC \
	if (!ipc.isOpen()) \
		rb_raise(rb_eRuntimeError, "screen not started");

RB_METHOD(screenStart)
{
	const char *name;
	bool titlebar;
	rb_get_args(argc, argv, "zb", &name, &titlebar RB_ARG_END);

	start(name, titlebar);

	return Qnil;
}

RB_METHOD(screenFinish)
{
	RB_UNUSED_PARAM;
	ipc.write("END", sizeof("END"));
	ipc.close();
	return Qnil;
}

RB_METHOD(screenSet)
{
	RB_UNUSED_PARAM;
	const char *imageName;
	rb_get_args(argc, argv, "z", &imageName RB_ARG_END);
	GUARD_IPC
	ipc.write((std::string(imageName) + '\n').c_str(), strlen(imageName) + 1);
	return Qnil;
}

RB_METHOD(screenMove) {
	int x, y;
	rb_get_args(argc, argv, "ii", &x, &y);
	GUARD_IPC
	std::string str = "MOV"; 
	str += std::to_string(x) + ";" + std::to_string(y) + '\n';
	ipc.write(str.c_str(), str.size());
	return Qnil;
}

void screenBindingInit()
{
	VALUE module = rb_define_module("Screen");
	_rb_define_module_function(module, "start", screenStart);
	_rb_define_module_function(module, "finish", screenFinish);
	_rb_define_module_function(module, "set", screenSet);
	_rb_define_module_function(module, "move", screenMove);
}
