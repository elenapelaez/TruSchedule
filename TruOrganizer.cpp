#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <stdlib.h>

using namespace std;

//converts string time into two int of hour and minute
class Time
{
private:
	string hourAndMin;
	int hour;
	int minute;
	void convertStringTime()
	{
		vector<int> time;
		splitHourAndMin(this->hourAndMin, ':', time);
		this->hour = time.at(0);
		this->minute = time.at(1);
	}
	void splitHourAndMin(const string& stringTime, char delimiter, vector<int>& intTime)
	{
	  size_t token_start = 0;
	  size_t delim_position = stringTime.find(delimiter);

	  int splittedHour = stringToInteger(stringTime.substr(token_start, delim_position - token_start));
	  intTime.push_back(splittedHour);
	  delim_position++;
	  int splittedMin = stringToInteger(stringTime.substr(delim_position, stringTime.length()));
	  intTime.push_back(splittedMin);
	}
	int stringToInteger(const string &string)
	{
		stringstream convertion(string);
		int integerValue;
		convertion >> integerValue;
		return integerValue;
	}
public:
	Time()
	{
		this->hourAndMin = "";
		this->hour = 0;
		this->minute = 0;
	}
	Time(string time)
	{

		this->hourAndMin = time;
		this->hour = 0;
		this->minute = 0;
		convertStringTime();
	}

	int getHour() const
	{
		return this->hour;
	}
	int getMinute() const
	{
		return this->minute;
	}

	int intReturn()
	{
		return ((this -> hour)*100) + this -> minute;
	}


	friend ostream &operator << (ostream &strm, const Time &obj)
	{
		strm << obj.hour << ":" << obj.minute;
		return strm;
	}
};

class Event
{
private:
	string name;
	string day;
	Time startTime;
	Time endTime;
	string location;
public:
	Event()
	{
		this->location = "";
		this->day = "";
		this->name = "";
	}
	Event(string name, string day, string start, string end, string location) : startTime(start), endTime(end)
	{
		this -> name = name;
		this -> day = day;
		this -> location = location;
	}

	Time& getStartTime()
	{
		return this->startTime;
	}
	Time& getEndTime()
	{
		return this->endTime;
	}
	string getLocation() const
	{
		return this->location;
	}
	string getDay() const
	{
		return this->day;
	}
	string getName() const
	{
		return this->name;
	}

	vector<size_t> convertDayIntoArrayPosition()
	{
		vector<size_t> position;
		for(size_t index = 0; index < this->day.length(); index++)
		{
			if(this->day.at(index) == 'M')
			{
				position.push_back(0);
			}
			else if(this->day.at(index) == 'T')
			{
				position.push_back(1);
			}
			else if(this->day.at(index) == 'W')
			{
				position.push_back(2);
			}
			else if(this->day.at(index) == 'R')
			{
				position.push_back(3);
			}
			else if(this->day.at(index) == 'F')
			{
				position.push_back(4);
			}
			else
			{
				cout << "Invalid day" << endl;
				exit(0);
			}
		}

		return position;
	}

	void setLocation(string setLocation)
	{
		this->location = setLocation;
	}
	void setDay(string setDay)
	{
		this->day = setDay;
	}
	void setName(string setName)
	{
		this->name = setName;
	}


};

class Person
{
private:
	string name;
	string email;
public:
	Person()
	{
		this->name = "";
		this->email = "";
	}

	Person(string name, string studentID)
	{
		this->name = name;
		this->email = studentID + "@truman.edu";
	}

	/*
	void setName(string initialName)
	{
		this->name = initialName;
	}
	*/
	void setContactInfo(string initialContactInfo)
	{
		this->email = initialContactInfo;
	}

	string getName() const
	{
		return this->name;
	}
	string getContactInfo() const
	{
		return this->email;
	}
};

class Professor: public Person
{
private:
	Event officeHourTimes;
	string department;
public:
	Professor()
	{
		this->department = "";
	}
	Professor(string name,
			  string department,
			  string eventName ,
			  string day,
			  string startTime,
			  string endTime,
			  string location = "Your momma's bed",
			  string email = "Your mom's Number") :
				  Person (name, email), officeHourTimes(eventName, day, startTime, endTime, location)
	{
		this->department = department;
	}

