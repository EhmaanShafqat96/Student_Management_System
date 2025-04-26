#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <fstream>
#include <vector>
using namespace std;

static int studentCount = 0; // Tracks number of students enrolled in courses
const int MAX_ENROLLMENT = 8; // Maximum students per course

// Student data structure
struct Student {
    string name;
    string id;
    int semester;
    int totalFee;
    int cnic;
    int phone;
    string department;
    string batch;
    Student* nextStudent;
};
Student* studentListHead = NULL;

// Faculty data structure
struct Faculty {
    string date;
    string name;
    string id;
    string office;
    Faculty* nextFaculty;
    float marks[10];
    float obtainedMarks[10];
    int slot;
    int cnic;
    int phone;
};
Faculty* facultyListHead = NULL;

// Course data structure
struct Course {
    string facultyName;
    string enrolledStudents[MAX_ENROLLMENT];
    int enrollmentCount = 0;
    int semester;
    int attendance[MAX_ENROLLMENT];
    int creditHours;
    int fee;
    int courseSemester;
    string name;
    string year;
    string id;
    Course* nextCourse;
};
Course* courseListHead = NULL;

// Helper functions
void printSeparator() {
    for (int i = 0; i < 50; i++) cout << "-";
    cout << endl << endl;
}

bool isStudentIdExists(string id) {
    Student* current = studentListHead;
    while (current != NULL) {
        if (current->id == id) return true;
        current = current->nextStudent;
    }
    return false;
}

bool isFacultyIdExists(string id) {
    Faculty* current = facultyListHead;
    while (current != NULL) {
        if (current->id == id) return true;
        current = current->nextFaculty;
    }
    return false;
}

bool isCourseIdExists(string id) {
    Course* current = courseListHead;
    while (current != NULL) {
        if (current->id == id) return true;
        current = current->nextCourse;
    }
    return false;
}

class Admin {
public:
    void displayAdminMenu() {
        cout << "\t~~~~~ Welcome to Admin Portal ~~~~~\n";
        int choice;

        do {
            cout << "\t\tMain Menu of admin:\n";
            cout << "\tPress 1 to register student\n";
            cout << "\tPress 2 for data entry of faculty member\n";
            cout << "\tPress 3 to offer course\n";
            cout << "\tPress 4 to search records\n";
            cout << "\tPress 5 to log out\n";
            cin >> choice;
            system("cls");

            if (choice == 1) registerStudent();
            else if (choice == 2) registerFaculty();
            else if (choice == 3) offerCourse();
            else if (choice == 4) searchRecords();
        } while (choice != 5);
    }

    void registerStudent() {
        Student* newStudent = new Student;

        cout << "Enter student data:\n";
        cout << "Name: ";
        cin.ignore();
        getline(cin, newStudent->name);

        // Check for duplicate ID
        string id;
        do {
            cout << "ID: ";
            cin >> id;
            if (isStudentIdExists(id))
                cout << "Error: Student ID already exists. Please enter a unique ID.\n";
        } while (isStudentIdExists(id));
        newStudent->id = id;

        cout << "CNIC: ";
        cin >> newStudent->cnic;
        cout << "Phone: ";
        cin >> newStudent->phone;
        cout << "Department: ";
        cin >> newStudent->department;
        cout << "Batch: ";
        cin >> newStudent->batch;
        cout << "Semester: ";
        cin >> newStudent->semester;

        // Add to linked list
        newStudent->nextStudent = NULL;
        if (studentListHead == NULL) {
            studentListHead = newStudent;
        }
        else {
            Student* current = studentListHead;
            while (current->nextStudent != NULL)
                current = current->nextStudent;
            current->nextStudent = newStudent;
        }
        cout << "Student registered successfully!\n\n";
    }

