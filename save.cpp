#include "save.h"
#include <iostream>
#include <ranges>
#include "extract.h"

#include "utils.h"

SaveSelectModal::SaveSelectModal() {
    GetSaves();
    m_num_of_lines = static_cast<int>(m_options.size());
}

void SaveSelectModal::GetSaves() {
    for (auto [name, path] : SAVE_PATHS) {
        File* file = ISFS_GetFile(path);
        if (file->error_code == ISFS_ENOENT) {
            // Skip as it doesn't exist
            continue;
        }

        free(file->data);
        m_options.push_back(name);
    }

    b_has_save = !m_options.empty();
}

bool SaveSelectModal::HasSave() const {
    return b_has_save;
}

[[noreturn]] void SaveSelectModal::Start() {
    for (int i = 0; true; i++) {
        if (i != 0 || m_num_of_lines != 1) {
            ClearScreen();
            std::cout << OVERSCAN_Y_LINES << OVERSCAN_X_SPACES << "Wii Fit Password Retriever - (c) 2025 Noah Pistilli";
            PrintTopBar("Pick an option");

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
            auto extract = new ExtractModal(m_options.at(m_index), SAVE_PATHS[m_options.at(m_index)]);
            extract->Start();
        }
    }

    __builtin_unreachable();
}