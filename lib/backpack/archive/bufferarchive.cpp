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
#include "bufferarchive.h"
#include <stdlib.h>
#include <cstring>

BufferArchive::BufferArchive()
{
    init_state();
}

BufferArchive::BufferArchive(const uint8_t *data, const size_t& size)
    :m_data(nullptr), m_data_size(size)
{
    // Copy the input data
    m_data = (uint8_t*)malloc(m_data_size);
    memcpy(m_data, data, m_data_size);

    m_data_capacity = 0;
    m_data_pos = 0;
}

BufferArchive::~BufferArchive()
{
    free_data_no_init();
}


size_t BufferArchive::get_data_size() const
{
    return m_data_size;
}

bool BufferArchive::write_byte_array(const uint8_t *data, size_t len, const std::string& key)
{
    if (len > INT32_MAX) {
        // don't accept size_t values which may have come from an
        // inadvertent conversion from a negative int.
        return false;
    }

    if ((m_data_pos+len) <= m_data_capacity) {

        uint8_t* const d = m_data + m_data_pos;
        memcpy(d, data, len);

        return finish_write(len);

    }

    bool grown = grow_data(len);

    if (grown == true)
    {
        uint8_t* const d = m_data + m_data_pos;
        memcpy(d, data, len);

        return finish_write(len);;
    }

    return false;
}

bool BufferArchive::write_int32(int32_t val, const std::string &key)
{
    return write_aligned(val);
}

bool BufferArchive::write_uint32(uint32_t val, const std::string &key)
{
    return write_aligned(val);
}

bool BufferArchive::write_int64(int64_t val, const std::string& key)
{
    return write_aligned(val);
}

bool BufferArchive::write_uint64(uint64_t val, const std::string &key)
{
    return write_aligned(val);
}

bool BufferArchive::write_float(float val, const std::string& key)
{
    return write_aligned(val);
}

bool BufferArchive::write_double(double val, const std::string& key)
{
    return write_aligned(val);
}

bool BufferArchive::write_bool(bool val, const std::string &key)
{
    return write_int32(int32_t(val), key);
}

bool BufferArchive::write_string(const std::string &str, const std::string &key)
{
    // save size
    bool result = write_int32((int32_t)str.size(), key);

    // only write string if its length is more than zero characters,
    // as read_string will only read if the length field is non-zero.
    if (str.size() > 0 && result == true) {
        result = write_byte_array((uint8_t*)str.c_str(), str.size(), key);
    }
    return result;
}

bool BufferArchive::write_archivable(const Archivable &archivable, const std::string& key)
{
    bool result = write_int32(1, key);  // archivable is not null.
    if (!result) {
        return result;
    }

    archivable.write_to_archive(*this);
    return true;
}

bool BufferArchive::write_nullable_archivable(const Archivable *archivable, const std::string &key)
{
    if (!archivable) {
        return write_int32(0, key);
    }

    return write_archivable(*archivable, key);
}

template<class T>
bool BufferArchive::write_aligned(T val) {

    if ((m_data_pos+sizeof(val)) <= m_data_capacity) {
        *reinterpret_cast<T*>(m_data+m_data_pos) = val;
        return finish_write(sizeof(val));
    }

    bool result = grow_data(sizeof(val));
    if (result == true)
    {
        *reinterpret_cast<T*>(m_data+m_data_pos) = val;
        return finish_write(sizeof(val));
    }

    return result;
}

bool BufferArchive::finish_write(size_t len)
{
    // move pointer
    m_data_pos += len;

    // update data size
    if (m_data_pos > m_data_size) {
        m_data_size = m_data_pos;
    }

    return true;
}

uint8_t *BufferArchive::get_data() const
{
    return m_data;
}

bool BufferArchive::grow_data(size_t len)
{
    size_t newSize = ((m_data_size+len)*3)/2;
    return (newSize <= m_data_size) ? false : continue_write(newSize);
}

