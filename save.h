#pragma once

#include "tui.h"
#include "utils.h"
#include <vector>
#include <map>

class SaveSelectModal : public TUI {
public:
    SaveSelectModal();
    bool HasSave() const;

    [[noreturn]] void Start() override;

private:
    std::map<std::string_view, std::string_view> SAVE_PATHS = {
        {"Japan", "/title/00010004/5246504a/data/FitPlus0.dat"},
        {"Europe", "/title/00010004/52465050/data/FitPlus0.dat"},
        {"USA", "/title/00010004/52465045/data/FitPlus0.dat"},
        {"Korea", "/title/00010004/5246504b/data/FitPlus0.dat"},
        {"Taiwan", "/title/00010004/52465057/data/FitPlus0.dat"},
    };

    void GetSaves();
    std::vector<std::string_view> m_options{};
    bool b_has_save = false;
};
