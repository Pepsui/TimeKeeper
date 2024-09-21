#include "timekeeper.hh"
#include <QHBoxLayout>
#include <QTextStream>

void current_time_holder::load_holder_from_yaml(std::string &filename)
{
	// Not implemented yet, but putting logic to get rid of warning
	if (!filename.empty())
	{
		std::cout << "Will implement eventually...\n";
	}
}

void current_time_holder::save_holder_to_yaml(std::string &filename)
{
   // Start encoding of file using yaml emitter
	YAML::Emitter holder;
	std::ofstream new_charge(filename);

	holder << YAML::BeginMap;
	holder << YAML::Key << this->program_name; 
	holder << YAML::BeginMap;
	holder << YAML::Key << this->effort_name;
	holder << YAML::BeginSeq << YAML::BeginMap << YAML::Key << "Charge Number" << YAML::Value << this->current_charge_number.toStdString()
			<< YAML::Key << "Amount Spent on Number" << YAML::Value << this->time_passed << "Date this number was used" 
			<< YAML::Value << this->current_date.toString().toStdString() << "Start Time" << YAML::Value << this->start_time.toString().toStdString() 
			<< "End Time" << YAML::Value << this->end_time.toString().toStdString() << YAML::EndMap << YAML::EndSeq;
	holder << YAML::EndMap;
	holder << YAML::EndMap;

	new_charge << holder.c_str();
	new_charge.close();
}

TimeKeeper::TimeKeeper(app_defaults defaults, QWidget *parent)
   : QWidget(parent) {
	this->setDefaults(defaults);
	this->setSavedChargesLocation(defaults.save_location);
	auto *startBtn = new QPushButton("Start", this);
	auto *StopBtn = new QPushButton("Stop", this);
	auto *FindWeeklyBtn = new QPushButton("Calculate", this);
	SaveBtn = new QPushButton("Save", this);
	time_worked = new QElapsedTimer();
	charge_number = new QLineEdit();
	startLbl = new QLabel(this);
	stopLbl = new QLabel(this);
	hoursWorkedLbl = new QLabel(this);
	hoursWorkedLbl2 = new QLabel(this);
	saved_timeslots = new QLabel(this);
	Programs = new QComboBox(this);
	effort_name = new QLineEdit(this);
	charge_number->setPlaceholderText("insert charge number here");
	effort_name->setPlaceholderText("Add custom effort name here");
	SaveBtn->setEnabled(false);
	for (size_t item{}; item < program_list.size(); item++) {
		Programs->addItem(QString::fromStdString(program_list[item]));
	}

	auto *MainLayout = new QVBoxLayout(this);
	auto *TopLayout = new QHBoxLayout(this);
	TopLayout->addWidget(charge_number);
	TopLayout->addWidget(Programs);
	TopLayout->addWidget(effort_name);
	TopLayout->addWidget(SaveBtn);
	MainLayout->addLayout(TopLayout);
	MainLayout->addWidget(startBtn);
	MainLayout->addWidget(StopBtn);
	MainLayout->addWidget(startLbl);
	MainLayout->addWidget(stopLbl);
	MainLayout->addWidget(hoursWorkedLbl);
	MainLayout->addWidget(hoursWorkedLbl2);
	MainLayout->addWidget(FindWeeklyBtn);
	MainLayout->addWidget(saved_timeslots);

	setLayout(MainLayout);

	connect(startBtn, &QPushButton::clicked, this, &TimeKeeper::OnStart);
	connect(StopBtn, &QPushButton::clicked, this, &TimeKeeper::OnStop);
	connect(FindWeeklyBtn, &QPushButton::clicked, this, &TimeKeeper::calculate_time_left_in_week);
	connect(SaveBtn, &QPushButton::clicked, this, &TimeKeeper::save_charge_number_and_times_assoc);
}

TimeKeeper::~TimeKeeper() {
	delete SaveBtn;
	delete time_worked;
	delete startLbl;
	delete stopLbl;
	delete charge_number;
	delete hoursWorkedLbl;
	delete hoursWorkedLbl2;
	delete saved_timeslots;
	delete effort_name;
	delete Programs;
}

void TimeKeeper::setDefaults(app_defaults default_things)
{
	this->resize(default_things.window_length, default_things.window_width);
	this->setWindowTitle(QString::fromStdString(default_things.windowTitle));
	this->setSavedChargesLocation(default_things.save_location);
	this->setProgramList(default_things.program_list);
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
  current_charged_time_holder.time_elapsed_ms = time_worked->elapsed();
  current_charged_time_holder.end_time = QTime::currentTime();

  SaveBtn->setEnabled(true);
  stopLbl->setText(QString(current_charged_time_holder.end_time.toString()));
}

void TimeKeeper::calculate_time_left_in_week() {
	hoursWorkedLbl2->setText(QString("OG time amount: ") + QString::number(current_charged_time_holder.time_elapsed_ms, 'f', 10));

	// Turn ms elapsed time variable into hours and then truncate to 10th place since it's what gets put into time system
	current_charged_time_holder.time_passed = (current_charged_time_holder.time_elapsed_ms * 2.77778e-7);

	hoursWorkedLbl->setText(QString::number(current_charged_time_holder.time_passed, 'f', 2));
}

void TimeKeeper::save_charge_number_and_times_assoc()
{
	if (!std::filesystem::is_directory(saved_charges_location))
		std::filesystem::create_directory(saved_charges_location);
	current_charged_time_holder.program_name = Programs->currentText().toStdString();
	current_charged_time_holder.effort_name = effort_name->text().toStdString();
	current_charged_time_holder.current_charge_number = charge_number->text();
	current_charged_time_holder.current_date = QDate::currentDate();
	std::string filename = saved_charges_location + current_charged_time_holder.effort_name + ".yml";
	current_charged_time_holder.save_holder_to_yaml(filename);
	saved_times.push_back(current_charged_time_holder);

	for(size_t place{}; place < saved_times.size(); place++) {
		saved_timeslots->setText(QString("Number: " + saved_times[place].current_charge_number + "\n" + "Today's Date: " + saved_times[place].current_date.toString() + "\n" + "Time passed: " + QString::number(saved_times[place].time_passed) + "\n" + "Start time: " + saved_times[place].start_time.toString() + "\n" + "End Time: " + saved_times[place].end_time.toString()));
	}
}

