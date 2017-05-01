/*
 * Copyright 2017 Vincenzo Micelli
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "jsonarchive.h"

JsonArchive::JsonArchive()
{
    writer = new Writer<StringBuffer>(s);
}

JsonArchive::~JsonArchive()
{
    delete writer;
}

bool JsonArchive::write_byte_array(const uint8_t *data, size_t len, const std::string &key)
{
    // do not write empty buffer
    if(len > 0)
    {
        writer->Key(key.c_str());
        writer->String((char*)data, len, true);

        return true;
    }

    return false;
}

void JsonArchive::start_archive_object()
{
    writer->Reset(s);
    writer->StartObject();
}


void JsonArchive::end_archive_object()
{
    writer->EndObject();
}

bool JsonArchive::set_json_from_string(const std::string &json)
{
    document.Parse(json.c_str());

    if(document.IsObject())
    {
        member_iterator = document.MemberBegin();
    }

    return document.IsObject();
}

std::string JsonArchive::get_json_string() const
{
    return s.GetString();
}

bool JsonArchive::write_int32(int32_t val, const std::string &key)
{
    writer->Key(key.c_str());
    writer->Int64(val);

    return true;
}

bool JsonArchive::write_uint32(uint32_t val, const std::string &key)
{
    writer->Key(key.c_str());
    writer->Uint64(val);

    return true;
}


bool JsonArchive::write_int64(int64_t val, const std::string& key)
{
    writer->Key(key.c_str());
    writer->Int64(val);

    return true;
}

bool JsonArchive::write_uint64(uint64_t val, const std::string &key)
{
    writer->Key(key.c_str());
    writer->Uint64(val);

    return true;
}

bool JsonArchive::write_float(float val, const std::string &key)
{
    writer->Key(key.c_str());
    writer->Double(val);

    return true;
}

bool JsonArchive::write_double(double val, const std::string &key)
{
    writer->Key(key.c_str());
    writer->Double(val);

    return true;
}

bool JsonArchive::write_bool(bool val, const std::string &key)
{
    writer->Key(key.c_str());
    writer->Bool(val);

    return true;
}

bool JsonArchive::write_string(const std::string &str, const std::string &key)
{
    writer->Key(key.c_str());
    writer->String(str.c_str());

    return true;
}

bool JsonArchive::write_archivable(const Archivable &archivable, const std::string &key)
{
    writer->Key(key.c_str());
    writer->StartObject();
    archivable.write_to_archive(*this);
    writer->EndObject();

    return true;
}

bool JsonArchive::write_nullable_archivable(const Archivable *archivable, const std::string &key)
{
    if(archivable)
    {
        return write_archivable(*archivable, key);
    }

    return false;
}

bool JsonArchive::read_byte_array(uint8_t *outData, size_t len, const std::string &key) const
{
    if(member_iterator->name.GetString() == key)
    {
        std::string data = member_iterator->value.GetString();
        data.copy((char*)outData, len);
        member_iterator++;

        return true;
    }

    return false;
}

int32_t JsonArchive::read_int32(const std::string &key) const
{
    if(member_iterator->name.GetString() == key)
    {
        int32_t value = (int32_t)member_iterator->value.GetInt64();
        member_iterator++;
        return value;
    }

    return 0;
}

uint32_t JsonArchive::read_uint32(const std::string &key) const
{
    if(member_iterator->name.GetString() == key)
    {
        uint32_t value = (uint32_t)member_iterator->value.GetUint64();
        member_iterator++;
        return value;
    }

    return 0;
}

int64_t JsonArchive::read_int64(const std::string& key) const
{

    if(member_iterator->name.GetString() == key)
    {
        int64_t value = member_iterator->value.GetInt64();
        member_iterator++;
        return value;
    }

    return 0;
}

uint64_t JsonArchive::read_uint64(const std::string &key) const
{
    if(member_iterator->name.GetString() == key)
    {
        uint64_t value = member_iterator->value.GetUint64();
        member_iterator++;
        return value;
    }

    return 0;
}

float JsonArchive::read_float(const std::string& key) const
{
    if(member_iterator->name.GetString() == key)
    {
        float value = member_iterator->value.GetFloat();
        member_iterator++;
        return value;
    }

    return 0;

}

double JsonArchive::read_double(const std::string& key) const
{

    if(member_iterator->name.GetString() == key)
    {

        double value = member_iterator->value.GetDouble();
        member_iterator++;
        return value;

    }

    return 0;
}

bool JsonArchive::read_bool(const std::string &key) const
{
    if(member_iterator->name.GetString() == key)
    {

        bool value = member_iterator->value.GetBool();
        member_iterator++;
        return value;

    }

    return false;
}

bool JsonArchive::read_string(std::string &str, const std::string &key) const
{
    if(member_iterator->name.GetString() == key)
    {
        str = member_iterator->value.GetString();
        member_iterator++;

        return true;
    }

    return false;
}

bool JsonArchive::read_archivable(Archivable &archivable, const std::string& key) const
{

    if(member_iterator->name.GetString() == key)
    {
        Value::ConstMemberIterator saved_member_iterator = member_iterator;
        member_iterator = member_iterator->value.GetObject().MemberBegin();

        archivable.read_from_archive(*this);

        member_iterator = saved_member_iterator;
        member_iterator++;

        return true;

    }

    return false;
}
