#pragma once
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <map>
#include <list>
#include "Item.h"

class Factory {
public:
	Factory() {}

	// adds new item type to factory
	void AddItem(Item item) {
		factory[item.name()] = item;
	}

	// produces new item of the type given. returns pointer or nullptr
	Item* TakeItem(std::string name) {
		if (factory.count(name) > 0) {
			Item* pointer = &factory[name];
			return pointer;
		}
		else {
			return nullptr;
		}
	}

private:
	std::map<std::string, Item> factory;

};