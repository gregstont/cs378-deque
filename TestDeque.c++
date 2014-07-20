// ----------------------------
// projects/deque/TestDeque.c++
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

/*
Google Test Libraries:
    % ls -al /usr/include/gtest/
    ...
    gtest.h
    ...

    % locate libgtest.a
    /usr/lib/libgtest.a

    % locate libpthread.a
    /usr/lib/x86_64-linux-gnu/libpthread.a
    /usr/lib32/libpthread.a

    % locate libgtest_main.a
    /usr/lib/libgtest_main.a

To compile the test:
    % g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Integer.c++ TestInteger.c++ -o TestInteger -lgtest -lgtest_main -lpthread

To run the test:
    % valgrind TestInteger

To obtain coverage of the test:
    % gcov-4.7 -b Integer.c++ TestInteger.c++
*/

// --------
// includes
// --------

#include <algorithm> // equal
#include <cstring>   // strcmp
#include <deque>     // deque
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>    // ==

#include "gtest/gtest.h"

#include "Deque.h"

#define ALL_OF_IT       typedef typename TestFixture::deque_type      deque_type; \
                        typedef typename TestFixture::allocator_type  allocator_type; \
                        typedef typename TestFixture::value_type      value_type; \
                        typedef typename TestFixture::size_type       size_type; \
                        typedef typename TestFixture::difference_type difference_type; \
                        typedef typename TestFixture::pointer         pointer; \
                        typedef typename TestFixture::const_pointer   const_pointer; \
                        typedef typename TestFixture::reference       reference; \
                        typedef typename TestFixture::const_reference const_reference;
// ---------
// TestDeque
// ---------

template <typename D>
struct TestDeque : testing::Test {
    // --------
    // typedefs
    // --------

    typedef          D                  deque_type;
    typedef typename D::allocator_type  allocator_type;
    typedef typename D::value_type      value_type;
    typedef typename D::size_type       size_type;
    typedef typename D::difference_type difference_type;
    typedef typename D::pointer         pointer;
    typedef typename D::const_pointer   const_pointer;
    typedef typename D::reference       reference;
    typedef typename D::const_reference const_reference;};

typedef testing::Types<
            std::deque<int>,
            std::deque<double>,
            my_deque<int>,
            my_deque<double> >
        my_types;

TYPED_TEST_CASE(TestDeque, my_types);

TYPED_TEST(TestDeque, Empty) {
    ALL_OF_IT

    deque_type x;
    const bool b = x.empty();
    ASSERT_TRUE(b);}

TYPED_TEST(TestDeque, Size) {
    ALL_OF_IT

    deque_type x;
    const size_type s = x.size();
    ASSERT_EQ(0, s);}

TYPED_TEST(TestDeque, push_back_1) {

    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    ASSERT_EQ(d[0], (value_type)7);
}

TYPED_TEST(TestDeque, push_back_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    //d.print_deque();
    d.push_back(7);
    d.push_back(6);
    d.push_back(5);
    d.push_back(4);
    d.push_back(3);
    d.push_back(2);
    d.push_back(1);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 6);
    ASSERT_EQ(d[2], 5);
    ASSERT_EQ(d[3], 4);
    ASSERT_EQ(d[4], 3);
    ASSERT_EQ(d[5], 2);
    ASSERT_EQ(d[6], 1);

}



TYPED_TEST(TestDeque, push_back_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    //pair<int,int> x = make_pair(3, 4);
    d.push_back(789);
    ASSERT_EQ(d[0], 789);
}

TYPED_TEST(TestDeque, push_front_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_front(7);
    ASSERT_EQ(d[0], 7);
}

