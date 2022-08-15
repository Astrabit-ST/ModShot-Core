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
	int rgssVersion = 1;

	bool debugMode = false;
	bool screenMode = false;
	bool printFPS = false;

	bool fullscreen = false;
	bool fixedAspectRatio = false;
	bool smoothScaling = false;
	bool vsync = true;

	int defScreenW = 640;
	int defScreenH = 480;
	std::string windowTitle = "";

	int fixedFramerate = 0;
	bool frameSkip = true;
	bool syncToRefreshrate = false;

	bool solidFonts = false;

	bool subImageFix = false;
	bool enableBlitting = true;
	int maxTextureSize = 0;

	std::string gameFolder ="..";
	bool allowSymlinks = false;
	bool pathCache = true;

	bool mjitEnabled = false;
	int mjitVerbosity = 0;
	int mjitMaxCache = 100;
	int mjitMinCalls = 10000;

	bool yjitEnabled = false;
	int yjitCallThreshold = 10;
	int yjitMaxVersions = 4;
	bool yjitGreedyVersioning = false;

	bool winConsole = false;

	std::string iconPath = "";

	struct
	{
		int sourceCount = 64;
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
		bool debug = false;
		bool battleTest = false;
	} editor;

	/* Game INI contents */
	struct {
		std::string scripts = "Data/xScripts.rxdata";
		std::string title = "OneShot";
	} game;

	/* Internal */
	std::string customDataPath;
	std::string commonDataPath = "OneShot";

	Config();

	void read(int argc, char *argv[], void (*errorFunc)(const std::string&));
};

#endif // CONFIG_H
