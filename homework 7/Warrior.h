//
// Created by Joy Wang on 11/7/2024.
//

#ifndef OVER5_WARRIOR_H
#define OVER5_WARRIOR_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {
    class Noble;

    class Warrior{
            friend std::ostream& operator<<(std::ostream& os, const Warrior& fighter);
            public:
            Warrior(const std::string& name, double points);
            const std::string& getName() const;

            double getStrength() const;
            void setStrength(double result);

            bool getMaster() const;
            void setMaster(Noble* sir);

            bool runaway();
            bool isHired() const;
            private:
            std::string warrior_name;
            double strength;
            Noble* master;
    };
}

#endif //OVER5_WARRIOR_H
