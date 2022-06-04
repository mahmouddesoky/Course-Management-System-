#include<iostream>
#include<string>
#include<fstream>
#include<conio.h>
#include<Windows.h>


using namespace std;
//Stream Objects for Write and Read Files 
ofstream out;
ifstream in; 
//Structs Courses and Student and enroll (student <--> Course)
struct courses{
	int id; 
	string name;
	string instructorName;
	int enrolledStudents = 0;
};
struct students{
	int id;
	string name; 
	int age; 
	string address; 
	int Course_id; 
	int grade;
};
struct enroll{
	int courseID;
	int studentID;
	int grade;
};
int student_num = 0;
int course_num = 0;
int enroll_num = 0;
students student[50];
courses course[50];
enroll enrollment[100];

//Function Load Course From File Course.txt to Struct Course
void loud_course()
{
	in.open("Course.txt",ios::in);
	while (!in.eof()) {
		in >> course[course_num].id;
		if (course[course_num].id == 0)
			break;
		getline(in, course[course_num].name, ',');
		getline(in, course[course_num].instructorName, ',');
		in >> course[course_num].enrolledStudents;
		course_num++;
	}
	in.close();
}
//Function Load Student From File Student.txt to Struct Student
void loud_student()
{
	in.open("Students.txt");
	while (!in.eof()) {
		in >> student[student_num].id;
		if (student[student_num].id == 0)
			break;
		getline(in, student[student_num].name, ',');
		in >> student[student_num].age;
		getline(in, student[student_num].address);
		student_num++;
	}
	in.close();
}
//Function Load Enroll From File Enrollments.txt to Struct Enrollment
void loud_enroll()
{
		in.open("Enrollments.txt");
		for (int i = 0; !in.eof(); i++){
			in >> enrollment[i].courseID;
			if (enrollment[i].courseID == 0)
				break;
			in >> enrollment[i].studentID;
			in >> enrollment[i].grade;
			enroll_num++;
		}
		in.close();
	}
//Function Display List Courses which in struct array Course
void list_courses(){
		cout << "This is The Courses available in The System\n_________________________________________________________\n";
		cout << "ID  Name\t\t\t Instructor Name \n_________________________________________________________\n";
		for (int p = 0; p<course_num; p++)
		{
			cout << course[p].id << "  " << course[p].name << "\t" << course[p].instructorName << endl;
		}
		cout << "\n_____________________________________________________\n\n";
}
//Function Display List student which in struct array student
void list_student(){
	cout << "Students in The System \n_______________________________________________________________________\n\n" << endl;
	cout << "ID         Name \t Age     Address \n_______________________________________________________________________\n";
	
	for (int s = 0; s<student_num; s++)
	{
		
		cout << student[s].id << "  " << student[s].name << "\t" << student[s].age << "\t" << student[s].address << "\n";
	}
	cout << "\n_____________________________________________________\n\n";
}
//1)Function Add New Student 
void new_student(){
		
		
		for (int i = student_num; i < student_num + 1; i++)
		{
			bool check = false;
			cout << "\nEnter Information about Student\n\n";
			cout << "Enter Student ID : "; cin >> student[i].id;
			for (int p = 0; p < student_num; p++)
			{

				if (student[i].id == student[p].id){
					cout << "\nThis ID is already taken\n_________________________________________\nEnter again \n" << endl;
					check = true;
					break;
				}
				 if (student[i].id <= 0)
				{
					cout << "\nThis ID is Not Vaild in System\n_________________________________________\nEnter again \n" << endl;
					check = true;
					break;
				}
			}
			if (check == true)
			{
				i=student_num-1;
				Sleep(1100);
				system("CLS");
				continue;
			}
			cout << "\nEnter Student Name : ";
			cin.ignore();
			getline(cin, student[i].name);

			do{
				cout << "\nEnter Age : "; cin >> student[i].age;
				if (student[i].age < 15 || student[i].age > 60){
					cout << "\n~This is Not Vaild Age in System~\n\nEnter Again\n";
				}
				else
				{
					break;
				}
			} while (true);
			
			cout << "\nEnter Address : ";
			cin.ignore(); 
			getline(cin, student[i].address);
			cout << "\n";
			list_courses();
			bool c = false;
			do{
				cout << "\n ~~ Enter The ID Course for student ~~ : ";
				cin >> student[i].Course_id; 
				if (student[i].Course_id <= 0)
				{
					cout << "\n~This is Not Vaild ID in System~\n\nPlease Enter Again\n";
					c = true;
					continue; 
				}
				for (int o = 0; o < course_num; o++){
					
					if (student[i].Course_id == course[o].id){
						c = false;
						break;
					}
					else
						c = true;	
				}
				if (c==true)
					cout << "~This ID is UnDefined in System~\n\n Please Enter Again\n";
			} while(c==true);
			
			cout << "\nEnter Grade for Student : ";
			cin >> student[i].grade;
			out.open("Students.txt", ios::app);
			out << student[i].id << student[i].name << "," << student[i].age << " " << student[i].address << endl;
			out.close();
			out.open("Enrollments.txt", ios::app);
			out << student[i].Course_id << " " << student[i].id << " " << student[i].grade << endl;
			out.close();
			cout << "\n\n~~ Enrolled Successful ~~ \n\n";
		}
		student_num++;

		Sleep(1500);
		system("CLS");
	}