TYPED_TEST(TestDeque, push_front_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    //d.print_deque();
    for(int i = 17; i > 0; --i)
        d.push_front(i);

    //d.print_deque();
    ASSERT_EQ(d[0], 1);
    ASSERT_EQ(d[1], 2);
    ASSERT_EQ(d[2], 3);
    ASSERT_EQ(d[3], 4);
    ASSERT_EQ(d[4], 5);
    ASSERT_EQ(d[5], 6);
    ASSERT_EQ(d[6], 7);
    ASSERT_EQ(d[7], 8);
    ASSERT_EQ(d[8], 9);
    ASSERT_EQ(d[9], 10);
    ASSERT_EQ(d[10], 11);
    ASSERT_EQ(d[11], 12);
    ASSERT_EQ(d[12], 13);
    ASSERT_EQ(d[13], 14);
    ASSERT_EQ(d[14], 15);
    ASSERT_EQ(d[15], 16);
    ASSERT_EQ(d[16], 17);
    
    
}

TYPED_TEST(TestDeque, push_front_4) {
    ALL_OF_IT
    using namespace std;
    my_deque< pair<int,int> > d;
    pair<int,int> x = make_pair(3, 4);
    d.push_front(x);
    ASSERT_EQ(d[0], make_pair(3, 4));
}

TYPED_TEST(TestDeque, pop_front_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(6);
    d.push_back(5);
    d.pop_front();
    ASSERT_EQ(d.size(), 2);
}

TYPED_TEST(TestDeque, pop_front_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(9);
    d.pop_front();
    ASSERT_EQ(d.size(), 0);
}

TYPED_TEST(TestDeque, pop_front_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_front(7);
    d.push_front(6);
    d.push_front(5);
    d.pop_front();
    ASSERT_EQ(d.size(), 2);
}
TYPED_TEST(TestDeque, pop_back_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(6);
    d.push_back(5);
    d.pop_back();
    ASSERT_EQ(d.size(), 2);
}

TYPED_TEST(TestDeque, pop_back_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_front(9);
    d.pop_back();
    ASSERT_EQ(d.size(), 0);
}

TYPED_TEST(TestDeque, pop_back_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_front(7);
    d.push_front(6);
    d.push_front(5);
    d.pop_back();
    ASSERT_EQ(d.size(), 2);
}

TYPED_TEST(TestDeque, front_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    //d.pop_back();
    //d.print_deque();
    int tt = d.front();
    ASSERT_EQ(tt, 1);
}

TYPED_TEST(TestDeque, front_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    //d.pop_back();
    //d.print_deque();

    ASSERT_EQ(d.front(), 3);
    d.pop_front();
    ASSERT_EQ(d.front(), 2);
}

TYPED_TEST(TestDeque, front_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    //d.pop_back();
    //d.print_deque();
    
    ASSERT_EQ(d.front(), 3);
    d.pop_front();
    ASSERT_EQ(d.front(), 2);
    d.push_front(9);
    ASSERT_EQ(d.front(), 9);
}
TYPED_TEST(TestDeque, const_front_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    const deque_type e(d);
    ASSERT_EQ(e.front(), 1);
}

TYPED_TEST(TestDeque, const_front_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    //d.pop_back();
    //d.print_deque();
    
    const deque_type e(d);
    
    ASSERT_EQ(e.front(), 3);
    //d.pop_front();
    //ASSERT_EQ(d.front(), 2);
}

TYPED_TEST(TestDeque, const_front_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    //d.pop_back();
    //d.print_deque();
    
    const deque_type e(d);
    
    ASSERT_EQ(d.front(), 3);
}



TYPED_TEST(TestDeque, back_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    ASSERT_EQ(d.back(), 3);
}

TYPED_TEST(TestDeque, back_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    ASSERT_EQ(d.back(), 3);
    d.pop_back();
    ASSERT_EQ(d.back(), 2);
}


TYPED_TEST(TestDeque, back_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    
    ASSERT_EQ(d.back(), 1);
    d.pop_back();
    ASSERT_EQ(d.back(), 2);
}

TYPED_TEST(TestDeque, at_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    
    ASSERT_EQ(d.at(0), 3);
    ASSERT_EQ(d.at(1), 2);
}

