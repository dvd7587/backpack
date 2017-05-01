#ifndef BAZ_H
#define BAZ_H

#include <iostream>
#include <string>
#include "backpack/archive/archivable.h"
#include "backpack/archive/archive.h"
#include "foo.h"
#include "bar.h"

class Baz : public Archivable
{
public:
    Baz();
    ~Baz();

    void write_to_archive(Archive& archive) const override;
    void read_from_archive(const Archive& archive) override;


    const Foo* get_foo() const;
    void set_foo(Foo *value);

    double get_beer() const;
    void set_beer(double value);

    const Bar& get_bar() const;
    void set_bar(const Bar &value);

    float get_yeah() const;
    void set_yeah(float value);

    const std::string& get_text() const;
    void set_text(const std::string &value);

    bool get_glass() const;
    void set_glass(bool value);

private:
    Foo* foo;
    double beer;
    Bar bar;
    float yeah;
    std::string text;
    bool glass;
};

std::ostream& operator<<(std::ostream& out, const Baz& baz);

#endif // BAZ_H