//2)Function Unenroll student from Course 
void unenroll_student(){
		int id_student, id_course;
		bool c = false;
		do
		{
			cout << "Enter ID Student who you want to unenroll: ";
			cin >> id_student;
			if (id_student<=0)
			{
				cout << "\n~This is Not Vaild ID in System~\n\nPlease Enter Again\n\n";
				c = true;
				continue;
			}
			for (int y = 0; y < student_num; y++){
				if (id_student == student[y].id){
					c = false;
					break;
				}
				else
					c = true;	
			}
		if (c == true)
			cout << "~This ID is UnDefined in System~\n\n Please Enter Again\n\n";
		
		} while (c==true);
		c = false;
		do
		{
			cout << "Enter ID Course who you want to unenroll : ";
			cin >> id_course;
			if (id_course <= 0)
			{
				cout << "\n~This is Not Vaild ID in System~\n\nPlease Enter Again\n\n";
				c = true;
				continue;
			}
			for (int y = 0; y < course_num; y++){
				if (id_course == course[y].id)
				{
					c = false;
					break;
				}
				else
					c = true;
			}
			if (c == true)
				cout << "~This ID is UnDefined in System~\n\n Please Enter Again\n\n";
		} while (c == true);
		
		out.open("Enrollments.txt");
		bool found = false;
		for (int i = 0; i < enroll_num; i++)
		{
			if (id_student == enrollment[i].studentID && id_course == enrollment[i].courseID)
			{
				found = true;
				continue;
			}
			else 
				found = false;	
			if (enrollment[i].courseID == 0)
				break;
			out << enrollment[i].courseID << " " << enrollment[i].studentID << " " << enrollment[i].grade << endl;
		}
		out.close();
		if (found == true)
			cout << "\n\n ~~ Process Successful ~~ \n\n";
		else
			cout << "\n\n ~~ The Id of student is already unenrolled ~~ \n\n";

		Sleep(1600);
		system("CLS");
	}
