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
#ifndef ARCHIVABLE_H
#define ARCHIVABLE_H

//#include "archive.h"

class Archive;

/*!
 * \brief The Archivable interface
 *
 * Archivable interface represents an object that can write its state to an archive to be saved and read the state from an
 * archive to be loaded.
 * Using this interface objects can put their data into the archive in order to be serialized, and get data from the archive
 * in order to be deserialized.
 *
 * When Archivable objects read from an archive they must read the data in the same order that the data has been written.
 * (Example:
 *
 *  if in write_to_archive an object writes the following:
 *
 *  archive.write_int32(value, "myValue");
 *  archive.write_float(float_value, "myFloatValue");
 *
 *  then when reading the data from the archive (in read_from_archive method) the object must read in the same order:
 *
 *  value = value.read_int32("myValue")
 *  float_value = value.read_int32("myFloatValue")
 *
 *  Following this pattern objects can be saved/loaded to/from archives.
 */
class Archivable
{
public:

    /*!
     * \brief Method used to write the state of an object to an archive.
     * Implementing this method objects can be serialized into an archive.
     * \param archive The archive where to pack the object.
     */
    virtual void write_to_archive(Archive& archive) const = 0;

    /*!
     * \brief Method used to read the state of an object from an archive.
     * Implementing this method objects can be deserialized from an archive.
     * \param archive The archive where to read the object state.
     */
    virtual void read_from_archive(const Archive& archive) = 0;
};

#endif // ARCHIVABLE_H
