#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#define CLEAR_SCREEN "cls"

// Constants
#define MAX_USERNAME 21
#define MAX_PASSWORD 51
#define MAX_NAME 51
#define MAX_ROLL 21
#define MAX_COURSE_CODE 20
#define MAX_MARKS 20
#define MAX_INPUT 100

// Structures
struct Admin{
    char user[MAX_USERNAME];
    char pass[MAX_PASSWORD];
};

struct Student{
    char user[MAX_USERNAME];
    char pass[MAX_PASSWORD];
    char roll[MAX_ROLL];
    char name[MAX_NAME];
};

struct Teacher{
    char user[MAX_USERNAME];
    char pass[MAX_PASSWORD];
    char name[MAX_NAME];
};

struct Marks{
    char user[MAX_USERNAME];
    char cc[MAX_COURSE_CODE];
    char marks[MAX_MARKS];
};

struct CourseAssignment{
    char teacher_user[MAX_USERNAME];
    char course_code[MAX_COURSE_CODE];
};

// Global variables
static char current_student_user[MAX_USERNAME] = {0};
static char current_teacher_user[MAX_USERNAME] = {0};

// Utility functions
void clear_screen(void) {
    system(CLEAR_SCREEN);
}

void pause_screen(void) {
    printf("\nPress any key to continue...");
    getch();
}

void safe_input(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        // Remove newline if present
        char *newline = strchr(buffer, '\n');
        if (newline) *newline = '\0';
    }
}

void flush_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int validate_string(const char *str) {
    return str != NULL && strlen(str) > 0;
}

// File operations with error checking
int safe_file_write(const char *filename, const void *data, size_t size) {
    FILE *fp = fopen(filename, "ab");
    if (!fp) return 0;
    
    size_t written = fwrite(data, size, 1, fp);
    fclose(fp);
    return written == 1;
}

