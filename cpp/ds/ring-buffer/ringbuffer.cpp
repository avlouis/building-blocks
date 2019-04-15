// This file is part of avlouis's building-blocks.
//
// It is licensed under the terms of the University of Illinois/NCSA
// Open Source License.  See the LICENSE file for detailed information
// regarding the copyright and license terms.
//
// SPDX-License-Identifier: NCSA

template <typename T, typename S>
RingBuffer<T,S>::RingBuffer(S bufferSize)
{
    _size = bufferSize;
    _buf = new T[_size];
    _front = 0;
    _back = 0;
    _full = false;
}

template <typename T, typename S>
RingBuffer<T,S>::RingBuffer(const RingBuffer<T,S> & other)
{
    _size = other._size;
    _buf = new T[_size];
    _front = other._front;
    _back = other._back;
    _full = other._full;
    if(_full) {
	for(S i = 0; i < _size; i++) {
	    _buf[i] = other._buf[i];
	}
    } else {
	for(S i = _front; i != _back; i = (i+1)%_size) {
	    _buf[i] = other._buf[i];
	}
    }
}

template <typename T, typename S>
RingBuffer<T,S>::RingBuffer(RingBuffer<T,S> && other)
{
    _size = other._size;
    _buf = other._buf;
    other._buf = nullptr;
    _front = other._front;
    _back = other._back;
    _full = other._full;
}

template <typename T, typename S>
RingBuffer<T,S>::~RingBuffer()
{
    delete[] _buf;
}

template <typename T, typename S>
RingBuffer<T,S> & RingBuffer<T,S>::operator=(const RingBuffer<T,S> & rhs)
{
    if(this == &rhs) {
	return *this;
    }
    *this = RingBuffer<T,S>(rhs);
    return *this;
}

template <typename T, typename S>
RingBuffer<T,S> & RingBuffer<T,S>::operator=(RingBuffer<T,S> && rhs)
{
    if(this == &rhs) {
	return *this;
    }
    _size = rhs._size;
    T * tmp = _buf;
    _buf = rhs._buf;
    rhs._buf = tmp;
    _front = rhs._front;
    _back = rhs._back;
    _full = rhs._full;
    return *this;
}

template <typename T, typename S>
void RingBuffer<T,S>::add(const T & t, bool overrun)
{
    if(!_full) {
	_buf[_back] = t;
	_back = (_back + 1) % _size;
	_full = (_back == _front);
    } else if(overrun) {
	_buf[_back] = t;
	_back = (_back + 1) % _size;
	_front = _back;
    }
}

template <typename T, typename S>
void RingBuffer<T,S>::add(T && t, bool overrun)
{
    if(!_full) {
	_buf[_back] = t;
	_back = (_back + 1) % _size;
	_full = (_back == _front);
    } else if(overrun) {
	_buf[_back] = t;
	_back = (_back + 1) % _size;
	_front = _back;
    }
}

template <typename T, typename S>
S RingBuffer<T,S>::capacity() const
{
    return _size;
}

template <typename T, typename S>
T RingBuffer<T,S>::get(T defaultVal)
{
    if((_front == _back) && !_full) {
	return defaultVal;
    } else {
	T r = _buf[_front];
	_front = (_front + 1) % _size;
	if(_full) {
	    _full = false;
	}
	return r;
    }
}

template <typename T, typename S>
bool RingBuffer<T,S>::isEmpty() const
{
    return !_full && (_front == _back);
}

template <typename T, typename S>
bool RingBuffer<T,S>::isFull() const
{
    return _full;
}

template <typename T, typename S>
S RingBuffer<T,S>::size() const
{
    if(_full) {
	return _size;
    } else {
	return (_back - _front) % _size;
    }
}
