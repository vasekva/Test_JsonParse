#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "./json/include/nlohmann/json.hpp"
#include <fstream>

#ifndef COLOR

#define COLOR
# define BACK_GRAY		"\033[47m"
# define NORM			"\033[0m"
# define BOLD			"\033[1m"
# define RED			"\033[31m"
# define GREEN			"\033[32m"
# define YELLOW			"\033[33m"
# define BLUE			"\033[34m"
# define PURPLE			"\033[35m"
# define BRIGHT_BLUE	"\033[36m"
# define NONE			"\033[37m"

# define URED			"\033[4;31m"
# define UGREEN			"\033[4;32m"
# define UBRIGHT_BLUE	"\033[4;36m"

#endif

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
		virtual ~Item() = default;
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

void print_message(nlohmann::json *json_arr, string item_ident, double new_value)
{
	string	type = (*json_arr)["type"];
	string	mod_ident = (*json_arr)["ident"];
	int		applied_buff = (*json_arr)["value"];

	cout << PURPLE << mod_ident << " " << NORM
		<< BLUE << type
		<< GREEN << " has been applied" << NORM << " to "
		<< BLUE << item_ident << NORM
		<< " and changed its value from "
		<< UBRIGHT_BLUE << new_value - applied_buff << NORM
		<< " to "
		<< UBRIGHT_BLUE << new_value << NORM
		<< endl;
}

void change_item_value(Item *item, nlohmann::json *json_arr)
{
	Weapon	*weapon = nullptr;
	Armour	*armour = nullptr;
	string	buff_type = (*json_arr)["type"];
	int		value = (*json_arr)["value"];
	string	mod_ident = (*json_arr)["ident"];


	if (item->type != "Armour")
		weapon = dynamic_cast<Weapon *>(item);
	else
		armour = dynamic_cast<Armour *>(item);
	if (weapon != nullptr)
	{
		if (buff_type == "DamageBuff")
		{
			weapon->damage += value;
			print_message(json_arr, item->ident, weapon->damage);
		}
		else if (buff_type == "SpeedBuff")
		{
			weapon->speed += value;
			print_message(json_arr, item->ident, weapon->speed);
		}
	}
	else
	{
		if (armour != nullptr)
		{
			if (buff_type == "ProtectionBuff")
			{
				armour->protection += value;
				print_message(json_arr,mod_ident, armour->protection);
			}
		}
		else
			cout << item->ident << RED << " Cast error!" << NORM;
	}
}

int is_enough_value(Item *item, nlohmann::json *j)
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

	int return_val = 0;
	switch (index)
	{
		case 0:
		{
			if (item->level > parameter_val) { return_val = 1; } break ;
		}
		case 1:
		{
			if (item->level < parameter_val) { return_val = 1; } break ;
		}
		case 2:
		{
			if (item->level >= parameter_val) { return_val = 1; } break;
		}
		case 3:
		{
			if (item->level <= parameter_val) { return_val = 1; } break ;
		}
		case 4:
		{
			if (item->level == parameter_val) { return_val = 1; } break ;
		}
		default: { return_val = -1; }
	}
	return (return_val);
}

void change_items_by_rare(std::vector<Item *> *items, nlohmann::json *j, string buff_type, int value)
{

}


int parse_numeric_parameter(Item *item, nlohmann::json *filer)
{
	string	parameters[] = {"level", "damage", "speed", "protection"};
	string	parameter_name = (*filer)[0];
	int		index = 0;

	int length = (sizeof(parameters) / sizeof(parameters[0]));
	while (index < length)
	{
		if (parameters[index] == parameter_name)
			break;
		index++;
	}

//	for (int i = 0; i < (*items).size(); i++)
//	{
		switch (index)
		{
			case 0:
			{
				int res = is_enough_value(item, filer);
//				cout << "Item " << item->ident << " has got value: " << res << endl;
				return (res);
			}
//			case 1:
//				change_items_by_damage(items, j, buff_type, value); return ;
//			case 2:
//				change_items_by_speed(items, j, buff_type, value); return ;
//			case 3:
//				change_items_by_protection(items, j, buff_type, value); return ;
			default:
				return (-1);
		}
//	}
}

int parse_string_parameter(Item *item, nlohmann::json *j)
{
	int return_val = 0;

	try
	{
		if (j[0]["type"] == item->type)
		{
//			cout << j[0]["type"] << " == " << item->type << endl;
			return_val = 1;
		}
	}
	catch (std::exception e)
	{

	}
	return (return_val);
}

//TODO:: изменить код так, чтобы изменения применялись только к тем объектам, которые имеют все
// необоходимые параметры согласно фильтрам
void parse_filter_attribute(std::vector<Item *> *items, nlohmann::json *json_arr)
{
	int				result_sum = 0;
	string			buff_type = (*json_arr)["type"];
	nlohmann::json	*filters = &(*json_arr)["filters"];

	for (int i = 0; i < (*items).size(); i++)
	{
		for (int ind = 0; ind < (*filters).size(); ind++)
		{
			if ((*filters)[ind].is_array())
				result_sum += parse_numeric_parameter((*items)[i], &(*filters)[ind]);
			else
			{
				result_sum += parse_string_parameter((*items)[i], &(*filters)[ind]);
			}
		}
//		cout << (*items)[i]->ident << " RES_FLAG: " << result_sum << " vs " << (*filters).size() << endl;
		if (result_sum == (*filters).size())
		{
			change_item_value((*items)[i], json_arr);
		}
		result_sum = 0;
	}
}

void read_item_modificators(std::vector<Item *> *items)
{
	std::ifstream stream("modificators.json");
	nlohmann::json json;
	stream >> json;
	std::cout << json << std::endl;

	std::string s = json.dump();

	for (int i = 0; json[i] != nullptr; i++)
	{
		try
		{
			if (json[i]["filters"].is_array())
			{
				parse_filter_attribute(items, &json[i]);
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

	read_item_modificators(&items);
}

//git commit -m"Completed applying the DamageBuff filters by level and type"