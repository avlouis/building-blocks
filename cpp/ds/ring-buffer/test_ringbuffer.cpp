// This file is part of avlouis's building-blocks.
//
// It is licensed under the terms of the University of Illinois/NCSA
// Open Source License.  See the LICENSE file for detailed information
// regarding the copyright and license terms.
//
// SPDX-License-Identifier: NCSA

#include "ringbuffer.hpp"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

TEST_CASE("An empty RingBuffer is tested", "[RingBuffer]")
{
    const std::size_t s = 16;
    RingBuffer<char> rb(s);
    REQUIRE(rb.capacity() == s);
    REQUIRE(rb.size() == 0);
    REQUIRE(rb.isEmpty());
    REQUIRE(!rb.isFull());
}

TEST_CASE("RingBuffer::add ref is tested", "[RingBuffer]")
{
    const std::size_t s = 4;
    RingBuffer<int> rb(s);
    REQUIRE(rb.capacity() == s);
    for(int i = 0; i < s; i++) {
	rb.add(i);
	REQUIRE(rb.size() == i + 1);
	REQUIRE(!rb.isEmpty());
	REQUIRE(rb.isFull() == (i == s-1));
    }
}

TEST_CASE("RingBuffer::add ref with overrun is tested", "[RingBuffer]")
{
    const std::size_t s = 4;
    RingBuffer<int> rb(s);
    for(int i = 0; i < s+2; i++) {
	rb.add(i, true);
	REQUIRE(rb.size() == ((i < s) ? i+1 : s));
	REQUIRE(!rb.isEmpty());
	REQUIRE(rb.isFull() == (i >= s-1));
    }
    for(int i = 0; i < s; i++) {
	REQUIRE(rb.get() == i+2);
    }
}

TEST_CASE("RingBuffer::add rvalue is tested", "[RingBuffer]")
{
    const std::size_t s = 4;
    RingBuffer<float> rb(s);
    REQUIRE(rb.capacity() == s);
    for(int i = 0; i < s; i++) {
	rb.add(i/(i+1));
	REQUIRE(rb.size() == i + 1);
	REQUIRE(!rb.isEmpty());
	REQUIRE(rb.isFull() == (i == s-1));
    }
}

TEST_CASE("RingBuffer::add rvalue with overrun is tested", "[RingBuffer]")
{
    const std::size_t s = 5;
    const std::size_t extra = 7;
    RingBuffer<int> rb(s);
    for(int i = 0; i < s+extra; i++) {
	rb.add(i+1, true);
	REQUIRE(rb.size() == ((i < s) ? i+1 : s));
	REQUIRE(!rb.isEmpty());
	REQUIRE(rb.isFull() == (i >= s-1));
    }
    for(int i = 0; i < s; i++) {
	REQUIRE(rb.get() == i+extra+1);
    }
}

TEST_CASE("RingBuffer::get is tested", "[RingBuffer]")
{
    RingBuffer<char> rb(16);
    REQUIRE(rb.capacity() == 16);
    rb.add('a');
    rb.add('b');
    rb.add('c');
    REQUIRE(rb.get() == 'a');
    REQUIRE(rb.get() == 'b');
    REQUIRE(rb.get() == 'c');
    REQUIRE(rb.get() == char());
    rb.add('d');
    rb.add('e');
    REQUIRE(rb.get() == 'd');
    rb.add('f');
    REQUIRE(rb.get() == 'e');
    REQUIRE(rb.get() == 'f');
    REQUIRE(rb.get() == char());
}

TEST_CASE("RingBuffer wrap around is tested", "[RingBuffer]")
{
    RingBuffer<int> rb(8);
    REQUIRE(rb.capacity() == 8);
    for(int i = 0; i < 8; i++) {
	rb.add(i);
    }
    for(int i = 0; i < 4; i++) {
	REQUIRE(rb.get() == i);
    }
    for(int i = 8; i < 12; i++) {
	rb.add(i);
    }
    for(int i = 4; i < 10; i++) {
	REQUIRE(rb.get() == i);
    }
    for(int i = 12; i < 18; i++) {
	rb.add(i);
    }
    for(int i = 10; i < 18; i++) {
	REQUIRE(rb.get() == i);
    }
    REQUIRE(rb.isEmpty());
}

TEST_CASE("RingBuffer copy constructor is tested", "[RingBuffer]")
{
    RingBuffer<int> rb(8);
    for(int i = 0; i < 4; i++) {
	rb.add(i);
    }
    RingBuffer<int> rb2(rb);
    for(int i = 0; i < 4; i++) {
	REQUIRE(rb.get() == i);
	REQUIRE(rb2.get() == i);
    }
}

TEST_CASE("RingBuffer move constructor is tested", "[RingBuffer]")
{
    RingBuffer<int> rb(8);
    for(int i = 0; i < 4; i++) {
	rb.add(i);
    }
    RingBuffer<int> rb2(std::move(rb));
    // NOTE rb is now invalid
    for(int i = 0; i < 4; i++) {
	REQUIRE(rb2.get() == i);
    }
}

TEST_CASE("RingBuffer copy assignment is tested", "[RingBuffer]")
{
    RingBuffer<int> rb(8);
    for(int i = 0; i < 6; i++) {
	rb.add(i);
    }
    RingBuffer<int> rb2(4);
    rb2 = rb;
    for(int i = 0; i < 6; i++) {
	REQUIRE(rb.get() == i);
	REQUIRE(rb2.get() == i);
    }
}

TEST_CASE("RingBuffer move assignment is tested", "[RingBuffer]")
{
    RingBuffer<int> rb(8);
    for(int i = 0; i < 3; i++) {
	rb.add(i);
    }
    RingBuffer<int> rb2(4);
    rb2 = std::move(rb);
    // NOTE rb is now invalid
    for(int i = 0; i < 3; i++) {
	REQUIRE(rb2.get() == i);
    }
}
