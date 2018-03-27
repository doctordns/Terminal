/*++
Copyright (c) Microsoft Corporation

Module Name:
- OutputCell.hpp

Abstract:
- Representation of all data stored in a cell of the output buffer.
- RGB color supported.

Author:
- Austin Diviness (AustDi) 20-Mar-2018

--*/

#pragma once

#include "DbcsAttribute.hpp"
#include "TextAttribute.hpp"

class OutputCell final
{
public:
    OutputCell(_In_ const wchar_t charData,
               _In_ const DbcsAttribute dbcsAttribute,
               _In_ const TextAttribute textAttribute) noexcept;

    void swap(_Inout_ OutputCell& other) noexcept;

    CHAR_INFO ToCharInfo();

    wchar_t& GetCharData() noexcept;
    DbcsAttribute& GetDbcsAttribute() noexcept;
    TextAttribute& GetTextAttribute() noexcept;

    constexpr const wchar_t& GetCharData() const
    {
        return _charData;
    }

    constexpr const DbcsAttribute& GetDbcsAttribute() const
    {
        return _dbcsAttribute;
    }

    constexpr const TextAttribute& GetTextAttribute() const
    {
        return _textAttribute;
    }

private:
    wchar_t _charData;
    DbcsAttribute _dbcsAttribute;
    TextAttribute _textAttribute;
};