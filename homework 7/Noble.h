//
// Created by Joy Wang on 11/7/2024.
//

#ifndef OVER5_NOBLE_H
#define OVER5_NOBLE_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {
    class Warrior;

    class Noble {
        friend std::ostream &operator<<(std::ostream &os, const Noble &sir);

    public:
        Noble(const std::string &name);

        const std::string &getName() const;

        bool getLife() const;

        double armyStrength() const;

        size_t getArmySize() const;

        bool hire(Warrior &fighter);

        bool fire(Warrior &fighter);

        bool remove(size_t &location);

        void resultingStrength(double winner, double loser);

        void battle(Noble &enemy);

        void rip();

        size_t find_warrior(const Warrior *warrior) const;

    private:
        std::string noble_name;
        std::vector<Warrior *> army;
        bool is_alive;
    };
}

#endif //OVER5_NOBLE_H