    void registerFaculty() {
        Faculty* newFaculty = new Faculty;

        cout << "Enter faculty data:\n";
        cout << "Name: ";
        cin.ignore();
        getline(cin, newFaculty->name);

        // Check for duplicate ID
        string id;
        do {
            cout << "ID: ";
            cin >> id;
            if (isFacultyIdExists(id))
                cout << "Error: Faculty ID already exists. Please enter a unique ID.\n";
        } while (isFacultyIdExists(id));
        newFaculty->id = id;

        cout << "CNIC: ";
        cin >> newFaculty->cnic;
        cout << "Phone: ";
        cin >> newFaculty->phone;
        cout << "Office: ";
        cin.ignore();
        getline(cin, newFaculty->office);

        // Add to linked list
        newFaculty->nextFaculty = NULL;
        if (facultyListHead == NULL) {
            facultyListHead = newFaculty;
        }
        else {
            Faculty* current = facultyListHead;
            while (current->nextFaculty != NULL)
                current = current->nextFaculty;
            current->nextFaculty = newFaculty;
        }
        cout << "Faculty registered successfully!\n\n";
    }

    void offerCourse() {
        Course* newCourse = new Course;

        cout << "Course offering:\n";
        cout << "Semester: ";
        cin >> newCourse->courseSemester;
        cout << "Year: ";
        cin.ignore();
        getline(cin, newCourse->year);

        // Check for duplicate course ID
        string id;
        do {
            cout << "Course ID: ";
            getline(cin, id);
            if (isCourseIdExists(id))
                cout << "Error: Course ID already exists. Please enter a unique ID.\n";
        } while (isCourseIdExists(id));
        newCourse->id = id;

        cout << "Course name: ";
        getline(cin, newCourse->name);
        cout << "Credit hours: ";
        cin >> newCourse->creditHours;
        cout << "Fee: ";
        cin >> newCourse->fee;

        // Validate faculty exists
        string facultyName;
        bool facultyFound = false;
        do {
            cout << "Faculty member: ";
            cin.ignore();
            getline(cin, facultyName);

            Faculty* current = facultyListHead;
            while (current != NULL) {
                if (current->name == facultyName) {
                    facultyFound = true;
                    break;
                }
                current = current->nextFaculty;
            }
            if (!facultyFound)
                cout << "Faculty not found. Please enter a valid faculty name.\n";
        } while (!facultyFound);
        newCourse->facultyName = facultyName;

        // Add to linked list
        newCourse->nextCourse = NULL;
        if (courseListHead == NULL) {
            courseListHead = newCourse;
        }
        else {
            Course* current = courseListHead;
            while (current->nextCourse != NULL)
                current = current->nextCourse;
            current->nextCourse = newCourse;
        }
        cout << "Course offered successfully!\n\n";
    }

    void searchRecords() {
        int choice;
        cout << "\tSearch Options:\n";
        cout << "\t1. Search Student\n";
        cout << "\t2. Search Faculty\n";
        cout << "\t3. Search Course\n";
        cout << "\t4. Back to Main Menu\n";
        cin >> choice;
        system("cls");

        if (choice == 1) searchStudent();
        else if (choice == 2) searchFaculty();
        else if (choice == 3) searchCourse();
    }

    void searchStudent() {
        int option;
        cout << "Search student by:\n";
        cout << "1. ID\n2. Name\n";
        cin >> option;
        cin.ignore();

        string query;
        cout << "Enter search term: ";
        getline(cin, query);

        Student* current = studentListHead;
        bool found = false;

        while (current != NULL) {
            if ((option == 1 && current->id == query) ||
                (option == 2 && current->name.find(query) != string::npos)) {
                displayStudentInfo(current);
                found = true;
            }
            current = current->nextStudent;
        }

        if (!found) cout << "No matching student found.\n";
        cout << endl;
    }

    void searchFaculty() {
        int option;
        cout << "Search faculty by:\n";
        cout << "1. ID\n2. Name\n";
        cin >> option;
        cin.ignore();

        string query;
        cout << "Enter search term: ";
        getline(cin, query);

        Faculty* current = facultyListHead;
        bool found = false;

        while (current != NULL) {
            if ((option == 1 && current->id == query) ||
                (option == 2 && current->name.find(query) != string::npos)) {
                displayFacultyInfo(current);
                found = true;
            }
            current = current->nextFaculty;
        }

        if (!found) cout << "No matching faculty found.\n";
        cout << endl;
    }

