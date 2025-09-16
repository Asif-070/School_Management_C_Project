#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <conio.h>

struct admin{
    char user[21],pass[21];
};

struct student{
    char user[21],pass[51],roll[21],name[51];
};

struct teacher{
    char user[21],pass[51],name[51];
};

struct marks{
    char user[21],cc[20],marks[20];
};

char studuser[50];
char teachuser[50];

// For checking admin username & password
int check_admin(char us[20], char pa[20]){
    struct admin a;
    strcpy(a.user,us);
    strcpy(a.pass,pa);
    int y = 0;
    FILE *fp;
    fp = fopen("admin.txt", "r");
    if(fp == NULL){
		// for first time login
		fclose(fp);
		fp = fopen("admin.txt","w");
		fwrite(&a,sizeof(a),1,fp);
		fclose(fp);
		printf("\nNew Username & Password is Set.. Press Any Button to continue.. \n");
		getch();
        y = 1;
        return y;
	}
    else{
        struct admin a1;
        while(fread(&a1,sizeof(a1),1,fp)){
            if(strcmp(a1.user,a.user)==0 && strcmp(a1.pass,a.pass)==0){
                    y = 1;
                    break;
            }
        }
        fclose(fp);
        return y;
    }
}

//For creating teacher information
int add_teacher(){
    system("cls");
    char ch[101];
    struct teacher t1;
    printf("Add Username:  ");
    scanf("%s",t1.user);
    printf("Add Password:  ");
    scanf("%s",t1.pass);
    printf("Add Full name:  ");
    gets(ch);
    gets(t1.name);
    FILE *fp = fopen("teacher.txt","a");
    fwrite(&t1,sizeof(t1),1,fp);
    fclose(fp);
    printf("\nTeacher added successfully!!\n\n");
    printf("Press any button to go back");
}

//For creating student information
int add_student(){
    system("cls");
    char ch[5];
    struct student s1;
    printf("Add Username:  ");
    scanf("%s",s1.user);
    printf("Add Password:  ");
    scanf("%s",s1.pass);
    printf("Add full Name: ");
    gets(ch);
    gets(s1.name);
    //scanf("%s",s1.name);
    printf("Add Roll No.:  ");
    scanf("%s",s1.roll);
    FILE *fp = fopen("student.txt","a");
    fwrite(&s1,sizeof(s1),1,fp);
    fclose(fp);
    printf("\nStudent added successfully!!\n\n");
    printf("Press any button to go back");
}

//Updating teacher's information
int update_teacher(){
    system("cls");
    char user[101];
    printf("Enter Username:  ");
    scanf("%s",user);
    struct teacher st;
    FILE *ptr = fopen("teacher.txt","r");
    int m=0;
    if(ptr!=NULL){
        while(fread(&st,sizeof(st),1,ptr)){
                if(strcmp(st.user,user)==0){
                    m=1;
                    break;
                }
        }
    }
    fclose(ptr);
    if(m==1){
        printf("Enter teacher new info:\n");
        struct teacher t1;
        printf("Add Username:  ");
        scanf("%s",t1.user);
        printf("Add Password:  ");
        scanf("%s",t1.pass);
        printf("Add Full name:  ");
        scanf("%s",t1.name);
        ptr = fopen("teacher.txt","r+");
        while(fread(&st,sizeof(st),1,ptr)){
            if(strcmp(st.user,user)==0){
                fseek(ptr,-sizeof(st),1);
                fwrite(&t1,sizeof(t1),1,ptr);
                fseek(ptr,0,1);
            }
        }
        printf("Teacher info successfully updated.\n");
    }
    else{
        printf("No teacher information found related to this username\n");
    }
}

//For updating student's information
int update_student(){
    system("cls");
    char user[101];
    printf("Enter Username:  ");
    scanf("%s",user);
    struct student st;
    FILE *ptr = fopen("student.txt","r");
    int m=0;
    if(ptr!=NULL){
        while(fread(&st,sizeof(st),1,ptr)){
            if(strcmp(st.user,user)==0){
                m=1;
                break;
            }
        }
    }
    fclose(ptr);
    if(m==1){
        printf("Enter student's new informations:\n");
        struct student s1;
        printf("Add Username:  ");
        scanf("%s",s1.user);
        printf("Add Password:  ");
        scanf("%s",s1.pass);
        printf("Add Roll No.:  ");
        scanf("%s",s1.roll);
        printf("Add full Name: ");
        scanf("%s",s1.name);
        ptr = fopen("student.txt","r+");
        while(fread(&st,sizeof(st),1,ptr)){
            if(strcmp(st.user,user)==0){
                fseek(ptr,-sizeof(st),1);
                fwrite(&s1,sizeof(s1),1,ptr);
                fseek(ptr,0,1);
            }
        }
        printf("\nStudent info successfully updated!!\n\n");
    }
    else{
        printf("No student information found related to this username.\n");
    }
}

