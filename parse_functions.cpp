#include "classes_prototypes.hpp"

/**
 * Проверяет совместимость уровня указанного в фильтре
 * с полем 'level' предмета
 *
 * @param item: элемент инвентаря
 * @param filter_item: json модификатор
 *
 * @return
 * Возвращает true, если предмет имеет необходимый уровень
 */
static bool	is_enough_level(Item *item, nlohmann::json *filter_item)
{
	string	comparisons[] = {">", "<", ">=", "<=", "="};
	string	parameter_action = (*filter_item)[1];
	int		parameter_val = (*filter_item)[2];
	int		index = 0;

	int length = (sizeof(comparisons) / sizeof(comparisons[0]));
	while (index != length)
	{
		if (comparisons[index] == parameter_action)
			break;
		index++;
	}

	bool isEnoughLvl = false;
	switch (index)
	{
		case 0: { if (item->level > parameter_val) { isEnoughLvl = true; } break ; }
		case 1: { if (item->level < parameter_val) { isEnoughLvl = true; } break ; }
		case 2: { if (item->level >= parameter_val) { isEnoughLvl = true; } break; }
		case 3: { if (item->level <= parameter_val) { isEnoughLvl = true; } break ; }
		case 4: { if (item->level == parameter_val) { isEnoughLvl = true; } break ; }
		default: { isEnoughLvl = false; }
	}
	return (isEnoughLvl);
}

/**
 * Проверяет совместимость фильтра по типу или редкости
 * с полем 'type' или 'rarity' соответственно с предметом
 *
 * @param item: элемент инвентаря
 * @param filter_item: json модификатор
 *
 * @exception
 *	Выбрасывает пустое исключение в случае ошибки обращения к полю json
 *
 * @return
 * 	Возвращает true, если модификтор можно применить к предмету
 */
static bool	check_string_parameter(Item *item, nlohmann::json *filter_item)
{
	bool isCorrectItem = false;

	try
	{
		if (filter_item[0]["type"] == item->type)
			isCorrectItem = true;
		else if (filter_item[0]["rarity"] == item->rarity)
			isCorrectItem = true;
	}
	catch (std::exception e)
	{

	}
	return (isCorrectItem);
}

/**
 * Проверяет каждый элемент поля 'filters' полученного модификатора
 * на совпадения с предметом инвентаря
 *
 * @param item: предмет инвентаря
 * @param json_modifier: json элемент модификаторов
 *
 * @return
 *  Возвращает true, если текущий модификтор можно применить к предмету
 */
bool	check_filter_attributes(Item *item, nlohmann::json *json_modifier)
{
	int check_result = 0;
	nlohmann::json	*filters = &(*json_modifier)["filters"];

	for (int ind = 0; ind < (*filters).size(); ind++)
	{
		if ((*filters)[ind].is_array())
		{
			if ((*filters)[ind][0] == "level")
				check_result += is_enough_level(item, &(*filters)[ind]);
		}
		else
			check_result += check_string_parameter(item, &(*filters)[ind]);
	}
	return (check_result > 0);
}