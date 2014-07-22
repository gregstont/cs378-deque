// ----------------------
// projects/deque/Deque.h
// Copyright (C) 2014
// Glenn P. Downing
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

#define DIV_ROW_SHIFT       4
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
        //cout << "destroy:" << endl;
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
// uninitialized_copy_backwards
// ------------------

template <typename A, typename II, typename BI>
BI uninitialized_copy_backwards (A& a, II b, II e, BI x) {
    using namespace std;
    BI p = x;
    try {
        while (b != e) {
            a.construct(&*x, *b);
            --b;
            --x;
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
         * <your documentation>
         */
        friend bool operator == (const my_deque& lhs, const my_deque& rhs) {
            // <your code>
            // you must use std::equal()
            return (lhs.size() == rhs.size()) && std::equal(lhs.begin(), lhs.end(), rhs.begin());
        }

        // ----------
        // operator <
        // ----------

        /**
         * <your documentation>
         */
        friend bool operator < (const my_deque& lhs, const my_deque& rhs) {
            // <your code>
            // you must use std::lexicographical_compare()
            return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
        }

    private:
        // ----
        // data
        // ----

        allocator_type _a;
        typename A::template rebind<T*>::other _ap;
        T** deque_root;
        size_t row_count;   //number of rows
        size_t deque_size;  //how many elements in here
        size_t begin_index; //where is the begining?
        size_t end_index;   //where is the end?

        // <your data>

    private:
        // -----
        // valid
        // -----

        bool valid () const {
            // <your code>
            return true;
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
                 * <your documentation>
                 */
                friend bool operator == (const iterator& lhs, const iterator& rhs) {
                    // <your code>
                    //using namespace std;
                    //cout << "in equal1!!" << endl;
                    return (lhs.owner == rhs.owner) && (lhs.index == rhs.index);
                }

                /**
                 * <your documentation>
                 */
                friend bool operator != (const iterator& lhs, const iterator& rhs) {
                    return !(lhs == rhs);
                }

                // ----------
                // operator +
                // ----------

                /**
                 * <your documentation>
                 */
                friend iterator operator + (iterator lhs, difference_type rhs) {
                    return lhs += rhs;
                }

                // ----------
                // operator -
                // ----------

                /**
                 * <your documentation>
                 */
                friend iterator operator - (iterator lhs, difference_type rhs) {
                    return lhs -= rhs;
                }

            private:
                // ----
                // data
                // ----

                // <your data>
                my_deque *owner;
                size_t index;

            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    // <your code>
                    return true;
                }

            public:
                // -----------
                // constructor
                // -----------
            
                /**
                 * <your documentation>
                 */
                iterator (my_deque *owner_, size_t index_) {
                    // <your code>
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
                 * <your documentation>
                 */
                reference operator * () const {
                    
                    return owner->deque_root[index >> DIV_ROW_SHIFT][index & MOD_ROW_MASK];
                }

                // -----------
                // operator ->
                // -----------

                /**
                 * <your documentation>
                 */
                pointer operator -> () const {
                    return &**this;
                }

                // -----------
                // operator ++
                // -----------

                /**
                 * <your documentation>
                 */
                iterator& operator ++ () {
                    // <your code>
                    ++index;
                    assert(valid());
                    return *this;
                }

                /**
                 * <your documentation>
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
                 * <your documentation>
                 */
                iterator& operator -- () {
                    // <your code>
                    --index;
                    assert(valid());
                    return *this;
                }

                /**
                 * <your documentation>
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
                 * <your documentation>
                 */
                iterator& operator += (difference_type d) {
                    // <your code>
                    index += d;
                    assert(valid());
                    return *this;
                }

                // -----------
                // operator -=
                // -----------

                /**
                 * <your documentation>
                 */
                iterator& operator -= (difference_type d) {
                    // <your code>
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
                 * <your documentation>
                 */
                friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) {
                    // <your code>
                    return (lhs.owner == rhs.owner) && (lhs.index == rhs.index);
                }

                /**
                 * <your documentation>
                 */
                friend bool operator != (const const_iterator& lhs, const const_iterator& rhs) {
                    return !(lhs == rhs);
                }

                // ----------
                // operator +
                // ----------

                /**
                 * <your documentation>
                 */
                friend const_iterator operator + (const_iterator lhs, difference_type rhs) {
                    return lhs += rhs;
                }

                // ----------
                // operator -
                // ----------

                /**
                 * <your documentation>
                 */
                friend const_iterator operator - (const_iterator lhs, difference_type rhs) {
                    return lhs -= rhs;
                }

            private:
                // ----
                // data
                // ----

                // <your data>
                const my_deque *owner;
                size_t index;

            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    // <your code>
                    return true;
                }
            

            public:
                // -----------
                // constructor
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator (const my_deque *owner_, const size_t index_) {
                    // <your code>
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
                 * <your documentation>
                 */
                reference operator * () const {
                    return owner->deque_root[index >> DIV_ROW_SHIFT][index & MOD_ROW_MASK];
                }

                // -----------
                // operator ->
                // -----------

                /**
                 * <your documentation>
                 */
                pointer operator -> () const {
                    return &**this;
                }

                // -----------
                // operator ++
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator& operator ++ () {
                    // <your code>
                    ++index;
                    assert(valid());
                    return *this;
                }

                /**
                 * <your documentation>
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
                 * <your documentation>
                 */
                const_iterator& operator -- () {
                    --index;
                    assert(valid());
                    return *this;
                }

                /**
                 * <your documentation>
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
                 * <your documentation>
                 */
                const_iterator& operator += (difference_type d) {
                    // <your code>
                    index += d;
                    assert(valid());
                    return *this;
                }

                // -----------
                // operator -=
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator& operator -= (difference_type d) {
                    // <your code>
                    index -= d;
                    assert(valid());
                    return *this;
                }
        };

    public:
    
        void print_deque() {
            using namespace std;
            cout << "Printing; size:" << deque_size << " rows:" << row_count << endl;
            for(size_t i = 0; i < row_count; ++i) {
                cout << "\tROW" << i << ": ";
                for(int j = 0; j < INITIAL_ROW_SIZE; ++j) {
                    //T temp = deque_root[i][j];
                    cout << deque_root[i][j] << "  ";
                }
                cout << endl;
            }
            cout << "Done printing" << endl;
        }
        // ------------
        // constructors
        // ------------
    
        void allocate_rows(size_type num_elements) {
            using namespace std;
            //cout << "allocate_rows:" << num_elements << endl;
            
            size_type rows_to_make = (num_elements + INITIAL_ROW_SIZE - 1) / INITIAL_ROW_SIZE;
            
            //cout << "allocate_rows:" << num_elements << " rows:" << rows_to_make << endl;
            T** pointers = _ap.allocate(rows_to_make);
            
            T* temp_p;
            uninitialized_fill (_ap, pointers, pointers + rows_to_make, temp_p );
            
            for(size_type i = 0; i < rows_to_make; ++i) {
                pointers[i] = _a.allocate(INITIAL_ROW_SIZE);
            }
            deque_root = pointers;
            row_count = rows_to_make;
        }
    

    
        /**
         * <your documentation>
         */
        explicit my_deque (const allocator_type& a = allocator_type()) :
            _a(a)
        {
            // <your code>
            using namespace std;
            
            
            T* the_first_row = _a.allocate(INITIAL_ROW_SIZE);

            T** pointers = _ap.allocate(1);
            T* temp_p;
            uninitialized_fill (_ap, pointers, pointers + 1, temp_p );
            
            row_count = 1;
            deque_size = 0;
            begin_index = INITIAL_ROW_SIZE >> 1;
            end_index = begin_index;
            
            (*pointers) = the_first_row;
            
            deque_root = pointers;
            
            
            //cout << "HEWERREREE" << endl;
            assert(valid());
        }

        /**
         * <your documentation>
         */
        explicit my_deque (size_type s, const_reference v = value_type(), const allocator_type& a = allocator_type()) :
            _a(a)
        {

            // <your code>
            
            using namespace std;
            
            size_type rows_to_make = (s + INITIAL_ROW_SIZE - 1) / INITIAL_ROW_SIZE;
            T** pointers = _ap.allocate(rows_to_make);
            
            T* temp_p;
            uninitialized_fill (_ap, pointers, pointers + rows_to_make, temp_p );
            
            for(size_type i = 0; i < rows_to_make; ++i) {
                pointers[i] = _a.allocate(INITIAL_ROW_SIZE);
                uninitialized_fill (_a, pointers[i], pointers[i] + INITIAL_ROW_SIZE, v);
            }

            row_count = rows_to_make;
            deque_size = s;
            begin_index = 0; //TODO: should this be somewhere different?
            end_index = s;
            
            
            deque_root = pointers;
    
            assert(valid());
        }

        /**
         * <your documentation>
         */
        my_deque (const my_deque& that) :
            _a(that._a)
        {
            using namespace std;

            allocate_rows(that.deque_size);
        
            deque_size = that.deque_size;
            begin_index = 0; //INITIAL_ROW_SIZE / 2; //TODO: should this be somewhere different?
            end_index = begin_index + deque_size;
            
            uninitialized_copy (_a, that.begin(), that.end(), begin());
            assert(valid());
        }

        // ----------
        // destructor
        // ----------

        /**
         * <your documentation>
         */
        ~my_deque () {
            // <your code>
            using namespace std;

            if(deque_root)
                clear();

            assert(valid());
        }

        // ----------
        // operator =
        // ----------

        /**
         * <your documentation>
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
         * <your documentation>
         */
        reference operator [] (size_type index) {
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            
            size_type temp = index + begin_index;
            return deque_root[temp >> DIV_ROW_SHIFT][temp & MOD_ROW_MASK];

        }

        /**
         * <your documentation>
         */
        const_reference operator [] (size_type index) const {
            return const_cast<my_deque*>(this)->operator[](index);
        }

        // --
        // at
        // --

        /**
         * <your documentation>
         */
        reference at (size_type index) {
            if(index >= deque_size)
                throw std::out_of_range("at index out of range");
            size_type temp = index + begin_index;
            return deque_root[temp >> DIV_ROW_SHIFT][temp & MOD_ROW_MASK];
        }

        /**
         * <your documentation>
         */
        const_reference at (size_type index) const {
            return const_cast<my_deque*>(this)->at(index);
        }

        // ----
        // back
        // ----

        /**
         * <your documentation>
         */
        reference back () {
            
            return deque_root[(end_index - 1) >> DIV_ROW_SHIFT][(end_index - 1) & MOD_ROW_MASK];
        }

        /**
         * <your documentation>
         */
        const_reference back () const {
            return const_cast<my_deque*>(this)->back();
        }

        // -----
        // begin
        // -----

        /**
         * <your documentation>
         */
        iterator begin () {

            return iterator(this, begin_index);
        }

        /**
         * <your documentation>
         */
        const_iterator begin () const {
            // <your code>
            return const_iterator(this, begin_index);
        }

        // -----
        // clear
        // -----

        /**
         * <your documentation>
         */
        void clear () {
            // <your code>
            using namespace std;

            if(deque_root)
                destroy(_a, begin(), end());

            for(size_t i = 0; i < row_count; ++i)
                _a.deallocate(deque_root[i], INITIAL_ROW_SIZE);
        
            destroy(_ap, deque_root, deque_root + row_count);
            _ap.deallocate(deque_root, row_count);
            
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
         * <your documentation>
         */
        bool empty () const {
            return !size();
        }

        // ---
        // end
        // ---

        /**
         * <your documentation>
         */
        iterator end () {
            return iterator(this, end_index);
        }

        /**
         * <your documentation>
         */
        const_iterator end () const {
            return const_iterator(this, end_index);
        }

        // -----
        // erase
        // -----

        /**
         * <your documentation>
         */
        iterator erase (iterator remove) {

            _a.destroy(&*remove);
            uninitialized_copy(_a, remove + 1, end(), remove);
            _a.destroy(&*(--end()));
            
            --deque_size;
            --end_index;
            assert(valid());
            return ++remove;
        }

        // -----
        // front
        // -----

        /**
         * <your documentation>
         */
        reference front () {

            return deque_root[begin_index >> DIV_ROW_SHIFT][begin_index & MOD_ROW_MASK];
        }

        /**
         * <your documentation>
         */
        const_reference front () const {
            return const_cast<my_deque*>(this)->front();}

        // ------
        // insert
        // ------

        /**
         * <your documentation>
         */
        iterator insert (iterator spot, const_reference ins) {

            if(((end_index & MOD_ROW_MASK) == 0) && (end_index >> DIV_ROW_SHIFT == row_count)) {
                push_back(T());
                --deque_size;
                --end_index;
                
            }
            uninitialized_copy_backwards(_a, --end(), spot - 1, end());
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
         * <your documentation>
         */
        void pop_back () {

            if(begin_index != end_index) {
                _a.destroy(&*(--end()));
                --end_index;
                --deque_size;
            }
            assert(valid());
        }

        /**
         * <your documentation>
         */
        void pop_front () {

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
         * <your documentation>
         */
        void push_back (const_reference val) {

            using namespace std;

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
         * <your documentation>
         */
        void push_front (const_reference val) {
            
            using namespace std;
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
         * <your documentation>
         */
        void resize (size_type s, const_reference v = value_type()) {
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
         * <your documentation>
         */
        size_type size () const {
            return deque_size;
        }

        // ----
        // swap
        // ----

        /**
         * <your documentation>
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
