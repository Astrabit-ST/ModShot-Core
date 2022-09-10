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

		int64_t defScreenW = 640;
		int64_t defScreenH = 480;
		int64_t maxTextureSize = 0;
		int64_t fixedFramerate = 0;
	} graphics;

	struct
	{
		bool enabled = false;

		int64_t verbosity = 0;
		int64_t maxCache = 100;
		int64_t minCalls = 10000;
	} mjit;

	struct
	{
		bool enabled = false;
		bool greedyVersioning = false;

		int64_t callThreshold = 10;
		int64_t maxVersions = 4;
	} yjit;

	struct
	{
		int64_t sourceCount = 64;
		int64_t audioChannels = 0;
	} audio;

	struct
	{
		std::vector<std::string> rtps;
		std::vector<std::string> fontSubs;
		std::vector<std::string> rubyLoadpaths;

		std::string customDataPath;
		std::string commonDataPath = "OneShot";
		std::string iconPath = "";
		std::string exeName = "modshot";

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

		int64_t rgssVersion = 1;

		bool console = false;
		bool debugMode = false;
	} game;

	struct {
		bool enabled = false;
		bool titlebar = false;
		std::string name = "The Journal";
		std::string imagePath = "./Graphics/Journal/";
	} screen_mode;

	Config();

	void read(int argc, char *argv[], void (*errorFunc)(const std::string &));
	void read_config_file(void (*errorFunc)(const std::string &));
	void read_arguments(int argc, char *argv[], void (*errorFunc)(const std::string &));
};

#endif // CONFIG_H
