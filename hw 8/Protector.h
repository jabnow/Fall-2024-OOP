//
// Created by Joy Wang on 11/22/2024.
// Protector header file
//

#ifndef AFTER10_PROTECTOR_H
#define AFTER10_PROTECTOR_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {
    class Lord;
    class Protector {
        friend std::ostream& operator<<
                (std::ostream& os, const Protector& protector);
    public:
        Protector(const std::string& name, double strength);

        const std::string& getName() const;
        virtual void defend () const = 0;

        double getStrength() const;
        void setStrength(double result);

        // now that Protectors have more abilities and rights,
        // the Nobles are more of employers than masters
        Lord* getEmployer() const;
        void setEmployer(Lord* newEmployer);

        bool isHired() const;
        bool runaway();

    private:
        std::string name;
        double strength;
        Lord* employer;
    };

    // strength is set at birth
    // have weird old names
    // each protector type has a unique way of defending
    class Warrior : public Protector {
    public:
        Warrior(const std::string& name, double strength);
        void defend () const override = 0;
    };

    class Wizard : public Protector {
    public:
        Wizard(const std::string& name, double strength);
        void defend () const override;
    };

    class Archer : public Warrior {
    public:
        Archer(const std::string& name, double strength);
        void defend () const override;
    };

    class Swordsman : public Warrior {
    public:
        Swordsman(const std::string& name, double strength);
        void defend () const override;
    };
}

#endif //AFTER10_PROTECTOR_H