bool BufferArchive::continue_write(size_t desired)
{
    if (m_data) {
        if (desired > m_data_capacity) {
            uint8_t* data = (uint8_t*)realloc(m_data, desired);
            if (data) {
                m_data = data;
                m_data_capacity = desired;
            } else {
                // NO_MEMORY
                return false;
            }
        } else {
            if (m_data_size > desired) {
                m_data_size = desired;
            }
            if (m_data_pos > desired) {
                m_data_pos = desired;
            }
        }

    } else {
        // This is the first data.
        uint8_t* data = (uint8_t*)malloc(desired);
        if (!data) {
            // NO_MEMORY
            return false;
        }

        m_data = data;
        m_data_size = m_data_pos = 0;
        m_data_capacity = desired;
    }

    return true;
}

bool BufferArchive::read_byte_array(uint8_t *outData, size_t len, const std::string& key) const
{
    if (len > INT32_MAX) {
        // don't accept size_t values which may have come from an
        // inadvertent conversion from a negative int.
        return false;
    }

    if ((m_data_pos+len) >= m_data_pos && (m_data_pos+len) <= m_data_size) {
        memcpy(outData, m_data+m_data_pos, len);
        m_data_pos += len;

        return true;
    }

    return false;
}

int32_t BufferArchive::read_int32(const std::string &key) const
{
    return read_aligned<int32_t>();
}

uint32_t BufferArchive::read_uint32(const std::string &key) const
{
    return read_aligned<uint32_t>();
}

int64_t BufferArchive::read_int64(const std::string& key) const
{
    return read_aligned<int64_t>();
}

uint64_t BufferArchive::read_uint64(const std::string &key) const
{
    return read_aligned<uint64_t>();
}

float BufferArchive::read_float(const std::string& key) const
{
    return read_aligned<float>();
}

double BufferArchive::read_double(const std::string& key) const
{
    return read_aligned<double>();
}

bool BufferArchive::read_bool(const std::string &key) const
{
    return read_int32(key) != 0;
}

bool BufferArchive::read_string(std::string &str, const std::string &key) const
{
    int32_t size = read_int32(key);

    // watch for potential int overflow from size+1
    if (size < 0 || size >= INT32_MAX) {
        return false;
    }

    // |write_string| writes nothing for empty string.
    if (size == 0) {
        return true;
    }

    const char* c_str = (const char*)read_inplace(size);
    if (c_str == NULL) {
        return false;
    }

    str.assign(c_str, size);

    return true;
}

const void* BufferArchive::read_inplace(size_t len) const
{
    if (len > INT32_MAX) {
        // don't accept size_t values which may have come from an
        // inadvertent conversion from a negative int.
        return NULL;
    }

    if ((m_data_pos+len) >= m_data_pos && (m_data_pos+len) <= m_data_size) {
        const void* data = m_data + m_data_pos;
        m_data_pos += len;

        return data;
    }

    return NULL;
}

template<class T>
bool BufferArchive::read_aligned(T *pArg) const {

    if ((m_data_pos+sizeof(T)) <= m_data_size) {

        const void* data = m_data+m_data_pos;
        m_data_pos += sizeof(T);
        *pArg =  *reinterpret_cast<const T*>(data);

        return true;

    } else {
        return false;
    }
}

template<class T>
T BufferArchive::read_aligned() const {

    T result;
    if (!read_aligned(&result)) {
        result = 0;
    }

    return result;
}

bool BufferArchive::read_archivable(Archivable &archivable, const std::string& key) const
{
    int32_t have_archivable = read_int32(key);

    if (!have_archivable) {
        return false;
    }

    archivable.read_from_archive(*this);
    return true;
}

void BufferArchive::init_state()
{
    m_data = 0;
    m_data_size = 0;
    m_data_capacity = 0;
    m_data_pos = 0;
}

void BufferArchive::free_data_no_init()
{
    if (m_data)
        free(m_data);

    m_data = nullptr;
}

void BufferArchive::free_data()
{
    free_data_no_init();
    init_state();
}

void BufferArchive::reset_pos()
{
    m_data_pos = 0;
}



