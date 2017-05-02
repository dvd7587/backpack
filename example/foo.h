#ifndef FOO_H
#define FOO_H

#include <stdint.h>
#include "backpack/archive/archivable.h"
#include "backpack/archive/archive.h"

class Foo : public Archivable
{
public:
    Foo();
    virtual ~Foo();

    int64_t get_value() const;
    void set_value(const int64_t &value);

    int64_t get_foo() const;
    void set_foo(const int64_t &value);

    void write_to_archive(Archive& archive) const override;
    void read_from_archive(const Archive& archive) override;

private:
    int64_t value;
    int64_t foo;
};

#endif // FOO_H