//For Course Assignment
int course_assign(){
    system("cls");
    struct teacher t2;
    struct temp{
        char name[21];
        char cc[20];
    }tt;
    fflush(stdin);
    printf("Enter teacher's Username:  ");
    scanf("%s",tt.name);
    FILE *ptr = fopen("teacher.txt","r");
    int check=0;
    if(ptr!=NULL){
        while(fread(&t2,sizeof(t2),1,ptr)){
            if(strcmp(t2.user,tt.name)==0){
                check=1;
                break;
            }
        }
    }
    fclose(ptr);
    if(check==1){
        printf("Enter course code you want to assign:  ");
        scanf("%s",tt.cc);
        ptr = fopen("course.txt","a");
        fwrite(&tt,sizeof(tt),1,ptr);
        printf("\nCourse assignment completed.\n");
        fclose(ptr);
    }
    else{
        printf("\nNo teacher found with your given userName.\n");
    }
}

void admin_panel(){
    system("cls");
    int x;
    char ch[5];
    printf("--------------------------------------------\n");
    printf("<<<        Welcome to Admin Panel        >>>\n");
    printf("--------------------------------------------\n\n");
    printf(" Select one of the following-\n");
    printf("    1.Add Teacher's Information\n");
    printf("    2.Add Student's Information\n");
    printf("    3.Update Teacher's Information\n");
    printf("    4.Update Student's Information\n");
    printf("    5.Assign Course\n");
    printf("    6.Main Menu\n\n");
    printf(" Enter your choice : ");
    scanf("%d",&x);
    if(x==1)
        add_teacher();
    else if(x==2)
        add_student();
    else if(x==3)
        update_teacher();
    else if(x==4)
        update_student();
    else if(x==5)
        course_assign();
    else if(x==6){
        system("cls");
        return;
    }
    gets(ch);
    admin_panel();
}

// Admin login
int admin_log(){
    system("cls");
    char ch[5],user[20],pas[20];
    int a,b,y;
    printf("Admin Login---\n\n ");
    printf("Enter Username: ");
    gets(ch);
    gets(user);
    printf(" Enter Password: ");
    gets(pas);
    y = check_admin(user, pas);
    if(y == 0){
        printf("\nWrong User-name or Password.. \nPress any button to go back to main menu\n");
        getch();
        system("cls");
    }
    else if(y == 1){
        admin_panel();
    }
}

//For Assigning CT marks
int ctmarks(){
    system("cls");
    struct marks m;
    printf("Enter course code:  ");
    scanf("%s",&m.cc);
    FILE *ptr;
    ptr = fopen("course.txt","r");
    if(ptr!=NULL){
        struct cformat{
            char user[21],cc[20];
        }cf1;
        int found=0;
        while(fread(&cf1,sizeof(cf1),1,ptr)){
            if(strcmp(cf1.user,teachuser)==0 && strcmp(cf1.cc,m.cc)==0){
                found=1;
                break;
            }
        }
        fclose(ptr);
        if(found==0){
            printf("You are not assigned to this course.\n");
        }
        else{
            printf("Enter student Username:  ");
            scanf("%s",m.user);
            struct student st;
            ptr = fopen("student.txt","r");
            int isfound=0;
            while(fread(&st,sizeof(st),1,ptr)){
                if(strcmp(st.user,m.user)==0){
                    isfound = 1;
                    break;
                }
            }
            fclose(ptr);
            if(isfound==0){
                printf("\nNo student found with given username\n");
            }
            else{
                printf("Enter marks:  ");
                scanf("%s",m.marks);
                FILE *ptr = fopen("marks.txt","a");
                fwrite(&m,sizeof(m),1,ptr);
                fclose(ptr);
                printf("\nMarks successfully added.\n");
                fclose(ptr);
            }
        }
    printf("Press any button to go back...");
    }
}

//For Showing student information
int stud_inf(){
    system("cls");
    char ch[5],name[51];
    printf("Enter student's name:  ");
    gets(ch);
    gets(name);
    struct student st1;
    FILE *ptr = fopen("student.txt","r");
    int count=0;
    while(fread(&st1,sizeof(st1),1,ptr)){
        if(strstr(st1.name,name)!=0){
            printf("\nUsername: %s\nName: %s\nRoll No.: %s\n\n",st1.user,st1.name,st1.roll);
            count++;
        }
    }
    fclose(ptr);
    if(count==0){
        printf("\nSORRY!! NO STUDENT FOUND WITH GIVEN NAME \n");
    }
    printf("Press any button to go back...");
}

