#include "webpage.h"
webpage:: webpage() {
	
	// set_pclicks(0);
	
	 pctr = (double)get_clicks() / (double)get_impressions();
	 set_pscore();
		
	
}
void webpage ::set_pctr() {
	 pctr = (double)get_clicks() / (double)get_impressions();
	
}

void webpage::set_pname(string name) {
	pname = name;
}
void webpage::set_prank(double rank) {
	prank = rank;
}
void webpage:: set_number(int sitenum) {
	site_num = sitenum;
}
int webpage::get_number() {
	return site_num;
}

void webpage::set_pclicks(int clicks) {
	pclicks = clicks;
}
void webpage::set_pimpressions(int impressions) {
	pimpressions = impressions;
}


string webpage:: get_name() const {
	return pname;

}

double webpage::get_rank() const {
	return prank;
}
int webpage::get_clicks() const {
	return pclicks;
}
int webpage::get_impressions() const {
	return pimpressions;
}

void webpage::set_pscore() {
	set_pctr();
	pscore = (0.4 * prank) + 0.6 * (((1 - (0.1 * pimpressions) / (1 + 0.1 * pimpressions))*prank) + pctr*((0.1 * pimpressions) / (1 + 0.1 * pimpressions)));
}
double webpage::get_score() const {
	return pscore;
}

double webpage::get_ctr() const {
	return pctr;
}



