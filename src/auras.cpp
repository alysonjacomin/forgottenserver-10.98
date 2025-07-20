// Copyright 2023 The Forgotten Server Authors. All rights reserved.
// Use of this source code is governed by the GPL-2.0 License that can be found in the LICENSE file.

#include "otpch.h"

#include "auras.h"

#include "pugicast.h"
#include "tools.h"

bool Auras::reload()
{
	auras.clear();
	return loadFromXml();
}

bool Auras::loadFromXml()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("data/XML/auras.xml");
	if (!result) {
		printXMLError("Error - Auras::loadFromXml", "data/XML/auras.xml", result);
		return false;
	}

	for (auto auraNode : doc.child("auras").children()) {
		uint16_t nodeId = pugi::cast<uint16_t>(auraNode.attribute("id").value());
		if (nodeId == 0 || nodeId > std::numeric_limits<uint16_t>::max()) {
			std::cout << "[Notice - Auras::loadFromXml] Aura id "" << nodeId << "" is not within 1 and 65535 range"
				<< std::endl;
			continue;
		}

		if (getAuraByID(nodeId)) {
			std::cout << "[Notice - Auras::loadFromXml] Duplicate aura with id: " << nodeId << std::endl;
			continue;
		}

		auras.emplace_back(
			static_cast<uint16_t>(nodeId),
			auraNode.attribute("name").as_string(), pugi::cast<int32_t>(auraNode.attribute("speed").value()),
			auraNode.attribute("premium").as_bool());
	}
	auras.shrink_to_fit();
	return true;
}

Aura* Auras::getAuraByID(uint16_t id)
{
	auto it = std::find_if(auras.begin(), auras.end(), [id](const Aura& aura) { return aura.id == id; });

	return it != auras.end() ? &*it : nullptr;
}

Aura* Auras::getAuraByName(std::string_view name)
{
	for (auto& it : auras) {
		if (_stricmp(name.data(), it.name.c_str()) == 0) {
			return &it;
		}
	}

	return nullptr;
}