//3)Function Add New Course 
void new_course(){
		bool check = false;
		for (int j = course_num; j < 1+ course_num; j++)
		{

			cout << "Enter Informaion about Course #" << j + 1 << "\n______________________________________________________________________________\n";
			cout << "Enter ID Course : "; cin >> course[j].id;
			for (int p = 0; p < course_num; p++)
			{

				if (course[j].id == course[p].id){
					cout << "This ID is already taken\n_________________________________________\nEnter again \n" << endl;
					check = true;
					break;
				}
				if (course[j].id <= 0)
				{
					cout << "\nThis ID is Not Vaild in System\n_________________________________________\nEnter again \n" << endl;
					check = true;
					break;
				}
				else
					check = false;
			}
			if (check == true){
				j = course_num - 1;
				Sleep(1100);
				system("CLS");
				continue;
			}
			cout << "Enter Name Course : ";
			cin.ignore();
			getline(cin, course[j].name);
			cout << "Enter Instructor Name : ";
			getline(cin, course[j].instructorName);
			do{
				cout << "Enter #Enrolled Student : ";
				cin >> course[j].enrolledStudents;
				if (course[j].enrolledStudents <= 0)
					cout << "\n~This is Not Vaild Number in System~\n\nEnter Again\n";
				else
					break;
			} while (true);
			out.open("Course.txt", ios::app);
			out << course[j].id << course[j].name << "," << course[j].instructorName << "," << course[j].enrolledStudents << endl;
			out.close();
			cout << "\n\n ~~ Process Successful ~~ \n\n";
		}
		course_num += 1;

		Sleep(1500);
		system("CLS");
	}
//4)Function Display Course in System
void display_course(){

		cout << "Courses in The System \n_______________________________________________________________________" << endl;
		cout << "ID     Name \t\t Instructor Name \t #Enrolled Student\n_______________________________________________________________________\n";
		for (int p = 0; p<course_num; p++)
		{
			cout << course[p].id << "  " << course[p].name << "\t" << course[p].instructorName << "  " << course[p].enrolledStudents << endl;
		}
		system("Pause");
		system("CLS");
}
//5)Function Display Student in System
void display_student(){
		cout << "Students in The System \n_______________________________________________________________________\n\n" << endl;
		cout << "ID         Name \t Age     Address \n_______________________________________________________________________\n";
		for (int s = 0; s<student_num; s++)
		{
			cout << student[s].id << "  " << student[s].name << "\t" << student[s].age << "\t" << student[s].address << "\n";
		}
		system("Pause");
		system("CLS");
}
//6)Function Delete Course 
void delete_course(){
	int id_delete = 0;
	bool check = false;
	do{
		list_courses();
		cout << "Enter ID Course to Delete : ";
		cin >> id_delete;
		if (id_delete > 0){
			out.open("Course.txt");
			for (int c = 0; c < course_num; c++)
			{
				if (id_delete == course[c].id)
				{
					check = true;
					course[c].id = 0;
					course[c].name = "";
					course[c].instructorName = "";
					course[c].enrolledStudents = 0;
					continue;
				}
				out << course[c].id << course[c].name << "," << course[c].instructorName << "," << course[c].enrolledStudents << endl;
			}
			out.close();
			out.open("Enrollments.txt");
			for (int u = 0; u < enroll_num; u++){
				if (id_delete == enrollment[u].courseID)
					continue;
				out << enrollment[u].courseID << " " << enrollment[u].studentID << " " << enrollment[u].grade << endl;
			}
			out.close();
			if (check == true)
				cout << "\n\n ~~ Deleted Successful ~~ \n\n";
			else
				cout << "\n\n ~~ This ID is Not Found ~~ \n\n";
		}
		else
			cout << "\nthis ID is Not Vaild \n\n Enter Again \n";
		Sleep(1100);
		system("CLS");
	} while (id_delete <= 0);
}
//7)Function Delete Student 
void delete_student(){
	int id_delete;
	bool check = false;
	do{
		list_student();
		cout << "Enter ID Student to Delete :  ";
		cin >> id_delete;
		if (id_delete > 0){
			out.open("Students.txt");
			for (int a = 0; a < student_num; a++)
			{
				if (id_delete == student[a].id)
				{
					check = true;
					continue;
				}
				out << student[a].id << student[a].name << "," << student[a].age << student[a].address << "\n";
			}
			out.close();
			out.open("Enrollments.txt");
			for (int u = 0; u < enroll_num; u++){
				if (id_delete == enrollment[u].studentID)
					continue;
				out << enrollment[u].courseID << " " << enrollment[u].studentID << " " << enrollment[u].grade << endl;

			}
			out.close();
			if (check == true)
				cout << "\n\n ~~ Deleted Successful ~~ \n\n";
			else
				cout << "\n\n ~~ This ID is Not Found ~~ \n\n";
		}
		else
		{
		cout << "\nthis ID is Not Vaild \n\n Enter Again \n";
		Sleep(1100);
		system("CLS");
		}
		
	} while (id_delete <= 0);
	Sleep(1300);
	system("CLS");
}
//8)Function Edit Student 
void edit_student(){
	
	bool check = false;
	int id_edit;
	do{
		list_student();
		cout << "Enter The ID Student you want to edit : ";
		cin >> id_edit;
		if (id_edit > 0){
		for (int a = 0; a < student_num; a++)
		{
			if (id_edit == student[a].id)
			{
				check = true;
				cout << "___________________________________________\n";
				cout << "Enter New Age : ";
				cin >> student[a].age;
				cin.ignore();
				cout << "Enter New Address : ";
				getline(cin, student[a].address);
				out.open("Students.txt");
				for (int q = 0; q < student_num; q++){
					if (id_edit == student[q].id)
					{	
						out << student[q].id << student[q].name << "," << student[q].age << " " << student[q].address << "\n";
						continue;
					}
					out << student[q].id << student[q].name << "," << student[q].age << student[q].address << "\n";
				}
				out.close();
				cout << "\n\n ~~ Process Successful ~~ \n\n";
				break;
			}
			else
			{
				check = false;
			}
		}
		if (check == false){
			cout << "This is ID is Undefined in the System \n\nPlease Enter Again \n\n";
			Sleep(1100);
			system("CLS");
		}
		}
		else
		{
			check = false;
			cout << "\nthis ID is Not Vaild \n\n Enter Again \n";
			Sleep(1100);
			system("CLS");
		}
	} while (check == false);

	Sleep(1500);
	system("CLS");
	}