//To count Total student
int total_stud(){
    system("cls");
    FILE *ptr = fopen("student.txt","r");
    struct student st;
    int count=0;
    while(fread(&st,sizeof(st),1,ptr)){
        count++;
    }
    fclose(ptr);
    printf("Total number of students is %d\n",count);
    printf("\nPress any button to go back...");
}

//Teacher's Panel
int teacher_panel(){
    system("cls");
    int x;
    char ch[5];
    printf("--------------------------------------------\n");
    printf("<<<      Welcome to Teacher's Panel      >>>\n");
    printf("--------------------------------------------\n\n");
    printf(" Select one of the following-\n");
    printf("    1.Add CT mark\n");
    printf("    2.Find student information\n");
    printf("    3.Find total number of students\n");
    printf("    4.Main Menu\n\n");
    printf(" Enter your choice : ");
    scanf("%d",&x);
    if(x==1)
        ctmarks();
    else if(x==2)
        stud_inf();
    else if(x==3)
        total_stud();
    else if(x==4){
        system("cls");
        return 0;
    }
    gets(ch);
    teacher_panel();
}

//Teacher's Login
int teachlog(){
    system("cls");
    char user[51],pass[51];
    printf("Enter teacher's Username:  ");
    scanf("%s",&user);
    printf("Enter Password:  ");
    scanf("%s",&pass);
    FILE *ptr;
    ptr = fopen("teacher.txt","r");
    struct teacher info;
    int check=0;
    while(fread(&info,sizeof(info),1,ptr)){
        if(strcmp(info.user,user)==0 && strcmp(info.pass,pass)==0){
            strcpy(teachuser,info.user);
            check=1;
            break;
        }
    }
    fclose(ptr);
    if(check == 0){
            printf("\nWrong User-name or Password.. \nPress any button to go back to main menu\n");
            getch();
            system("cls");
    }
    else if(check == 1){
        teacher_panel();
    }
}

//For showing CT marks
int showctmarks(){
    system("cls");
    FILE *ptr;
    ptr = fopen("marks.txt","r");
    int check=0;
    struct marks m;
    while(fread(&m,sizeof(m),1,ptr)!=0){
        if(strcmp(m.user,studuser)==0){
            printf("\nClass Code: %s\nMarks: %s\n\n",m.cc,m.marks);
        }
    }
    printf("Press any button to go back...");
}

//Student Panel
int student_corner(){
    system("cls");
    int x;
    printf("--------------------------------------------\n");
    printf("<<<      Welcome to Student's Panel      >>>\n");
    printf("--------------------------------------------\n\n");
    printf(" Select one of the following-\n");
    printf("    1.Show CT mark\n");
    printf("    2.Main Menu\n\n");
    printf(" Enter your choice : ");
    scanf("%d",&x);
    if(x==1)
        showctmarks();
    else if(x==2){
        return 0;
    }
}

//Student Login
int studlog(){
    system("cls");
    char user[51],pass[51];
    printf("Enter student's Username:  ");
    scanf("%s",&user);
    printf("Enter Password:  ");
    scanf("%s",&pass);
    FILE *ptr;
    ptr = fopen("student.txt","r");
    struct student info;
    int check=0;
    while(fread(&info,sizeof(info),1,ptr)){
        if(strcmp(info.user,user)==0 && strcmp(info.pass,pass)==0){
            strcpy(studuser,info.user);
            check=1;
            break;
        }
    }
    fclose(ptr);
    if(check == 0){
            printf("\nWrong User-name or Password.. \nPress any button to go back to main menu\n");
    }
    else if(check == 1){
        student_corner();
    }
}

int main(){
    system("cls");
    int x;
    char ch[5];
    printf("--------------------------------------------------\n");
    printf("Welcome to Class Management System\n");
    printf("--------------------------------------------------\n");
    printf("1. Admin Login\n");
    printf("2. Teacher Login\n");
    printf("3. Student Login\n");
    printf("4. Exit\n");
    printf("--------------------------------------------------\n");
    printf("Choose your option:  ");
    scanf("%d",&x);
    if(x==1){
        admin_log();
    }
    else if(x==2){
        teachlog();
    }
    else if(x==3){
        studlog();
    }
    else if(x==4){
        system("cls");
        printf("Exiting the program...\n");
        exit(0);
    }
    else{
        printf("Invalid input.. Press any button to go back to main menu\n");
        getch();
        system("cls");
    }
    // gets(ch);
    main();


return 0;
}