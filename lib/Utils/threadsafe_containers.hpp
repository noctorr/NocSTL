#include <memory>
#include <memory_resource>
#include <mutex>
#include <cstddef>
#include <initializer_list>
#include <span>
#include <stdexcept>

namespace stl {
    template < typename _Type, typename Alloc = std::pmr::polymorphic_allocator<_Type>>
    class vector final {
        mutable std::mutex m_lock;
        _Type* m_data        { nullptr };
        std::size_t m_size   { 0 };
        std::size_t m_cap    { 0 };
        public:
        vector() : m_cap(5)
        {
            m_data = allocTraits::allocate(
                m_attr, m_cap
            );
        }

        vector(
            std::initializer_list<_Type> _list
        ) : m_size(_list.size()), m_cap(_list.size() * 2)
        {
            m_data = allocTraits::allocate(
                m_attr, m_cap
            );

            std::size_t index{};
            for (
                typename std::initializer_list<_Type>::iterator It = _list.begin();
                It != _list.end();
                It++, index++
            ) {
                allocTraits::construct(m_attr, m_data + index, *It);
            }
        }

        vector(
            std::span<_Type> _list
        ) : m_size(_list.size()), m_cap(_list.size() * 2)
        {
            m_data = allocTraits::allocate(
                m_attr, m_cap
            );

            std::size_t index{};
            for (
                typename std::span<_Type>::iterator It = _list.begin();
                It != _list.end();
                It++, index++
            ) {
                allocTraits::construct(m_attr, m_data + index, *It);
            }
        }

        vector(
            const vector& other
        ) : m_data(other.m_data), m_cap(other.m_cap), m_size(other.m_size)
        {}

        vector(
            vector&& other
        ) : m_data(other.m_data), m_cap(other.m_cap), m_size(other.m_size)
        {
            other.m_data = nullptr;
            other.m_cap = 0;
            other.m_size = 0;
        }

        ~vector() {
            clear();
            allocTraits::deallocate(m_attr, m_data, m_cap);
        }

        vector& operator= ( const vector& other ) noexcept
        {
            std::lock_guard<std::mutex> _cpy(m_lock);

            if ( this != &other ) {
                m_data = other.m_data;
                m_cap = other.m_cap;
                m_size = other.m_size;
            }

            return *this;
        }

        vector& operator= ( vector&& other ) noexcept
        {
            std::lock_guard<std::mutex> _mov(m_lock);

            if ( this != &other ) {
                m_data = other.m_data;
                m_cap = other.m_cap;
                m_size = other.m_size;

                other.m_data = nullptr;
                other.m_cap = 0;
                other.m_size = 0;
            }

            return *this;
        }

        _Type& operator[] ( const std::size_t index ) const
        {
            std::lock_guard<std::mutex> _dang_check(m_lock);

            return m_data[index];
        }

        _Type& at ( const std::size_t index ) const
        {
            std::lock_guard<std::mutex> _throw_check(m_lock);

            if (
                index >= m_size
            ) {
                throw std::out_of_range("Input index for vector is out of the array's range.");
            } else {
                return m_data[index];
            }
        }

        void push_back(_Type _payload) {
            std::lock_guard<std::mutex> _psh_bck(m_lock);
            if ( m_size == m_cap ) {
                realloc_cap(
                    m_cap * 2
                );
                m_size += 1;
                allocTraits::construct(m_attr, m_data + m_size, _payload);
            } else {
                m_size += 1;
                allocTraits::construct(m_attr, m_data + m_size, _payload);
            }
        }

        void clear() noexcept {
            std::lock_guard<std::mutex> _clr(m_lock);
            if (
                m_size != 0
            ) {
                for (
                    std::size_t index{};
                    index < m_size;
                    index++
                ) {
                    allocTraits::destroy(
                        m_attr,
                        m_data + index
                    );
                }
                m_size = 0;
            }
        }
        private:
        using allocTraits = std::allocator_traits<Alloc>;
        Alloc m_attr;

        void realloc_cap(
            const std::size_t _new_cap
        ) {
            if (
                m_size == 0 &&
                m_cap == 0
            ) {
                m_data = allocTraits::allocate(m_attr, _new_cap);
                m_data = _new_cap;
            } else if (
                m_size == 0 &&
                m_cap != 0
            ) {
                allocTraits::deallocate(m_attr, m_data, m_cap);
                m_data = allocTraits::allocate(m_attr, _new_cap);
                m_cap = _new_cap;
            } else if (
                m_size != 0 &&
                m_cap != 0
            ) {
                _Type* _buffer = allocTraits::allocate(m_attr, m_cap);
                for (
                    std::size_t index{};
                    index < m_cap;
                    index++
                ) {
                    allocTraits::construct(m_attr, _buffer + index, *(m_data + index));
                    allocTraits::destroy(m_attr, m_data + index);
                }

                allocTraits::deallocate(m_attr, m_data, m_cap);
                m_data = allocTraits::allocate(m_attr, _new_cap);
                
                for (
                    std::size_t index{};
                    index < m_cap;
                    index++
                ) {
                    allocTraits::construct(m_attr, m_data + index, *(_buffer + index));
                    allocTraits::destroy(m_attr, _buffer + index);
                }

                allocTraits::deallocate(m_attr, _buffer, m_cap);
                m_cap = _new_cap;
            }
        }

        void realloc_cap_only(
            const std::size_t _new_cap
        ) {
            if (
                m_size == 0 &&
                m_cap == 0
            )  {
                m_data = allocTraits::allocate(m_attr, _new_cap);
                m_cap = _new_cap;
            } else if (
                m_size == 0 &&
                m_cap != 0
            ) {
                allocTraits::deallocate(m_attr, m_data, m_cap);
                m_data = allocTraits::allocate(m_attr, _new_cap);
                m_cap = _new_cap;
            } else if (
                m_size != 0 && 
                m_cap != 0
            ) {
                for (
                    std::size_t index{};
                    index < m_size;
                    index++
                ) {
                    allocTraits::destroy(m_attr, m_data + index);
                }

                allocTraits::deallocate(m_attr, m_data, m_cap);
                m_data = allocTraits::allocate(m_attr, _new_cap);
                m_cap = _new_cap;
            }
        }

        void realloc_data(
            const std::size_t _new_cap,
            std::span<_Type> _new_data
        ) {
            realloc_cap_only(_new_cap);

            std::size_t index{};
            for (
                typename std::span<_Type>::iterator It = _new_data.begin();
                It != _new_data.end();
                It++, index++
            ) {
                allocTraits::construct(m_attr, m_data + index, *It);
            }
        }
    };
}