    void searchCourse() {
        int option;
        cout << "Search course by:\n";
        cout << "1. ID\n2. Name\n3. Faculty\n";
        cin >> option;
        cin.ignore();

        string query;
        cout << "Enter search term: ";
        getline(cin, query);

        Course* current = courseListHead;
        bool found = false;

        while (current != NULL) {
            if ((option == 1 && current->id == query) ||
                (option == 2 && current->name.find(query) != string::npos) ||
                (option == 3 && current->facultyName.find(query) != string::npos)) {
                displayCourseInfo(current);
                found = true;
            }
            current = current->nextCourse;
        }

        if (!found) cout << "No matching course found.\n";
        cout << endl;
    }

    void displayStudentInfo(Student* student) {
        cout << "\nStudent Details:\n";
        cout << "Name: " << student->name << "\nID: " << student->id;
        cout << "\nCNIC: " << student->cnic << "\nPhone: " << student->phone;
        cout << "\nDepartment: " << student->department;
        cout << "\nSemester: " << student->semester;
        cout << "\nBatch: " << student->batch << endl;
    }

    void displayFacultyInfo(Faculty* faculty) {
        cout << "\nFaculty Details:\n";
        cout << "Name: " << faculty->name << "\nID: " << faculty->id;
        cout << "\nCNIC: " << faculty->cnic << "\nPhone: " << faculty->phone;
        cout << "\nOffice: " << faculty->office << endl;
    }

    void displayCourseInfo(Course* course) {
        cout << "\nCourse Details:\n";
        cout << "Name: " << course->name << "\nID: " << course->id;
        cout << "\nSemester: " << course->courseSemester;
        cout << "\nCredit Hours: " << course->creditHours;
        cout << "\nFee: " << course->fee;
        cout << "\nFaculty: " << course->facultyName;
        cout << "\nYear: " << course->year;
        cout << "\nEnrolled Students: " << course->enrollmentCount << "/" << MAX_ENROLLMENT << endl;

        if (course->enrollmentCount > 0) {
            cout << "Student List: ";
            for (int i = 0; i < course->enrollmentCount; i++) {
                cout << course->enrolledStudents[i];
                if (i < course->enrollmentCount - 1) cout << ", ";
            }
            cout << endl;
        }
    }

    bool authenticate(string name, int userType) {
        if (userType == 1) { // Student
            Student* current = studentListHead;
            while (current != NULL) {
                if (current->name == name) return true;
                current = current->nextStudent;
            }
        }
        else if (userType == 2) { // Faculty
            Faculty* current = facultyListHead;
            while (current != NULL) {
                if (current->name == name) return true;
                current = current->nextFaculty;
            }
        }
        return false;
    }

    void showEnrolledCourses(string studentName) {
        int option;
        Course* currentCourse = courseListHead;

        if (courseListHead == NULL) {
            cout << "No courses available for enrollment.\n";
            return;
        }

        while (currentCourse != NULL) {
            cout << "\nCourse: " << currentCourse->name;
            cout << "\nID: " << currentCourse->id;
            cout << "\nCredit Hours: " << currentCourse->creditHours;
            cout << "\nFee: " << currentCourse->fee;
            cout << "\nFaculty: " << currentCourse->facultyName;
            cout << "\nEnrollment: " << currentCourse->enrollmentCount << "/" << MAX_ENROLLMENT << endl;

            cout << "Press 1 to enroll\nPress 2 to skip\n";
            cin >> option;

            if (option == 1) {
                if (currentCourse->enrollmentCount < MAX_ENROLLMENT) {
                    currentCourse->enrolledStudents[currentCourse->enrollmentCount] = studentName;
                    currentCourse->enrollmentCount++;
                    cout << "Enrollment successful!\n";
                }
                else {
                    cout << "Course is full. Cannot enroll.\n";
                }
            }
            currentCourse = currentCourse->nextCourse;
        }
    }
};

