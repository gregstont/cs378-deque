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
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::size_type       size_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;
    typedef typename TestFixture::const_pointer   const_pointer;
    typedef typename TestFixture::reference       reference;
    typedef typename TestFixture::const_reference const_reference;

    deque_type x;
    const bool b = x.empty();
    ASSERT_TRUE(b);}

TYPED_TEST(TestDeque, Size) {
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::size_type       size_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;
    typedef typename TestFixture::const_pointer   const_pointer;
    typedef typename TestFixture::reference       reference;
    typedef typename TestFixture::const_reference const_reference;

    deque_type x;
    const size_type s = x.size();
    ASSERT_EQ(0, s);}

TEST(TestDeque, push_back_1) {
    using namespace std;
    my_deque<int> d;
    d.push_back(7);
    ASSERT_EQ(d[0], 7);
}

TEST(TestDeque, push_back_2) {
    using namespace std;
    my_deque<int> d;
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
    
    //d.print_deque();
    //cout << "fff" << d[1] << endl;
    /*const int a[] = {2, 3, 4};
    const int b[] = {2, 3, 4};
    int x[10];
    const int* p = shift_right_digits(a, a + 3, 0, x);
    ASSERT_EQ(3, p - x);
    ASSERT_TRUE(std::equal(const_cast<const int*>(x), p, b));*/
}



TEST(TestDeque, push_back_3) {
    using namespace std;
    my_deque< pair<int,int> > d;
    pair<int,int> x = make_pair(3, 4);
    d.push_back(x);
    ASSERT_EQ(d[0], make_pair(3, 4));
}

TEST(TestDeque, push_front_1) {
    using namespace std;
    my_deque<int> d;
    d.push_front(7);
    ASSERT_EQ(d[0], 7);
}

