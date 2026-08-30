//
// Created by siii on 30-08-2026.
//

#ifndef CALIBURNER_JSON_HPP
#define CALIBURNER_JSON_HPP
#include <nlohmann/json.hpp>

using json = nlohmann::json;

template <typename T>
T json_getOrDefault(const nlohmann::json& json, std::string_view key, T fallback)
{
	try
	{
		return json.value<T>(key, fallback);
	}
	catch (const nlohmann::json::exception&)
	{
		return fallback;
	}
}

#endif //CALIBURNER_JSON_HPP
