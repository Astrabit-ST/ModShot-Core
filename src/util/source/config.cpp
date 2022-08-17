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

#define CONF_FILE "../modshot.toml"

Config::Config()
{
}

void Config::read(int argc, char *argv[], void (*errorFunc)(const std::string &))
{
	SDLRWStream confFile(CONF_FILE, "r");

	if (confFile)
	{
		toml::table table;
		try
		{
			table = toml::parse(confFile.stream());
			Debug() << table;
		}
		catch (const toml::parse_error &error)
		{
			std::stringstream ss("Config file parsing failed:\n");
			ss << error;
			errorFunc(ss.str());
		}
	}

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

	audio.sourceCount = clamp(audio.sourceCount, 1, 64);
}
