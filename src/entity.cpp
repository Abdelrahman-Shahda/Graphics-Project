//
// Created by 20101 on 12/4/2020.
//
#include <entity.hpp>
unsigned int Entity::next_id = 0;
Entity::Entity(std::string tag) {
    this->id = next_id++;
    this->tag = tag;
}
bool Entity::withTag(std::string tag) {
    return tag == this->tag;
}
void Entity::setTag(std::string tag) {
    this->tag = tag;
}
unsigned int Entity::getId() {
    return this->id;
}