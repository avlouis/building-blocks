// This file is part of avlouis's building-blocks.
//
// It is licensed under the terms of the University of Illinois/NCSA
// Open Source License.  See the LICENSE file for detailed information
// regarding the copyright and license terms.
//
// SPDX-License-Identifier: NCSA

#ifndef AVLOUIS_BB_RINGBUFFER_HPP_INCLUDED
#define AVLOUIS_BB_RINGBUFFER_HPP_INCLUDED

#include <cstddef>

template <typename T, typename S = std::size_t>
class RingBuffer
{
public:
    RingBuffer(S bufferSize);
    RingBuffer(const RingBuffer & other);
    RingBuffer(RingBuffer && other);
    ~RingBuffer();

    RingBuffer & operator=(const RingBuffer & rhs);
    RingBuffer & operator=(RingBuffer && rhs);

    void add(const T & t, bool overrun = false);
    void add(T && t, bool overrun = false);
    S capacity() const;
    T get(T defaultVal = T());
    bool isEmpty() const;
    bool isFull() const;
    S size() const;
    
private:
    S _size;
    T * _buf;
    S _front;
    S _back;
    bool _full;
};

#include "ringbuffer.cpp"

#endif
