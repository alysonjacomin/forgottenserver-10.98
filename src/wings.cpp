#include "otpch.h"

#include "wings.h"

#include "pugicast.h"
#include "tools.h"

bool Wings::reload()
{
	wings.clear();
	return loadFromXml();
}

bool Wings::loadFromXml()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("data/XML/wings.xml");
	if (!result) {
		printXMLError("Error - Wings::loadFromXml", "data/XML/wings.xml", result);
		return false;
	}

	for (auto wingNode : doc.child("wings").children()) {
		uint16_t nodeId = pugi::cast<uint16_t>(wingNode.attribute("id").value());
		if (nodeId == 0 || nodeId > std::numeric_limits<uint16_t>::max()) {
			std::cout << "[Notice - Wings::loadFromXml] Wing id \"" << nodeId << "\" is not within 1 and 65535 range"
				<< std::endl;
			continue;
		}

		if (getWingByID(nodeId)) {
			std::cout << "[Notice - Wings::loadFromXml] Duplicate wing with id: " << nodeId << std::endl;
			continue;
		}

		wings.emplace_back(
			static_cast<uint16_t>(nodeId),
			wingNode.attribute("name").as_string(), pugi::cast<int32_t>(wingNode.attribute("speed").value()),
			wingNode.attribute("premium").as_bool());
	}
	wings.shrink_to_fit();
	return true;
}

Wing* Wings::getWingByID(uint16_t id)
{
	auto it = std::find_if(wings.begin(), wings.end(), [id](const Wing& wing) { return wing.id == id; });

	return it != wings.end() ? &*it : nullptr;
}

Wing* Wings::getWingByName(std::string_view name)
{
	for (auto& it : wings) {
		if (_stricmp(name.data(), it.name.c_str()) == 0) {
			return &it;
		}
	}

	return nullptr;
}
