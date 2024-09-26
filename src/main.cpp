#include "timekeeper.hh"
#include <memory>
#include <yaml-cpp/yaml.h>
#include <iostream>

int main(int argc, char *argv[]) {
    
    QApplication app(argc, argv);

    app_defaults defaults;

    try {
        YAML::Node config = YAML::LoadFile("../config/config.yml");

        defaults.window_length = config["appsettings"]["length"].as<int>();
        defaults.window_width = config["appsettings"]["width"].as<int>();
        defaults.windowTitle = config["appsettings"]["app-name"].as<std::string>();
        defaults.save_location = config["appsettings"]["saved_charges_location"].as<std::string>();
        for(size_t current_spot{}; current_spot < config["Programs"].size(); current_spot++) {
            defaults.program_list.push_back(config["Programs"][current_spot].as<std::string>());
        }
    }
    catch(YAML::BadFile& e) {
        std::cout << "Can't find file or bad format, using preset defaults\n";

        defaults.window_length = 480;
        defaults.window_width = 360;
        defaults.windowTitle = "Time Keeper App";
        defaults.save_location = "../saved_charges/";
        // Could put default values for programs here
    }

    TimeKeeper window(defaults);
    window.show();

    return app.exec();
}