class StudentPortal : public Admin {
public:
    void displayStudentMenu(string studentName) {
        cout << "\t~~~~~ Welcome to Student Portal ~~~~~\n";

        Student* currentStudent = studentListHead;
        while (currentStudent != NULL) {
            if (currentStudent->name == studentName) {
                displayStudentInfo(currentStudent);
                break;
            }
            currentStudent = currentStudent->nextStudent;
        }

        int option;
        do {
            cout << "\n\tStudent Menu:\n";
            cout << "\t1. Course Enrollment\n";
            cout << "\t2. View Attendance\n";
            cout << "\t3. View Grades\n";
            cout << "\t4. View Fee Challan\n";
            cout << "\t5. Search Courses\n";
            cout << "\t6. Log Out\n";
            cin >> option;
            system("cls");

            if (option == 1) showEnrolledCourses(studentName);
            else if (option == 2) viewAttendance(currentStudent);
            else if (option == 3) viewGrades(currentStudent);
            else if (option == 4) viewFeeChallan(currentStudent);
            else if (option == 5) searchCourses();
        } while (option != 6);
    }

private:
    void searchCourses() {
        int option;
        cout << "Search courses by:\n";
        cout << "1. Name\n2. Faculty\n";
        cin >> option;
        cin.ignore();

        string query;
        cout << "Enter search term: ";
        getline(cin, query);

        Course* current = courseListHead;
        bool found = false;

        while (current != NULL) {
            if ((option == 1 && current->name.find(query) != string::npos) ||
                (option == 2 && current->facultyName.find(query) != string::npos)) {
                displayCourseInfo(current);
                found = true;
            }
            current = current->nextCourse;
        }

        if (!found) cout << "No matching courses found.\n";
        cout << endl;
    }

    void viewAttendance(Student* student) {
        string courseName;
        cout << "Enter course name to view attendance: ";
        cin >> courseName;

        bool found = false;
        Course* currentCourse = courseListHead;

        while (currentCourse != NULL) {
            for (int i = 0; i < currentCourse->enrollmentCount; i++) {
                if (student->name == currentCourse->enrolledStudents[i] &&
                    currentCourse->name == courseName) {

                    cout << "\nAttendance for " << currentCourse->name << ":\n";
                    Faculty* faculty = facultyListHead;
                    while (faculty != NULL) {
                        if (faculty->name == currentCourse->facultyName) {
                            cout << "Date: " << faculty->date << " | Slot: " << faculty->slot;
                            cout << " | Status: " << (currentCourse->attendance[i] == 1 ? "Present" : "Absent") << endl;
                            break;
                        }
                        faculty = faculty->nextFaculty;
                    }
                    found = true;
                    break;
                }
            }
            currentCourse = currentCourse->nextCourse;
        }

        if (!found) cout << "No attendance records found.\n";
    }

    void viewGrades(Student* student) {
        string courseName;
        cout << "Enter course name to view grades: ";
        cin >> courseName;

        bool found = false;
        Course* currentCourse = courseListHead;

        while (currentCourse != NULL) {
            for (int i = 0; i < currentCourse->enrollmentCount; i++) {
                if (student->name == currentCourse->enrolledStudents[i] &&
                    currentCourse->name == courseName) {

                    Faculty* faculty = facultyListHead;
                    while (faculty != NULL) {
                        if (faculty->name == currentCourse->facultyName) {
                            cout << "\nGrades for " << currentCourse->name << ":\n";
                            float percentage = faculty->obtainedMarks[i] / faculty->marks[i] * 100.0;
                            cout << "Grade: ";
                            if (percentage >= 80) cout << "A";
                            else if (percentage >= 70) cout << "B";
                            else if (percentage >= 60) cout << "C";
                            else if (percentage > 50) cout << "D";
                            else cout << "F";
                            cout << "\nMarks: " << faculty->obtainedMarks[i] << "/" << faculty->marks[i];
                            cout << " (" << percentage << "%)\n";
                            found = true;
                            break;
                        }
                        faculty = faculty->nextFaculty;
                    }
                    break;
                }
            }
            currentCourse = currentCourse->nextCourse;
        }

        if (!found) cout << "No grade records found.\n";
    }

