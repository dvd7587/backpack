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
#ifndef BUFFERARCHIVE_H
#define BUFFERARCHIVE_H
#include "archive.h"

class BufferArchive : public Archive
{
public:
    BufferArchive();
    BufferArchive(const uint8_t *data, const size_t& size);
    ~BufferArchive();

    uint8_t* get_data() const;

    bool write_byte_array(const uint8_t *data, size_t len, const std::string& key) override;
    bool write_int32(int32_t val, const std::string &key) override;
    bool write_uint32(uint32_t val, const std::string &key) override;
    bool write_int64(int64_t val, const std::string& key) override;
    bool write_uint64(uint64_t val, const std::string &key) override;
    bool write_float(float val, const std::string& key)  override;
    bool write_double(double val, const std::string& key) override;
    bool write_bool(bool val, const std::string &key) override;
    bool write_string(const std::string &str, const std::string &key) override;
    bool write_archivable(const Archivable& archivable, const std::string& key) override;
    bool write_nullable_archivable(const Archivable* archivable, const std::string& key) override;

    bool read_byte_array(uint8_t *outData, size_t len, const std::string& key) const override;
    int32_t read_int32(const std::string &key) const override;
    uint32_t read_uint32(const std::string &key) const override;
    int64_t read_int64(const std::string& key) const override;
    uint64_t read_uint64(const std::string &key) const override;
    float read_float(const std::string& key) const override;
    double read_double(const std::string& key) const override;
    bool read_bool(const std::string &key) const override;
    bool read_string(std::string& str, const std::string &key) const override;
    bool read_archivable(Archivable& archivable, const std::string& key) const override;

    void free_data();
    size_t get_data_size() const;
    void reset_pos();

private:
    template<class T>
    bool write_aligned(T val);

    template<class T>
    bool read_aligned(T *pArg) const;

    const void* read_inplace(size_t len) const;

    template<class T>
    T read_aligned() const;

    void init_state();
    void free_data_no_init();
    bool grow_data(size_t len);
    bool continue_write(size_t desired);
    bool finish_write(size_t len);

    uint8_t* m_data;
    size_t m_data_size;
    size_t m_data_capacity;
    mutable size_t m_data_pos;

};

#endif // BUFFERARCHIVE_H
