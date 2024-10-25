// Princess.h
// 24F - Sec C

#ifndef PRINCESS_H
#define PRINCESS_H

#include <iostream>
#include <string>
//using namespace std; // Not here!!!!!

namespace Fantasy {

    class FrogPrince;

    class Princess {
        friend std::ostream& operator<<(std::ostream& os, const Princess& rhs);
    public:
        Princess(const std::string& name);
        const std::string& getName() const;
        void marries(FrogPrince& betrothed);
    private:
        std::string name;
        FrogPrince* spouse;
    };

}

#endif // PRINCESS_H