	void setOfficeHourTimes(const Event& initialOfficeHourTimes)
	{
		this->officeHourTimes = initialOfficeHourTimes;
	}
	void setDepartment(string initialDepartment)
	{
		this->department = initialDepartment;
	}

	const Event& getOfficeHourTimes()
	{
		return this->officeHourTimes;
	}
	string getDepartment()
	{
		return this->department;
	}
};

class Course : public Event
{
private:
	Professor courseProfessor;
public:
	Course(const Professor& instructor, string name, string day, string start, string end, string location) :
		Event(name, day, start, end, location)
	{
		this->courseProfessor = instructor;
	}


	const Professor& getCourseProfessor()
	{
		return this->courseProfessor;
	}
	void setCourseProfessor(const Professor& setProfessor)
	{
		this->courseProfessor = setProfessor;
	}

};

class Club : public Event
{
private:
	string contactInfo;
	string socialMedia;
public:
	Club()
	{
		contactInfo = "";
		socialMedia = "";
	}
	//eventName(club meeting), day, startTime, endTime, location, contactInfo, socialMedia
	Club(string eventName,
		 string day,
		 string start,
		 string end,
		 string location,
		 string info,
		 string socialMedia) : Event(eventName, day, start, end, location)
	{
		this -> contactInfo = info;
		this -> socialMedia = socialMedia;
	}


	string getContactInfo() const
	{
		return this->contactInfo;
	}
	string getSocialMedia() const
	{
		return this->socialMedia;
	}

	void setContactInfo(string info)
	{
		this->contactInfo = info;
	}
	void setSocialMedia(string media)
	{
		this->socialMedia = media;
	}
};

class Schedule
{
private:
	vector<Course> enrolledCourses;
	vector<Club> participatingClubs;
public:
	Schedule()
	{
	}

	void operator=(const vector<Course>& courses)
	{
		this->enrolledCourses = courses;
	}

	void operator=(const vector<Club>& clubs)
	{
		this->participatingClubs = clubs;
	}

	vector<Course>& getEnrolledCourses()
	{
		return this->enrolledCourses;
	}
	vector<Club>& getParticipatingClubs()
	{
		return this->participatingClubs;
	}
};

class Student : public Person
{
private:
	string bannerID;
	string studentID;
	string year;
	Schedule studentSchedule;

public:
	Student()
	{
		this->bannerID = "";
		this->studentID = "";
		this->year = "";
	}
	Student(string name, string bID, string sID, string grade): Person(name, bID)
	{
		this -> bannerID = bID;
		this -> studentID = sID;
		this -> year = grade;
	}

	string getBannerID() const
	{
		return this->bannerID;
	}

	string getStudentID() const
	{
		return this->studentID;
	}
	string getYear() const
	{
		return this->year;
	}
	Schedule& getStudentSchedule()
	{
		return this->studentSchedule;
	}

	/*
	void setBannerID(string setBannerID)
	{
		this->bannerID = bannerID;
	}

	void setStudentID(string setStudentID)
	{
		this->studentID = studentID;
	}
	*/
};

class DataBaseProcess
{
private:
	string fileName;
	ifstream file;
	vector<Professor> professorsData;
	vector<Club> clubsData;
public:
	DataBaseProcess(string dataFileName)
	{
		this->fileName = dataFileName;
		openFile();
		processData();
	}

	void openFile()
	{
		this->file.open(this->fileName);
		if(file.fail())
		{
			cout << "Invalid file name." << endl;
			exit(0);
		}
	}

	void processData()
	{
		string dummy;
		getline(file, dummy);

		string line;
		if(isProfessorFile())
		{
			while(getline(file, line))
			{
				vector<string> processedData;
				split(line, ',', processedData);
				Professor professorData(processedData.at(0), processedData.at(1), processedData.at(2),
										processedData.at(3), processedData.at(4), processedData.at(5),
										processedData.at(6), processedData.at(7));
				this->professorsData.push_back(professorData);
			}
		}
		else if(isClubFile())
		{
			while(getline(file, line))
			{
				vector<string> processedData;
				split(line, ',', processedData);
				Club clubData(processedData.at(0), processedData.at(1), processedData.at(2),
								processedData.at(3), processedData.at(4), processedData.at(5),
								processedData.at(6));
				this->clubsData.push_back(clubData);
			}
		}
		else
		{
			cout << "Logical error." ;
			cout << "The file must be either professorData.txt or clubData.txt given that the file was successfully opened." << endl;
			exit(0);
		}
	}