TYPED_TEST(TestDeque, at_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    ASSERT_EQ(d.at(0), 1);
    ASSERT_EQ(d.at(1), 2);
    
    try {
        d.at(3);
        ASSERT_TRUE(false);
    } catch (std::out_of_range) {
        ASSERT_TRUE(true);
    }
}

TYPED_TEST(TestDeque, at_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    ASSERT_EQ(d.at(0), 1);
    ASSERT_EQ(d.at(1), 2);
    ASSERT_EQ(d.at(2), 3);
    
    d.pop_back();
    d.push_back(5);
    ASSERT_EQ(d.at(2), 5);
    
}

TYPED_TEST(TestDeque, const_at_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    
    const deque_type e(d);
    
    ASSERT_EQ(e.at(0), 3);
    ASSERT_EQ(e.at(1), 2);
}

TYPED_TEST(TestDeque, const_at_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    ASSERT_EQ(d.at(0), 1);
    ASSERT_EQ(d.at(1), 2);
    
    const deque_type e(d);
    
    try {
        e.at(3);
        ASSERT_TRUE(false);
    } catch (std::out_of_range) {
        ASSERT_TRUE(true);
    }
}

TYPED_TEST(TestDeque, const_at_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    const deque_type e(d);
    
    ASSERT_EQ(e.at(0), 1);
    ASSERT_EQ(e.at(1), 2);
    ASSERT_EQ(e.at(2), 3);
    
}

////////////
/// []

TYPED_TEST(TestDeque, bracket_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    
    ASSERT_EQ(d[0], 3);
    ASSERT_EQ(d[1], 2);
}

TYPED_TEST(TestDeque, bracket_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    ASSERT_EQ(d[0], 1);
    ASSERT_EQ(d[1], 2);
    
    try {
        d[3];
        ASSERT_TRUE(true);
    } catch (std::exception) {
        ASSERT_TRUE(false);
    }
}

TYPED_TEST(TestDeque, bracket_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    ASSERT_EQ(d[0], 1);
    ASSERT_EQ(d[1], 2);
    ASSERT_EQ(d[2], 3);
    
    d.pop_back();
    d.push_back(5);
    ASSERT_EQ(d[2], 5);
    
}
TYPED_TEST(TestDeque, const_bracket_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    
    const deque_type e(d);
    
    ASSERT_EQ(e[0], 3);
    ASSERT_EQ(e[1], 2);
}

TYPED_TEST(TestDeque, const_bracket_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    const deque_type e(d);
    
    ASSERT_EQ(e[0], 1);
    ASSERT_EQ(e[1], 2);
    
    try {
        e[3];
        ASSERT_TRUE(true);
    } catch (std::exception) {
        ASSERT_TRUE(false);
    }
}

TYPED_TEST(TestDeque, const_bracket_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    d.pop_back();
    
    const deque_type e(d);
    
    ASSERT_EQ(e[0], 1);
    ASSERT_EQ(e[1], 2);
    //ASSERT_EQ(d[2], 3);
    
}


TYPED_TEST(TestDeque, begin_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    //my_deque<int>::iterator temp = d.begin();
    ASSERT_EQ(*d.begin(), 1);
    ASSERT_EQ(d[1], 2);
    ASSERT_EQ(d[1], 2);
}

TYPED_TEST(TestDeque, begin_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    //my_deque<int>::iterator temp = d.begin();
    ASSERT_EQ(*d.begin(), 1);
    ASSERT_EQ(d[1], 2);
    ASSERT_EQ(d[1], 2);
    
    d.pop_front();
    ASSERT_EQ(*d.begin(), 2);
}

TYPED_TEST(TestDeque, begin_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    //my_deque<int>::iterator temp = d.begin();
    ASSERT_EQ(*d.begin(), 1);
    ASSERT_EQ(d[1], 2);
    ASSERT_EQ(d[1], 2);
    
    d.pop_front();
    ASSERT_EQ(*d.begin(), 2);
    
    d.push_front(9);
    ASSERT_EQ(*d.begin(), 9);
}