    void viewFeeChallan(Student* student) {
        student->totalFee = 0;
        cout << "\nFee Details:\n";

        Course* currentCourse = courseListHead;
        while (currentCourse != NULL) {
            for (int i = 0; i < currentCourse->enrollmentCount; i++) {
                if (student->name == currentCourse->enrolledStudents[i]) {
                    cout << currentCourse->name << ": " << currentCourse->fee << endl;
                    student->totalFee += currentCourse->fee;
                }
            }
            currentCourse = currentCourse->nextCourse;
        }

        cout << "Internet fee: 1000\nLibrary fee: 5000\n";
        int choice;
        cout << "1. Avail hostel (20000)\n2. Avail transport (17000)\n";
        cin >> choice;

        if (choice == 1) student->totalFee += 20000;
        else student->totalFee += 17000;

        student->totalFee += 6000; // Internet + Library
        cout << "Total Fee: " << student->totalFee << endl;
    }
};

class FacultyPortal : public StudentPortal {
public:
    void displayFacultyMenu(string facultyName) {
        cout << "\t~~~~~ Welcome to Faculty Portal ~~~~~\n";

        Faculty* currentFaculty = facultyListHead;
        while (currentFaculty != NULL) {
            if (currentFaculty->name == facultyName) {
                displayFacultyInfo(currentFaculty);
                break;
            }
            currentFaculty = currentFaculty->nextFaculty;
        }

        int option;
        do {
            cout << "\n\tFaculty Menu:\n";
            cout << "\t1. View Assigned Courses\n";
            cout << "\t2. View Enrolled Students\n";
            cout << "\t3. Enter Attendance\n";
            cout << "\t4. Enter Grades\n";
            cout << "\t5. Search Students\n";
            cout << "\t6. Log Out\n";
            cin >> option;
            system("cls");

            if (option == 1) viewAssignedCourses(currentFaculty);
            else if (option == 2) viewEnrolledStudents(currentFaculty);
            else if (option == 3) enterAttendance(currentFaculty);
            else if (option == 4) enterGrades(currentFaculty);
            else if (option == 5) searchStudents();
        } while (option != 6);
    }

private:
    void searchStudents() {
        int option;
        cout << "Search students by:\n";
        cout << "1. ID\n2. Name\n3. Department\n";
        cin >> option;
        cin.ignore();

        string query;
        cout << "Enter search term: ";
        getline(cin, query);

        Student* current = studentListHead;
        bool found = false;

        while (current != NULL) {
            if ((option == 1 && current->id == query) ||
                (option == 2 && current->name.find(query) != string::npos) ||
                (option == 3 && current->department.find(query) != string::npos)) {
                displayStudentInfo(current);
                found = true;
            }
            current = current->nextStudent;
        }

        if (!found) cout << "No matching students found.\n";
        cout << endl;
    }

    void viewAssignedCourses(Faculty* faculty) {
        Course* current = courseListHead;
        bool found = false;

        while (current != NULL) {
            if (current->facultyName == faculty->name) {
                cout << "\nAssigned Course: " << current->name;
                cout << "\nID: " << current->id;
                cout << "\nSemester: " << current->courseSemester;
                cout << "\nEnrollment: " << current->enrollmentCount << "/" << MAX_ENROLLMENT << endl;
                found = true;
            }
            current = current->nextCourse;
        }

        if (!found) cout << "No assigned courses found.\n";
    }

    void viewEnrolledStudents(Faculty* faculty) {
        string courseName;
        cout << "Enter course name: ";
        cin >> courseName;

        Course* currentCourse = courseListHead;
        bool found = false;

        while (currentCourse != NULL) {
            if (currentCourse->facultyName == faculty->name && currentCourse->name == courseName) {
                cout << "\nStudents enrolled in " << currentCourse->name << ":\n";
                for (int i = 0; i < currentCourse->enrollmentCount; i++) {
                    cout << (i + 1) << ". " << currentCourse->enrolledStudents[i] << endl;
                }
                found = true;
                break;
            }
            currentCourse = currentCourse->nextCourse;
        }

        if (!found) cout << "No enrolled students found.\n";
    }

