#pragma once
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <map>

class Item {
public:
    Item(int packs, int weight, int days, int price, int spoiled_price
        , int days_critical, std::string name)
        : packs_(packs)
        , weight_(weight)
        , days_(days)
        , price_(price)
        , spoiled_price_(spoiled_price)
        , days_critical_(days_critical)
        , name_(name)
        , days_left_(days) {}

    Item(const Item& item) {
        this->days_left_ = item.days_left_;
        this->weight_ = item.weight_;
        this->packs_ = item.packs_;
        this->days_ = item.days_;
        this->price_ = item.price_;
        this->spoiled_price_ = item.spoiled_price_;
        this->days_critical_ = item.days_critical_;
        this->price_factory_ = item.price_factory_;
    }

    Item& operator=(Item item) {
        swap(*this, item);
        return *this;
    }

    void swap(Item& lhs, Item& rhs) {
        std::exchange(lhs.days_left_, rhs.days_left_);
        std::exchange(lhs.weight_, rhs.weight_);
        std::exchange(lhs.packs_, rhs.packs_);
        std::exchange(lhs.days_, rhs.days_);
        std::exchange(lhs.price_, rhs.price_);
        std::exchange(lhs.spoiled_price_, rhs.spoiled_price_);
        std::exchange(lhs.days_critical_, rhs.days_critical_);
        std::exchange(lhs.price_factory_, rhs.price_factory_);
    }

    // returns total weight of wholesale pack
    int get_weight_total() {
        return packs_ * weight_;
    }

    // returns weight of a single pack
    int get_weight() {
        return weight_;
    }

    // returns days until spoil
    int get_days_left() {
        return days_left_;
    }

    // returns number of packs in wholesale pack
    int get_packs() {
        return packs_;
    }

    // returns duration of storage life
    int get_days() {
        return days_;
    }

    // sets days left until spoil
    void set_days_left(int days) {
        days_left_ = std::min(days_, days);
    }

    // sets duration of storage life
    void set_days(int days) {
        days_ = days;
    }

    //return name of item
    std::string name() {
        return name_;
    }

    //returns price
    int price() {
        return price_;
    }

    // returns price of spoiled
    int price_spoiled() {
        return spoiled_price_;
    }

    // if this amount of days left, we should sell by spoiled_price_
    int days_critical() {
        return days_critical_;
    }

    // returns factory price
    int price_factory() {
        return price_factory_;
    }




private:
    int days_left_, weight_, packs_, days_, price_
        , spoiled_price_, days_critical_, price_factory_;
    std::string name_;

};