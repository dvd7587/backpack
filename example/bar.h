#ifndef BAR_H
#define BAR_H

#include "backpack/archive/archivable.h"
#include "backpack/archive/archive.h"
#include "foo.h"

class Bar : public Archivable
{
public:
    Bar();
    virtual ~Bar();

    void write_to_archive(Archive& archive) const override;
    void read_from_archive(const Archive& archive) override;

    const Foo& get_foo() const;
    void set_foo(const Foo &value);

    double get_beer() const;
    void set_beer(double value);

    const Foo& get_another_foo() const;
    void set_another_foo(const Foo &value);

    float get_yeah() const;
    void set_yeah(float value);

private:
    Foo foo;
    double beer;
    Foo another_foo;
    float yeah;
};

#endif // BAR_H