    void enterAttendance(Faculty* faculty) {
        string courseName;
        cout << "Enter course name: ";
        cin >> courseName;

        Course* currentCourse = courseListHead;
        bool courseFound = false;

        while (currentCourse != NULL) {
            if (currentCourse->facultyName == faculty->name && currentCourse->name == courseName) {
                courseFound = true;
                cout << "Enter date (DD-MM-YYYY): ";
                cin.ignore();
                getline(cin, faculty->date);
                cout << "Enter slot: ";
                cin >> faculty->slot;

                cout << "\nMark attendance for " << currentCourse->name << ":\n";
                for (int i = 0; i < currentCourse->enrollmentCount; i++) {
                    cout << currentCourse->enrolledStudents[i] << ": (1=Present, 0=Absent) ";
                    cin >> currentCourse->attendance[i];
                }
                cout << "Attendance recorded successfully!\n";
                break;
            }
            currentCourse = currentCourse->nextCourse;
        }

        if (!courseFound) cout << "Course not found.\n";
    }

    void enterGrades(Faculty* faculty) {
        string courseName;
        cout << "Enter course name: ";
        cin >> courseName;

        Course* currentCourse = courseListHead;
        bool courseFound = false;

        while (currentCourse != NULL) {
            if (currentCourse->facultyName == faculty->name && currentCourse->name == courseName) {
                courseFound = true;
                cout << "Enter total marks: ";
                cin >> faculty->marks[0]; // Using first index for all students in this course

                cout << "\nEnter obtained marks for each student:\n";
                for (int i = 0; i < currentCourse->enrollmentCount; i++) {
                    cout << currentCourse->enrolledStudents[i] << ": ";
                    cin >> faculty->obtainedMarks[i];
                }
                cout << "Grades recorded successfully!\n";
                break;
            }
            currentCourse = currentCourse->nextCourse;
        }

        if (!courseFound) cout << "Course not found.\n";
    }
};

// File handling functions
void saveStudentData() {
    ofstream file("Student.txt");
    if (!file) {
        cout << "Error saving student data.\n";
        return;
    }

    Student* current = studentListHead;
    while (current != NULL) {
        file << current->name << "," << current->id << "," << current->cnic << ",";
        file << current->phone << "," << current->department << ",";
        file << current->batch << "," << current->semester << "\n";
        current = current->nextStudent;
    }
    file.close();
}

void saveFacultyData() {
    ofstream file("Faculty.txt");
    if (!file) {
        cout << "Error saving faculty data.\n";
        return;
    }

    Faculty* current = facultyListHead;
    while (current != NULL) {
        file << current->name << "," << current->id << "," << current->cnic << ",";
        file << current->phone << "," << current->office << "\n";
        current = current->nextFaculty;
    }
    file.close();
}

void saveCourseData() {
    ofstream file("Course.txt");
    if (!file) {
        cout << "Error saving course data.\n";
        return;
    }

    Course* current = courseListHead;
    while (current != NULL) {
        file << current->name << "," << current->id << "," << current->facultyName << ",";
        file << current->courseSemester << "," << current->creditHours << ",";
        file << current->fee << "," << current->year << "," << current->enrollmentCount;

        for (int i = 0; i < current->enrollmentCount; i++) {
            file << "," << current->enrolledStudents[i];
        }
        file << "\n";
        current = current->nextCourse;
    }
    file.close();
}

