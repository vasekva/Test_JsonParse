#include "classes_prototypes.hpp"

/**
 * Cчитывает данные из файла и заносит их в json-буффер
 * библиотеки <nlohmann/json>, после чего создает
 * новые объекты основываясь на считанных данных
 * и заполняет ими вектор предметов.
 */
void read_fill_game_inventory(std::vector<Item *> *items)
{
	std::ifstream stream("./json_files/inventory.json");
	nlohmann::json j;
	stream >> j;

	stream.close();
	if (j.is_null())
		throw std::exception();

	for (int i = 0; j[i] != nullptr; i++)
	{
		if (j[i]["type"].get<std::string>() == "Armour")
		{
			Armour *object = new Armour();
			object->ident = j[i]["ident"].get<std::string>();
			object->type = j[i]["type"].get<std::string>();
			object->level = j[i]["level"].get<int>();
			object->rarity = j[i]["rarity"].get<std::string>();
			object->protection = j[i]["protection"].get<double>();
			(*items).push_back(object);
		}
		else
		{
			Weapon *object = new Weapon();
			object->ident = j[i]["ident"].get<std::string>();
			object->type = j[i]["type"].get<std::string>();
			object->level = j[i]["level"].get<int>();
			object->rarity = j[i]["rarity"].get<std::string>();
			object->damage = j[i]["damage"].get<double>();
			object->speed =  j[i]["speed"].get<double>();
			(*items).push_back(object);
		}
	}
}