TEST(TestDeque, push_front_2) {
    using namespace std;
    my_deque<int> d;
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

TEST(TestDeque, push_front_4) {
    using namespace std;
    my_deque< pair<int,int> > d;
    pair<int,int> x = make_pair(3, 4);
    d.push_front(x);
    ASSERT_EQ(d[0], make_pair(3, 4));
}

TEST(TestDeque, pop_front_1) {
    using namespace std;
    my_deque<int> d;
    d.push_back(7);
    d.push_back(6);
    d.push_back(5);
    d.pop_front();
    ASSERT_EQ(d.size(), 2);
}

TEST(TestDeque, pop_front_2) {
    using namespace std;
    my_deque<int> d;
    d.pop_front();
    ASSERT_EQ(d.size(), 0);
}

TEST(TestDeque, pop_front_3) {
    using namespace std;
    my_deque<int> d;
    d.push_front(7);
    d.push_front(6);
    d.push_front(5);
    d.pop_front();
    ASSERT_EQ(d.size(), 2);
}
TEST(TestDeque, pop_back_1) {
    using namespace std;
    my_deque<int> d;
    d.push_back(7);
    d.push_back(6);
    d.push_back(5);
    d.pop_back();
    ASSERT_EQ(d.size(), 2);
}

TEST(TestDeque, pop_back_2) {
    using namespace std;
    my_deque<int> d;
    d.pop_back();
    ASSERT_EQ(d.size(), 0);
}

TEST(TestDeque, pop_back_3) {
    using namespace std;
    my_deque<int> d;
    d.push_front(7);
    d.push_front(6);
    d.push_front(5);
    d.pop_back();
    ASSERT_EQ(d.size(), 2);
}

TEST(TestDeque, front_1) {
    using namespace std;
    my_deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    //d.pop_back();
    //d.print_deque();
    int tt = d.front();
    ASSERT_EQ(tt, 1);
}

TEST(TestDeque, front_2) {
    using namespace std;
    my_deque<int> d;
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    //d.pop_back();
    //d.print_deque();

    ASSERT_EQ(d.front(), 3);
    d.pop_front();
    ASSERT_EQ(d.front(), 2);
}

TEST(TestDeque, front_3) {
    using namespace std;
    my_deque<int> d;
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
TEST(TestDeque, const_front_1) {
    using namespace std;
    my_deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    const my_deque<int> e(d);
    ASSERT_EQ(e.front(), 1);
}

TEST(TestDeque, const_front_2) {
    using namespace std;
    my_deque<int> d;
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    //d.pop_back();
    //d.print_deque();
    
    const my_deque<int> e(d);
    
    ASSERT_EQ(e.front(), 3);
    //d.pop_front();
    //ASSERT_EQ(d.front(), 2);
}

TEST(TestDeque, const_front_3) {
    using namespace std;
    my_deque<int> d;
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    //d.pop_back();
    //d.print_deque();
    
    const my_deque<int> e(d);
    
    ASSERT_EQ(d.front(), 3);
}



TEST(TestDeque, back_1) {
    using namespace std;
    my_deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    ASSERT_EQ(d.back(), 3);
}

TEST(TestDeque, back_2) {
    using namespace std;
    my_deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    ASSERT_EQ(d.back(), 3);
    d.pop_back();
    ASSERT_EQ(d.back(), 2);
}


TEST(TestDeque, back_3) {
    using namespace std;
    my_deque<int> d;
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    
    ASSERT_EQ(d.back(), 1);
    d.pop_back();
    ASSERT_EQ(d.back(), 2);
}

TEST(TestDeque, at_1) {
    using namespace std;
    my_deque<int> d;
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    
    ASSERT_EQ(d.at(0), 3);
    ASSERT_EQ(d.at(1), 2);
}

TEST(TestDeque, at_2) {
    using namespace std;
    my_deque<int> d;
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

TEST(TestDeque, at_3) {
    using namespace std;
    my_deque<int> d;
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

TEST(TestDeque, const_at_1) {
    using namespace std;
    my_deque<int> d;
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    
    const my_deque<int> e(d);
    
    ASSERT_EQ(e.at(0), 3);
    ASSERT_EQ(e.at(1), 2);
}

TEST(TestDeque, const_at_2) {
    using namespace std;
    my_deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    ASSERT_EQ(d.at(0), 1);
    ASSERT_EQ(d.at(1), 2);
    
    const my_deque<int> e(d);
    
    try {
        e.at(3);
        ASSERT_TRUE(false);
    } catch (std::out_of_range) {
        ASSERT_TRUE(true);
    }
}

TEST(TestDeque, const_at_3) {
    using namespace std;
    my_deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    const my_deque<int> e(d);
    
    ASSERT_EQ(e.at(0), 1);
    ASSERT_EQ(e.at(1), 2);
    ASSERT_EQ(e.at(2), 3);
    
}

////////////
/// []

TEST(TestDeque, bracket_1) {
    using namespace std;
    my_deque<int> d;
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    
    ASSERT_EQ(d[0], 3);
    ASSERT_EQ(d[1], 2);
}

TEST(TestDeque, bracket_2) {
    using namespace std;
    my_deque<int> d;
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

TEST(TestDeque, bracket_3) {
    using namespace std;
    my_deque<int> d;
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
TEST(TestDeque, const_bracket_1) {
    using namespace std;
    my_deque<int> d;
    d.push_front(1);
    d.push_front(2);
    d.push_front(3);
    
    const my_deque<int> e(d);
    
    ASSERT_EQ(e[0], 3);
    ASSERT_EQ(e[1], 2);
}

TEST(TestDeque, const_bracket_2) {
    using namespace std;
    my_deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    const my_deque<int> e(d);
    
    ASSERT_EQ(e[0], 1);
    ASSERT_EQ(e[1], 2);
    
    try {
        e[3];
        ASSERT_TRUE(true);
    } catch (std::exception) {
        ASSERT_TRUE(false);
    }
}

TEST(TestDeque, const_bracket_3) {
    using namespace std;
    my_deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    d.pop_back();
    
    const my_deque<int> e(d);
    
    ASSERT_EQ(e[0], 1);
    ASSERT_EQ(e[1], 2);
    //ASSERT_EQ(d[2], 3);
    
}


TEST(TestDeque, begin_1) {
    using namespace std;
    my_deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    my_deque<int>::iterator temp = d.begin();
    ASSERT_EQ(*temp, 1);
    ASSERT_EQ(d[1], 2);
    ASSERT_EQ(d[1], 2);
}

TEST(TestDeque, begin_2) {
    using namespace std;
    my_deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    my_deque<int>::iterator temp = d.begin();
    ASSERT_EQ(*temp, 1);
    ASSERT_EQ(d[1], 2);
    ASSERT_EQ(d[1], 2);
    
    d.pop_front();
    ASSERT_EQ(*d.begin(), 2);
}

TEST(TestDeque, begin_3) {
    using namespace std;
    my_deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    my_deque<int>::iterator temp = d.begin();
    ASSERT_EQ(*temp, 1);
    ASSERT_EQ(d[1], 2);
    ASSERT_EQ(d[1], 2);
    
    d.pop_front();
    ASSERT_EQ(*d.begin(), 2);
    
    d.push_front(9);
    ASSERT_EQ(*d.begin(), 9);
}

TEST(TestDeque, const_begin_1) {
    using namespace std;
    my_deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    const my_deque<int> e(d);
    //my_deque<int>::iterator temp = e.begin();
    ASSERT_EQ(*e.begin(), 1);
    ASSERT_EQ(e[1], 2);
}
TEST(TestDeque, const_begin_2) {
    using namespace std;
    my_deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    d.pop_front();
    
    const my_deque<int> e(d);
    
    ASSERT_EQ(*e.begin(), 2);
    ASSERT_EQ(e[0], 2);
    
    d.pop_front();
    ASSERT_EQ(*e.begin(), 2);
}

TEST(TestDeque, const_begin_3) {
    using namespace std;
    my_deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    const my_deque<int> e(d);
    
    ASSERT_EQ(*e.begin(), 1);

}


TEST(TestDeque, end_1) {
    using namespace std;
    my_deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    //my_deque<int>::iterator temp = d.begin();
    ASSERT_EQ(*(--d.end()), 3);
    ASSERT_EQ(d[1], 2);
    //ASSERT_EQ(d[1], 2);
}

TEST(TestDeque, end_2) {
    using namespace std;
    my_deque<int> d;
    d.push_back(22);
    
    //my_deque<int>::iterator temp = d.begin();
    ASSERT_EQ(*d.begin(), 22);
    ASSERT_EQ(*(--d.end()), 22);
    ASSERT_EQ(d[0], 22);
    //ASSERT_EQ(d[1], 2);
}
TEST(TestDeque, end_3) {
    using namespace std;
    my_deque<int> d;
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

TEST(TestDeque, const_end_1) {
    using namespace std;
    my_deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    
    const my_deque<int> e(d);
    
    //my_deque<int>::iterator temp = d.begin();
    ASSERT_EQ(*(--e.end()), 3);
    ASSERT_EQ(e[1], 2);
    //ASSERT_EQ(d[1], 2);
}
TEST(TestDeque, const_end_2) {
    using namespace std;
    my_deque<int> d;
    d.push_back(22);
    
    const my_deque<int> e(d);
    
    //my_deque<int>::iterator temp = d.begin();
    ASSERT_EQ(*e.begin(), 22);
    ASSERT_EQ(*(--e.end()), 22);
    ASSERT_EQ(e[0], 22);
    //ASSERT_EQ(d[1], 2);
}
TEST(TestDeque, const_end_3) {
    using namespace std;
    my_deque<int> d;
    d.push_back(-1);
    
    const my_deque<int> e(d);
    
    //my_deque<int>::iterator temp = d.begin();
    ASSERT_EQ(*e.begin(), -1);
    ASSERT_EQ(*(--e.end()), -1);
    ASSERT_EQ(e[0], -1);
}


TEST(TestDeque, constructor_1) {
    using namespace std;
    my_deque<int> d;
    //d.push_back(7);
    ASSERT_EQ(d.size(), 0);
}

TEST(TestDeque, constructor_2) {
    using namespace std;
    my_deque<int> d;
    d.push_back(7);
    ASSERT_EQ(d.size(), 1);
    ASSERT_EQ(d[0], 7);
}

TEST(TestDeque, constructor_3) {
    using namespace std;
    my_deque<int> d;
    d.push_back(7);
    d.push_front(7);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
}


TEST(TestDeque, constructor_size_1) {
    using namespace std;
    my_deque<int> d(20);
    d.push_back(7);
    ASSERT_EQ(d.size(), 1);
    ASSERT_EQ(d[0], 7);
    //d.print_deque();
}

TEST(TestDeque, constructor_size_2) {
    using namespace std;
    my_deque<int> d(1);
    d.push_back(7);
    ASSERT_EQ(d.size(), 1);
    ASSERT_EQ(d[0], 7);
    //d.print_deque();
}

TEST(TestDeque, constructor_size_3) {
    using namespace std;
    my_deque<int> d(45);
    d.push_back(7);
    ASSERT_EQ(d.size(), 1);
    ASSERT_EQ(d[0], 7);
    //d.print_deque();
}


TEST(TestDeque, constructor_that_1) {
    using namespace std;
    my_deque<int> d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
    my_deque<int> e(d);
    
    e.push_back(8);
    
    ASSERT_EQ(e.size(), 3);
    ASSERT_EQ(e[0], 7);
    ASSERT_EQ(e[1], 9);
    ASSERT_EQ(e[2], 8);
    
    //d.print_deque();
}

TEST(TestDeque, constructor_that_2) {
    using namespace std;
    my_deque<int> d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
    my_deque<int> e(d);
    d.push_back(6);
    
    e.push_back(8);
    
    ASSERT_EQ(e.size(), 3);
    ASSERT_EQ(e[0], 7);
    ASSERT_EQ(e[1], 9);
    ASSERT_EQ(e[2], 8);
    
    //d.print_deque();
}

TEST(TestDeque, constructor_that_3) {
    using namespace std;
    my_deque<int> d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
    my_deque<int> e(d);
    d.push_back(6);
    
    e.push_back(10);
    
    ASSERT_EQ(e.size(), 3);
    ASSERT_EQ(e[0], 7);
    ASSERT_EQ(e[1], 9);
    ASSERT_EQ(e[2], 10);
    
    //d.print_deque();
}

TEST(TestDeque, assignment_1) {
    using namespace std;
    my_deque<int> d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
    my_deque<int> e = d;
    d.push_back(6);
    
    e.push_back(10);
    
    ASSERT_EQ(e.size(), 3);
    ASSERT_EQ(e[0], 7);
    ASSERT_EQ(e[1], 9);
    ASSERT_EQ(e[2], 10);
    
    //d.print_deque();
}

TEST(TestDeque, assignment_2) {
    using namespace std;
    my_deque<int> d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
    my_deque<int> e = d;
    
    e.push_back(8);
    
    ASSERT_EQ(e.size(), 3);
    ASSERT_EQ(e[0], 7);
    ASSERT_EQ(e[1], 9);
    ASSERT_EQ(e[2], 8);
    
    //d.print_deque();
}

TEST(TestDeque, assignment_3) {
    using namespace std;
    my_deque<int> d;
    d.push_back(7);
    d.push_back(9);
    ASSERT_EQ(d.size(), 2);
    ASSERT_EQ(d[0], 7);
    ASSERT_EQ(d[1], 9);
    
    my_deque<int> e = d;
    d.push_back(6);
    
    e.push_back(8);
    
    ASSERT_EQ(e.size(), 3);
    ASSERT_EQ(e[0], 7);
    ASSERT_EQ(e[1], 9);
    ASSERT_EQ(e[2], 8);
    
    //d.print_deque();
}



TEST(TestDeque, reference_write_1) {
    using namespace std;
    my_deque<int> d(45);
    d.push_back(7);
    //my_deque<int>::iterator ttt = d.begin();
    *d.begin() = 8;
    
    ASSERT_EQ(d.size(), 1);
    ASSERT_EQ(d[0], 8);
    //d.print_deque();
}





















































