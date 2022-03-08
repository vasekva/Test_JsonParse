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

void print_message(string ident, string parameter, double prev_value, double new_value)
{
	cout << BLUE << ident << NORM
		<< " item " << PURPLE << parameter
		<< GREEN << " successfully changed" << NORM
		<< " from "
		<< UBRIGHT_BLUE << prev_value << NORM
		<< " to "
		<< UBRIGHT_BLUE << new_value << NORM << endl;
}

void change_item_value(Item *item, string buff_type, int value)
{
	Weapon	*weapon = nullptr;
	Armour	*armour = nullptr;

	if (item->type != "Armour")
		weapon = dynamic_cast<Weapon *>(item);
	else
		armour = dynamic_cast<Armour *>(item);
	if (weapon != nullptr)
	{
		if (buff_type == "DamageBuff")
		{
			double prev_val = weapon->damage;
			weapon->damage += value;
			print_message(item->ident, "damage", prev_val, weapon->damage);
		}
		else if (buff_type == "SpeedBuff")
		{
			double prev_val = weapon->speed;
			weapon->speed += value;
			print_message(item->ident, "speed", prev_val, weapon->speed);
		}
	}
	else
	{
		if (armour != nullptr)
		{
			if (buff_type == "ProtectionBuff")
			{
				double prev_val = armour->protection;
				armour->protection += value;
				print_message(item->ident, "protection", prev_val, armour->protection);
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

//	for (int i = 0; i < (*items).size(); i++)
//	{
		int return_val = 0;
		switch (index)
		{
			case 0:
			{
				if (item->level > parameter_val)
				{
//					cout << item->ident << " level " << item->level << " > " << parameter_val << endl;
//					cout << "RETURN 0" << endl;
					return_val = 1;
//					change_item_value((*items)[i], buff_type, value);
				}
				break ;
			}
			case 1:
			{
				if (item->level < parameter_val)
				{
//					cout << item->ident << " level " << item->level << " < " << parameter_val << endl;
//					cout << "RETURN 1" << endl;
					return_val = 1;
//					change_item_value((*items)[i], buff_type, value);
				}
				break ;
			}
			case 2:
			{
//				cout << item->ident << endl;
				if (item->level >= parameter_val)
				{
//					cout << item->ident << " level " << item->level << " >= " << parameter_val << endl;
//					cout << "RETURN 2" << endl;
					return_val = 1;
//					change_item_value((*items)[i], buff_type, value);
				}
				break;
			}
			case 3:
			{
				if (item->level <= parameter_val)
				{
//					cout << item->ident << " level " << item->level << " <= " << parameter_val << endl;
//					cout << "RETURN 3" << endl;
					return_val = 1;
//					change_item_value((*items)[i], buff_type, value);
				}
				break ;
			}
			case 4:
			{
				if (item->level == parameter_val)
				{
//					cout << item->ident << " level " << item->level << " = " << parameter_val << endl;
//					cout << "RETURN 4" << endl;
					return_val = 1;
//					change_item_value((*items)[i], buff_type, value);
				}
				break ;
			}
			default:
			{
//				cout << "RETURN -1" << endl;
				return_val = -1;
			}
		}
		return (return_val);
//	}
}

void change_items_by_rare(std::vector<Item *> *items, nlohmann::json *j, string buff_type, int value)
{

}


int parse_numeric_parameter(Item *item, nlohmann::json *j)
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

//	for (int i = 0; i < (*items).size(); i++)
//	{
		switch (index)
		{
			case 0:
			{
				int res = is_enough_value(item, j);
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

//TODO:: изменить код так, чтобы изменения применялись только к тем объектам, которые имеют все
// необоходимые параметры согласно фильтрам
void parse_filter_attribute(std::vector<Item *> *items, nlohmann::json *j, string buff_type, int value) {
	int result_flag = 0;

	for (int i = 0; i < (*items).size(); i++)
	{
		for (int ind = 0; ind < (*j).size(); ind++)
		{
			if ((*j)[ind].is_array())
				result_flag = parse_numeric_parameter((*items)[i], &(*j)[ind]);
			else
			{
				if ((*j).size() > 1)
				{
//					cout << "This modificator has two filters!" << " ";
//					cout << *j << endl;
				}
				else
				{
//					cout << "This modificator has one filters!" << " ";
//					cout << *j << endl;
//					cout << (*j)[ind] << endl;
				}
			}
		}
		cout << "RES_FLAG: " << result_flag << endl;
		if (result_flag == 1)
		{
			change_item_value((*items)[i], buff_type, value);
			result_flag = 0;
		}
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
				parse_filter_attribute(items, &j[i]["filters"], j[i]["type"], j[i]["value"]);
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
