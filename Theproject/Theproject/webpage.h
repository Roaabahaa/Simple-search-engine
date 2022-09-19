
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
const int ALPHABET_SIZE = 26;

using namespace std;

class webpage {
private: string pname;
	   double prank;
	   
	
	   double pctr;
	   double pscore;
	   int site_num;
	   int pimpressions;
	   
	 
	 
	   
public :

	webpage();
	int pclicks;
	vector <webpage> pages_out;
	vector <webpage> pages_in;
	void set_pname(string name);
	void set_number(int sitenum);
	void set_prank(double rank);
	void set_pscore();
	int get_number();

	void set_pctr();
	void set_pclicks(int clicks);
	void set_pimpressions(int impressions);

	string get_name() const ;
	double get_rank() const;
	int get_clicks() const;
    int  get_impressions() const;
	double get_score() const;
	
     double   get_ctr() const;
	
	vector <string> keywords;


	




};
