/*
** config.cpp
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

#include "config.h"
#include "util.h"
#include "debugwriter.h"
#include "sdl-util.h"
#include "version.h"
#include <toml++/toml.h>
#include <argparse/argparse.hpp>
#include <sstream>
#include <filesystem>

#define CONF_FILE "../modshot.toml"

Config::Config()
{
}

#define READ_VALUE_CAST(type, path, location, cast)                        \
	if (node[#location])                                                   \
	{                                                                      \
		if (node[#location].is_##type())                                   \
			path = (cast)*node[#location].as_##type();                     \
		else                                                               \
			Debug() << "Invalid type for" << #path << "expected" << #type; \
	}

#define READ_BOOL(path, location) READ_VALUE_CAST(boolean, path, location, bool);
#define READ_INT(path, location) READ_VALUE_CAST(integer, path, location, long int);

void Config::read(int argc, char *argv[], void (*errorFunc)(const std::string &))
{
	read_config_file(errorFunc);

	read_arguments(argc, argv, errorFunc);
}

void Config::read_arguments(int argc, char *argv[], void (*errorFunc)(const std::string &))
{
	argparse::ArgumentParser program("modshot", MODSHOT_VERSION);

	program.add_argument("--printFPS", "-pfps")
		.help("print fps in the window titlebar")
		.nargs(0)
		.action([&](const std::string &value)
				{ graphics.printFPS = true; });

	program.add_argument("--fullscreen", "-f")
		.help("start modshot in fullscreen")
		.nargs(0)
		.action([&](const std::string &value)
				{ graphics.fullscreen = true; });

	program.add_argument("--fixedAspectRatio", "-far")
		.help("force a fixed aspect ratio")
		.nargs(0)
		.action([&](const std::string &value)
				{ graphics.fixedAspectRatio = true; });

	program.parse_args(argc, argv);
}

void Config::read_config_file(void (*errorFunc)(const std::string &))
{
		if (std::filesystem::exists(CONF_FILE))
	{
		toml::table table;
		try
		{
			table = toml::parse_file(CONF_FILE);
			if (table["graphics"])
			{
				auto node = table["graphics"];

				READ_BOOL(graphics.printFPS, printFPS)
				READ_BOOL(graphics.fullscreen, fullscreen)
				READ_BOOL(graphics.fixedAspectRatio, fixedAspectRatio)
				READ_BOOL(graphics.smoothScaling, smoothScaling)
				READ_BOOL(graphics.vsync, vsync)
				READ_BOOL(graphics.subImageFix, subImageFix)
				READ_BOOL(graphics.enableBlitting, enableBlitting)
				READ_BOOL(graphics.frameSkip, frameSkip)
				READ_BOOL(graphics.solidFonts, solidFonts)

				READ_INT(graphics.defScreenW, defScreenW)
				READ_INT(graphics.defScreenH, defScreenH)
				READ_INT(graphics.maxTextureSize, maxTextureSize)
				READ_INT(graphics.fixedFramerate, fixedFramerate)
			}

			if (table["mjit"])
			{
				auto node = table["mjit"];

				READ_BOOL(mjit.enabled, enabled)
				
				READ_INT(mjit.verbosity, verbosity)
				READ_INT(mjit.maxCache, maxCache)
				READ_INT(mjit.minCalls, minCalls)
			}

			if (table["yjit"])
			{
				auto node = table["yjit"];

				READ_BOOL(yjit.enabled, enabled)
				READ_BOOL(yjit.greedyVersioning, greedyVersioning)

				READ_INT(yjit.callThreshold, callThreshold)
				READ_INT(yjit.maxVersions, maxVersion)
			}

			if (table["audio"])
			{
				auto node = table["audio"];

				READ_INT(audio.sourceCount, sourceCount)
				READ_INT(audio.audioChannels, audioChannels)
			}
		}
		catch (const toml::parse_error &error)
		{
			std::stringstream ss("Config file parsing failed:\n");
			ss << error;
			errorFunc(ss.str());
		}
	}
}