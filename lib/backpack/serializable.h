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
#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H
#include <string>

/*!
 * \brief The Serializable interface
 *
 * Simple interface to serialize an object in a string and deserialize an object from a string.
 * Serialization methods take as input a string, since this library is designed to be easy to wrap
 * in multiple languages (Python, Java, etc...). For this reason string is prefered to types such as
 * streams. An alternative parameter type could be a byte array.
 *
 * This interface should be used only when wrapped in other languages that provide reflection in order
 * to exploit libraries that provide quick conversions to a string (pickle, json, xml, etc..).
 * Only small objects should be serialized using this interface.
 * For an efficient serialization pattern see Archivable.
 */
class Serializable
{
public:

    /*!
     * \brief Method used to write the state of an object to a string.
     * Implementing this method objects can be serialized to a string.
     * \param out_string The string where to serialize the object.
     */
    virtual void serialize(std::string& out_string) const = 0;

    /*!
     * \brief Method used to read the state of an object from a string.
     * Implementing this method objects can be deserialized from a string.
     * \param in_string The string that contains the object state.
     */
    virtual void deserialize(const std::string& in_string) = 0;
};

#endif // SERIALIZABLE_H
