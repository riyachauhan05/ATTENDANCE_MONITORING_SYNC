#include <iostream>
#include <vector>
#include <string>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50
#define MAX_DAYS 5 // Number of days to store attendance

// Structure to represent a student
struct Student {
    int id;
    std::string name;
    bool isPresent;
};

// Function to mark attendance for multiple students
void markAttendance(std::vector<Student>& students) {
    int numStudents;
    std::cout << "Enter the number of students attending: ";
    std::cin >> numStudents;

    for (int i = 0; i < numStudents; i++) {
        int studentId;
        std::cout << "Enter student ID: ";
        std::cin >> studentId;

        for (auto& student : students) {
            if (student.id == studentId) {
                student.isPresent = true;
                std::cout << "Attendance marked for student ID " << studentId << std::endl;
                break;
            }
        }
    }
}

// Function to display attendance report
void displayAttendance(const std::vector<Student>& students) {
    std::cout << "Attendance Report:" << std::endl;
    std::cout << "------------------" << std::endl;

    for (const auto& student : students) {
        std::cout << "Student ID: " << student.id << "\tName: " << student.name << "\t\t";
        if (student.isPresent) {
            std::cout << "Present" << std::endl;
        } else {
            std::cout << "Absent" << std::endl;
        }
    }
}

int main() {
    std::vector<Student> students;
    int numStudents;

    std::cout << "Enter the number of students: ";
    std::cin >> numStudents;

    if (numStudents > MAX_STUDENTS) {
        std::cout << "Maximum number of students exceeded. Please re-run the program with a smaller number." << std::endl;
        return 1;
    }

    // Read student information
    for (int i = 0; i < numStudents; i++) {
        Student student;
        std::cout << "Enter details for Student " << i + 1 << ":" << std::endl;
        std::cout << "ID: ";
        std::cin >> student.id;
        std::cout << "Name: ";
        std::cin.ignore();
        std::getline(std::cin, student.name);
        student.isPresent = false;
        students.push_back(student);
    }

    // Array to store attendance for the last few days
    bool attendanceHistory[MAX_DAYS][MAX_STUDENTS] = {false};

    int choice;
    do {
        std::cout << "\nAttendance Monitoring System" << std::endl;
        std::cout << "1. Mark Attendance" << std::endl;
        std::cout << "2. Display Attendance Report" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                markAttendance(students);

                // Update attendance history
                for (int i = 0; i < numStudents; i++) {
                    attendanceHistory[MAX_DAYS - 1][i] = students[i].isPresent;
                }

                // Shift attendance history to store the last few days
                for (int day = 0; day < MAX_DAYS - 1; day++) {
                    for (int i = 0; i < numStudents; i++) {
                        attendanceHistory[day][i] = attendanceHistory[day + 1][i];
                    }
                }

                // Reset isPresent flag for the next day's attendance
                for (auto& student : students) {
                    student.isPresent = false;
                }
                break;
            case 2:
                displayAttendance(students);

                // Display attendance history for the last few days
                std::cout << "\nAttendance History (Last " << MAX_DAYS << " Days):" << std::endl;
                for (int day = 0; day < MAX_DAYS; day++) {
                    std::cout << "Day " << day + 1 << ": ";
                    for (int i = 0; i < numStudents; i++) {
                        std::cout << (attendanceHistory[day][i] ? "P " : "A ");
                    }
                    std::cout << std::endl;
                }
                break;
            case 3:
                std::cout << "Exiting program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    } while (choice != 3);

    return 0;
}