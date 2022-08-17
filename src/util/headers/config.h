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
	struct
	{
		bool printFPS = false;
		bool fullscreen = false;
		bool fixedAspectRatio = true;
		bool smoothScaling = false;
		bool vsync = true;
		bool subImageFix = false;
		bool enableBlitting = true;
		bool frameSkip = true;
		bool syncToRefreshrate = false;
		bool solidFonts = false;

		long int defScreenW = 640;
		long int defScreenH = 480;
		long int maxTextureSize = 0;
		long int fixedFramerate = 0;
	} graphics;

	struct
	{
		bool enabled = false;

		long int verbosity = 0;
		long int maxCache = 100;
		long int minCalls = 10000;
	} mjit;

	struct
	{
		bool enabled = false;
		bool greedyVersioning = false;

		long int callThreshold = 10;
		long int maxVersions = 4;
	} yjit;

	struct
	{
		long int sourceCount = 64;
		long int audioChannels = 0;
	} audio;

	struct
	{
		std::vector<std::string> rtps;
		std::vector<std::string> fontSubs;
		std::vector<std::string> rubyLoadpaths;

		std::string customDataPath;
		std::string commonDataPath = "OneShot";
		std::string iconPath = "";

		bool useScriptNames;
		bool allowSymlinks = false;
		bool pathCache = true;
	} paths;

	/* Editor flags */
	struct
	{
		bool debug = false;
		bool battleTest = false;
	} editor;

	/* Game INI contents */
	struct
	{
		std::string scripts = "Data/xScripts.rxdata";
		std::string title = "OneShot";
		std::string folder = "..";
		std::string windowTitle = "";
		std::string customScript;

		std::set<std::string> preloadScripts;

		long int rgssVersion = 1;

		bool winConsole = false;
		bool debugMode = false;
		bool screenMode = false;
	} game;

	Config();

	void read(int argc, char *argv[], void (*errorFunc)(const std::string &));
	void read_config_file(void (*errorFunc)(const std::string &));
	void read_arguments(int argc, char *argv[], void (*errorFunc)(const std::string &));
};

#endif // CONFIG_H
