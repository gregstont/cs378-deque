// ----------------------
// projects/deque/Deque.h
// Copyright (C) 2014
// Taylor Gregston
// Glenn P. Downing (skeleton)
// ----------------------

#ifndef Deque_h
#define Deque_h

// --------
// includes
// --------

#include <algorithm> // copy, equal, lexicographical_compare, max, swap
#include <cassert>   // assert
#include <iterator>  // iterator, bidirectional_iterator_tag
#include <memory>    // allocator
#include <stdexcept> // out_of_range
#include <utility>   // !=, <=, >, >=

// -----
// using
// -----

using std::rel_ops::operator!=;
using std::rel_ops::operator<=;
using std::rel_ops::operator>;
using std::rel_ops::operator>=;

// -------
// defines
// -------

/**
 * This deque will use rows of size INITIAL_ROW_SIZE.
 * That value must be a power of 2 in this implementation because
 * it allows us to replace the expensive divide and mod with 
 * bit shifts and masking.
 * The following constraints must be adhered to!
 */

#define DIV_ROW_SHIFT       4   // THIS VALUE MUST BE == log2(INITIAL_ROW_SIZE)
#define INITIAL_ROW_SIZE    16  // THIS VALUE MUST BE == 2^DIV_ROW_SHIFT
#define MOD_ROW_MASK        15  // THIS VALUE MUST BE == INITIAL_ROW_SIZE - 1


// -------
// destroy
// -------

template <typename A, typename BI>
BI destroy (A& a, BI b, BI e) {
    using namespace std;
    while (b != e) {
        --e;
        a.destroy(&*e);}
    return b;
}

// ------------------
// uninitialized_copy
// ------------------

template <typename A, typename II, typename BI>
BI uninitialized_copy (A& a, II b, II e, BI x) {
    using namespace std;
    BI p = x;
    try {
        while (b != e) {
            a.construct(&*x, *b);
            ++b;
            ++x;
        }
    }
    catch (...) {
        destroy(a, p, x);
        throw;}
    return x;
}

// ------------------
// uninitialized_fill
// ------------------

template <typename A, typename BI, typename U>
BI uninitialized_fill (A& a, BI b, BI e, const U& v) {
    BI p = b;
    try {
        while (b != e) {
            a.construct(&*b, v);
            ++b;}}
    catch (...) {
        destroy(a, p, b);
        throw;}
    return e;
}

// -------
// my_deque
// -------

template < typename T, typename A = std::allocator<T> >
class my_deque {
public:
    // --------
    // typedefs
    // --------
    
    typedef A                                        allocator_type;
    typedef typename allocator_type::value_type      value_type;
    
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;
    
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    
public:
    // -----------
    // operator ==
    // -----------
    
