#ifndef _MSC_VER
#define NOEXCEPT noexcept
#else
#define NOEXCEPT throw()
#endif

#include <iostream>     // for cout, endl
#include <cstddef>      // for size_t, ptrdiff_t
#include <new>          // for std::bad_alloc
#include <stdexcept>    // for std::length_error

template <class T>
class simple_allocator
{
public:

    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    // rebind
    template <class U>
    struct rebind { using other = simple_allocator<U>; };

    // ctors, dtor
    simple_allocator() NOEXCEPT {};
    simple_allocator(const simple_allocator&) NOEXCEPT {};
    template <class U>
    simple_allocator(const simple_allocator<U>&) NOEXCEPT {};
    // allocators are not required to be assignable
    simple_allocator& operator=(const simple_allocator& other) = delete;	
    ~simple_allocator() {};
	
    // obtains the address of an object
    pointer address(reference r) const { return &r; };
    const_pointer address(const_reference r) const { return &r; };
	
    // returns the largest supported allocation size
    size_type max_size() const NOEXCEPT { 
        return (static_cast<size_t>(0) - static_cast<size_t>(1)) / sizeof(T); };

    // equality of allocators does not imply that they must have exactly 
    // the same internal state,  only that they must both be able to 
    // deallocate memory that was allocated with either allocator 
    bool operator!=(const simple_allocator& other) { return !(*this == other); };
    bool operator==(const simple_allocator&) { return true; };

    // allocation
    pointer allocate(size_type n, std::allocator<void>::const_pointer = 0) const
        throw(std::bad_alloc, std::length_error) 
    {
        std::cout << "Allocating " 
            << n 
            << (n == 1 ? " object" : " objects")
            << " of size " 
            << sizeof(T)
            << "." << std::endl;

        if (n == 0) return nullptr;

        if (n > max_size()) 
            throw std::length_error("simple_allocator<T>::allocate() - Integer overflow.");

        // call for non-throwing allocation
        void * const vcp = ::operator new (n * sizeof(T), std::nothrow);

        if (vcp == nullptr)
        {
            // good way to log and pick backup plan here ...
            throw std::bad_alloc();
        }

        std::cout << "Allocation has been completed at " 
            << std::showbase 
            << vcp 
            << std::noshowbase << std::endl;

        return static_cast<pointer>(vcp);
    };

    void deallocate(pointer p, size_type n) 
    {
        if (p == nullptr) return;

        std::cout << "Deallocating " 
	    << n 
	    << (n == 1 ? " object" : " objects")
	    << " of size " 
	    << sizeof(T) 
	    << "." << std::endl;

        ::operator delete(p);
    };
	
    // construction
    template <class U, class... Args>
    void construct(U* p, Args&&... args) 
    {
        //std::cout << "Constructing object" << std::endl;

        void* const cvp = static_cast<void*>(p);

        ::new(cvp) U(std::forward<Args>(args)...);
    };
	
    template <class U>
    void destroy(U* p) 
    { 
        //std::cout << "Destroying object" << std::endl; 
        p->~U(); 
    };
};