//9)Function Edit Course 
void edit_course(){
	bool check = false;
		int id_edit;
		do{
			list_courses();
		cout << "Enter The ID Course you want to edit : ";
		cin >> id_edit;
		if (id_edit > 0){
			for (int w = 0; w < course_num; w++)
			{
				if (id_edit == course[w].id)
				{
					check = true;
					cout << "\n__________________________________________\n\n";
					cout << "Enter New Instructor Name : ";
					cin.ignore();
					getline(cin, course[w].instructorName);
					cout << "Enter New #Enrolled Student : ";
					cin >> course[w].enrolledStudents;
					out.open("Course.txt");
					for (int j = 0; j < course_num; j++)
						out << course[j].id << course[j].name << "," << course[j].instructorName << "," << course[j].enrolledStudents << endl;
					out.close();
					cout << "\n\n ~~ Process Successful ~~ \n\n";
					break;
				}
				else
					check = false;
			}
			if (check == false){
				cout << "This is ID is Undefined in the System \n\nPlease Enter Again \n\n";
				Sleep(1100);
				system("CLS");
			}
		}
		else
		{
			check = false;
			cout << "\nthis ID is Not Vaild \n\n Enter Again \n";
			Sleep(1100);
			system("CLS");
		}
		} while (check == false);

		
		Sleep(1500);
		system("CLS");
	}
//10)Function Search Course and show list all students with grades 
void search_course() {
	list_courses();
		int id;
		cout << "Enter the ID Course to Display all Students enrolled : ";
		cin >> id;
		cout << "\n";
		for (int u = 0; u < course_num; u++){
			if (id == course[u].id){
				cout << "Name Course : " << course[u].name << "\n\n";
				break;
			}
		}
		cout << "Name \t\t Grade \n_____________________________________________________________\n";
		for (int j = 0; j < enroll_num; j++)
		{
			if (id == enrollment[j].courseID)
			{
				for (int k = 0; k < student_num; k++)
				{
					if (enrollment[j].studentID == student[k].id)
					{
						cout << student[k].name << "  " << enrollment[j].grade << endl;
						break;
					}
				}
			}
		}

		Sleep(1500);
		system("CLS");
	}