    /**
     * checks to see if the lhs == rhs
     * @param   lhs the left hand side in question
     * @param   rhs the right hand side in question
     * @return  true if the lhs and rhs have same value and number of items
     */
    friend bool operator == (const my_deque& lhs, const my_deque& rhs) {
        return (lhs.size() == rhs.size()) && std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
    
    // ----------
    // operator <
    // ----------
    
    /**
     * checks to see if the lhs < rhs
     * @param   lhs the left hand side in question
     * @param   rhs the right hand side in question
     * @return  true if the lhs is less than the rhs
     */
    friend bool operator < (const my_deque& lhs, const my_deque& rhs) {
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
    
private:
    // ----
    // data
    // ----
    
    allocator_type _a;  //the standard allocator
    typename A::template rebind<T*>::other _ap; //the pointer allocator
    T** deque_root;     //root of our 2d deque
    size_t row_count;   //number of rows
    size_t deque_size;  //how many elements in here
    size_t begin_index; //where is the begining?
    size_t end_index;   //where is the end?
    
    
private:
    // -----
    // valid
    // -----
    
    bool valid () const {
        return (begin_index <= end_index) && (deque_size >= 0) && (row_count >= 0);
    }
    
    /**
     * print this deck to cout - for debugging only
     */
    void print_deque() {
        using namespace std;
        cout << "Printing; size:" << deque_size << " rows:" << row_count << endl;
        for(size_t i = 0; i < row_count; ++i) {
            cout << "\tROW" << i << ": ";
            for(int j = 0; j < INITIAL_ROW_SIZE; ++j)
                cout << deque_root[i][j] << "  ";
            cout << endl;
        }
        cout << "Done printing" << endl;
    }
    
    /**
     * allocate some rows for the deque
     * @param   num_elements the number of elements this container should hold
     */
    void allocate_rows(size_type num_elements) {
        row_count = (num_elements + INITIAL_ROW_SIZE - 1) / INITIAL_ROW_SIZE;
        
        //allocate/construct pointers
        deque_root = _ap.allocate(row_count);
        uninitialized_fill (_ap, deque_root, deque_root + row_count, (T*)0 );
        
        //allocate rows
        for(size_type i = 0; i < row_count; ++i)
            deque_root[i] = _a.allocate(INITIAL_ROW_SIZE);
    }
    
public:
    // --------
    // iterator
    // --------
    
    class iterator {
    public:
        // --------
        // typedefs
        // --------
        
        typedef std::bidirectional_iterator_tag   iterator_category;
        typedef typename my_deque::value_type      value_type;
        typedef typename my_deque::difference_type difference_type;
        typedef typename my_deque::pointer         pointer;
        typedef typename my_deque::reference       reference;
        
    public:
        // -----------
        // operator ==
        // -----------
        
        /**
         * checks to see if the lhs == rhs
         * @param   lhs the left hand side in question
         * @param   rhs the right hand side in question
         * @return  true if the lhs and rhs point to the same value
         */
        friend bool operator == (const iterator& lhs, const iterator& rhs) {
            return (lhs.owner == rhs.owner) && (lhs.index == rhs.index);
        }
        
        /**
         * checks to see if the lhs != rhs
         * @param   lhs the left hand side in question
         * @param   rhs the right hand side in question
         * @return  false if the lhs and rhs point to the same value
         */
        friend bool operator != (const iterator& lhs, const iterator& rhs) {
            return !(lhs == rhs);
        }
        
        // ----------
        // operator +
        // ----------
        
        /**
         * adds a value to the iterator
         * @param   lhs the iterator to add to
         * @param   rhs the amount to add
         * @return  the iterator with its new value
         */
        friend iterator operator + (iterator lhs, difference_type rhs) {
            return lhs += rhs;
        }
        
        // ----------
        // operator -
        // ----------
        
        /**
         * subtracts a value from the iterator
         * @param   lhs the iterator to subtract from
         * @param   rhs the amount to subtract
         * @return  the iterator with its new value
         */
        friend iterator operator - (iterator lhs, difference_type rhs) {
            return lhs -= rhs;
        }
        
    private:
        // ----
        // data
        // ----
        
        my_deque *owner;
        size_t index;
        
    private:
        // -----
        // valid
        // -----
        
        bool valid () const {
            return (index <= owner->end_index + 1) && (owner != NULL);
        }
        
    public:
        // -----------
        // constructor
        // -----------
        
        /**
         * creates a new my_deque<T>::iterator
         * @param   *owner_ a pointer to the underlying container
         * @param   index_ the index in the container to point to
         * @return  the iterator
         */
        iterator (my_deque *owner_, size_t index_) {
            owner = owner_;
            index = index_;
            assert(valid());
        }
        
        // Default copy, destructor, and copy assignment.
        // iterator (const iterator&);
        // ~iterator ();
        // iterator& operator = (const iterator&);
        
        // ----------
        // operator *
        // ----------
        
        /**
         * dereference this iterator
         * @returns the value at which this iterator is pointing
         */
        reference operator * () const {
            return owner->deque_root[index >> DIV_ROW_SHIFT][index & MOD_ROW_MASK];
        }
        
        // -----------
        // operator ->
        // -----------
        
        /**
         * dereference pointer this iterator
         * @returns a pointer to this
         */
        pointer operator -> () const {
            return &**this;
        }
        
        // -----------
        // operator ++
        // -----------
        
        /**
         * increment (pre) this iterator by one. the iterator will point to the next value
         * @returns iterator with its NEW value
         */
        iterator& operator ++ () {
            ++index;
            assert(valid());
            return *this;
        }
        
        /**
         * increment (post) this iterator by one. the iterator will point to the next value
         * @returns iterator with its OLD value
         */
        iterator operator ++ (int) {
            iterator x = *this;
            ++(*this);
            assert(valid());
            return x;
        }
        
        // -----------
        // operator --
        // -----------
        
        /**
         * decrement (pre) this iterator by one. the iterator will point to the previous value
         * @returns iterator with its NEW value
         */
        iterator& operator -- () {
            --index;
            assert(valid());
            return *this;
        }
        
        /**
         * decrement (post) this iterator by one. the iterator will point to the previous value
         * @returns iterator with its OLD value
         */
        iterator operator -- (int) {
            iterator x = *this;
            --(*this);
            assert(valid());
            return x;
        }
        
        // -----------
        // operator +=
        // -----------
        
        /**
         * increment this iterator by a value d. the iterator will point to the value that is d slots ahead
         * @param d the value to increment by
         * @returns iterator with its NEW value
         */
        iterator& operator += (difference_type d) {
            index += d;
            assert(valid());
            return *this;
        }
        
        // -----------
        // operator -=
        // -----------
        
        /**
         * decrement this iterator by a value d. the iterator will point to the value that is d slots behind
         * @param d the value to decrement by
         * @returns iterator with its NEW value
         */
        iterator& operator -= (difference_type d) {
            index -= d;
            assert(valid());
            return *this;
        }
    }; //end iterator
    
public:
    // --------------
    // const_iterator
    // --------------
    
    class const_iterator {
    public:
        // --------
        // typedefs
        // --------
        
        typedef std::bidirectional_iterator_tag   iterator_category;
        typedef typename my_deque::value_type      value_type;
        typedef typename my_deque::difference_type difference_type;
        typedef typename my_deque::const_pointer   pointer;
        typedef typename my_deque::const_reference reference;
        
    public:
        // -----------
        // operator ==
        // -----------
        
        /**
         * checks to see if the lhs == rhs
         * @param   lhs the left hand side in question
         * @param   rhs the right hand side in question
         * @return  true if the lhs and rhs point to the same value
         */
        friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) {
            return (lhs.owner == rhs.owner) && (lhs.index == rhs.index);
        }
        
        /**
         * checks to see if the lhs != rhs
         * @param   lhs the left hand side in question
         * @param   rhs the right hand side in question
         * @return  false if the lhs and rhs point to the same value
         */
        friend bool operator != (const const_iterator& lhs, const const_iterator& rhs) {
            return !(lhs == rhs);
        }
        
        // ----------
        // operator +
        // ----------
        
        /**
         * adds a value to the iterator
         * @param   lhs the iterator to add to
         * @param   rhs the amount to add
         * @return  the iterator with its new value
         */
        friend const_iterator operator + (const_iterator lhs, difference_type rhs) {
            return lhs += rhs;
        }
        
        // ----------
        // operator -
        // ----------
        
        /**
         * subtracts a value from the iterator
         * @param   lhs the iterator to subtract from
         * @param   rhs the amount to subtract
         * @return  the iterator with its new value
         */
        friend const_iterator operator - (const_iterator lhs, difference_type rhs) {
            return lhs -= rhs;
        }
        
    private:
        // ----
        // data
        // ----
        
        const my_deque *owner;
        size_t index;
        
    private:
        
        // -----
        // valid
        // -----
        
        bool valid () const {
            return (index <= owner->end_index) && (owner != NULL);
        }
        
        
        
    public:
        
        // -----------
        // constructor
        // -----------
        
        /**
         * creates a new my_deque<T>::const_iterator, underlying values cannot be changed
         * @param   *owner_ a pointer to the underlying container
         * @param   index_ the index in the container to point to
         * @return  the iterator
         */
        const_iterator (const my_deque *owner_, const size_t index_) {
            owner = owner_;
            index = (size_t)index_;
        }
        // Default copy, destructor, and copy assignment.
        // const_iterator (const const_iterator&);
        // ~const_iterator ();
        // const_iterator& operator = (const const_iterator&);
        
        // ----------
        // operator *
        // ----------
        
        /**
         * dereference this iterator
         * @returns the value at which this iterator is pointing
         */
        reference operator * () const {
            return owner->deque_root[index >> DIV_ROW_SHIFT][index & MOD_ROW_MASK];
        }
        
        // -----------
        // operator ->
        // -----------
        
        /**
         * dereference pointer this iterator
         * @returns a pointer to this
         */
        pointer operator -> () const {
            return &**this;
        }
        
        // -----------
        // operator ++
        // -----------
        
        /**
         * increment (pre) this iterator by one. the iterator will point to the next value
         * @returns iterator with its NEW value
         */
        const_iterator& operator ++ () {
            ++index;
            assert(valid());
            return *this;
        }
        
        /**
         * increment (post) this iterator by one. the iterator will point to the next value
         * @returns iterator with its OLD value
         */
        const_iterator operator ++ (int) {
            const_iterator x = *this;
            ++(*this);
            assert(valid());
            return x;
        }
        
        // -----------
        // operator --
        // -----------
        
        /**
         * decrement (pre) this iterator by one. the iterator will point to the previous value
         * @returns iterator with its NEW value
         */
        const_iterator& operator -- () {
            --index;
            assert(valid());
            return *this;
        }
        
        /**
         * decrement (post) this iterator by one. the iterator will point to the previous value
         * @returns iterator with its OLD value
         */
        const_iterator operator -- (int) {
            const_iterator x = *this;
            --(*this);
            assert(valid());
            return x;
        }
        
        // -----------
        // operator +=
        // -----------
        
        /**
         * increment this iterator by a value d. the iterator will point to the value that is d slots ahead
         * @param d the value to increment by
         * @returns iterator with its NEW value
         */
        const_iterator& operator += (difference_type d) {
            index += d;
            assert(valid());
            return *this;
        }
        
        // -----------
        // operator -=
        // -----------
        
        /**
         * decrement this iterator by a value d. the iterator will point to the value that is d slots behind
         * @param d the value to decrement by
         * @returns iterator with its NEW value
         */
        const_iterator& operator -= (difference_type d) {
            index -= d;
            assert(valid());
            return *this;
        }
    };
    
public:
    
    // ------------
    // constructors
    // ------------
    
    /**
     * create a new deque of no given size.
     * This deck is a two-dimensional structure that will not invalidate old references on reallocations
     * @param   a the allocator to be used for this deque
     * @return  the new deque
     */
    explicit my_deque (const allocator_type& a = allocator_type()) :
    _a(a)
    {
        allocate_rows(INITIAL_ROW_SIZE);
        deque_size = 0;
        begin_index = INITIAL_ROW_SIZE >> 1; //start at the middle
        end_index = begin_index;
        assert(valid());
    }
    
    /**
     * create a new deque of size s, filled with v
     * @param   s the size of the deque to be created
     * @param   v the value that should be filled into all values (optional)
     * @param   a the allocator to be used for this deque
     * @return  the new deque
     */
    explicit my_deque (size_type s, const_reference v = value_type(), const allocator_type& a = allocator_type()) :
    _a(a)
    {
        allocate_rows(s);
        deque_size = s;
        begin_index = 0; //should this be somewhere different?
        end_index = s;
        
        uninitialized_fill (_a, begin(), end(), v);
        
        assert(valid());
    }
    
    /**
     * create a new deque containing the same elements as that
     * @param   that the deque to be replicated
     * @return  the new deque
     */
    my_deque (const my_deque& that) :
    _a(that._a)
    {
        allocate_rows(that.deque_size);
        
        deque_size = that.deque_size;
        begin_index = 0; //should this be somewhere different?
        end_index = begin_index + deque_size;
        
        uninitialized_copy (_a, that.begin(), that.end(), begin());
        assert(valid());
    }
    
    // ----------
    // destructor
    // ----------
    
    /**
     * destroy this deque and all it's members and free all memory
     */
    ~my_deque () {
        
        if(deque_root)
            clear();
        
        assert(valid());
    }
    
    // ----------
    // operator =
    // ----------
    
    /**
     * assignment operator, will set this to have values equivalent of rhs
     * @param rhs the deque that is to be replicated into this
     * @returns this
     */
    my_deque& operator = (const my_deque& rhs) {
        using namespace std;
        
        if(this == &rhs)
            return *this;
        if(rhs.size() == deque_size) //same size
            std::copy(rhs.begin(), rhs.end(), begin());
        else if (rhs.size() < deque_size) { //rhs smaller
            iterator temp = std::copy(rhs.begin(), rhs.end(), begin());
            destroy(_a, temp, end());
            deque_size = rhs.size();
            end_index = begin_index + deque_size;
        }
        else { //rhs is too big to fit
            clear();
            allocate_rows(rhs.size());
            begin_index = 0;
            uninitialized_copy(_a, rhs.begin(), rhs.end(), begin());
            deque_size = rhs.size();
            end_index = deque_size;
        }
        
        
        assert(valid());
        return *this;
    }
    
    // -----------
    // operator []
    // -----------
    
    /**
     * index this deque
     * @param index the index in this deque to be evaluated
     * @return a reference to the value at index in this deque
     */
    reference operator [] (size_type index) {
        size_type temp = index + begin_index;
        return deque_root[temp >> DIV_ROW_SHIFT][temp & MOD_ROW_MASK];
        
    }
    
    /**
     * index this deque, does not allow write
     * @param index the index in this deque to be evaluated
     * @return a reference to the value at index in this deque (read only)
     */
    const_reference operator [] (size_type index) const {
        return const_cast<my_deque*>(this)->operator[](index);
    }
    
    // --
    // at
    // --
    
    /**
     * index this deque
     * @param index the index in this deque to be evaluated
     * @return a reference to the value at index in this deque
     * @throws out_of_range if the index is greater or equal to size
     */
    reference at (size_type index) {
        if(index >= deque_size)
            throw std::out_of_range("at index out of range");
        size_type temp = index + begin_index;
        return deque_root[temp >> DIV_ROW_SHIFT][temp & MOD_ROW_MASK];
    }
    
    /**
     * index this deque (read only)
     * @param index the index in this deque to be evaluated
     * @return a reference to the value at index in this deque
     * @throws out_of_range if the index is greater or equal to size
     */
    const_reference at (size_type index) const {
        return const_cast<my_deque*>(this)->at(index);
    }
    
    // -----
    // front
    // -----
    
    /**
     * reference the front end of this deque
     * @returns the reference to the element at the front of the deque
     */
    reference front () {
        return deque_root[begin_index >> DIV_ROW_SHIFT][begin_index & MOD_ROW_MASK];
    }
    
    /**
     * reference the front end of this deque (read only)
     * @returns the reference to the element at the front of the deque
     */
    const_reference front () const {
        return const_cast<my_deque*>(this)->front();
    }
    
    
    // ----
    // back
    // ----
    
    /**
     * reference the back end of this deque
     * @returns the reference to the element at the back of the deque
     */
    reference back () {
        return deque_root[(end_index - 1) >> DIV_ROW_SHIFT][(end_index - 1) & MOD_ROW_MASK];
    }
    
    /**
     * reference the back end of this deque (read only)
     * @returns the reference to the element at the back of the deque
     */
    const_reference back () const {
        return const_cast<my_deque*>(this)->back();
    }
    
    
    // -----
    // clear
    // -----
    
    /**
     * clears this deque, destroying all members and deallocating all memory
     */
    void clear () {
        //destroy the elements
        destroy(_a, begin(), end());
        
        //deallocate elements
        for(size_t i = 0; i < row_count; ++i)
            _a.deallocate(deque_root[i], INITIAL_ROW_SIZE);
        
        //destroy/deallocate the pointers
        destroy(_ap, deque_root, deque_root + row_count);
        _ap.deallocate(deque_root, row_count);
        
        //reset members
        deque_size = 0;
        deque_root = NULL;
        row_count = 0;
        begin_index = INITIAL_ROW_SIZE >> 1;
        end_index = begin_index;
        
        assert(valid());
    }
    
    // -----
    // empty
    // -----
    
    /**
     * checks to see if the deque contains any values
     * @returns true if size == 0
     */
    bool empty () const {
        return !size();
    }
    
    // -----
    // begin
    // -----
    
    /**
     * get an iterator that points to the first value in this iterator
     * @returns an iterator pointing to the first value
     */
    iterator begin () {
        return iterator(this, begin_index);
    }
    
    /**
     * get an iterator that points to the first value in this iterator (read only)
     * @returns an iterator pointing to the first value
     */
    const_iterator begin () const {
        return const_iterator(this, begin_index);
    }
    
    // ---
    // end
    // ---
    
    /**
     * get an iterator that points past the last value in this iterator
     * @returns an iterator pointing past the end
     */
    iterator end () {
        return iterator(this, end_index);
    }
    
    /**
     * get an iterator that points past the last value in this iterator (read only)
     * @returns an iterator pointing past the end
     */
    const_iterator end () const {
        return const_iterator(this, end_index);
    }
    
    // -----
    // erase
    // -----
    
    /**
     * erase a value in this deque, destroying it and concatenating the remaining elements
     * @return an iterator pointing past the value erased
     */
    iterator erase (iterator remove) {
        std::copy(remove + 1, end(), remove);
        _a.destroy(&*(--end()));
        
        --deque_size;
        --end_index;
        assert(valid());
        return ++remove;
    }
    
    // ------
    // insert
    // ------
    
    /**
     * insert a value into a spot in this deque, shifting following values to make room
     * @param spot where to insert the value
     * @ins the value to be inserted
     * @return an iterator pointing to the value inserted
     */
    iterator insert (iterator spot, const_reference ins) {
        using namespace std;
        if(!deque_root)
            allocate_rows(INITIAL_ROW_SIZE);
        if(spot == begin()) {
            push_front(ins);
            return spot;
        }
        if(((end_index & MOD_ROW_MASK) == 0) && (end_index >> DIV_ROW_SHIFT == row_count)) {
            //push empty T to allocate a new row
            push_back(T());
            --deque_size;
            --end_index;
            
        }
        else
            _a.construct(&*end(), T());

        copy_backward(spot , end(), ++end());
        
        *spot = ins;
        ++deque_size;
        ++end_index;
        assert(valid());
        return spot;
    }
    
    // ---
    // pop
    // ---
    
    /**
     * removes (destroys) the value at the back of the deque
     */
    void pop_back () {
        assert(!empty());
        if(begin_index != end_index) {
            _a.destroy(&*(--end()));
            --end_index;
            --deque_size;
        }
        assert(valid());
    }
    
    /**
     * removes (destroys) the value at the front of the deque
     */
    void pop_front () {
        assert(!empty());
        if(begin_index != end_index) {
            _a.destroy(&*begin());
            ++begin_index;
            --deque_size;
        }
        assert(valid());
    }
    
    // ----
    // push
    // ----
    
    /**
     * push a value onto the back side of this deque
     * @param val the value to add to the deque
     */
    void push_back (const_reference val) {
        if(!deque_root)
            allocate_rows(INITIAL_ROW_SIZE);
        if(((end_index & MOD_ROW_MASK) == 0) && (end_index >> DIV_ROW_SHIFT == row_count)) { //row full
            //add new row pointer
            T** new_pointers = _ap.allocate(row_count + 1);
            uninitialized_copy (_ap, deque_root, deque_root + row_count, new_pointers);
            
            //destroy old pointers
            _ap.deallocate(deque_root, row_count);
            
            //point to new
            deque_root = new_pointers;
            
            ++row_count;
            
            //allocate new row
            deque_root[row_count - 1] = _a.allocate(INITIAL_ROW_SIZE);
            
        }
        _a.construct(&deque_root[end_index >> DIV_ROW_SHIFT][end_index & MOD_ROW_MASK], val);
        ++end_index;
        ++deque_size;
        
        
        assert(valid());
    }
    
    /**
     * push a value onto the front side of this deque
     * @param val the value to add to the deque
     */
    void push_front (const_reference val) {
        if(!deque_root)
            allocate_rows(INITIAL_ROW_SIZE);
        if(begin_index == 0) { //add row
            //add new row pointer
            T** new_pointers = _ap.allocate(row_count + 1);
            uninitialized_copy (_ap, deque_root, deque_root + row_count, new_pointers + 1);
            
            //destroy old pointers
            _ap.deallocate(deque_root, row_count);
            
            //point to new
            deque_root = new_pointers;
            ++row_count;
            
            //allocate new row
            deque_root[0] = _a.allocate(INITIAL_ROW_SIZE);
            begin_index += INITIAL_ROW_SIZE;
            end_index += INITIAL_ROW_SIZE;
        }
        
        --begin_index;
        _a.construct(&deque_root[begin_index >> DIV_ROW_SHIFT][begin_index & MOD_ROW_MASK], val);
        ++deque_size;
        assert(valid());
    }
    
    // ------
    // resize
    // ------
    
    /**
     * resize this deque to a given amount
     * @param s the number of elements this deque should hold
     * @param v the value to fill any extra slots with
     */
    void resize (size_type s, const_reference v = value_type()) { //This function should be rewritten so push and pop depend on it
        if(s > deque_size) { //expand deque
            size_type diff = s - deque_size;
            for(size_type i = 0; i < diff; ++i)
                push_back(v);
        }
        else { //contract deque
            size_type diff = deque_size - s;
            for(size_type i = 0; i < diff; ++i)
                pop_back();
        }
        assert(valid());
    }
    
    // ----
    // size
    // ----
    
    /**
     * get the size of the deque, ie, how many elements
     * @returns the number of elements in this deque
     */
    size_type size () const {
        return deque_size;
    }
    
    // ----
    // swap
    // ----
    
    /**
     * swap this deque's values with another
     * @param other the other deque to be swapped with
     */
    void swap (my_deque& other) {
        if (_a == other._a && _ap == other._ap) {
            std::swap(deque_root, other.deque_root);
            std::swap(row_count, other.row_count);
            std::swap(deque_size, other.deque_size);
            std::swap(begin_index, other.begin_index);
            std::swap(end_index, other.end_index);
        }
        else {
            my_deque x = *this;
            *this = other;
            other  = x;
        }
        assert(valid());
    }
};

#endif // Deque_h
