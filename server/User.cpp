#include <iostream>
#include <string>
#include <fstream>
#include <map>


using namespace std;

class User {
	
	public:
	string name;
	string password;
    User (string, string);
	
};


class UsersMap{
	public:
	string fn;
	map<string, string> users_map;
	UsersMap (string);
	void write_db();
	bool validate(User);
	bool add_user(User);
	bool remove_user(User);
};


User::User (string n, string p) {
	name = n;
	password = p;
}


UsersMap::UsersMap (string filename){
	string n;
	string p;
	this->fn = filename;
	ifstream infile(filename);
	while (infile >> n >> p)
	{
		this->users_map[n] = p;
	}
	infile.close();
}


bool UsersMap::validate(User user){
	if(users_map.find(user.name) == users_map.end()){
		cout<<"You are not signed up"<<endl;
		return false;
	}else{
		if(users_map[user.name] == user.password){
			cout<<"Successfuly validated"<<endl;
			return true;
		}else{
			cout<<"Incorrect password"<<endl;
			return false;
		}
	}
	
}


void UsersMap::write_db(){
	ofstream outfile;
	outfile.open(this->fn);
	map<string, string>::iterator it;
	for ( it = this->users_map.begin(); it != this->users_map.end(); it++ )
	{
		outfile << it->first << " " << it->second << endl;
	}
	outfile.close();	
}


bool UsersMap::add_user(User user){
	this->users_map[user.name] = user.password;
	write_db();
}


bool UsersMap::remove_user(User user){
	this->users_map.erase(user.name);
	write_db();
}
