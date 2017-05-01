#include <iostream>
#include <string>
#include "backpack/archive/bufferarchive.h"
#include "backpack/archive/jsonarchive.h"
#include "foo.h"
#include "bar.h"
#include "baz.h"
#include "fred.h"

using namespace std;

Baz* make_baz()
{
    Foo foo;
    foo.set_value(3);
    foo.set_foo(5);

    Foo anotherFoo;
    anotherFoo.set_value(7);
    anotherFoo.set_foo(56);

    Bar bar;
    bar.set_foo(foo);
    bar.set_beer(100.5);
    bar.set_another_foo(anotherFoo);
    bar.set_yeah(3000.12f);

    Foo* bazFoo = new Foo();
    bazFoo->set_value(33);
    bazFoo->set_foo(78);

    Baz* baz = new Baz();
    baz->set_bar(bar);
    baz->set_foo(bazFoo);
    baz->set_beer(333);
    baz->set_yeah(12);
    baz->set_text("this is my text!");
    baz->set_glass(true);

    return baz;
}

void exec_buffer_archive_example()
{
    cout << "----- START BUFFER ARCHIVABLE EXAMPLE -----" << endl;

    BufferArchive archive;

    Baz* baz = make_baz();

    baz->write_to_archive(archive);

    delete baz;

    BufferArchive newArchive(archive.get_data(), archive.get_data_size());

    Baz newBaz;

    newBaz.read_from_archive(newArchive);

    cout << "DESERIALIZED BAZ:" << endl;
    cout << newBaz;

    cout << "----- END BUFFER ARCHIVABLE EXAMPLE -----" << endl << endl;

}

void exec_JSON_archive_example()
{
    cout << "----- START JSON ARCHIVABLE EXAMPLE -----" << endl;

    JsonArchive archive;

    Baz* baz = make_baz();

    archive.start_archive_object();
    baz->write_to_archive(archive);
    archive.end_archive_object();

    delete baz;

    cout << "SERIALIZED JSON BAZ:" << endl;
    cout << archive.get_json_string() << endl << endl;

    JsonArchive newArchive;
    newArchive.set_json_from_string(archive.get_json_string());

    Baz newBaz;

    newBaz.read_from_archive(newArchive);

    cout << "DESERIALIZED BAZ:" << endl;
    cout << newBaz;

    cout << "----- END JSON ARCHIVABLE EXAMPLE -----" << endl << endl;
}

void exec_serializable_example()
{
    cout << "----- START SERIALIZABLE EXAMPLE -----" << endl;

    Fred fred;
    fred.set_relax(234);
    fred.set_couch(12203.4);
    fred.set_surf(12);

    string serialized_fred;
    fred.serialize(serialized_fred);

    Fred newFred;
    newFred.deserialize(serialized_fred);

    cout << "DESERIALIZED FRED:" << endl;
    cout << newFred;

    cout << "----- END SERIALIZABLE EXAMPLE -----" << endl << endl;
}

int main(int argc, char *argv[])
{
    exec_serializable_example();
    exec_JSON_archive_example();
    exec_buffer_archive_example();

    return 0;
}

