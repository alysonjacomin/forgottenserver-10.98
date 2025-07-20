// Copyright 2023 The Forgotten Server Authors. All rights reserved.
// Use of this source code is governed by the GPL-2.0 License that can be found in the LICENSE file.

#ifndef FS_WINGS_H
#define FS_WINGS_H

struct Wing
{
	Wing(uint16_t id, std::string_view name, int32_t speed, bool premium) :
		name{ name }, speed{ speed }, id{ id }, premium{ premium }
	{
	}

	std::string name;
	int32_t speed;

	uint16_t id;
	bool premium;
};

class Wings
{
public:
	bool reload();
	bool loadFromXml();
	Wing* getWingByID(uint16_t id);
	Wing* getWingByName(std::string_view name);


	const std::vector<Wing>& getWings() const { return wings; }

private:
	std::vector<Wing> wings;
};

#endif // FS_WINGS_H#pragma once