void loadData() {
    // Load student data
    ifstream studentFile("Student.txt");
    if (studentFile) {
        string line;
        while (getline(studentFile, line)) {
            stringstream ss(line);
            string token;
            vector<string> tokens;

            while (getline(ss, token, ',')) {
                tokens.push_back(token);
            }

            if (tokens.size() == 7) {
                Student* newStudent = new Student;
                newStudent->name = tokens[0];
                newStudent->id = tokens[1];
                newStudent->cnic = stoi(tokens[2]);
                newStudent->phone = stoi(tokens[3]);
                newStudent->department = tokens[4];
                newStudent->batch = tokens[5];
                newStudent->semester = stoi(tokens[6]);
                newStudent->nextStudent = NULL;

                if (studentListHead == NULL) {
                    studentListHead = newStudent;
                }
                else {
                    Student* current = studentListHead;
                    while (current->nextStudent != NULL)
                        current = current->nextStudent;
                    current->nextStudent = newStudent;
                }
            }
        }
        studentFile.close();
    }

    // Load faculty data
    ifstream facultyFile("Faculty.txt");
    if (facultyFile) {
        string line;
        while (getline(facultyFile, line)) {
            stringstream ss(line);
            string token;
            vector<string> tokens;

            while (getline(ss, token, ',')) {
                tokens.push_back(token);
            }

            if (tokens.size() == 5) {
                Faculty* newFaculty = new Faculty;
                newFaculty->name = tokens[0];
                newFaculty->id = tokens[1];
                newFaculty->cnic = stoi(tokens[2]);
                newFaculty->phone = stoi(tokens[3]);
                newFaculty->office = tokens[4];
                newFaculty->nextFaculty = NULL;

                if (facultyListHead == NULL) {
                    facultyListHead = newFaculty;
                }
                else {
                    Faculty* current = facultyListHead;
                    while (current->nextFaculty != NULL)
                        current = current->nextFaculty;
                    current->nextFaculty = newFaculty;
                }
            }
        }
        facultyFile.close();
    }

    // Load course data
    ifstream courseFile("Course.txt");
    if (courseFile) {
        string line;
        while (getline(courseFile, line)) {
            stringstream ss(line);
            string token;
            vector<string> tokens;

            while (getline(ss, token, ',')) {
                tokens.push_back(token);
            }

            if (tokens.size() >= 8) {
                Course* newCourse = new Course;
                newCourse->name = tokens[0];
                newCourse->id = tokens[1];
                newCourse->facultyName = tokens[2];
                newCourse->courseSemester = stoi(tokens[3]);
                newCourse->creditHours = stoi(tokens[4]);
                newCourse->fee = stoi(tokens[5]);
                newCourse->year = tokens[6];
                newCourse->enrollmentCount = stoi(tokens[7]);

                for (int i = 0; i < newCourse->enrollmentCount; i++) {
                    if (i + 8 < tokens.size()) {
                        newCourse->enrolledStudents[i] = tokens[i + 8];
                    }
                }
                newCourse->nextCourse = NULL;

                if (courseListHead == NULL) {
                    courseListHead = newCourse;
                }
                else {
                    Course* current = courseListHead;
                    while (current->nextCourse != NULL)
                        current = current->nextCourse;
                    current->nextCourse = newCourse;
                }
            }
        }
        courseFile.close();
    }
}

int main() {
    loadData(); // Load existing data at startup

    FacultyPortal system;
    int option;

    do {
        cout << "\t********** UNIVERSITY MANAGEMENT SYSTEM **********\n";
        cout << "\t1. Login as Admin\n";
        cout << "\t2. Login as Student\n";
        cout << "\t3. Login as Faculty\n";
        cout << "\t4. Exit\n";
        cout << "Enter choice: ";
        cin >> option;
        
        if (option == 1) {
            string username;
            cout << "Enter admin username: ";
            cin.ignore();
            getline(cin, username);

            if (username == "admin") {
                system.displayAdminMenu();
            }
            else {
                cout << "Invalid admin username.\n";
            }
        }
        else if (option == 2) {
            string username;
            cout << "Enter student name: ";
            cin.ignore();
            getline(cin, username);

            if (system.authenticate(username, 1)) {
                system.displayStudentMenu(username);
            }
            else {
                cout << "Student not found.\n";
            }
        }
        else if (option == 3) {
            string username;
            cout << "Enter faculty name: ";
            cin.ignore();
            getline(cin, username);

            if (system.authenticate(username, 2)) {
                system.displayFacultyMenu(username);
            }
            else {
                cout << "Faculty not found.\n";
            }
        }

        if (option != 4) {
            cout << "\n";
            printSeparator();
        }
    } while (option != 4);

    saveStudentData();
    saveFacultyData();
    saveCourseData();

    cout << "Data saved. Exiting system...\n";
    return 0;
}