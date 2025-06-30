#pragma once

#include <array>
#include <gctypes.h>
#include "tui.h"
#include "utils.h"
#include <vector>
#include <map>

#pragma pack(push, 1)
struct WiiFitUser {
    char16_t name[10];
    char padding[3];
    u8 height;
    u16 dob_year;
    u8 dob_month;
    u8 dob_day;
    s16 password;
    char unk[37475];
};
static_assert(sizeof(WiiFitUser) == 37505);
#pragma pack(pop)

#pragma pack(push, 1)
struct WiiFitSave {
    char magic[8];
    WiiFitUser users[8];
};
static_assert(sizeof(WiiFitSave) == 300048);
#pragma pack(pop)

class ExtractModal : public TUI {
public:
    ExtractModal(std::string_view region_name, std::string_view path);

    void Start() override;

private:
    std::string_view m_region_name;
    std::vector<std::string> m_options{};
    std::map<std::string, s16> m_passwords{};
};