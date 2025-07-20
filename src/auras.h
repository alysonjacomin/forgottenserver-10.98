// Copyright 2023 The Forgotten Server Authors. All rights reserved.
// Use of this source code is governed by the GPL-2.0 License that can be found in the LICENSE file.

#ifndef FS_AURAS_H
#define FS_AURAS_H

struct Aura
{
	Aura(uint16_t id, std::string_view name, int32_t speed, bool premium) :
		name{ name }, speed{ speed }, id{ id }, premium{ premium }
	{
	}

	std::string name;
	int32_t speed;

	uint16_t id;
	bool premium;
};

class Auras
{
public:
	bool reload();
	bool loadFromXml();
	Aura* getAuraByID(uint16_t id);
	Aura* getAuraByName(std::string_view name);


	const std::vector<Aura>& getAuras() const { return auras; }

private:
	std::vector<Aura> auras;
};

#endif // FS_AURAS_H
