//
// Created by Joy Wang on 11/22/2024.
// Noble header file
//

#ifndef AFTER10_NOBLE_H
#define AFTER10_NOBLE_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {
    class Protector;

    class Noble {
        friend std::ostream &operator<<(std::ostream &os, const Noble &noble);
    public:
        Noble(const std::string& name);
        const std::string& getName() const;
        virtual void display(std::ostream &os) const = 0;

        bool isAlive() const;
        virtual void die() = 0;

        virtual double getStrength() const = 0;
        virtual void setStrength(double result) = 0;

        virtual void result(double oppStrong);
        void battle(Noble &opponent);
        virtual void defend() const = 0;

    private:
        std::string name;
        bool alive = true;
    };

    class Lord : public Noble {
    public:
        Lord(const std::string& name);
        // virtual output operator wrapper
        void display(std::ostream &os) const override;

        double getStrength() const override;
        void setStrength(double newStrength) override;

        bool hires(Protector &fighter);
        bool fires(Protector &fighter);

        void removeFromArmy(size_t idx);
        size_t findInArmy(const Protector& protector) const;

        void defend() const override;
        void die() override;

    private:
        std::vector<Protector*> army;
    };

    // the type that fights without an army, has their own strength
    class PersonWithStrengthToFight : public Noble {
    public:
        PersonWithStrengthToFight(const std::string& name, double strength);
        void display(std::ostream &os) const override;

        double getStrength() const override;
        void setStrength(double strengthRatio) override;

        void defend() const override;
        void die() override;

    private:
        double strength;
    };
}

#endif //AFTER10_NOBLE_H
