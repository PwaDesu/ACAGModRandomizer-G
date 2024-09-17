// Authored by Pwa the 17/09/2024

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <time.h>
#include <cstdlib>

int main()
{
    std::cout << "Genshin mod randomizer - this is a miniscule free script, if you've paid for this, you've been scammed";
    srand(time(NULL));
    const std::filesystem::path mods_path{ std::filesystem::absolute("Mods")};
    const std::filesystem::path random_mods_path{ std::filesystem::absolute("Random Mods") };

    std::cout << "Removing previous mods.\n";
    for (auto const& dir_entry : std::filesystem::directory_iterator{ mods_path }) {
        if (dir_entry._Is_symlink_or_junction()) {
            std::filesystem::remove(dir_entry.path());
            std::cout << "Removed " + dir_entry.path().filename().string() + "\n";
        }
    }

    std::cout << "Previous mods removed. Selecting new mods.\n";
    for (auto const& dir_entry : std::filesystem::directory_iterator{ random_mods_path }) {
        if (dir_entry.is_directory()) {
            std::map<int, std::filesystem::directory_entry> mods{};
            int mod_count = 0;
            for (auto const& mod_entry : std::filesystem::directory_iterator{ dir_entry.path()}) {
                if (mod_entry.is_directory()) {
                    mods.insert({ mod_count, mod_entry });
                    mod_count += 1;
                }
            }

            if (mods.size() > 0) {
                const std::filesystem::directory_entry selected_mod{ mods[rand() % mods.size()] };
                std::cout << "Selected " + selected_mod.path().stem().string() + " for " + dir_entry.path().stem().string() + ", linking the mod now.\n";
                std::error_code ec;
                std::filesystem::create_directory_symlink(selected_mod.path(), std::filesystem::path{ std::filesystem::absolute("Mods/" + dir_entry.path().stem().string() + " - " + selected_mod.path().stem().string()) }, ec);

                if (ec.value() != 0) {
                    std::cout << ec.message() << "\n";
                }
            }
            else {
                std::cout << "No mods for " + dir_entry.path().stem().string() + "\n";
            }

        }
    }

    std::cout << "Mods selected. Launching 3DMigoto.\n";
    std::cout.flush();
    std::system("\"3DMigoto Loader.exe\"");
}

