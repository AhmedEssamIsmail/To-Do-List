#include "task.h"

task::task(){
	done = false;
}

void list::add_task(){
	task T;
	cout << "Subject : " << endl;
	cin >> T.subject;
	if (find_subject(T.subject)){
		cout << "Invalid subject !" << endl;
		sleep_sec();
		return;
	}
	cout << "Description : " << endl;
	cin.ignore();
	getline(cin, T.description);
	cout << "Priority (High,Medium,Low) : " << endl;
	cin >> T.priority;
	cout << "Due-Date (dd/mm/yyyy) : " << endl;
	cin >> T.duedate;
	T.days = convert_to_days(T.duedate);
	todo_list.push_back(T);
	sort_list();
	cout << "The task has been added !" << endl;
	sleep_sec();
}

void list::delete_task(){
	string str;
	cout << "Enter the task's subject you want to delete : " << endl;
	cin >> str;
	if (!find_subject(str)){
		cout << "Task not founded !" << endl;
		sleep_sec();
		return;
	}
	for (vector<task>::iterator it = todo_list.begin(); it != todo_list.end() ; it++)
	{
		if (it->subject == str)
		{
			todo_list.erase(it);
			break;
		}
	}
	cout << "The task has been deleted !" << endl;
	sleep_sec();
}

void list::edit_task(){
	string str,str2;
	cout << "Enter the task's subject you want to edit : " << endl;
	cin >> str;
	if (!find_subject(str)){
		cout << "Task not founded" << endl;
		sleep_sec();
		return;
	}
	cout << "Enter the element you want to edit ( description , priority , due-date , status ) : " << endl;
	cin >> str2;
	vector<task>::iterator it;
	for (it = todo_list.begin(); it != todo_list.end(); it++)
	{
		if (it->subject == str) 
			break;
	}
	if (str2 == "description") {
		cout << "Enter the new description : ";
		cin.ignore();
		getline(cin ,it->description);
	}
	else if (str2 == "priority"){
		cout << "Enter the new priority : ";
		cin >> it->priority;
	}
	else if (str2 == "due-date"){
		cout << "Enter the new due-date : ";
		cin >> it->duedate;
	}
	else {
		cout << "Enter the new status (done) : ";
		cin >> it->done;
	}
	cout << "The task has been edited !" << endl;
	sleep_sec();
}

void list::display_task(){
	string str;
	cout << "Enter the task's subject you want to display : " << endl;
	cin >> str;
	if (!find_subject(str)){
		cout << "Task not founded" << endl;
		return;
	}
	vector<task>::iterator it;
	for (it = todo_list.begin(); it != todo_list.end(); it++)
	{
		if (it->subject == str)
			break;
	}
	disp(it);
}

void list::display_all_tasks(){
	bool prn = false;
	vector<task>::iterator it;
	for (it = todo_list.begin(); it != todo_list.end(); it++)
	{
		if (!it->done)
		{
			prn = true;
			disp(it);
		}
	}
	if (!prn)
	{
		cout << "There is no tasks have been founded to display !" << endl;
		sleep_sec();
	}
}

void list::sort_list()
{
	sort(todo_list.begin(), todo_list.end(), comp_priority);
	sort(todo_list.begin(), todo_list.end(), comp_duedate );
}

void list::search(){
	string str;
	bool before = false ;
	long long days;
	cout << "Enter the date" << endl;
	cin >> str;
	days = convert_to_days(str);
	for (vector<task>::iterator it = todo_list.begin() ; it != todo_list.end() ; it++)
	{
		if (days >= it->days)
		{
			disp(it);
		}
	}
}

void list::disp(vector<task>::iterator T)
{
	cout << endl << "Subject : " ;
	cout << T->subject << endl;
	cout << "Description : ";
	cout << T->description << endl;
	cout << "Priority : " ;
	cout << T->priority << endl;
	cout << "Due-Date : ";
	cout << T->duedate << endl;
	cout << "Status : ";
	if (T->done)
		cout << "Done" << endl;
	else
		cout << "Not Done" << endl << endl;
}

bool list::find_subject(string str){
	for (vector<task>::iterator it = todo_list.begin(); it != todo_list.end(); it++)
	{
		if (str == it->subject)
			return true;
	}
	return false;
}

string System::log_in(){
	string username, password;
	cout << "Enter the username : ";
	cin >> username;
	cout << "Enter the password : ";
	cin >> password; 
	if (!users.count(username))
	{
		cout << "Invalid username !" << endl;
		sleep_sec();
	}
	else if (users[username].first != password)
	{
		cout << "Wrong password" << endl;
		sleep_sec();
	}
	else
	{
		cout << "Loging-in";
		int delay = 3;
		while (delay--){
			Sleep(400);
			cout << ".";
		}
		sleep_sec();
		return username;
	}
	return "";
}

string System::log_out(){
	sleep_sec();
	return "";
}

void System::Init(string username)
{
	currlist = &(users[username].second);
}

void System::add_user(){
	string username, password;
	list my_list;
	cout << "Enter the username : ";
	cin >> username;
	cout << "Enter the password : "; 
	cin >> password;
	if (users.count(username))
	{
		cout << "Invalid username !" << endl;
		sleep_sec();
		return;
	}
	pair <string, list > my_pair = make_pair(password, my_list);
	users[username] = my_pair;
	cout << "The user has been added !" << endl;
	sleep_sec();
}