TYPED_TEST(TestDeque, const_begin_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    const deque_type e(d);
    //my_deque<int>::iterator temp = e.begin();
    ASSERT_EQ(*e.begin(), 1);
    ASSERT_EQ(e[1], 2);
}
TYPED_TEST(TestDeque, const_begin_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    d.pop_front();
    
    const deque_type e(d);
    
    ASSERT_EQ(*e.begin(), 2);
    ASSERT_EQ(e[0], 2);
    
    d.pop_front();
    ASSERT_EQ(*e.begin(), 2);
}

TYPED_TEST(TestDeque, const_begin_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    const deque_type e(d);
    
    ASSERT_EQ(*e.begin(), 1);

}


TYPED_TEST(TestDeque, end_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    //my_deque<int>::iterator temp = d.begin();
    ASSERT_EQ(*(--d.end()), 3);
    ASSERT_EQ(d[1], 2);
    //ASSERT_EQ(d[1], 2);
}

TYPED_TEST(TestDeque, end_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(22);
    
    //my_deque<int>::iterator temp = d.begin();
    ASSERT_EQ(*d.begin(), 22);
    ASSERT_EQ(*(--d.end()), 22);
    ASSERT_EQ(d[0], 22);
    //ASSERT_EQ(d[1], 2);
}
TYPED_TEST(TestDeque, end_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(22);
    
    //my_deque<int>::iterator temp = d.begin();
    ASSERT_EQ(*d.begin(), 22);
    ASSERT_EQ(*(--d.end()), 22);
    ASSERT_EQ(d[0], 22);
    d.push_back(9);
    ASSERT_EQ(*(--d.end()), 9);
    ASSERT_EQ(*d.begin(), 22);
    //ASSERT_EQ(d[1], 2);
}

TYPED_TEST(TestDeque, const_end_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    const deque_type e(d);
    
    //my_deque<int>::iterator temp = d.begin();
    ASSERT_EQ(*(--e.end()), 3);
    ASSERT_EQ(e[1], 2);
    //ASSERT_EQ(d[1], 2);
}
TYPED_TEST(TestDeque, const_end_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(22);
    
    const deque_type e(d);
    
    //my_deque<int>::iterator temp = d.begin();
    ASSERT_EQ(*e.begin(), 22);
    ASSERT_EQ(*(--e.end()), 22);
    ASSERT_EQ(e[0], 22);
    //ASSERT_EQ(d[1], 2);
}
TYPED_TEST(TestDeque, const_end_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(-1);
    
    const deque_type e(d);
    
    //my_deque<int>::iterator temp = d.begin();
    ASSERT_EQ(*e.begin(), -1);
    ASSERT_EQ(*(--e.end()), -1);
    ASSERT_EQ(e[0], -1);
}


TYPED_TEST(TestDeque, constructor_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    //d.push_back(7);
    ASSERT_EQ(d.size(), 0);
}

TYPED_TEST(TestDeque, constructor_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    ASSERT_EQ(d.size(), 1);
    ASSERT_EQ(d[0], 7);
}

TYPED_TEST(TestDeque, constructor_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_front(7);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
}


TYPED_TEST(TestDeque, constructor_size_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d(20,6);
    d.push_back(7);
    ASSERT_EQ(d.size(), 21);
    ASSERT_EQ(d[0], 6);
    //d.print_deque();
}

TYPED_TEST(TestDeque, constructor_size_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d(1);
    d.push_back(7);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 0);
    ASSERT_EQ(d[1], 7);
    //d.print_deque();
}

TYPED_TEST(TestDeque, constructor_size_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d(45,9);
    d.push_back(7);
    ASSERT_EQ(d.size(), 46);
    ASSERT_EQ(d[0], 9);
    ASSERT_EQ(d[45], 7);
    //d.print_deque();
}


