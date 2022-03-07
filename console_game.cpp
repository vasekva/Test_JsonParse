#include <iostream>
#include <string>
#include <vector>
#include "./json/include/nlohmann/json.hpp"
//#include "./json/include/delohmann/json.hpp"
#include <fstream>

struct Person
{
    std::string name;
    int age;
};

struct Item
{
	std::string ident;
};

struct myAnswer
{
    int everything;
};

struct myObject
{
    std::string currency;
    double value;
};

struct  myStruct
{
    float pi;
    bool happy;
    std::string name;
    void *nothing;
    myAnswer answer;
    std::vector<int> list;
    myObject object;
};

void to_json(nlohmann::json &j_obj, const Person &p)
{
//    nlohmann::json j_obj{};

    j_obj["pi"] = 3.141;
    j_obj["happy"] = true;
    j_obj["name"] = "Niels";
    j_obj["nothing"] = nullptr;
    j_obj["answer"]["everything"] = 42;
    j_obj["list"] = {1, 0, 2};
    j_obj["object"] = { {"currency", "USD"}, {"value", 42.99} };
}

//void from_json(const nlohmann::json &j_obj, Person &person)
//{
//    myStruct obj{};
//    obj.pi = j_obj["pi"].get<float>();
//    obj.happy = j_obj["happy"].get<bool>();
//    obj.name = j_obj["name"].get<std::string>();
////    obj.nothing = j_obj["nothing"].get_ptr<nlohmann::json::object_t*>();
//    obj.nothing = j_obj["nothing"].get_ptr<nlohmann::json::object_t*>();
//    obj.answer = myAnswer{ j_obj["answer"]["everything"].get<int>() };
//    j_obj["list"].get_to<std::vector<int>>(obj.list);
//    obj.object = myObject{ j_obj["object"]["currency"].get<std::string>(), j_obj["object"]["value"].get<double>() };
//
//}

void read_game_object()
{
	std::ifstream stream("data.json");
    nlohmann::json j;
	stream >> j;
    std::cout << j << std::endl;

    Item item;
	item.ident = j[0]["ident"].get<std::string>();

	for (int i = 0; j[i] != nullptr; i++)
	{
		std::cout << j[i]["ident"].get<std::string>() << " ";
		std::cout << j[i]["type"].get<std::string>() << " ";
		std::cout << j[i]["level"].get<int>() << " ";
		std::cout << j[i]["rarity"].get<std::string>() << " ";
		if (j[i]["type"].get<std::string>() == "Armour")
		{
			std::cout << j[i]["protection"].get<double>() << " ";;
		}
		else
		{
			std::cout << j[i]["damage"].get<double>() << " ";;
			std::cout << j[i]["speed"].get<double>() << " ";;
		}
		std::cout << std::endl;
	}

}

int main()
{

	read_game_object();
    /**
    {
         "pi": 3.141,
         "happy": true,
         "name": "Niels",
         "nothing": null,
         "answer": {
            "everything": 42
         },
         "list": [1, 0, 2],
         "object": {
            "currency": "USD",
            "value": 42.99
         }
     }
    */


//    std::ifstream i("demo.json");
//    nlohmann::json j;
//    i >> j;
//    std::cout << j << std::endl;
//
//    Person person;
//
//    myStruct obj{};
//    obj.pi = j["pi"].get<float>();
//    obj.happy = j["happy"].get<bool>();
//    obj.name = j["name"].get<std::string>();
//    obj.nothing = j["nothing"].get_ptr<nlohmann::json::object_t*>();
//    obj.answer = myAnswer{ j["answer"]["everything"].get<int>() };
//    j["list"].get_to<std::vector<int>>(obj.list);
//    obj.object = myObject{ j["object"]["currency"].get<std::string>(), j["object"]["value"].get<double>() };
//
//    std::cout << obj.name << std::endl;
//    std::cout << obj.answer.everything << std::endl;


}