	bool isProfessorFile()
	{
		string professor = "professor";
		bool match = true;
		size_t index = 0;
		while(match && index < 9) // number of characters in "professor"
		{
			match = this->fileName.at(index) == professor.at(index);
			index++;
		}
		return match;
	}

	bool isClubFile()
	{
		string club = "club";
		bool match = true;
		size_t index = 0;
		while(match && index < 4) // number of characters in "club"
		{
			match = this->fileName.at(index) == club.at(index);
			index++;
		}

		return match;
	}

	const Professor& professorSearch(string professorName)
	{
		size_t index = 0;
		bool done = false;
		while(!done && index < this->professorsData.size())
		{
			if(this->professorsData.at(index).getName().find(professorName) != string::npos)
			{
				done = true;
			}
			else
			{
				index++;
			}
		}
		return (this->professorsData).at(index);
	}

	const Club& clubSearch(string clubName)
	{
		size_t index = 0;
		bool done = false;
		while(!done && index < this->clubsData.size())
		{
			if(this->clubsData.at(index).getName().find(clubName) != string::npos)
			{
				done = true;
			}
			else
			{
				index++;
			}
		}
		return this->clubsData.at(index);
	}

	void split(const string& line, char delimiter, vector<string>& tokens)
	{
	  size_t token_start = 0;
	  size_t delim_position = line.find(delimiter);

	  while(delim_position != string::npos)
	  {
	    string token =
	      line.substr(token_start, delim_position - token_start);
	    tokens.push_back(token);
	    delim_position++;
	    token_start = delim_position;
	    delim_position = line.find(delimiter, delim_position);

	    if(delim_position == string::npos)
	    {
	      token = line.substr(token_start);
	      tokens.push_back(token);
	    }
	  }
	}
};

class SampleStudents
{
private:
	vector<Student> sampleStudents;
public:
	SampleStudents(DataBaseProcess& professorDataBase, DataBaseProcess& clubDataBase)
	{
		Course cs181_1(professorDataBase.professorSearch("Jaiswal"), "CS181", "MWF", "8:30", "9:20", "VH 1345");
		Course cs181_2(professorDataBase.professorSearch("Jaiswal"), "CS181", "MWF", "11:30", "12:20", "VH 1345");
		Course cs191_1(professorDataBase.professorSearch("Halma"), "CS191", "MWF", "13:30", "14:20", "VH 1135");
		Course cs191_2(professorDataBase.professorSearch("Halma"), "CS191", "MWF", "14:30", "15:20", "VH 1135");
		Course math263_1(professorDataBase.professorSearch("Fernando"), "MATH263", "MTWRF", "12:30", "13:20", "VH 1224");
		Course math263_2(professorDataBase.professorSearch("Fernando"), "MATH263", "MTWRF", "13:30", "14:20", "VH 1224");

		Student JacobChoi("Jacob Choi", "001358684", "hc7341", "Freshman");
		vector<Course> ajustinGalangCourses;
		ajustinGalangCourses.push_back(cs181_1);
		ajustinGalangCourses.push_back(cs191_2);
		ajustinGalangCourses.push_back(math263_1);
		JacobChoi.getStudentSchedule() = ajustinGalangCourses;
		vector<Club> jacobChoiClubs;
		jacobChoiClubs.push_back(clubDataBase.clubSearch("KASA"));
		jacobChoiClubs.push_back(clubDataBase.clubSearch("JLEG"));
		JacobChoi.getStudentSchedule() = jacobChoiClubs;

		Student JustinGalang("Justin Galang", "001356969", "jg6969", "Freshman");
		vector<Course> justinGalangCourses;
		justinGalangCourses.push_back(cs181_1);
		justinGalangCourses.push_back(cs191_2);
		justinGalangCourses.push_back(math263_1);
		JustinGalang.getStudentSchedule() = justinGalangCourses;
		vector<Club> justinGalangClubs;
		justinGalangClubs.push_back(clubDataBase.clubSearch("KASA"));
		JustinGalang.getStudentSchedule() = justinGalangClubs;

		Student ElenaPelaez("Elena Pelaez", "001355123", "ecp1004", "Freshman");
		vector<Course> elenaPelaezCourse;
		elenaPelaezCourse.push_back(cs181_1);
		elenaPelaezCourse.push_back(cs191_1);
		elenaPelaezCourse.push_back(math263_2);
		ElenaPelaez.getStudentSchedule() = elenaPelaezCourse;

		this->sampleStudents.push_back(JacobChoi);
		this->sampleStudents.push_back(JustinGalang);
		this->sampleStudents.push_back(ElenaPelaez);
	}