TYPED_TEST(TestDeque, constructor_that_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
    deque_type e(d);
    
    e.push_back(8);
    
    ASSERT_EQ(e.size(), 3);
    ASSERT_EQ(e[0], 7);
    ASSERT_EQ(e[1], 9);
    ASSERT_EQ(e[2], 8);
    
    //d.print_deque();
}

TYPED_TEST(TestDeque, constructor_that_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
    deque_type e(d);
    d.push_back(6);
    
    e.push_back(8);
    
    ASSERT_EQ(e.size(), 3);
    ASSERT_EQ(e[0], 7);
    ASSERT_EQ(e[1], 9);
    ASSERT_EQ(e[2], 8);
    
    //d.print_deque();
}

TYPED_TEST(TestDeque, constructor_that_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
    deque_type e(d);
    d.push_back(6);
    
    e.push_back(10);
    
    ASSERT_EQ(e.size(), 3);
    ASSERT_EQ(e[0], 7);
    ASSERT_EQ(e[1], 9);
    ASSERT_EQ(e[2], 10);
    
    //d.print_deque();
}

TYPED_TEST(TestDeque, assignment_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
    deque_type e = d;
    d.push_back(6);
    
    e.push_back(10);
    
    ASSERT_EQ(e.size(), 3);
    ASSERT_EQ(e[0], 7);
    ASSERT_EQ(e[1], 9);
    ASSERT_EQ(e[2], 10);
    
    //d.print_deque();
}

TYPED_TEST(TestDeque, assignment_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
    deque_type e = d;
    
    e.push_back(8);
    
    ASSERT_EQ(e.size(), 3);
    ASSERT_EQ(e[0], 7);
    ASSERT_EQ(e[1], 9);
    ASSERT_EQ(e[2], 8);
    
    //d.print_deque();
}

TYPED_TEST(TestDeque, assignment_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
    deque_type e = d;
    d.push_back(6);
    
    e.push_back(8);
    
    ASSERT_EQ(e.size(), 3);
    ASSERT_EQ(e[0], 7);
    ASSERT_EQ(e[1], 9);
    ASSERT_EQ(e[2], 8);
    
    //d.print_deque();
}

TYPED_TEST(TestDeque, swap_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
    deque_type e;
    e.push_back(6);
    e.push_back(8);
    
    ASSERT_EQ(e.size(), 2);
    ASSERT_EQ(e[0], 6);
    ASSERT_EQ(e[1], 8);
    
    e.swap(d);
    
    ASSERT_EQ(e[0], 7);
    ASSERT_EQ(e[1], 9);
    ASSERT_EQ(d[0], 6);
    ASSERT_EQ(d[1], 8);
    
    //d.print_deque();
}

TYPED_TEST(TestDeque, swap_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    d.push_back(11);
    ASSERT_EQ(d.size(), 3);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    ASSERT_EQ(d[2], 11);
    
    deque_type e;
    e.push_back(6);
    e.push_back(8);
    
    ASSERT_EQ(e.size(), 2);
    ASSERT_EQ(e[0], 6);
    ASSERT_EQ(e[1], 8);
    
    e.swap(d);
    
    ASSERT_EQ(e.size(), 3);
    ASSERT_EQ(e[0], 7);
    ASSERT_EQ(e[1], 9);
    ASSERT_EQ(e[2], 11);
    
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 6);
    ASSERT_EQ(d[1], 8);
    
    //d.print_deque();
}

TYPED_TEST(TestDeque, swap_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(1);
    d.push_back(2);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 1);
    ASSERT_EQ(d[1], 2);
    
    deque_type e;
    e.push_back(6);
    e.push_back(8);
    
    ASSERT_EQ(e.size(), 2);
    ASSERT_EQ(e[0], 6);
    ASSERT_EQ(e[1], 8);
    
    e.swap(d);
    
    ASSERT_EQ(e[0], 1);
    ASSERT_EQ(e[1], 2);
    ASSERT_EQ(d[0], 6);
    ASSERT_EQ(d[1], 8);
    
    //d.print_deque();
}

