#pragma once

#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QDate>
#include <QTime>
#include <QElapsedTimer>
#include <QComboBox>
#include <QLineEdit>
#include <chrono>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <fstream>
#include <filesystem>

struct current_time_holder {
    std::string effort_name;
    std::string program_name;
    qint64 time_elapsed_ms;
    QTime start_time, end_time; 
    QDate current_date;
    QString current_charge_number;
    double time_passed;

    void save_holder_to_yaml(std::string &filename);
    void load_holder_from_yaml(std::string &filename); 
};

struct app_defaults {
    int window_length, window_width;
    std::string windowTitle;
    std::string save_location;
    std::vector<std::string> program_list{};
};

class TimeKeeper : public QWidget {

  Q_OBJECT

  public:
    TimeKeeper(app_defaults defaults, QWidget *parent = nullptr);
    ~TimeKeeper();
    void setDefaults(app_defaults default_things);
    void setSavedChargesLocation(std::string &filename) { saved_charges_location = filename; }
    void setProgramList(std::vector<std::string> &list) { program_list = list; }

  private slots:
    void OnStart();
    void OnStop();

  private:
    void calculate_time_left_in_week();
    void save_charge_number_and_times_assoc();
    void add_program_to_list(); // Want to have this pop up a tiny window to add stuff to that list
    QElapsedTimer *time_worked;
    QPushButton *SaveBtn;
    QComboBox *Programs;
    QLineEdit *charge_number;
    QLineEdit *effort_name;
    QLabel *startLbl;
    QLabel *stopLbl;
    QLabel *hoursWorkedLbl;
    QLabel *hoursWorkedLbl2;
    QLabel *saved_timeslots;
    current_time_holder current_charged_time_holder;
    std::vector<current_time_holder> saved_times;
    std::string saved_charges_location;
    std::vector<std::string> program_list;
};