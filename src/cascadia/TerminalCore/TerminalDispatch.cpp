/********************************************************
 *                                                       *
 *   Copyright (C) Microsoft. All rights reserved.       *
 *                                                       *
 ********************************************************/

#include "pch.h"
#include "TerminalDispatch.hpp"
using namespace ::Microsoft::Terminal::Core;
using namespace ::Microsoft::Console::VirtualTerminal;

// NOTE:
// Functions related to Set Graphics Renditions (SGR) are in
//      TerminalDispatchGraphics.cpp, not this file

TerminalDispatch::TerminalDispatch(ITerminalApi& terminalApi) :
    _terminalApi{ terminalApi }
{

}

void TerminalDispatch::Execute(const wchar_t wchControl)
{
    _terminalApi.ExecuteChar(wchControl);
}

void TerminalDispatch::Print(const wchar_t wchPrintable)
{
    _terminalApi.PrintString({ &wchPrintable, 1 });
}

void TerminalDispatch::PrintString(const wchar_t *const rgwch, const size_t cch)
{
    _terminalApi.PrintString({ rgwch, cch });
}

bool TerminalDispatch::CursorPosition(const unsigned int uiLine,
                                      const unsigned int uiColumn)
{
    const auto columnInBufferSpace = uiColumn - 1;
    const auto lineInBufferSpace = uiLine - 1;
    short x = static_cast<short>(uiColumn - 1);
    short y = static_cast<short>(uiLine - 1);
    return _terminalApi.SetCursorPosition(x, y);
}

bool TerminalDispatch::CursorForward(const unsigned int uiDistance)
{
    const auto cursorPos = _terminalApi.GetCursorPosition();
    const COORD newCursorPos { cursorPos.X + gsl::narrow<short>(uiDistance), cursorPos.Y };
    return _terminalApi.SetCursorPosition(newCursorPos.X, newCursorPos.Y);
}

bool TerminalDispatch::EraseCharacters(const unsigned int uiNumChars)
{
    return _terminalApi.EraseCharacters(uiNumChars);
}

bool TerminalDispatch::SetWindowTitle(std::wstring_view title)
{
    return _terminalApi.SetWindowTitle(title);
}