TYPED_TEST(TestDeque, size_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
}

TYPED_TEST(TestDeque, size_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    d.pop_front();
    ASSERT_EQ(d.size(), 1);
}

TYPED_TEST(TestDeque, size_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    d.push_back(9);
    ASSERT_EQ(d.size(), 3);
}

TYPED_TEST(TestDeque, resize_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
    d.resize(5,4);
    ASSERT_EQ(d.size(), 5);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    ASSERT_EQ(d[2], 4);
    ASSERT_EQ(d[3], 4);
    ASSERT_EQ(d[4], 4);
    
}

TYPED_TEST(TestDeque, resize_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
    d.resize(15,4);
    ASSERT_EQ(d.size(), 15);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    ASSERT_EQ(d[2], 4);
    ASSERT_EQ(d[3], 4);
    ASSERT_EQ(d[4], 4);
    ASSERT_EQ(d[14], 4);
    
}

TYPED_TEST(TestDeque, resize_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    d.push_back(11);
    d.push_back(13);
    ASSERT_EQ(d.size(), 4);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
    d.resize(2,4);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
}

TYPED_TEST(TestDeque, clear_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
    d.clear();
    ASSERT_EQ(d.size(), 0);
    
}

TYPED_TEST(TestDeque, clear_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
    d.clear();
    ASSERT_EQ(d.size(), 0);
    d.push_back(5);
    ASSERT_EQ(d.size(), 1);
    ASSERT_EQ(d[0], 5);
    
}

TYPED_TEST(TestDeque, clear_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
    d.clear();
    ASSERT_EQ(d.size(), 0);
    d.push_back(5);
    ASSERT_EQ(d.size(), 1);
    ASSERT_EQ(d[0], 5);
    d.clear();
    ASSERT_EQ(d.size(), 0);
    
}

TYPED_TEST(TestDeque, erase_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
    d.erase(d.begin());
    ASSERT_EQ(d.size(), 1);
    ASSERT_EQ(d[0], 9);
    
}

TYPED_TEST(TestDeque, erase_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    d.push_back(11);
    ASSERT_EQ(d.size(), 3);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    ASSERT_EQ(d[2], 11);
    
    d.erase(d.begin());
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 9);
    ASSERT_EQ(d[1], 11);
    
}

TYPED_TEST(TestDeque, erase_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    d.push_back(11);
    ASSERT_EQ(d.size(), 3);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    ASSERT_EQ(d[2], 11);
    
    d.erase(d.begin());
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 9);
    ASSERT_EQ(d[1], 11);
    
    d.erase(d.begin());
    ASSERT_EQ(d.size(), 1);
    ASSERT_EQ(d[0], 11);
    
}

TYPED_TEST(TestDeque, insert_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
    d.insert(d.begin(), 77);
    ASSERT_EQ(d.size(), 3);
    ASSERT_EQ(d[0], 77);
    ASSERT_EQ(d[1], 7);
    ASSERT_EQ(d[2], 9);
    
}

TYPED_TEST(TestDeque, insert_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    d.push_back(10);
    d.push_back(11);
    d.push_back(12);
    ASSERT_EQ(d.size(), 5);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
    d.insert(d.begin(), 77);
    ASSERT_EQ(d.size(), 6);
    ASSERT_EQ(d[0], 77);
    ASSERT_EQ(d[1], 7);
    ASSERT_EQ(d[2], 9);
    
}

TYPED_TEST(TestDeque, insert_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    

    d.insert(++d.begin(), 77);

    ASSERT_EQ(d.size(), 3);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 77);
    ASSERT_EQ(d[2], 9);
    
}

