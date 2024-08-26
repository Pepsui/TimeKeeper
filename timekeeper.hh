#pragma once

#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QDate>
#include <QTime>
#include <QElapsedTimer>
#include <QLineEdit>
#include <chrono>
#include <string>

struct current_time_holder {
    qint64 time_passed_in_ms;
    QTime start_time, end_time; 
};

struct app_defaults {
    int window_length, window_width;
    std::string windowTitle;
};

class TimeKeeper : public QWidget {

  Q_OBJECT

  public:
    TimeKeeper(QWidget *parent = nullptr);
    ~TimeKeeper();

  private slots:
    void OnStart();
    void OnStop();

  private:
    void calculate_time_left_in_week();
    QElapsedTimer *time_worked;
    QLineEdit *charge_number;
    QLabel *startLbl;
    QLabel *stopLbl;
    QLabel *hoursWorkedLbl;
    current_time_holder current_charged_time_holder;
};