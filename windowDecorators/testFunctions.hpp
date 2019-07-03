// ==========================================================================
//
// Author    : Stijn van Wijk
// File      : testFunctions.hpp
// Part of   : C++ hwlib windowdecorator library
// Copyright : stijn.vanwijk@student.hu.nl 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef TESTFUNCTIONS_HPP
#define TESTFUNCTIONS_HPP

#include "windowDecorator.hpp"
#include "../MAX7219-Library/MAX7219.hpp"

using hwlib::wait_ms;

void testMirrorX(window& w1, window& w2);

void testMirrorY(window& w1, window& w2);

void testDuplicate(window& w1, window& w2);

void testCombineWindowsHort(array<window*,2> arr);

void testCombineWindowsVert(array<window*,2> arr);

#endif // TESTFUNCTIONS_HPP