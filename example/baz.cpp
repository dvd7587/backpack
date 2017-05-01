#include "baz.h"

Baz::Baz() :
    beer(0), yeah(0)
{
    foo = NULL;
}

Baz::~Baz()
{
    if(foo) delete foo;
}

const Foo* Baz::get_foo() const
{
    return foo;
}

void Baz::set_foo(Foo *value)
{
    // delete old data (Baz owns the foo data)
    delete foo;

    foo = value;
}

double Baz::get_beer() const
{
    return beer;
}

void Baz::set_beer(double value)
{
    beer = value;
}

const Bar& Baz::get_bar() const
{
    return bar;
}

void Baz::set_bar(const Bar &value)
{
    bar = value;
}

float Baz::get_yeah() const
{
    return yeah;
}

void Baz::set_yeah(float value)
{
    yeah = value;
}

const std::string& Baz::get_text() const
{
    return text;
}

void Baz::set_text(const std::string &value)
{
    text = value;
}

bool Baz::get_glass() const
{
    return glass;
}

void Baz::set_glass(bool value)
{
    glass = value;
}

void Baz::write_to_archive(Archive &archive) const
{
    archive.write_double(beer, "beer");
    archive.write_nullable_archivable(foo, "foo");
    archive.write_archivable(bar, "bar");
    archive.write_float(yeah, "yeah");
    archive.write_string(text, "text");
    archive.write_bool(glass, "glass");
}

void Baz::read_from_archive(const Archive &archive)
{
    beer = archive.read_double("beer");

    if(foo) delete foo;
    foo = new Foo();
    archive.read_archivable(*foo, "foo");

    archive.read_archivable(bar, "bar");
    yeah = archive.read_float("yeah");
    archive.read_string(text, "text");
    glass = archive.read_bool("glass");
}

std::ostream& operator<<(std::ostream& out, const Baz& baz)
{
    out << "baz->beer: " << baz.get_beer() << std::endl;
    out << "baz->foo->value: " <<baz.get_foo()->get_value() << std::endl;
    out << "baz->foo->foo: " << baz.get_foo()->get_foo() << std::endl;
    out << "baz->bar->beer: " << baz.get_bar().get_beer() << std::endl;
    out << "baz->bar->foo->value: " << baz.get_bar().get_foo().get_value() << std::endl;
    out << "baz->bar->foo->foo: " << baz.get_bar().get_foo().get_foo() << std::endl;
    out << "baz->bar->yeah: " << baz.get_bar().get_yeah() << std::endl;
    out << "baz->bar->another_foo->value: " << baz.get_bar().get_another_foo().get_value() << std::endl;
    out << "baz->bar->another_foo->foo: " << baz.get_bar().get_another_foo().get_foo() << std::endl;
    out << "baz->yeah: " << baz.get_yeah() << std::endl;
    out << "baz->text: " << baz.get_text() << std::endl;
    out << std::boolalpha;
    out << "baz->glass: " << baz.get_glass() << std::endl;

   return out;
}
