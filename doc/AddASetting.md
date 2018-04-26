# Adding a Settings Property

1. Add to wincon.w
    * THIS IS NOT IN OPENCONSOLE. Make sure you update
      `.../console/published/wincon.w` in the OS repo when you submit the PR.
      The branch won't build without it.
    * For now, you can update winconp.h with your consumable changes.
    * define registry name (ex `CONSOLE_REGISTRY_CURSORCOLOR`)
    * add the setting to `CONSOLE_STATE_INFO`
    * define the property key ID and the property key itself
        - Yes, the large majority of the `DEFINE_PROPERTYKEY` defs are the same, it's only the last byte of the guid that changes
2. Add matching fields to Settings.hpp
    - add getters, setters, the whole drill.
3. Add to the propsheet.
    - We need to add it to *writing* the rigistry from the propsheet, and *reading* the link from the propsheet. Yes, that's weird, but the propsheet is smart enough to re-use ShortcutSerialization::s_SetLinkValues, but not smart enough to do the same with RegistrySerialization.
    - `src/propsheet/registry.cpp`
    - `src/propsheet/readlink.cpp`, `LoadConsoleV2LinkProperties`
4. Add the field to the propslib registry map
5. Add the value to `ShortcutSerialization.cpp`
    - Read the value in `ShortcutSerialization::s_PopulateV2Properties`
    - Write the value in `ShortcutSerialization::s_SetLinkValues`
6. Add the setting to `Menu::s_GetConsoleState`, and `Menu::s_PropertiesUpdate`
Now, your new setting should be stored just like all the other properties.
7. Update the feature test properties to get add the setting as well.
    - `ft_uia/Common/NativeMethods.cs@WinConP`:
        - `Wtypes.PROPERTYKEY PKEY_Console_`
        - `NT_CONSOLE_PROPS`