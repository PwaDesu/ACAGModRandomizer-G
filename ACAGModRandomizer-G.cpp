// Authored by Pwa the 17/09/2024

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <time.h>
#include <cstdlib>
#include <chrono>
#include <thread>


static int path_exists(std::string path)
{
    return std::filesystem::exists(std::filesystem::absolute(path));
}

static std::string read_file(std::string file)
{
    if (std::ifstream is{ file, std::ios::binary | std::ios::ate })
    {
        auto size = is.tellg();
        std::string str(size, '\0'); // construct string to stream size
        is.seekg(0);

        if (is.read(&str[0], size)) {
            //std::cout << str << '\n';
        }
        else {
            std::cout << "Failed to read " << file << " for unknown reasons, mods settings may not be preserved.\n";
            return "";
        }

        return str;
    }
}

static void launch_3dmigoto()
{
    using namespace std::chrono_literals;

    if (path_exists("3DMigoto Loader.exe")) {
        std::cout << "Mods selected. Launching 3DMigoto.\n";
        std::cout.flush();
        std::system("\"3DMigoto Loader.exe\"");
    }
    else {
        std::cout << "Mods selected.\n3DMigoto not found. Assuming that user has an alternative launcher and quitting in 2 seconds.\n";
        std::this_thread::sleep_for(2000ms);
    }
}

static std::string str_tolower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return std::tolower(c); } 
    );
    return s;
}

static std::string get_mod_namespace(std::string mod_config, std::string path)
{
    const std::string::size_type namespace_position = mod_config.find("namespace=");

    if (namespace_position != std::string::npos) {
        const std::string::size_type end_of_line = mod_config.find("\n", namespace_position);

        if (end_of_line != std::string::npos) {
            return str_tolower("$\\" + mod_config.substr(namespace_position + 10, end_of_line - (namespace_position + 10)));
        }
        else {
            return str_tolower("$\\" + mod_config.substr(namespace_position));
        }
    }
    else {
        const std::string lowered = str_tolower("$\\" + path.replace(0, 11, "mods"));
        const std::string::size_type character_folder_delimitation = lowered.find("\\", 7);
        return lowered.substr(0, 7) + lowered.substr(7, character_folder_delimitation - 7) + " - " + lowered.substr(character_folder_delimitation + 1);
    }
}

static std::string update_settings(std::string mod_config, std::string mod_namespace, std::string data_file, std::string::size_type position) 
{
    const std::string::size_type variable_position = mod_config.find("global persist", position);

    if (variable_position != std::string::npos) {
        const std::string::size_type end_of_line = mod_config.find("\n", variable_position);
        const std::string::size_type variable_name_position = mod_config.find("$", variable_position);
        const std::string::size_type variable_value_position = mod_config.find("=", variable_name_position);

        if (variable_name_position == std::string::npos || variable_value_position == std::string::npos) {
            std::cout << "Mod " + mod_namespace + " seems to be malformed, its update will be aborted.\n";
            return mod_config;
        }
        else {
            const std::string variable_name = mod_config.substr(variable_name_position + 1, variable_value_position - variable_name_position - 1);
            const std::string::size_type saved_setting_position = data_file.find(mod_namespace + "\\" + variable_name);

            if (saved_setting_position != std::string::npos) {
                const std::string::size_type saved_setting_value_position = data_file.find("=", saved_setting_position);
                const std::string::size_type saved_setting_end_of_line = data_file.find("\n", saved_setting_position);
                const std::string saved_setting = data_file.substr(saved_setting_value_position + 2, saved_setting_end_of_line - saved_setting_value_position - 2);
                mod_config.replace(variable_value_position + 1, end_of_line - variable_value_position - 1, " " + saved_setting);
            }
            else {
                //std::cout << "Did not find a corresponding setting " + mod_namespace + "\\" + variable_name + " in the saved settings.\n";
            }
        }

        return update_settings(mod_config, mod_namespace, data_file, end_of_line);
    }
    else {
        return mod_config;
    }
}

static void iterate_over_mods(std::string data_file, std::string path)
{
    using namespace std::chrono_literals;
    const std::filesystem::path current_directory_path{ std::filesystem::absolute(path) };

    for (auto const& dir_entry : std::filesystem::directory_iterator{ current_directory_path }) {
        if (dir_entry.is_directory()) {
            iterate_over_mods(data_file, path + "\\" + dir_entry.path().stem().string());
        }
        else if (dir_entry.is_regular_file() && dir_entry.path().extension().string() == ".ini" && dir_entry.path().string().find("DISABLED") == std::string::npos) {
            const std::string file_path = path + "\\" + dir_entry.path().filename().string();
            std::string mod_config = read_file(file_path);
            const std::string mod_namespace = get_mod_namespace(mod_config, file_path);
            mod_config = update_settings(mod_config, mod_namespace, data_file, 0);
            std::ofstream(current_directory_path.string() + "\\" + dir_entry.path().filename().string(), std::ios::binary) << mod_config;
        }
    }
}

static void save_mods_settings()
{
    using namespace std::chrono_literals;
    std::cout << "Attempting to save mods settings from last run.\n";

    if (path_exists("d3dx_user.ini")) {
        std::string contents = read_file("d3dx_user.ini");
        iterate_over_mods(contents, "Random Mods");
        std::cout << "Mods settings saved. Moving on to mods selection.\n";
    }
    else {
        std::cout << "d3dx_user.ini file not found. Failed to save mods settings.\nMoving on to mods selection.\n";
    }
}

int main()
{
    std::cout << "Genshin mod randomizer 1.1.0 - this is a miniscule free script, if you've paid for this, you've been scammed\n";
    save_mods_settings();
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

    launch_3dmigoto();
}