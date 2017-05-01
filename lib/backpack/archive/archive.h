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
#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <stdint.h>
#include <string>
#include "archivable.h"

/*!
 * \brief The Archive interface
 *
 * Archive interface represents an abstract archive where it is possible to store the data of the object to serialize.
 * Using this interface objects that implement Archivable can put their data into the archive in order to be serialized,
 * and get data from the archive in order to be deserialized.
 * An archive provides a set of methods to write data into the archive and a set of methods to read data from the archive.
 *
 * When Archivable objects read from an archive they must read the data in the same order that the data has been written.
 *
 * Concrete implementations of this interface should provide methods to save and load the archive itself
 * (i.e to/from a stream, a file, etc...).
 *
 * This interface is still a draft.
 */
class Archive
{
public:

    virtual bool write_byte_array(const uint8_t* data, size_t len, const std::string& key) = 0;
    virtual bool write_int32(int32_t val, const std::string& key) = 0;
    virtual bool write_uint32(uint32_t  val, const std::string& key) = 0;
    virtual bool write_int64(int64_t val, const std::string& key) = 0;
    virtual bool write_uint64(uint64_t val, const std::string& key) = 0;
    virtual bool write_float(float val, const std::string& key) = 0;
    virtual bool write_double(double val, const std::string& key) = 0;
    virtual bool write_bool(bool val, const std::string& key) = 0;
    virtual bool write_string(const std::string& str, const std::string& key) = 0;
    virtual bool write_archivable(const Archivable& archivable, const std::string& key) = 0;
    virtual bool write_nullable_archivable(const Archivable* archivable, const std::string& key) = 0;

    virtual bool read_byte_array(uint8_t* outData, size_t len, const std::string& key) const = 0;
    virtual int32_t read_int32(const std::string& key) const = 0;
    virtual uint32_t read_uint32(const std::string& key) const = 0;
    virtual int64_t read_int64(const std::string& key) const = 0;
    virtual uint64_t read_uint64(const std::string& key) const = 0;
    virtual float read_float(const std::string& key) const = 0;
    virtual double read_double(const std::string& key) const = 0;
    virtual bool read_bool(const std::string& key) const = 0;
    virtual bool read_string(std::string& str, const std::string& key) const = 0;
    virtual bool read_archivable(Archivable& archivable, const std::string& key) const = 0;

};

#endif // ARCHIVE_H
