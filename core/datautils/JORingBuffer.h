#ifndef _RING_BUFFER_H_
#define _RING_BUFFER_H_

#include <atomic>
#include <cstddef>

#include "utils/JOMacro.h"

NS_JOFW_BEGIN

template <typename T> 
class JO_DLL JORingBuffer {	
public:
	JORingBuffer(const size_t size) : m_size(size), m_head(0), m_tail(0) {
		m_buffer = new T[size];
	}

	virtual ~JORingBuffer() {
		delete[] m_buffer;
	}

	inline bool push(const T &object) {
		size_t head = m_head.load(std::memory_order_relaxed);
		size_t nextHead = next(head);
		if (nextHead == m_tail.load(std::memory_order_acquire)) {
			return false;
		}
		m_buffer[head] = object;
		m_head.store(nextHead, std::memory_order_release);

		return true;
	}

	inline bool pop(T &object) {
		size_t tail = m_tail.load(std::memory_order_relaxed);
		if (tail == m_head.load(std::memory_order_acquire)) {
			return false;
		}

		object = m_buffer[tail];
        m_buffer[tail] = nullptr;
		m_tail.store(next(tail), std::memory_order_release);
		return true;
	}
    inline T pop() {
        size_t tail = m_tail.load(std::memory_order_relaxed);
        if (tail == m_head.load(std::memory_order_acquire)) {
            return nullptr;
        }
        
        T object = m_buffer[tail];
        m_buffer[tail] = nullptr;
        m_tail.store(next(tail), std::memory_order_release);
        return object;
    }
	inline bool empty() {
		return m_head == m_tail;
	}

	inline int avaliable() {
		return (m_tail > m_head ? (m_tail - m_head) : (m_tail - m_head + m_size));
	}

private:
	T *m_buffer;
	std::atomic<size_t> m_head;
	std::atomic<size_t> m_tail;
	const size_t m_size;

	size_t next(size_t current) {
		return (current + 1) % m_size;
	}

};

NS_JOFW_END
#endif