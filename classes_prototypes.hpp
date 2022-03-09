#ifndef TEST_EXERCISE_CLASSES_PROTOTYPES_HPP
#define TEST_EXERCISE_CLASSES_PROTOTYPES_HPP

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

void	read_fill_game_inventory(std::vector<Item *> *items);
bool	check_filter_attributes(Item *item, nlohmann::json *json_modifier);
void	print_message(nlohmann::json *json_arr, string item_ident, double new_value);
void	print_objects(std::vector<Item *> *items);

#endif
