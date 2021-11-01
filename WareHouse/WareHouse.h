#pragma once
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <map>
#include <list>
#include "Item.h"


class WareHouse {
public:

    WareHouse(int capacity, int money) : capacity_(capacity), money_(money) {}

    // adds items
    bool AddItem(Item* item, int number = 1) {
        try {
            for (int i = 0; i < number; ++i) {
                Item *new_item = &*item;
                storage_[item->name()].push_front(new_item);
            }
            return true;
        } 
        catch (...) {
            return false;
        }
    }

    // sells item (works as FIFO)
    bool SellItem(Item* item) {
        try {
            if (item->get_days_left() <= item->days_critical()) {
                money_ += item->price_spoiled();
                revenue_ += item->price_spoiled();
            }
            else {
                money_ += item->price();
                revenue_ += item->price();
            }
            PopItem(item);
        }
        catch (...) {
            return false;
        }
    }

    // says to drop this item because of date
    bool SpoilItem(Item* item) {
        try {
            PopItem(item);
            return true;
        }
        catch (...) {
            return false;
        }
    }

    // pops item from the queue after selling or spoiling
    bool PopItem(Item* item) {
        storage_[item->name()].pop_back();
        delete item;
        --size_;
    }

    // buys items from Factory and returns how many items it bought
    unsigned int BuyItem(Item* item, int number = 1) {
        try {
            number = std::min(number, capacity_ - size_);
            if (item->price_factory() * number <= money_) {
                money_ -= item->price_factory() * number;
                revenue_ -= item->price_factory() * number;
                AddItem(item, number);
                return number;
            }
            else {
                if (item->price_factory() > money_)
                    return false;
                int num = money_ / item->price_factory();
                num = std::min(num, capacity_ - size_);
                money_ -= num * item->price_factory();
                revenue_ -= num * item->price_factory();
                AddItem(item, num);
                return num;
            }
        }
        catch (...) {
            return 0;
        }
    }

    // shows the price of the item at the moment
    int ShowPrice(Item* item) {
        try {
            if (item->get_days_left() <= item->days_critical()) {
                return item->price_spoiled();
            }
            else {
                return item->price();
            }
        }
        catch (...) {
            return -1;
        }
    }

    // returns space available
    unsigned int SpaceLeft() {
        return std::max(0, capacity_ - size_);
    }


private:
    int capacity_, size_, money_, revenue_ = 0;
    std::map<std::string, std::list<Item*> > storage_;


};

