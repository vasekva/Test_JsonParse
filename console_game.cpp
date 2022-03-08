#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "./json/include/nlohmann/json.hpp"
#include <fstream>

using std::cout;
using std::endl;
using std::string;

class Item
{
	public:
		string	ident;
		string	type;
		string	rarity;
		int		level;

		Item() {}
		Item(string ident, string type, int level, string rarity)
			: ident(std::move(ident)), type(std::move(type)), level(level), rarity(std::move(rarity))
		{}
		~Item() = default;
	private:
};

class Weapon : public Item
{
	public:
		double damage;
		double speed;

		Weapon() {}
		Weapon(string ident, string type, int level, string rarity, double damage, double speed)
			: Item(ident, type, level, rarity), damage(damage), speed(speed)
		{}
		~Weapon() = default;
	private:
};

class Armour : public Item
{
	public:
		double protection;

		Armour(string ident, string type, int level, string rarity, double protection)
		: Item(ident, type, level, rarity), protection(protection)
		{}
		~Armour() = default;
		Armour() {}
	private:
};

void read_game_object(std::vector<Item *> *items)
{
	std::ifstream stream("inventory.json");
    nlohmann::json j;
	stream >> j;
    std::cout << j << std::endl;



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

void change_items_by_level(std::vector<Item *> *items, nlohmann::json *j)
{
	string	comparisons[] = {">", "<", ">=", "<=", "="};
	string	parameter_action = (*j)[1];
	string	parameter_name = (*j)[0];
	int		parameter_val = (*j)[2];
	int		index = 0;

	int length = (sizeof(comparisons) / sizeof(comparisons[0]));
	while (index != length)
	{
		if (comparisons[index] == parameter_action)
			break;
		index++;
	}

	for (int i = 0; i < (*items).size(); i++)
	{
		switch (index)
		{
			case 0:
				if ((*items)[i]->level > parameter_val)
				{
					cout << (*items)[i]->ident << " level " << (*items)[i]->level << " > " << parameter_val << endl;
				}
				break ;
			case 1:
				if ((*items)[i]->level < parameter_val)
				{
					cout << (*items)[i]->ident << " level " << (*items)[i]->level << " < " << parameter_val << endl;
				}
				break ;
			case 2:
				if ((*items)[i]->level >= parameter_val)
				{
					cout << (*items)[i]->ident << " level " << (*items)[i]->level << " >= " << parameter_val << endl;
				}
				break ;
			case 3:
				if ((*items)[i]->level <= parameter_val)
				{
					cout << (*items)[i]->ident << " level " << (*items)[i]->level << " <= " << parameter_val << endl;
				}
				break ;
			case 4:
				if ((*items)[i]->level == parameter_val)
				{
					cout << (*items)[i]->ident << " level " << (*items)[i]->level << " = " << parameter_val << endl;
				}
				break ;
		}
	}
}

void parse_numeric_parameter(std::vector<Item *> *items, nlohmann::json *j)
{
	string	parameters[] = {"level", "damage", "speed", "protection"};
	string	parameter_name = (*j)[0];
	int		index = 0;

	int length = (sizeof(parameters) / sizeof(parameters[0]));
	while (index < length)
	{
		if (parameters[index] == parameter_name)
			break;
		index++;
	}

	for (int i = 0; i < (*items).size(); i++)
	{
		switch (index)
		{
			case 0:
				change_items_by_level(items, j); return ;
		}
	}
}

void parse_filter_array(std::vector<Item *> *items, nlohmann::json *j)
{
	for (int ind = 0; ind < (*j).size(); ind++)
	{
		if ((*j)[ind].is_array())
			parse_numeric_parameter(items, &(*j)[ind]);
	}
}

void read_item_modificators(std::vector<Item *> *items)
{
	std::ifstream stream("modificators.json");
	nlohmann::json j;
	stream >> j;
	std::cout << j << std::endl;

	std::string s = j.dump();

	for (int i = 0; j[i] != nullptr; i++)
	{
		try
		{
			if (j[i]["filters"].is_array())
			{
				parse_filter_array(items, &j[i]["filters"]);
			}

		}
		catch (...)
		{
			cout << "Fuck" << endl;
		}
	}
}

int main()
{
	std::vector<Item *> items;

	read_game_object(&items);

	for (int i = 0; i < items.size(); i++)
	{
		if (items[i]->type == "Armour")
			cout << "Armour\n";
		else
			cout << "Weapon\n";
	}

	read_item_modificators(&items);
}
