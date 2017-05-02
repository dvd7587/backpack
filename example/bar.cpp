#include "bar.h"

Bar::Bar() :
    beer(0), yeah(0)
{

}

Bar::~Bar()
{

}

const Foo& Bar::get_foo() const
{
    return foo;
}

void Bar::set_foo(const Foo &value)
{
    foo = value;
}

double Bar::get_beer() const
{
    return beer;
}

void Bar::set_beer(double value)
{
    beer = value;
}

const Foo& Bar::get_another_foo() const
{
    return another_foo;
}

void Bar::set_another_foo(const Foo &value)
{
    another_foo = value;
}

float Bar::get_yeah() const
{
    return yeah;
}

void Bar::set_yeah(float value)
{
    yeah = value;
}

void Bar::write_to_archive(Archive &archive) const
{
    archive.write_double(beer, "beer");
    archive.write_archivable(foo, "foo");
    archive.write_float(yeah, "yeah");
    archive.write_archivable(another_foo, "anotherFoo");
}

void Bar::read_from_archive(const Archive &archive)
{
    beer = archive.read_double("beer");
    archive.read_archivable(foo, "foo");
    yeah = archive.read_float("yeah");
    archive.read_archivable(another_foo, "anotherFoo");
}
