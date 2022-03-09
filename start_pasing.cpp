#include "classes_prototypes.hpp"

/**
 * Применяет значение(value) модификатора к предмету
 * основываясь на типе буффера соответствующего
 * модификатора.
 *
 * Перед применением выполняется попытка каста
 * текущего типа предмета к нужному типу для
 * открытия соответствующих полей.
 *
 * @param item: предмет инвентаря
 * @param json_modifier: json элемент модификаторов
 *
 * @exception
 * 	Выводит в консоль сообщение об ошибке каста и
 * 	выбрасываает пустое исключение если не удалось
 * 	выполнить dynamic_cast
 */
static void change_item_value(Item *item, nlohmann::json *json_modifiers)
{
	Weapon	*weapon = nullptr;
	Armour	*armour = nullptr;
	string	buff_type = (*json_modifiers)["type"];
	double	value = (*json_modifiers)["value"];
	string	mod_ident = (*json_modifiers)["ident"];

	if (item->type != "Armour")
		weapon = dynamic_cast<Weapon *>(item);
	else
		armour = dynamic_cast<Armour *>(item);

	if (weapon != nullptr)
	{
		if (buff_type == "DamageBuff")
		{
			weapon->damage += value;
			print_message(json_modifiers, item->ident, weapon->damage);
		}
		else if (buff_type == "SpeedBuff")
		{
			weapon->speed += value;
			print_message(json_modifiers, item->ident, weapon->speed);
		}
	}
	else
	{
		if (armour != nullptr)
		{
			if (buff_type == "ProtectionBuff")
			{
				armour->protection += value;
				print_message(json_modifiers,item->ident, armour->protection);
			}
		}
		else
		{
			cout << item->ident << RED << " Cast error!" << NORM;
			throw std::exception();
		}
	}
}

/**
 * Проходит по каждому элементу массива предметов инвентаря,
 * если check_filter_attributes вернуло истину - применяет
 * улучшения к значениям предмета с помощью функции change_item_value.
 *
 * @param items: элементы инвентаря
 * @param json_inventory: json буффер модификаторов
 *
 * @exception
 * Выводит в консоль сообщение об ошибке, если change_item_value
 * выбросило исключение
 */
static void parse_filter_attribute(std::vector<Item *> *items, nlohmann::json *json_modifiers)
{
	for (int i = 0; i < (*items).size(); i++)
	{
		try
		{
			if (check_filter_attributes((*items)[i], json_modifiers))
				change_item_value((*items)[i], json_modifiers);
		}
		catch (...)
		{
			cout << RED << "Error during changing values" << NORM << endl;
		}
	}
	cout << endl;
}

/**
 * Проходит по каждому элементу json буффера модификаторов
 * и делегирует дальнейшее применение в функцию
 * parse_filter_attribute, которая парсит значения
 * поля filters и применяет модификаторы к инвентарю
 *
 * @param items: элементы инвентаря
 * @param json_modifiers: json буффер модификаторов
 *
 * @exception
 *	Выводит сообщение в консоль в случае ошибки
 *	при обращении к json полю
 */
static void read_apply_modifiers(std::vector<Item *> *items, nlohmann::json json_modifiers)
{
	for (int i = 0; json_modifiers[i] != nullptr; i++)
	{
		try
		{
			if (json_modifiers[i]["filters"].is_array())
				parse_filter_attribute(items, &json_modifiers[i]);
		}
		catch (...)
		{
			cout << RED << "Something went wrong! (The modifier wasn't applied!)" << NORM << endl;
		}
	}
}

int main()
{
	std::ifstream		stream("./json_files/modifiers.json");
	std::vector<Item *>	items;
	nlohmann::json		json_modifiers;

	try
	{
		read_fill_game_inventory(&items);

		try
		{
			stream >> json_modifiers;
			if (json_modifiers.is_null())
				throw std::exception();
			read_apply_modifiers(&items, json_modifiers);

			print_objects(&items);
		}
		catch (...)
		{
			cout << RED << "Json modifiers read error!" << endl << NORM;
		}

	}
	catch (...)
	{
		cout << RED << "Json inventory read error!" << endl << NORM;
	}
}