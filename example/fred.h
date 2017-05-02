#ifndef FRED_H
#define FRED_H

#include <iostream>
#include "backpack/serializable.h"

class Fred : public Serializable
{
public:
    Fred();
    virtual ~Fred();

    // Serializable interface
    void serialize(std::string &out_string) const override;
    void deserialize(const std::string &in_string) override;

    int get_relax() const;
    void set_relax(int value);

    double get_couch() const;
    void set_couch(double value);

    int get_surf() const;
    void set_surf(int value);

private:
    int relax;
    double couch;
    int surf;


};

std::ostream& operator<<(std::ostream& out, const Fred& fred);

#endif // FRED_H
