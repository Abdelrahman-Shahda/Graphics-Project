//
// Created by Hania on 1/17/2021.
//

#ifndef GRAPHICSPROJECT_ELF_HPP
#define GRAPHICSPROJECT_ELF_HPP
#include<components/component.h>
class Elf : public Component
{
private:
    unsigned int points;
public:
    Elf(std::weak_ptr<Entity> entity, int points): Component(entity), points(points){type = ELF;}
    unsigned int getPoints() { return points; }
};
#endif //GRAPHICSPROJECT_ELF_HPP
