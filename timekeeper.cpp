#include "timekeeper.hh"
#include <QGridLayout>
#include <QTextStream>

TimeKeeper::TimeKeeper(QWidget *parent)
    : QWidget(parent) {

  auto *startBtn = new QPushButton("Start", this);
  auto *StopBtn = new QPushButton("Stop", this);
  auto *FindWeeklyBtn = new QPushButton("Calculate", this);
  auto *empty = new QLabel(this);
  time_worked = new QElapsedTimer();
  charge_number = new QLineEdit();
  startLbl = new QLabel(this);
  stopLbl = new QLabel(this);
  hoursWorkedLbl = new QLabel(this);
  charge_number->setPlaceholderText("insert charge number here");

  auto *grid = new QGridLayout(this);
  grid->setColumnMinimumWidth(5, 1);
  grid->setRowMinimumHeight(5, 1);
  grid->addWidget(charge_number, 0, 2, 1, 3);
  grid->addWidget(startBtn, 1, 2);
  grid->addWidget(StopBtn, 1, 4);
  grid->addWidget(startLbl, 2, 2);
  grid->addWidget(stopLbl, 2, 4);
  grid->addWidget(hoursWorkedLbl, 3, 3);
  grid->addWidget(FindWeeklyBtn, 4, 2, 1, 3);

  setLayout(grid);

  connect(startBtn, &QPushButton::clicked, this, &TimeKeeper::OnStart);
  connect(StopBtn, &QPushButton::clicked, this, &TimeKeeper::OnStop);
  connect(FindWeeklyBtn, &QPushButton::clicked, this, &TimeKeeper::calculate_time_left_in_week);
}

TimeKeeper::~TimeKeeper() {
    delete time_worked;
    delete startLbl;
    delete stopLbl;
    delete charge_number;
    delete hoursWorkedLbl;
}

void TimeKeeper::OnStart() {
    //Start timer
    time_worked->start();
    
    // Need to grab the time and set it to the start label
    current_charged_time_holder.start_time = QTime::currentTime();
    startLbl->setText(QString(current_charged_time_holder.start_time.toString()));
}

void TimeKeeper::OnStop() {
  // Stop timer
  current_charged_time_holder.time_passed_in_ms = time_worked->elapsed();
  current_charged_time_holder.end_time = QTime::currentTime();

  stopLbl->setText(QString(current_charged_time_holder.end_time.toString()));
}

void TimeKeeper::calculate_time_left_in_week() {
    // Turn ms elapsed time variable into hours and then truncate to 10th place since it's what gets put into time system
    auto amount_worked_on_number = (current_charged_time_holder.time_passed_in_ms * 2.77778e-7);

    hoursWorkedLbl->setText(QString::number(amount_worked_on_number, 'f', 2));
}