void System::delete_user(){
	string username, password;
	cout << "Enter the username : ";
	cin >> username;
	cout << "Enter the password : ";
	cin >> password;
	if (!users.count(username))
	{
		cout << "Invalid username !" << endl;
		sleep_sec();
	}
	else if (users[username].first != password)
	{
		cout << "Wrong password" << endl;
		sleep_sec();
	}
	else
	{
		map <string, pair < string, list > > ::iterator itr;
		for (itr = users.begin(); itr != users.end(); itr++)
		{
			if (itr->first == username)
				break;
		}
		users.erase(itr);
		cout << "the user has been deleted ! " << endl;
		sleep_sec();
	}
}

void System::save(){
	fstream myfile("Text.txt");
	if (!myfile.is_open())
	{
		cout << "Error loading file\n";
	}
	else
	{
		int size = users.size();
		myfile << size << endl;
		for (map<string, pair<string, list> >::iterator it = users.begin(); it != users.end(); it++)
		{
			myfile << it->first << endl;
			myfile << it->second.first << endl;
			it->second.second.cont_saving(myfile);
		}
	}
	cout << "Saving";
	int delay = 3;
	while (delay--){
		Sleep(400);
		cout << ".";
	}
	sleep_sec();
	myfile.close();
}

void list::cont_saving(fstream& myfile){
	myfile << todo_list.size() << endl;
	for (int i = 0; i < todo_list.size(); i++)
	{
		todo_list[i].cont_saving(myfile);
	}
}

void task::cont_saving(fstream& myfile){
	myfile << subject << endl;
	myfile << duedate << endl;
	myfile << priority << endl;
	myfile << days << endl;
	myfile << done << endl;
	myfile << description << endl;
}

void System::load(){
	fstream myfile("Text.txt");
	int size;
	string username;
	myfile >> size;
	for (int i = 0; i < size; i++)
	{
		pair <string, list > my_pair;
		myfile >> username;
		myfile >> my_pair.first;
		my_pair.second.cont_loading(myfile);
		users[username] = my_pair;
	}
	myfile.close();
	cout << "Loading";
	int delay = 3;
	while (delay--){
		Sleep(800);
		cout << ".";
	}
	Sleep(500);
	system("cls");
}

void list::cont_loading(fstream& myfile){
	int size;
	myfile >> size;
	for (int i = 0; i < size; i++)
	{
		task T;
		T.cont_loading(myfile);
		todo_list.push_back(T);
	}
}

void task::cont_loading(fstream& myfile){
	myfile >> subject;
	myfile >> duedate;
	myfile >> priority;
	myfile >> days;
	myfile >> done;
	myfile.ignore();
	getline(myfile,description);
}

long long convert_to_days(string str){
	int base , counter,i;
	base = counter = 0;
	long long days=0;
	string s;
	for (i = 0; (unsigned int)i < str.size(); i++)
	{
		if (!isdigit(str[i]))
		{
			s = str.substr( i - counter , counter );
			if (!base) days += stoi(s);
			else if (base == 1) days += (stoi(s) * 12);
			else if (base == 2) days += (stoi(s) * 365);
			base++;
			counter = 0;
			continue;
		}
		counter++;
	}
	if (isdigit(str[str.size()-1]))
	{
		s = str.substr(str.size() - 4, 4);
		days += stoi(s) * 365;
	}
	return days;
}

bool comp_priority(task T1, task T2){
	if ((T1.priority == "High" || T1.priority == "Medium") && (T2.priority == "Low"))
		return true;
	if ((T1.priority == "High") && (T2.priority == "Medium" || T2.priority == "Low"))
		return true;
	return false;
}

bool comp_duedate(task T1, task T2){
	if (T1.priority != T2.priority)
		return false;
	if (T1.days > T2.days)
		return true;
	return false;
}

void System::process(){
	int choice;
	bool processing = true;
	while (processing)
	{
		cout << "Enter :" << endl;
		cout << "1 - To add a task" << endl << "2 - To review your task" << endl;
		cout << "3 - To delete a task" << endl << "4 - To show all the unfinished tasks" << endl << "5 - To edit a task" << endl;
		cout << "6 - To search on tasks before a specified date" << endl  << "7 - To log-out" << endl;
		cin >>	choice;
		switch (choice)
		{
		case 1:
			currlist->add_task();
			break;
		case 2:
			currlist->display_task();
			break;
		case 3:
			currlist->delete_task();
			break;
		case 4:
			currlist->display_all_tasks();
			break;
		case 5:
			currlist->edit_task();
			break;
		case 6:
			currlist->search();
			break;
		case 7:
			processing = false;
			sleep_sec();
			break;
		default:
			cout << "Please read the instructions carefully" << endl;
			break;
		}
	}
}

void System::Run(){
	bool choice = true;
	int option;
	string username;
	while (choice)
	{
		cout << "Enter : " << endl;
		cout << "1 - To add a user" << endl;
		cout << "2 - To delete a user" << endl;
		cout << "3 - To log-in" << endl;
		cout << "4 - To load" << endl;
		cout << "5 - To save" << endl;
		cout << "6 - To exit" << endl;
		cin >> option;
		switch (option)
		{
		case 1 :
			add_user();
			break;
		case 2 :
			delete_user();
			break;
		case 3:
			username = log_in();
			if (username == "")
				break;
			Init(username);
			process();
			break;
		case 4:
			load();
			break;
		case 5:
			save();
			break;
		case 6:
			choice = false;
			break;
		default:
			cout << "Please read the instructions carefully" << endl;
			break;
		}
	}
}

void sleep_sec(){
	Sleep(1500);
	system("cls");
}