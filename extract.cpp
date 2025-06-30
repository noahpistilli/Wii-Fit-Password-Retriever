#include "extract.h"
#include <iostream>
#include <codecvt>
#include <format>
#include <locale>
#include "utils.h"
#include <unistd.h>

ExtractModal::ExtractModal(std::string_view region_name, std::string_view path) {
    m_region_name = region_name;
    File* file = ISFS_GetFile(path);

    auto save = static_cast<WiiFitSave*>(file->data);
    for (WiiFitUser user : save->users) {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
        std::string name = converter.to_bytes(user.name);
        if (name.empty())
            continue;

        // Map the name to a password
        m_passwords[name] = user.password;
        m_options.push_back(name);
    }


    free(file->data);
    m_num_of_lines = static_cast<int>(m_options.size());
}


void ExtractModal::Start() {
    for (int i = 0; true; i++) {
        if (i != 0 || m_num_of_lines != 1) {
            ClearScreen();
            std::cout << OVERSCAN_Y_LINES << OVERSCAN_X_SPACES << "Wii Fit Password Retriever - (c) 2025 Noah Pistilli";
            PrintTopBar("Pick a user");

            int printable = MIN(25 - OVERSCAN_Y_TIMES_2, m_num_of_lines);
            for (int j = m_offset; j < (m_offset + printable); j++) {
                PrintCursor(j);
                std::cout << m_options.at(j) << std::endl;
            }

            PrintBottomBar("Press A to select an item");
        }

        Action ret = (i == 0 && m_num_of_lines == 1) ? Action::A : ProcessInputs(true);

        if (ret == Action::Home) {
            WII_ReturnToMenu();
        } else if (ret == Action::A) {
            ClearScreen();
            std::cout << OVERSCAN_Y_LINES << OVERSCAN_X_SPACES << "Wii Fit Password Retriever - (c) 2025 Noah Pistilli";
            std::string name = m_options.at(m_index);
            PrintTopBar(std::format("Password for {}", name));

            s16 password = m_passwords[name];
            if (password == 10000) {
                std::cout << OVERSCAN_X_SPACES << "Password is not enabled." << std::endl;
            } else {
                std::cout << OVERSCAN_X_SPACES << "Password is: " << password << std::endl;
            }

            sleep(5);
        } else if (ret == Action::B) {
            return;
        }
    }

    __builtin_unreachable();
}