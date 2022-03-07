#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "./json/include/nlohmann/json.hpp"
//#include "./json/include/delohmann/json.hpp"
#include <fstream>

using std::cout;
using std::endl;
using std::string;


struct Person
{
    string name;
    int age;
};

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

void read_game_object()
{
	std::ifstream stream("data.json");
    nlohmann::json j;
	stream >> j;
    std::cout << j << std::endl;

    Item item;

	std::vector<Item *> items;

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
			items.push_back(object);
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
			items.push_back(object);
		}
	}

	for (int i = 0; i < items.size(); i++)
	{
		cout << i << " " << items[i]->ident << endl;
	}
}

int main()
{
	read_game_object();
}