// Admin functions
int check_admin_credentials(const char *username, const char *password) {
    if (!validate_string(username) || !validate_string(password)) {
        return 0;
    }
    
    FILE *fp = fopen("admin.txt", "rb");
    if (!fp) {
        // First time setup
        struct Admin admin;
        strncpy(admin.user, username, MAX_USERNAME - 1);
        strncpy(admin.pass, password, MAX_PASSWORD - 1);
        admin.user[MAX_USERNAME - 1] = '\0';
        admin.pass[MAX_PASSWORD - 1] = '\0';
        
        if (safe_file_write("admin.txt", &admin, sizeof(struct Admin))) {
            printf("\nNew admin credentials set successfully!\n");
            pause_screen();
            return 1;
        }
        return 0;
    }
    
    struct Admin admin;
    int found = 0;
    while (fread(&admin, sizeof(struct Admin), 1, fp)) {
        if (strcmp(admin.user, username) == 0 && strcmp(admin.pass, password) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fp);
    return found;
}

int add_teacher(void) {
    clear_screen();
    struct Teacher teacher = {0};
    
    printf("=== Add Teacher ===\n\n");
    printf("Username: ");
    safe_input(teacher.user, MAX_USERNAME);
    
    if (!validate_string(teacher.user)) {
        printf("Invalid username!\n");
        pause_screen();
        return 0;
    }
    
    printf("Password: ");
    safe_input(teacher.pass, MAX_PASSWORD);
    
    printf("Full Name: ");
    safe_input(teacher.name, MAX_NAME);
    
    if (safe_file_write("teacher.txt", &teacher, sizeof(struct Teacher))) {
        printf("\nTeacher added successfully!\n");
    } else {
        printf("\nError adding teacher!\n");
    }
    
    pause_screen();
    return 1;
}

int add_student(void) {
    clear_screen();
    struct Student student = {0};
    
    printf("=== Add Student ===\n\n");
    printf("Username: ");
    safe_input(student.user, MAX_USERNAME);
    
    if (!validate_string(student.user)) {
        printf("Invalid username!\n");
        pause_screen();
        return 0;
    }
    
    printf("Password: ");
    safe_input(student.pass, MAX_PASSWORD);
    
    printf("Full Name: ");
    safe_input(student.name, MAX_NAME);
    
    printf("Roll Number: ");
    safe_input(student.roll, MAX_ROLL);
    
    if (safe_file_write("student.txt", &student, sizeof(struct Student))) {
        printf("\nStudent added successfully!\n");
    } else {
        printf("\nError adding student!\n");
    }
    
    pause_screen();
    return 1;
}

int update_teacher(void) {
    clear_screen();
    char username[MAX_USERNAME];
    
    printf("=== Update Teacher ===\n\n");
    printf("Enter teacher's username: ");
    safe_input(username, MAX_USERNAME);
    
    FILE *fp = fopen("teacher.txt", "r+b");
    if (!fp) {
        printf("Error opening teacher file!\n");
        pause_screen();
        return 0;
    }
    
    struct Teacher teacher;
    int found = 0;
    long position;
    
    while ((position = ftell(fp)) >= 0 && fread(&teacher, sizeof(struct Teacher), 1, fp)) {
        if (strcmp(teacher.user, username) == 0) {
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("Teacher not found!\n");
        fclose(fp);
        pause_screen();
        return 0;
    }
    
    struct Teacher new_teacher = {0};
    printf("\nEnter new information:\n");
    printf("Username: ");
    safe_input(new_teacher.user, MAX_USERNAME);
    printf("Password: ");
    safe_input(new_teacher.pass, MAX_PASSWORD);
    printf("Full Name: ");
    safe_input(new_teacher.name, MAX_NAME);
    
    fseek(fp, position, SEEK_SET);
    if (fwrite(&new_teacher, sizeof(struct Teacher), 1, fp) == 1) {
        printf("\nTeacher updated successfully!\n");
    } else {
        printf("\nError updating teacher!\n");
    }
    
    fclose(fp);
    pause_screen();
    return 1;
}

int update_student(void) {
    clear_screen();
    char username[MAX_USERNAME];
    
    printf("=== Update Student ===\n\n");
    printf("Enter student's username: ");
    safe_input(username, MAX_USERNAME);
    
    FILE *fp = fopen("student.txt", "r+b");
    if (!fp) {
        printf("Error opening student file!\n");
        pause_screen();
        return 0;
    }
    
    struct Student student;
    int found = 0;
    long position;
    
    while ((position = ftell(fp)) >= 0 && fread(&student, sizeof(struct Student), 1, fp)) {
        if (strcmp(student.user, username) == 0) {
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("Student not found!\n");
        fclose(fp);
        pause_screen();
        return 0;
    }
    
    struct Student new_student = {0};
    printf("\nEnter new information:\n");
    printf("Username: ");
    safe_input(new_student.user, MAX_USERNAME);
    printf("Password: ");
    safe_input(new_student.pass, MAX_PASSWORD);
    printf("Full Name: ");
    safe_input(new_student.name, MAX_NAME);
    printf("Roll Number: ");
    safe_input(new_student.roll, MAX_ROLL);
    
    fseek(fp, position, SEEK_SET);
    if (fwrite(&new_student, sizeof(struct Student), 1, fp) == 1) {
        printf("\nStudent updated successfully!\n");
    } else {
        printf("\nError updating student!\n");
    }
    
    fclose(fp);
    pause_screen();
    return 1;
}

int assign_course(void) {
    clear_screen();
    struct CourseAssignment assignment = {0};
    
    printf("=== Assign Course ===\n\n");
    printf("Teacher's username: ");
    safe_input(assignment.teacher_user, MAX_USERNAME);
    
    // Verify teacher exists
    FILE *fp = fopen("teacher.txt", "rb");
    if (!fp) {
        printf("Error opening teacher file!\n");
        pause_screen();
        return 0;
    }
    
    struct Teacher teacher;
    int teacher_found = 0;
    while (fread(&teacher, sizeof(struct Teacher), 1, fp)) {
        if (strcmp(teacher.user, assignment.teacher_user) == 0) {
            teacher_found = 1;
            break;
        }
    }
    fclose(fp);
    
    if (!teacher_found) {
        printf("Teacher not found!\n");
        pause_screen();
        return 0;
    }
    
    printf("Course code: ");
    safe_input(assignment.course_code, MAX_COURSE_CODE);
    
    if (safe_file_write("course.txt", &assignment, sizeof(struct CourseAssignment))) {
        printf("\nCourse assigned successfully!\n");
    } else {
        printf("\nError assigning course!\n");
    }
    
    pause_screen();
    return 1;
}

int delete_teacher(void) {
    clear_screen();
    char username[MAX_USERNAME];
    
    printf("=== Delete Teacher ===\n\n");
    printf("Enter teacher's username to delete: ");
    safe_input(username, MAX_USERNAME);
    
    FILE *fp = fopen("teacher.txt", "rb");
    if (!fp) {
        printf("Error opening teacher file!\n");
        pause_screen();
        return 0;
    }
    
    FILE *temp_fp = fopen("temp_teacher.txt", "wb");
    if (!temp_fp) {
        printf("Error creating temporary file!\n");
        fclose(fp);
        pause_screen();
        return 0;
    }
    
    struct Teacher teacher;
    int found = 0;
    int count = 0;
    
    while (fread(&teacher, sizeof(struct Teacher), 1, fp)) {
        if (strcmp(teacher.user, username) != 0) {
            fwrite(&teacher, sizeof(struct Teacher), 1, temp_fp);
            count++;
        } else {
            found = 1;
        }
    }
    
    fclose(fp);
    fclose(temp_fp);
    
    if (found) {
        remove("teacher.txt");
        rename("temp_teacher.txt", "teacher.txt");
        printf("\nTeacher deleted successfully!\n");
        
        // Also remove course assignments for this teacher
        fp = fopen("course.txt", "rb");
        if (fp) {
            temp_fp = fopen("temp_course.txt", "wb");
            if (temp_fp) {
                struct CourseAssignment assignment;
                while (fread(&assignment, sizeof(struct CourseAssignment), 1, fp)) {
                    if (strcmp(assignment.teacher_user, username) != 0) {
                        fwrite(&assignment, sizeof(struct CourseAssignment), 1, temp_fp);
                    }
                }
                fclose(fp);
                fclose(temp_fp);
                remove("course.txt");
                rename("temp_course.txt", "course.txt");
                printf("Associated course assignments also removed.\n");
            } else {
                fclose(fp);
            }
        }
    } else {
        remove("temp_teacher.txt");
        printf("Teacher not found!\n");
    }
    
    pause_screen();
    return found;
}

int delete_student(void) {
    clear_screen();
    char username[MAX_USERNAME];
    
    printf("=== Delete Student ===\n\n");
    printf("Enter student's username to delete: ");
    safe_input(username, MAX_USERNAME);
    
    FILE *fp = fopen("student.txt", "rb");
    if (!fp) {
        printf("Error opening student file!\n");
        pause_screen();
        return 0;
    }
    
    FILE *temp_fp = fopen("temp_student.txt", "wb");
    if (!temp_fp) {
        printf("Error creating temporary file!\n");
        fclose(fp);
        pause_screen();
        return 0;
    }
    
    struct Student student;
    int found = 0;
    
    while (fread(&student, sizeof(struct Student), 1, fp)) {
        if (strcmp(student.user, username) != 0) {
            fwrite(&student, sizeof(struct Student), 1, temp_fp);
        } else {
            found = 1;
        }
    }
    
    fclose(fp);
    fclose(temp_fp);
    
    if (found) {
        remove("student.txt");
        rename("temp_student.txt", "student.txt");
        printf("\nStudent deleted successfully!\n");
        
        // Also remove marks for this student
        fp = fopen("marks.txt", "rb");
        if (fp) {
            temp_fp = fopen("temp_marks.txt", "wb");
            if (temp_fp) {
                struct Marks marks;
                while (fread(&marks, sizeof(struct Marks), 1, fp)) {
                    if (strcmp(marks.user, username) != 0) {
                        fwrite(&marks, sizeof(struct Marks), 1, temp_fp);
                    }
                }
                fclose(fp);
                fclose(temp_fp);
                remove("marks.txt");
                rename("temp_marks.txt", "marks.txt");
                printf("Associated marks also removed.\n");
            } else {
                fclose(fp);
            }
        }
    } else {
        remove("temp_student.txt");
        printf("Student not found!\n");
    }
    
    pause_screen();
    return found;
}

int update_course(void) {
    clear_screen();
    char teacher_username[MAX_USERNAME];
    char prev_course[MAX_COURSE_CODE];
    
    printf("=== Update Course Assignment ===\n\n");
    printf("Teacher's username: ");
    safe_input(teacher_username, MAX_USERNAME);
    
    printf("Previous course code to update: ");
    safe_input(prev_course, MAX_COURSE_CODE);
    
    FILE *fp = fopen("course.txt", "r+b");
    if (!fp) {
        printf("Error opening course file!\n");
        pause_screen();
        return 0;
    }
    
    struct CourseAssignment assignment;
    int found = 0;
    long position;
    
    while ((position = ftell(fp)) >= 0 && fread(&assignment, sizeof(struct CourseAssignment), 1, fp)) {
        if (strcmp(assignment.teacher_user, teacher_username) == 0 && 
            strcmp(assignment.course_code, prev_course) == 0) {
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("Course assignment not found for teacher '%s' with course '%s'!\n", 
               teacher_username, prev_course);
        fclose(fp);
        pause_screen();
        return 0;
    }
    
    struct CourseAssignment new_assignment;
    strncpy(new_assignment.teacher_user, teacher_username, MAX_USERNAME - 1);
    new_assignment.teacher_user[MAX_USERNAME - 1] = '\0';
    
    printf("\nEnter new course code: ");
    safe_input(new_assignment.course_code, MAX_COURSE_CODE);
    
    fseek(fp, position, SEEK_SET);
    if (fwrite(&new_assignment, sizeof(struct CourseAssignment), 1, fp) == 1) {
        printf("\nCourse assignment updated successfully!\n");
        printf("Changed from '%s' to '%s' for teacher '%s'\n", 
               prev_course, new_assignment.course_code, teacher_username);
    } else {
        printf("\nError updating course assignment!\n");
    }
    
    fclose(fp);
    pause_screen();
    return 1;
}

void admin_panel(void) {
    int choice;
    
    do {
        clear_screen();
        printf("============================================\n");
        printf("           ADMIN PANEL\n");
        printf("============================================\n\n");
        printf("1. Add Teacher\n");
        printf("2. Add Student\n");
        printf("3. Update Teacher\n");
        printf("4. Update Student\n");
        printf("5. Delete Teacher\n");
        printf("6. Delete Student\n");
        printf("7. Assign Course\n");
        printf("8. Update Course Assignment\n");
        printf("9. Return to Main Menu\n\n");
        printf("Enter your choice (1-9): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            flush_input();
            pause_screen();
            continue;
        }
        flush_input();
        
        switch (choice) {
            case 1: add_teacher(); break;
            case 2: add_student(); break;
            case 3: update_teacher(); break;
            case 4: update_student(); break;
            case 5: delete_teacher(); break;
            case 6: delete_student(); break;
            case 7: assign_course(); break;
            case 8: update_course(); break;
            case 9: return;
            default:
                printf("Invalid choice!\n");
                pause_screen();
        }
    } while (choice != 9);
}

int admin_login(void) {
    clear_screen();
    char username[MAX_USERNAME], password[MAX_PASSWORD];
    
    printf("=== ADMIN LOGIN ===\n\n");
    printf("Username: ");
    safe_input(username, MAX_USERNAME);
    
    printf("Password: ");
    safe_input(password, MAX_PASSWORD);
    
    if (check_admin_credentials(username, password)) {
        admin_panel();
        return 1;
    } else {
        printf("\nInvalid credentials!\n");
        pause_screen();
        return 0;
    }
}

// Teacher functions
int teacher_exists(const char *username) {
    FILE *fp = fopen("teacher.txt", "rb");
    if (!fp) return 0;
    
    struct Teacher teacher;
    while (fread(&teacher, sizeof(struct Teacher), 1, fp)) {
        if (strcmp(teacher.user, username) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int is_course_assigned(const char *teacher_user, const char *course_code) {
    FILE *fp = fopen("course.txt", "rb");
    if (!fp) return 0;
    
    struct CourseAssignment assignment;
    while (fread(&assignment, sizeof(struct CourseAssignment), 1, fp)) {
        if (strcmp(assignment.teacher_user, teacher_user) == 0 && 
            strcmp(assignment.course_code, course_code) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int update_ct_marks(void) {
    clear_screen();
    char student_username[MAX_USERNAME];
    char course_code[MAX_COURSE_CODE];
    
    printf("=== Update CT Marks ===\n\n");
    printf("Course code: ");
    safe_input(course_code, MAX_COURSE_CODE);
    
    if (!is_course_assigned(current_teacher_user, course_code)) {
        printf("You are not assigned to this course!\n");
        pause_screen();
        return 0;
    }
    
    printf("Student username: ");
    safe_input(student_username, MAX_USERNAME);
    
    // Verify student exists
    FILE *fp = fopen("student.txt", "rb");
    if (!fp) {
        printf("Error opening student file!\n");
        pause_screen();
        return 0;
    }
    
    struct Student student;
    int student_found = 0;
    while (fread(&student, sizeof(struct Student), 1, fp)) {
        if (strcmp(student.user, student_username) == 0) {
            student_found = 1;
            break;
        }
    }
    fclose(fp);
    
    if (!student_found) {
        printf("Student not found!\n");
        pause_screen();
        return 0;
    }
    
    // Find and update marks
    fp = fopen("marks.txt", "r+b");
    if (!fp) {
        printf("Error opening marks file!\n");
        pause_screen();
        return 0;
    }
    
    struct Marks marks;
    int found = 0;
    long position;
    
    while ((position = ftell(fp)) >= 0 && fread(&marks, sizeof(struct Marks), 1, fp)) {
        if (strcmp(marks.user, student_username) == 0 && 
            strcmp(marks.cc, course_code) == 0) {
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("No existing marks found for student '%s' in course '%s'!\n", 
               student_username, course_code);
        fclose(fp);
        pause_screen();
        return 0;
    }
    
    printf("\nCurrent marks for %s in %s: %s\n", student_username, course_code, marks.marks);
    printf("Enter new marks: ");
    safe_input(marks.marks, MAX_MARKS);
    
    fseek(fp, position, SEEK_SET);
    if (fwrite(&marks, sizeof(struct Marks), 1, fp) == 1) {
        printf("\nMarks updated successfully!\n");
    } else {
        printf("\nError updating marks!\n");
    }
    
    fclose(fp);
    pause_screen();
    return 1;
}

int find_student_by_roll(void) {
    clear_screen();
    char search_roll[MAX_ROLL];
    
    printf("=== Find Student by Roll Number ===\n\n");
    printf("Enter roll number: ");
    safe_input(search_roll, MAX_ROLL);
    
    FILE *fp = fopen("student.txt", "rb");
    if (!fp) {
        printf("Error opening student file!\n");
        pause_screen();
        return 0;
    }
    
    struct Student student;
    int found = 0;
    
    while (fread(&student, sizeof(struct Student), 1, fp)) {
        if (strcmp(student.roll, search_roll) == 0) {
            printf("\n--- Student Found ---\n");
            printf("Username: %s\n", student.user);
            printf("Name: %s\n", student.name);
            printf("Roll No: %s\n", student.roll);
            printf("--------------------\n");
            
            // Also show marks for this student
            FILE *marks_fp = fopen("marks.txt", "rb");
            if (marks_fp) {
                struct Marks marks;
                int marks_count = 0;
                printf("\nMarks:\n");
                printf("%-15s %-10s\n", "Course Code", "Marks");
                printf("-------------------------\n");
                
                while (fread(&marks, sizeof(struct Marks), 1, marks_fp)) {
                    if (strcmp(marks.user, student.user) == 0) {
                        printf("%-15s %-10s\n", marks.cc, marks.marks);
                        marks_count++;
                    }
                }
                
                if (marks_count == 0) {
                    printf("No marks recorded.\n");
                }
                
                fclose(marks_fp);
            }
            
            found = 1;
            break;
        }
    }
    fclose(fp);
    
    if (!found) {
        printf("No student found with roll number '%s'\n", search_roll);
    }
    
    pause_screen();
    return found;
}

int add_ct_marks(void) {
    clear_screen();
    struct Marks marks = {0};
    
    printf("=== Add CT Marks ===\n\n");
    printf("Course code: ");
    safe_input(marks.cc, MAX_COURSE_CODE);
    
    if (!is_course_assigned(current_teacher_user, marks.cc)) {
        printf("You are not assigned to this course!\n");
        pause_screen();
        return 0;
    }
    
    printf("Student username: ");
    safe_input(marks.user, MAX_USERNAME);
    
    // Verify student exists
    FILE *fp = fopen("student.txt", "rb");
    if (!fp) {
        printf("Error opening student file!\n");
        pause_screen();
        return 0;
    }
    
    struct Student student;
    int student_found = 0;
    while (fread(&student, sizeof(struct Student), 1, fp)) {
        if (strcmp(student.user, marks.user) == 0) {
            student_found = 1;
            break;
        }
    }
    fclose(fp);
    
    if (!student_found) {
        printf("Student not found!\n");
        pause_screen();
        return 0;
    }
    
    printf("Marks: ");
    safe_input(marks.marks, MAX_MARKS);
    
    if (safe_file_write("marks.txt", &marks, sizeof(struct Marks))) {
        printf("\nMarks added successfully!\n");
    } else {
        printf("\nError adding marks!\n");
    }
    
    pause_screen();
    return 1;
}

int find_student_info(void) {
    clear_screen();
    char search_name[MAX_NAME];
    
    printf("=== Find Student Information ===\n\n");
    printf("Enter student's name (partial match allowed): ");
    safe_input(search_name, MAX_NAME);
    
    FILE *fp = fopen("student.txt", "rb");
    if (!fp) {
        printf("Error opening student file!\n");
        pause_screen();
        return 0;
    }
    
    struct Student student;
    int count = 0;
    
    printf("\n--- Search Results ---\n");
    while (fread(&student, sizeof(struct Student), 1, fp)) {
        if (strstr(student.name, search_name) != NULL) {
            printf("\nUsername: %s\n", student.user);
            printf("Name: %s\n", student.name);
            printf("Roll No: %s\n", student.roll);
            printf("-------------------------\n");
            count++;
        }
    }
    fclose(fp);
    
    if (count == 0) {
        printf("No students found matching '%s'\n", search_name);
    } else {
        printf("\nTotal students found: %d\n", count);
    }
    
    pause_screen();
    return 1;
}

int count_total_students(void) {
    clear_screen();
    
    FILE *fp = fopen("student.txt", "rb");
    if (!fp) {
        printf("Error opening student file!\n");
        pause_screen();
        return 0;
    }
    
    struct Student student;
    int count = 0;
    
    while (fread(&student, sizeof(struct Student), 1, fp)) {
        count++;
    }
    fclose(fp);
    
    printf("=== Student Statistics ===\n\n");
    printf("Total number of students: %d\n", count);
    
    pause_screen();
    return 1;
}

void teacher_panel(void) {
    int choice;
    
    do {
        clear_screen();
        printf("============================================\n");
        printf("           TEACHER PANEL\n");
        printf("============================================\n");
        printf("Welcome, %s!\n\n", current_teacher_user);
        printf("1. Add CT Marks\n");
        printf("2. Update CT Marks\n");
        printf("3. Find Student by Name\n");
        printf("4. Find Student by Roll Number\n");
        printf("5. Count Total Students\n");
        printf("6. Return to Main Menu\n\n");
        printf("Enter your choice (1-6): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            flush_input();
            pause_screen();
            continue;
        }
        flush_input();
        
        switch (choice) {
            case 1: add_ct_marks(); break;
            case 2: update_ct_marks(); break;
            case 3: find_student_info(); break;
            case 4: find_student_by_roll(); break;
            case 5: count_total_students(); break;
            case 6: return;
            default:
                printf("Invalid choice!\n");
                pause_screen();
        }
    } while (choice != 6);
}

int teacher_login(void) {
    clear_screen();
    char username[MAX_USERNAME], password[MAX_PASSWORD];
    
    printf("=== TEACHER LOGIN ===\n\n");
    printf("Username: ");
    safe_input(username, MAX_USERNAME);
    
    printf("Password: ");
    safe_input(password, MAX_PASSWORD);
    
    FILE *fp = fopen("teacher.txt", "rb");
    if (!fp) {
        printf("Error opening teacher file!\n");
        pause_screen();
        return 0;
    }
    
    struct Teacher teacher;
    int authenticated = 0;
    
    while (fread(&teacher, sizeof(struct Teacher), 1, fp)) {
        if (strcmp(teacher.user, username) == 0 && 
            strcmp(teacher.pass, password) == 0) {
            strncpy(current_teacher_user, teacher.user, MAX_USERNAME - 1);
            current_teacher_user[MAX_USERNAME - 1] = '\0';
            authenticated = 1;
            break;
        }
    }
    fclose(fp);
    
    if (authenticated) {
        teacher_panel();
        return 1;
    } else {
        printf("\nInvalid credentials!\n");
        pause_screen();
        return 0;
    }
}

// Student functions
int show_ct_marks(void) {
    clear_screen();
    
    printf("=== Your CT Marks ===\n\n");
    
    FILE *fp = fopen("marks.txt", "rb");
    if (!fp) {
        printf("No marks file found!\n");
        pause_screen();
        return 0;
    }
    
    struct Marks marks;
    int count = 0;
    
    printf("%-15s %-10s\n", "Course Code", "Marks");
    printf("-------------------------\n");
    
    while (fread(&marks, sizeof(struct Marks), 1, fp)) {
        if (strcmp(marks.user, current_student_user) == 0) {
            printf("%-15s %-10s\n", marks.cc, marks.marks);
            count++;
        }
    }
    fclose(fp);
    
    if (count == 0) {
        printf("No marks found for your account.\n");
    } else {
        printf("\nTotal entries: %d\n", count);
    }
    
    pause_screen();
    return 1;
}

void student_panel(void) {
    int choice;
    
    do {
        clear_screen();
        printf("============================================\n");
        printf("           STUDENT PANEL\n");
        printf("============================================\n");
        printf("Welcome, %s!\n\n", current_student_user);
        printf("1. View CT Marks\n");
        printf("2. Return to Main Menu\n\n");
        printf("Enter your choice (1-2): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            flush_input();
            pause_screen();
            continue;
        }
        flush_input();
        
        switch (choice) {
            case 1: show_ct_marks(); break;
            case 2: return;
            default:
                printf("Invalid choice!\n");
                pause_screen();
        }
    } while (choice != 2);
}

int student_login(void) {
    clear_screen();
    char username[MAX_USERNAME], password[MAX_PASSWORD];
    
    printf("=== STUDENT LOGIN ===\n\n");
    printf("Username: ");
    safe_input(username, MAX_USERNAME);
    
    printf("Password: ");
    safe_input(password, MAX_PASSWORD);
    
    FILE *fp = fopen("student.txt", "rb");
    if (!fp) {
        printf("Error opening student file!\n");
        pause_screen();
        return 0;
    }
    
    struct Student student;
    int authenticated = 0;
    
    while (fread(&student, sizeof(struct Student), 1, fp)) {
        if (strcmp(student.user, username) == 0 && 
            strcmp(student.pass, password) == 0) {
            strncpy(current_student_user, student.user, MAX_USERNAME - 1);
            current_student_user[MAX_USERNAME - 1] = '\0';
            authenticated = 1;
            break;
        }
    }
    fclose(fp);
    
    if (authenticated) {
        student_panel();
        return 1;
    } else {
        printf("\nInvalid credentials!\n");
        pause_screen();
        return 0;
    }
}

int main(void) {
    int choice;
    
    do {
        clear_screen();
        printf("================================================\n");
        printf("        CLASS MANAGEMENT SYSTEM\n");
        printf("================================================\n\n");
        printf("1. Admin Login\n");
        printf("2. Teacher Login\n");
        printf("3. Student Login\n");
        printf("4. Exit\n\n");
        printf("Enter your choice (1-4): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            flush_input();
            pause_screen();
            continue;
        }
        flush_input();
        
        switch (choice) {
            case 1: admin_login(); break;
            case 2: teacher_login(); break;
            case 3: student_login(); break;
            case 4: 
                clear_screen();
                printf("Thank you for using Class Management System!\n");
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Please select 1-4.\n");
                pause_screen();
        }
    } while (choice != 4);
    
    return 0;
}