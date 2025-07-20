#include "otpch.h"

#include "effects.h"

#include "pugicast.h"
#include "tools.h"

bool Effects::reload()
{
	effects.clear();
	return loadFromXml();
}

bool Effects::loadFromXml()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("data/XML/effects.xml");
	if (!result) {
		printXMLError("Error - Effects::loadFromXml", "data/XML/effects.xml", result);
		return false;
	}

	for (auto effectNode : doc.child("effects").children()) {
		uint16_t nodeId = pugi::cast<uint16_t>(effectNode.attribute("id").value());
		if (nodeId == 0 || nodeId > std::numeric_limits<uint16_t>::max()) {
			std::cout << "[Notice - Effects::loadFromXml] Effect id "" << nodeId << "" is not within 1 and 65535 range"
				<< std::endl;
			continue;
		}

		if (getEffectByID(nodeId)) {
			std::cout << "[Notice - Effects::loadFromXml] Duplicate effect with id: " << nodeId << std::endl;
			continue;
		}

		effects.emplace_back(
			static_cast<uint16_t>(nodeId),
			effectNode.attribute("name").as_string(), pugi::cast<int32_t>(effectNode.attribute("speed").value()),
			effectNode.attribute("premium").as_bool());
	}
	effects.shrink_to_fit();
	return true;
}

Effect* Effects::getEffectByID(uint16_t id)
{
	auto it = std::find_if(effects.begin(), effects.end(), [id](const Effect& effect) { return effect.id == id; });

	return it != effects.end() ? &*it : nullptr;
}

Effect* Effects::getEffectByName(std::string_view name)
{
	for (auto& it : effects) {
		if (_stricmp(name.data(), it.name.c_str()) == 0) {
			return &it;
		}
	}

	return nullptr;
}
