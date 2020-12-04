//
// Created by 20101 on 12/4/2020.
//
#include <entity.hpp>
unsigned int Entity::next_id = 0;
Entity::Entity() {
    this->id = next_id++;
}
unsigned int Entity::getId() {
    return this->id;
}