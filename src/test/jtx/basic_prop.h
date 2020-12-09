//------------------------------------------------------------------------------
/*
    This file is part of divvyd: https://github.com/xdv/divvyd
    Copyright (c) 2012, 2013 Divvy Labs Inc.

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#ifndef DIVVY_TEST_JTX_BASIC_PROP_H_INCLUDED
#define DIVVY_TEST_JTX_BASIC_PROP_H_INCLUDED

namespace divvy {
namespace test {
namespace jtx {

struct basic_prop
{
    virtual ~basic_prop() = default;
    virtual std::unique_ptr<
        basic_prop> clone() const = 0;
    virtual bool assignable(
        basic_prop const*) const = 0;
};

template <class T>
struct prop_type : basic_prop
{
    T t;

    template <class... Args>
    prop_type(Args&&... args)
        : t(std::forward <Args>(args)...)
    {
    }

    std::unique_ptr<
        basic_prop> clone() const override
    {
        return std::make_unique<
            prop_type<T>>(t);
    }

    bool assignable(
        basic_prop const* src) const override
    {
        return dynamic_cast<
            prop_type<T> const*>(
                src);
    }
};

} // jtx
} // test
} // divvy

#endif
