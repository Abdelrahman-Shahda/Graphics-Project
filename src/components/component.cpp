#include "../../inc/components/component.hpp"

Component::Component(std::weak_ptr<Entity> entity) {
    this->entity = entity;
}