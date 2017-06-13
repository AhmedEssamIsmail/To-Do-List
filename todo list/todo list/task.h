#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
#include <windows.h>

using namespace std;

struct task
{
	string duedate, description, priority,subject;
	bool done;
	long long days;
	task();
	void cont_saving(fstream&);
	void cont_loading(fstream&);
};

class list
{
	vector <task> todo_list;
public :
	void add_task();
	void delete_task();
	void edit_task();
	void display_task();
	bool find_subject(string);
	void disp(vector<task>:: iterator);
	void display_all_tasks();
	void search();
	void sort_list();
	void cont_saving(fstream&);
	void cont_loading(fstream&);
};

class System{
	map< string ,pair < string , list > > users;
public :
	list  * currlist;
	void Init(string);
	string log_in();
	string log_out();
	void add_user();
	void delete_user();
	void process();
	void Run();
	void save();
	void load();
};

long long convert_to_days(string);
bool comp_priority(task, task);
bool comp_duedate(task, task);
void sleep_sec();