	Student& searchStudent(string studentName)
	{
		size_t index = 0;
		bool done = false;
		while(!done && index < this->sampleStudents.size())
		{
			if(this->sampleStudents.at(index).getName().find(studentName) != string::npos)
			{
				done = true;
			}
			else
			{
				index++;
			}
		}
		return this->sampleStudents.at(index);
	}
};

void skipScreen();
void firstScreenStudentInfo(Student& userStudent);
void secondScreenAddCourse(Student& userStudent, DataBaseProcess& opennedProfessorFile);
void thirdScreenAddClub(Student& userStudent, DataBaseProcess& opennedClubFile);
void fourthScreenSearchStudent(DataBaseProcess& opennedProfessorFile, DataBaseProcess& opennedClubFile);

void skipScreen()
{
	for(size_t count = 0; count < (50/10); count++)
	{
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	}
}

void firstScreenStudentInfo(Student& userStudent)
{
	cout << endl << "Please enter in your student information." << endl;

	cout << "Student Name: ";
	string studentName;
	getline(cin, studentName);

	cout << "Student Banner ID: ";
	string studentBannerID;
	getline(cin, studentBannerID);

	cout << "Student ID: ";
	string studentID;
	getline(cin, studentID);

	cout << "Student Year: ";
	string studentYear;
	getline(cin, studentYear);

	cout << "Updating your information..." << endl;
	Student userInput(studentName, studentBannerID, studentID, studentYear);
	userStudent = userInput;
}

void secondScreenAddCourse(Student& userStudent, DataBaseProcess& opennedProfessorFile)
{
	vector<Course> enrolledCourses;
	cout << endl << "Add enrolled courses to fill out your schedule." << endl;

	bool done = false;
	while(!done)
	{
		cout << "Course Code: ";
		string courseCode;
		getline(cin, courseCode);

		cout << "Professor Name: ";
		string professorName;
		getline(cin, professorName);

		cout << "Class Day: ";
		string day;
		getline(cin, day);

		cout << "Start Time: ";
		string startTime;
		getline(cin, startTime);

		cout << "End Time: ";
		string endTime;
		getline(cin, endTime);

		cout << "Class Location: ";
		string classLocation;
		getline(cin, classLocation);

		cout << "Updating course schedule..." << endl;
		Course userInput(opennedProfessorFile.professorSearch(professorName), courseCode,
							day, startTime, endTime, classLocation);
		enrolledCourses.push_back(userInput);

		cout << "Add more courses? (Y/N): ";
		string userContinueInput;
		getline(cin, userContinueInput);
		if(userContinueInput.at(0) == 'n')
		{
			done = true;
		}
		else
		{
			cout << endl << "Adding another course." << endl;
		}
	}
	userStudent.getStudentSchedule() = enrolledCourses;
}

void thirdScreenAddClub(Student& userStudent, DataBaseProcess& opennedClubFile)
{
	vector<Club> participatingClub;
	cout << endl << "Add participating clubs to fill out your schedule." << endl;

	bool done = false;
	while(!done)
	{
		cout << "Club Name: ";
		string clubName;
		getline(cin, clubName);

		cout << "Searching for the club..." << endl;
		participatingClub.push_back(opennedClubFile.clubSearch(clubName));

		cout << "Add more club? (Y/N): ";
		string userContinueInput;
		getline(cin, userContinueInput);
		if(userContinueInput.at(0) == 'n')
		{
			done = true;
		}
		else
		{
			cout << endl << "Adding another club." << endl;
		}
	}
	userStudent.getStudentSchedule() = participatingClub;
}

