#ifndef OSRM_STRONG_TYPEDEF_HPP
#define OSRM_STRONG_TYPEDEF_HPP

// Based on:
// http://svn.boost.org/svn/boost/trunk/boost/serialization/strong_typedef.hpp
// But with explicit casts required for conversions
//
//
// Example usage:
//
//   OSRM_STRONG_TYPEDEF(int,Angle)
//   OSRM_STRONG_TYPEDEF(int,Distance)
//
//   Angle a(1);
//   Distance b(2);
//
//   a = b; // Compile error
//   std::cout << a << std::end; // Compile error
//   std::cout << int(a) << std::end;  // Works, explicit type conversion
//
// While this might seem annoying, the point is to make decisions about type
// conversion explicit.  We use lots of numbers in OSRM, it's easy to assign
// the wrong value to the wrong type.  Using OSRM_STRONG_TYPEDEF should
// help discourage re-use of typedefs in incompatible circumstances.

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif


/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// strong_typedef.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/serialization for updates, documentation, and revision history.

// macro used to implement a strong typedef.  strong typedef
// guarentees that two types are distinguised even though the
// share the same underlying implementation.  typedef does not create
// a new type.  OSRM_STRONG_TYPEDEF(T, D) creates a new type named D
// that operates as a type T.
//
// Based on BOOST_STRONG_TYPEDEF, but with `explicit` added to `operator T & ()`
// to ensure explicit casting is required for similar underlying types.

#include <boost/config.hpp>
#include <boost/operators.hpp>

#if !defined(__BORLANDC__) || __BORLANDC__ >= 0x590
    #define OSRM_STRONG_TYPEDEF(T, D)                               \
    struct D                                                        \
        : boost::totally_ordered1< D                                \
        , boost::totally_ordered2< D, T                             \
        > >                                                         \
    {                                                               \
        T val;                                                      \
        explicit D(const T t_) : val(t_) {};                        \
        D(): val() {};                                              \
        D(const D & t_) : val(t_.val){}                             \
        D & operator=(const D & rhs) { val = rhs.val; return *this;}  \
        D & operator=(const T & rhs) { val = rhs; return *this;}      \
        explicit operator const T & () const {return val; }         \
        explicit operator T & () { return val; }                    \
        bool operator==(const D & rhs) const { return val == rhs.val; } \
        bool operator<(const D & rhs) const { return val < rhs.val; }   \
    };
#else
    #define OSRM_STRONG_TYPEDEF(T, D)                               \
    struct D                                                        \
        : boost::totally_ordered1< D                                \
        , boost::totally_ordered2< D, T                             \
        > >                                                         \
    {                                                               \
        T val;                                                      \
        explicit D(const T t_) : val(t_) {};                        \
        D() : val(){};                                              \
        D(const D & t_) : val(t_.val){}                             \
        D & operator=(const D & rhs) { val = rhs.val; return *this;}  \
        D & operator=(const T & rhs) { val = rhs; return *this;}    \
        explicit operator const T & () const {return val; }           \
        explicit operator T & () { return val; }                      \
        bool operator==(const D & rhs) const { return val == rhs.val; } \
        bool operator<(const D & rhs) const { return val < rhs.val; }   \
    };
#endif // !defined(__BORLANDC) || __BORLANDC__ >= 0x590

#endif // OSRM_STRONG_TYPEDEF_HPP
