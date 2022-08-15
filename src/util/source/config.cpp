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
#include <toml++/toml.h>
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

	SE.sourceCount = clamp(SE.sourceCount, 1, 64);
}