void fourthScreenSearchStudent(DataBaseProcess& opennedProfessorFile, DataBaseProcess& opennedClubFile)
{
	SampleStudents sampleStudents(opennedProfessorFile, opennedClubFile);
	cout << endl << "Search a student to check their weekly schedule." << endl;

	bool done = false;
	while(!done)
	{
		cout << endl <<"Search Student Name: ";
		string searchStudentName;
		getline(cin, searchStudentName);

		cout << "Searching for the student..." << endl;
		Student searchedStudent = sampleStudents.searchStudent(searchStudentName);

		cout << endl << "Displaying student information..." << endl;
		cout << "Student Name: " << searchedStudent.getName() << endl;
		cout << "Student Banner ID: " << searchedStudent.getBannerID() << endl;
		cout << "Student Student ID: " << searchedStudent.getStudentID() << endl;
		cout << "Student Year: " << searchedStudent.getYear() << endl;


		cout << endl << "Search more student? (Y/N): ";
		string userContinueInput;
		getline(cin, userContinueInput);
		if(tolower(userContinueInput.at(0)) == 'n')
		{
			done = true;
		}
		else
		{
			cout << endl << "Searching another student." << endl;
		}
	}
}




int main()
{

    cout << "Welcome to the TruTouch: TruOrganizer!!" << endl;

	cout << endl << "Setting up..." << endl;
	DataBaseProcess professorDataBase("professorData.txt");
	DataBaseProcess clubDataBase("clubData.txt");
	Student userStudent;

	cout << endl << "Opening Screen One - Student Info Input..." << endl;
	firstScreenStudentInfo(userStudent);

	skipScreen();

	cout << endl << "Opening Screen Two - Add Course..." << endl;
	secondScreenAddCourse(userStudent, professorDataBase);

	skipScreen();
	cout << "Participating clubs (Y/N): ";
	string userClubInput;
	getline(cin, userClubInput);
	if(tolower(userClubInput.at(0)) == 'y')
	{
		thirdScreenAddClub(userStudent, clubDataBase);
	}

    // create window object with size, name in top left corner, and style
    sf::RenderWindow window(sf::VideoMode(1334, 832), "TruCoordinator", sf::Style::Default);

    sf::Font font;
    font.loadFromFile("arial.ttf");

//    sf::RectangleShape(Vector2f)
    sf::RectangleShape newSquare(sf::Vector2f(222.f, 52.f));
    newSquare.setFillColor(sf::Color(92, 22, 124));


    sf::Text headerName;
    headerName.setCharacterSize(50);
    headerName.setFillColor(sf::Color::White);
    headerName.setFont(font);
    headerName.setPosition(5,0);
    //student.getName();
    headerName.setString(userStudent.getName());

    sf::Text headerSID;
    headerSID.setCharacterSize(30);
    headerSID.setFillColor(sf::Color::White);
    headerSID.setFont(font);
    headerSID.setPosition(7,60);
    headerSID.setString(userStudent.getStudentID());

    sf::Text headerBID;
    headerBID.setCharacterSize(20);
    headerBID.setFillColor(sf::Color::White);
    headerBID.setFont(font);
    headerBID.setPosition(1225,75);
    headerBID.setString(userStudent.getBannerID());

    sf::Text mondayHeader;
    mondayHeader.setCharacterSize(25);
    mondayHeader.setFillColor(sf::Color::White);
    mondayHeader.setFont(font);
    mondayHeader.setPosition(290, 100);
    string mondayString = "Monday";
    mondayHeader.setString(mondayString);

    sf::Text tuesdayHeader;
    tuesdayHeader.setCharacterSize(25);
    tuesdayHeader.setFillColor(sf::Color::White);
    tuesdayHeader.setFont(font);
    tuesdayHeader.setPosition(512, 100);
    std::string tuesdayString = "Tuesday";
    tuesdayHeader.setString(tuesdayString);

    sf::Text wednesdayHeader;
    wednesdayHeader.setCharacterSize(25);
    wednesdayHeader.setFillColor(sf::Color::White);
    wednesdayHeader.setFont(font);
    wednesdayHeader.setPosition(700, 100);
    std::string wednesdayString = "Wednesday";
    wednesdayHeader.setString(wednesdayString);

    sf::Text thursdayHeader;
    thursdayHeader.setCharacterSize(25);
    thursdayHeader.setFillColor(sf::Color::White);
    thursdayHeader.setFont(font);
    thursdayHeader.setPosition(945, 100);
    std::string thursdayString = "Thursday";
    thursdayHeader.setString(thursdayString);

    sf::Text fridayHeader;
    fridayHeader.setCharacterSize(25);
    fridayHeader.setFillColor(sf::Color::White);
    fridayHeader.setFont(font);
    fridayHeader.setPosition(1178, 100);
    std::string fridayString = "Friday";
    fridayHeader.setString(fridayString);

    sf::Text header1;
    header1.setCharacterSize(25);
    header1.setFillColor(sf::Color::White);
    header1.setFont(font);
    header1.setPosition(85, 156);
    header1.setString("7:30");

    sf::Text header2;
    header2.setCharacterSize(25);
    header2.setFillColor(sf::Color::White);
    header2.setFont(font);
    header2.setPosition(85, 208);
    header2.setString("8:30");

    sf::Text header3;
    header3.setCharacterSize(25);
    header3.setFillColor(sf::Color::White);
    header3.setFont(font);
    header3.setPosition(85, 260);
    header3.setString("9:30");

    sf::Text header4;
    header4.setCharacterSize(25);
    header4.setFillColor(sf::Color::White);
    header4.setFont(font);
    header4.setPosition(75, 312);
    header4.setString("10:30");

    sf::Text header5;
    header5.setCharacterSize(25);
    header5.setFillColor(sf::Color::White);
    header5.setFont(font);
    header5.setPosition(75, 364);
    header5.setString("11:30");

    sf::Text header6;
    header6.setCharacterSize(25);
    header6.setFillColor(sf::Color::White);
    header6.setFont(font);
    header6.setPosition(75, 416);
    header6.setString("12:30");

    sf::Text header7;
    header7.setCharacterSize(25);
    header7.setFillColor(sf::Color::White);
    header7.setFont(font);
    header7.setPosition(85, 468);
    header7.setString("1:30");

    sf::Text header8;
    header8.setCharacterSize(25);
    header8.setFillColor(sf::Color::White);
    header8.setFont(font);
    header8.setPosition(85, 520);
    header8.setString("2:30");

    sf::Text header9;
    header9.setCharacterSize(25);
    header9.setFillColor(sf::Color::White);
    header9.setFont(font);
    header9.setPosition(85, 572);
    header9.setString("3:30");

    sf::Text header10;
    header10.setCharacterSize(25);
    header10.setFillColor(sf::Color::White);
    header10.setFont(font);
    header10.setPosition(85, 624);
    header10.setString("4:30");

    sf::Text header11;
    header11.setCharacterSize(25);
    header11.setFillColor(sf::Color::White);
    header11.setFont(font);
    header11.setPosition(85, 676);
    header11.setString("5:30");

    sf::Text header12;
    header12.setCharacterSize(25);
    header12.setFillColor(sf::Color::White);
    header12.setFont(font);
    header12.setPosition(85, 728);
    header12.setString("6:30");

    sf::Text header13;
    header13.setCharacterSize(25);
    header13.setFillColor(sf::Color::White);
    header13.setFont(font);
    header13.setPosition(85, 780);
    header13.setString("7:30");

    sf::Color colorArray[] = {sf::Color(53, 67, 221), sf::Color(204, 34, 34),
			  sf::Color(237, 138, 0), sf::Color(38, 193, 183),
			  sf::Color(214, 52, 138), sf::Color(23, 168, 35)};

    //Blue, Red, Orange, Teal, Magenta, Green


    while (window.isOpen())
    {
        sf::Event event;
        // checks when to close window
        while (window.pollEvent(event))
        {
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);
            switch(event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                std::cout << "NONE OF IT" << std::endl;
                break;
            }
        }


        //MAKES GRID
        window.clear(sf::Color(92, 22, 124));
        for(int wNumber = 0; wNumber <6; wNumber++)
        {
            for(int hNumber = 2; hNumber < 17; hNumber++)
            {
                //newSquare.setFillColor(sf::Color(196, 150, 234));
                newSquare.setOutlineColor(sf::Color::Black);
                if (hNumber == 2 || wNumber == 0)
                {
                    newSquare.setFillColor(sf::Color(118, 117, 119));

                   // newSquare.setOutlineThickness(0.00);
                }
                else
               {
                    newSquare.setFillColor(sf::Color(255, 233, 175));
               }

                newSquare.setOutlineThickness(2.00);
                newSquare.setPosition(wNumber*222, hNumber*52);
                window.draw(newSquare);
            }
        }


        // window.draw(newSquare);
        window.draw(headerName);
        window.draw(headerSID);
        window.draw(headerBID);
        window.draw(mondayHeader);
        window.draw(tuesdayHeader);
        window.draw(wednesdayHeader);
        window.draw(thursdayHeader);
        window.draw(fridayHeader);
        //7:30
        window.draw(header1);
        //8:30
        window.draw(header2);
        window.draw(header3);
        window.draw(header4);
        window.draw(header5);
        window.draw(header6);
        window.draw(header7);
        window.draw(header8);
        window.draw(header9);
        window.draw(header10);
        window.draw(header11);
        window.draw(header12);
        window.draw(header13);

        //COURSE SQUARE MAKER
        //sf::RectangleShape classRectangle(sf::Vector2f(222.f, 52.f));
        for(int index = 0; index < userStudent.getStudentSchedule().getEnrolledCourses().size() ; index++)
        {
            //Vector MTWRF -> <0,1,2,3,4>
           // vector <size_t> classDay(userStudent.getStudentSchedule().getEnrolledCourses().size()) =
//userStudent.getStudentSchedule().getEnrolledCourses().at(index).convertDayIntoArrayPosition();

            sf::RectangleShape classRectangle(sf::Vector2f(222.f, 52.f));
            sf::Text classLabel;
            classLabel.setFillColor(sf::Color::White);
            classLabel.setCharacterSize(30);
            classLabel.setFont(font);
            //classLabel.setStyle(sf::Style::Bold);
            classRectangle.setFillColor(colorArray[index]);
            //classRectangle.setFillColor(sf::Color::Black);
            classRectangle.setOutlineColor(sf::Color::Black);
            classRectangle.setOutlineThickness(2.00);

            for(int dayIndex = 0;
            dayIndex < userStudent.getStudentSchedule().getEnrolledCourses().at(index).convertDayIntoArrayPosition().size() ; dayIndex++)
            {
                double startingTime = userStudent.getStudentSchedule().getEnrolledCourses().at(index).getStartTime().intReturn();
                //startingTime is 8am == 800
                int startingTimePlace = ((((startingTime/100.0)-7.0)*52.0) + (166.0 - (26.0)));
                classRectangle.setPosition(userStudent.getStudentSchedule().getEnrolledCourses().at(index).convertDayIntoArrayPosition().at(dayIndex)*222 + 222 , startingTimePlace);
                classLabel.setPosition(userStudent.getStudentSchedule().getEnrolledCourses().at(index).convertDayIntoArrayPosition().at(dayIndex)*222 + 222 , startingTimePlace);
                classLabel.setString(userStudent.getStudentSchedule().getEnrolledCourses().at(index).getName());

                window.draw(classRectangle);
                window.draw(classLabel);
            }



        }


        //TEST
        /*
        sf::RectangleShape test(sf::Vector2f(255.f, 52.f));

        test.setFillColor(sf::Color::Black);
        test.setOutlineColor(sf::Color::Black);
        test.setOutlineThickness(2.00);
        test.setPosition(444, 130 );
        window.draw(test);
        */







        //window.draw(classRectangle);
        window.display();

    }
    skipScreen();
	cout << "Search other students? (Y/N): ";
	string userStudentSearchInput;
	getline(cin, userStudentSearchInput);
	if(tolower(userStudentSearchInput.at(0)) == 'y')
	{
		cout << endl << "Opening Screen Four - Search Student..." << endl;
		fourthScreenSearchStudent(professorDataBase, clubDataBase);
	}

    return 0;
}
