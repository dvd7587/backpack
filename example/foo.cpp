#include "foo.h"

Foo::Foo() :
    value(0), foo(0)
{

}

int64_t Foo::get_value() const
{
    return value;
}

void Foo::set_value(const int64_t &value_)
{
    value = value_;
}

int64_t Foo::get_foo() const
{
    return foo;
}

void Foo::set_foo(const int64_t &value)
{
    foo = value;
}

void Foo::write_to_archive(Archive &archive) const
{
    archive.write_int64(value, "value");
    archive.write_int64(foo, "foo");
}

void Foo::read_from_archive(const Archive &archive)
{
    value = archive.read_int64("value");
    foo = archive.read_int64("foo");
}


