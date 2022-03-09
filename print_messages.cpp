#include "classes_prototypes.hpp"

void	print_message(nlohmann::json *json_arr, string item_ident, double new_value)
{
	string	type = (*json_arr)["type"];
	string	mod_ident = (*json_arr)["ident"];
	double	applied_buff = (*json_arr)["value"];

	cout << PURPLE << mod_ident << " " << NORM
		 << BLUE << type
		 << GREEN << " has been applied" << NORM << " to "
		 << YELLOW << item_ident << NORM
		 << " and changed its value from "
		 << UBRIGHT_BLUE << new_value - applied_buff << NORM
		 << " to "
		 << UBRIGHT_BLUE << new_value << NORM
		 << endl;
}

void	print_objects(std::vector<Item *> *items)
{
	Weapon	*weapon = nullptr;
	Armour	*armour = nullptr;

	for (int i = 0; i < items->size(); i++)
	{
		weapon = dynamic_cast<Weapon *>((*items)[i]);
		if (weapon == nullptr)
		{
			armour = dynamic_cast<Armour *>((*items)[i]);
			cout << BLUE << armour->ident << ": " << endl
				 << NORM << "protection "
				 << YELLOW << armour->protection
				 << endl << endl;
		}
		else
		{
			cout << BLUE << weapon->ident << ": " << endl
				 << NORM << "damage " << YELLOW << weapon->damage << endl
				 << NORM << "speed " << YELLOW << weapon->speed << NORM
				 << endl << endl;
		}
	}
}