//11)Function Search Students and show list all Courses enrollments
void search_student(){
	list_student();
		int id_student;
		cout << "Enter the ID Student to Display all Courses he is exist : ";
		cin >> id_student;
		cout << "\n";
		for (int u = 0; u < student_num; u++){
			if (id_student == student[u].id){
				cout << "Name Student : " << student[u].name << "\n\n";
				break;
			}
		}
		cout << "Name Course \n_____________________________________________________________\n";
		for (int j = 0; j < enroll_num; j++)
		{
			if (id_student == enrollment[j].studentID)
			{
				for (int k = 0; k < course_num; k++)
				{
					if (enrollment[j].courseID == course[k].id)
					{
						cout << course[k].name << endl;
						break;
					}
				}
			}
		}

		Sleep(1500);
		system("CLS");
	}
// Main Run

int main()
{
	//Change Color Console
	system("COLOR f1");

	cout << "\n\n\n\n\n\n_______________________________________________________________________\n\n\n     ^^^^^~~~~~ Welcome to Course Management System~~~~~^^^^^\n\n_______________________________________________________________________\n " << endl;
	Sleep(1200);
	bool update = false;
	int choice;
	//Louds 
	loud_course();
	loud_student();
	loud_enroll();
	while (true)
	{
		if (update == true)
		{
			course_num = 0;
			student_num = 0;
			enroll_num = 0;
			loud_course();
			loud_student();
			loud_enroll();
		}
		
		system("CLS");
		cout << "\n                                    Main Window\n_______________________________________________________________________"
			<<"\n       Please Enter the appropriate Number\n\n ( 1 ) Add New Student  \n ( 2 ) UnEnroll Student \n ( 3 ) Add New Course \n ( 4 ) Display Courses \n ( 5 ) Display Students \n ( 6 ) Delete Course \n"
			<< " ( 7 ) Delete Students \n ( 8 ) Edit Courses \n ( 9 ) Edit Students \n ( 10 ) Search Students \n ( 11 ) Search Courses  \n ( 12 ) Exit  \n_______________________________________________________________________\n\nChoice : ";
		cin >> choice;
		if (choice == 1) //New Student
		{
			system("CLS");
			new_student();
			update = true;
		}
		else if (choice == 2) //unroll
		{
			system("CLS");
			unenroll_student();
			update = true;
		}
		else if (choice == 3)//NEW Course
		{
			system("CLS");
			new_course();
			update = true;
		}
		else if (choice == 4)//Display Courses
		{
			system("CLS");
			display_course();

		}
		else if (choice == 5)//Display Students
		{
			system("CLS");
			display_student();

		}
		else if (choice == 6)//Delete Courses
		{
			system("CLS");
			delete_course();
			update = true;
		}
		else if (choice == 7)//Delete Students
		{
			system("CLS");
			delete_student();
			update = true;
		}
		else if (choice == 8)//Edit Courses
		{
			system("CLS");
			edit_course();
			update = true;

		}
		else if (choice == 9)//Edit Students
		{
			system("CLS");
			edit_student();
			update = true;
		}
		else if (choice == 10)//Search Students
		{
			system("CLS");
			search_student();
			
		}
		else if (choice == 11)//Search Courses
		{
			system("CLS");
			search_course();
			
		}
		else if (choice == 12)//Exit
		{
			system("CLS");
			cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
				<< "        ^^__^^   Thanks for Using Course Mangement System   ^^__^^\n" <<
				"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n"
				<< "Credits: ~~~~~~~ Mahmoud Desoky ~~~~~~~\n" <<
				   "         ~~~~~~~ Mahmoud Wageeh ~~~~~~~\n"
				<< "         ~~~~~~~ Mariam Ibrahim ~~~~~~~\n"
				<< "         ~~~~~~~  Marwa Shehta  ~~~~~~~\n"
				<< "         ~~~~~~~ Mustafa Ahmed  ~~~~~~~\n\n";
			
			break;
		}
		else 
		{
			system("CLS");
			cout << "\n~~~~Not Vaild~~~~\n\n\n     ^^^___^^^Please Enter the Correct Choice^^^___^^^\n" << endl;
			Sleep(1200);
			system("CLS");
		}
	}
	
	return 0;
}