TYPED_TEST(TestDeque, equals_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    

    deque_type e;
    e.push_back(7);
    e.push_back(9);
    ASSERT_EQ(e.size(), 2);
    ASSERT_EQ(e, d);
}

TYPED_TEST(TestDeque, equals_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
    deque_type e;
    e.push_front(9);
    e.push_front(7);
    e.push_front(6);
    e.pop_front();
    ASSERT_EQ(e.size(), 2);
    ASSERT_EQ(e, d);
}

TYPED_TEST(TestDeque, equals_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
    deque_type e;
    e.push_front(9);
    e.push_front(7);
    e.push_front(6);
    ASSERT_EQ(e.size(), 3);
    ASSERT_EQ(e == d, false);
}

TYPED_TEST(TestDeque, compare_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
    deque_type e;
    e.push_back(6);
    e.push_back(9);
    ASSERT_EQ(e.size(), 2);
    ASSERT_TRUE(e < d);
}

TYPED_TEST(TestDeque, compare_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
    deque_type e;
    e.push_back(6);
    e.push_back(9);
    ASSERT_EQ(e.size(), 2);
    ASSERT_FALSE(d < e);
}

TYPED_TEST(TestDeque, compare_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(6);
    d.push_back(9);
    d.push_back(1);
    ASSERT_EQ(d.size(), 3);
    ASSERT_EQ(d[0], 6);
    ASSERT_EQ(d[1], 9);
    
    deque_type e;
    e.push_back(6);
    e.push_back(9);
    ASSERT_EQ(e.size(), 2);
    ASSERT_TRUE(e < d);
}

TYPED_TEST(TestDeque, empty_1) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    d.push_back(6);
    d.push_back(9);
    d.push_back(1);
    ASSERT_FALSE(d.empty());
    ASSERT_EQ(d[0], 6);
    ASSERT_EQ(d[1], 9);

}
TYPED_TEST(TestDeque, empty_2) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    ASSERT_TRUE(d.empty());
    d.push_back(6);
    d.push_back(9);
    d.push_back(1);
    ASSERT_FALSE(d.empty());
    ASSERT_EQ(d[0], 6);
    ASSERT_EQ(d[1], 9);
    
}
TYPED_TEST(TestDeque, empty_3) {
    ALL_OF_IT
    using namespace std;
    deque_type d;
    ASSERT_TRUE(d.empty());
    d.push_back(6);
    d.push_back(9);
    d.push_back(1);
    ASSERT_FALSE(d.empty());
    ASSERT_EQ(d[0], 6);
    ASSERT_EQ(d[1], 9);
    d.clear();
    ASSERT_TRUE(d.empty());
}

TYPED_TEST(TestDeque, destruct_1) {
    ALL_OF_IT
    using namespace std;
    {
    deque_type d;
    d.push_back(6);
    d.push_back(9);
    d.push_back(1);
    ASSERT_FALSE(d.empty());
    ASSERT_EQ(d[0], 6);
    ASSERT_EQ(d[1], 9);
    }
    ASSERT_TRUE(true);
}

TYPED_TEST(TestDeque, destruct_2) {
    ALL_OF_IT
    using namespace std;
    {
    deque_type d;
    }
    ASSERT_TRUE(true);
}
TYPED_TEST(TestDeque, destruct_3) {
    ALL_OF_IT
    using namespace std;
    {
        deque_type d;
        const deque_type e;
    }
    ASSERT_TRUE(true);
}


////////////////////////////////////////////////////////////////////////////
//////      iterator tests
////////////////////////////////////////////////////////////////////////////
/**
TYPED_TEST(TestDeque, reference_write_1) {
    ALL_OF_IT
    using namespace std;
    my_deque<int> d(45);
    d.push_back(7);
    //my_deque<int>::iterator ttt = d.begin();
    *d.begin() = 8;
    
    ASSERT_EQ(d.size(), 1);
    ASSERT_EQ(d[0], 8);
    //d.print_deque();
}
*/




















































