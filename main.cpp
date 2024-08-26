#include "timekeeper.hh"
#include <memory>
#include <yaml-cpp/yaml.h>
#include <iostream>

int main(int argc, char *argv[]) {
    
    QApplication app(argc, argv);

    TimeKeeper window;
    app_defaults defaults;

    try {
        YAML::Node config = YAML::LoadFile("../config.yml");

        defaults.window_length = config["appsettings"]["length"].as<int>();
        defaults.window_width = config["appsettings"]["width"].as<int>();
        defaults.windowTitle = config["appsettings"]["app-name"].as<std::string>();
    }
    catch(YAML::BadFile& e) {
        std::cout << "Can't find file or bad format, using preset defaults\n";

        defaults.window_length = 480;
        defaults.window_width = 360;
        defaults.windowTitle = "Time Keeper App";
    }

    window.resize(defaults.window_length, defaults.window_width);
    window.setWindowTitle(QString::fromStdString(defaults.windowTitle));
    window.show();

    return app.exec();
}