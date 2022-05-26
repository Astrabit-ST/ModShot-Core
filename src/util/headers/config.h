/*
** config.h
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

#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>
#include <set>

struct Config
{
	int rgssVersion;

	bool debugMode;
	bool screenMode;
	bool printFPS;

	bool fullscreen;
	bool fixedAspectRatio;
	bool smoothScaling;
	bool vsync;

	int defScreenW;
	int defScreenH;
	std::string windowTitle;

	int fixedFramerate;
	bool frameSkip;
	bool syncToRefreshrate;

	bool solidFonts;

	bool subImageFix;
	bool enableBlitting;
	int maxTextureSize;

	std::string gameFolder;
	bool allowSymlinks;
	bool pathCache;

	/*
	MJIT options (experimental):
	  --mjit-warnings Enable printing JIT warnings
	  --mjit-debug    Enable JIT debugging (very slow), or add cflags if specified
	  --mjit-wait     Wait until JIT compilation finishes every time (for testing)
	  --mjit-save-temps
	                  Save JIT temporary files in $TMP or /tmp (for testing)
	  --mjit-verbose=num
	                  Print JIT logs of level num or less to stderr (default: 0)
	  --mjit-max-cache=num
	                  Max number of methods to be JIT-ed in a cache (default: 10000)
	  --mjit-min-calls=num
	                  Number of calls to trigger JIT (for testing, default: 10000)

	YJIT options (experimental):
	  --yjit-exec-mem-size=num
	                  Size of executable memory block in MiB (default: 256)
	  --yjit-call-threshold
	                  Number of calls to trigger JIT (default: 10)
	  --yjit-max-versions
	                  Maximum number of versions per basic block (default: 4)
	  --yjit-greedy-versioning
	                  Greedy versioning mode (default: disabled)
	*/

	bool mjitEnabled;
	int mjitVerbosity;
	int mjitMaxCache;
	int mjitMinCalls;

	bool yjitEnabled;
	int yjitCallThreshold;
	int yjitMaxVersions;
	bool yjitGreedyVersioning;

	// This is for older versions of Ruby (3.0.* and below)
	bool jitEnabled;
	int jitVerbosity;
	int jitMaxCache;
	int jitMinCalls;

	bool winConsole;

	std::string customWindowFrames;

	std::string iconPath;

	struct
	{
		int sourceCount;
	} SE;

	int audioChannels;

	bool useScriptNames;

	std::string customScript;
	std::set<std::string> preloadScripts;
	std::vector<std::string> rtps;

	std::vector<std::string> fontSubs;

	std::vector<std::string> rubyLoadpaths;

	/* Editor flags */
	struct {
		bool debug;
		bool battleTest;
	} editor;

	/* Game INI contents */
	struct {
		std::string scripts;
		std::string title;
	} game;

	/* Internal */
	std::string customDataPath;
	std::string commonDataPath;

	Config();

	void read(int argc, char *argv[]);
};

#endif // CONFIG_H
