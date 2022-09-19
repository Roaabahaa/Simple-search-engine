
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <cassert>
#include <algorithm>

#include "webpage.h"
#include <unordered_map>
using namespace std;


unordered_map<int, webpage> mapped_websites;
/*unordered_map<int, webpage> making_map() {

}*/
void display_results(vector <webpage>& sorted_results);
void rewrite_ctr();
void print_websites(vector <webpage> websites);
vector<webpage> read_websites(string file_name) {
	

	vector<string> row;
	int row_num = 0, count = 0;
	vector<webpage> websites;
	webpage temp;

	vector<string> file_content;
	
	string line, word;

	fstream csv_file(file_name, ios::in);
	if (csv_file.is_open())
	{
		while (getline(csv_file, line))
		{
			count = 0;
			row.clear();

			stringstream str(line);

			while (getline(str, word, ','))
			{
				
				count ++;
				
				file_content.push_back(word);
				

			}
		

		}
	}
	else
		cout << "Error opening file\n";

	row_num = count;
	
	//print_vector(file_content);
	if (row_num == 2) {
		for (int i = 0; i < file_content.size(); i += 2) {
			temp.set_pname(file_content[i]);
			temp.set_pimpressions(stoi(file_content[i + 1]));
			websites.push_back(temp);

		}
	}
	if (row_num == 3) {
		for (int i = 0; i < file_content.size(); i += 3) {
			temp.set_pname(file_content[i]);
			temp.set_pimpressions(stoi(file_content[i + 1]));
			temp.set_pclicks(stoi(file_content[i + 2]));
			websites.push_back(temp);

		}
	}
	for (int i = 0; i < websites.size(); i++) {
		mapped_websites[i+1] = websites[i];
		websites[i].set_number(i+1 );
	}

	//print_websites(websites);// just to validate
	
	rewrite_ctr();
	return websites;
}
vector<webpage> websites = read_websites("impressions.csv");

vector <int> search_word(string word) {
	vector<int> results;

	for (int i = 0; i < websites.size(); i++) {
		for (int j = 0; j < websites[i].keywords.size(); j++) {
			if (websites[i].keywords[j] == word) {
				results.push_back(websites[i].get_number());
			}

		}

	}


	return results;
}
vector<int> Union(vector<int> vector_1, vector<int> vector_2) //Time Complexity: O(mlogm+nlogn).
{
	set <int> Union;
	for (int i = 0; i < vector_1.size(); i++)
	{
		Union.insert(vector_1[i]);
	}
	for (int i = 0; i < vector_2.size(); i++)
	{
		Union.insert(vector_2[i]);
	}
	vector_2.clear();

	for (auto itr = Union.begin(); itr != Union.end(); itr++)
	{
		vector_2.push_back(*itr);
	}
	return vector_2;
}
vector<int> intersection(vector<int> vector_1, vector<int> vector_2) 
{
	sort(vector_1.begin(), vector_1.end());
	sort(vector_2.begin(), vector_2.end());

	

	vector<int> combine(vector_1.size() + vector_2.size());
	vector<int>::iterator it1, it2;
	vector<int>intersect;
	it1 = set_intersection(vector_1.begin(),vector_1.end(),vector_2.begin(),vector_2.end(),combine.begin());

	
	for (it2 = combine.begin(); it2 != it1; ++it2) {
		intersect.push_back(*it2);
	}

	return intersect;

}
vector<int> numbered_results;
void heapify(vector<webpage>& arr, int n, int i)
{
	int smallest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && arr[l].get_score() < arr[smallest].get_score())
		smallest = l;

	if (r < n && arr[r].get_score() < arr[smallest].get_score())
		smallest = r;

	if (smallest != i) {
		swap(arr[i], arr[smallest]);
		heapify(arr, n, smallest);
	}
}

void build_heap(vector<webpage>& arr, int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);
}

void heap_sort(vector<webpage>& arr, int n)
{
	build_heap(arr, n);
	for (int i = n - 1; i >= 0; i--) {
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}
void calc_pr(webpage &page) {


	double temp,dF = 0.85;

	for (int i = 0; i < websites.size(); i++)
	{
		websites[i].set_prank((double)1 / (double)websites.size());
	}

	for (int i = 0; i < websites.size() - 1; i++)
	{
		for (int j = 0; j < websites.size(); j++) {
			temp = 0;
			for (int k = 0; k < websites[j].pages_in.size(); k++) {
				temp += websites[j].pages_in[k].get_rank() / websites[j].pages_in[k].pages_out.size();
			}
			temp *= dF;
			temp += (1 - dF) / websites.size();
			websites[j].set_prank(temp);

		}
	}

	for (int i = 0; i < websites.size(); i++)
	{
		websites[i].set_pscore();
	}
}




vector<webpage> sort_webpages(vector <int> &numbered_results) {
	for (int i = 0; i < websites.size(); i++) {// this for loop stes  the pr , the ctr and the score
		calc_pr(websites[i]);
	}
	vector<webpage> sorted_websites;
	for (int i = 0; i < numbered_results.size(); i++)
	{
		sorted_websites.push_back(mapped_websites[numbered_results[i]]);
		sorted_websites[i].set_number(numbered_results[i]);
	}
	heap_sort(sorted_websites, sorted_websites.size());

	return sorted_websites;



}
vector <webpage> sorted_results;
void search_steps(int CASE, vector <string >SEARCHED_WORDS) {
	vector <int> vector_1, vector_2;
	switch (CASE)
	{
	case 1:
	{
		vector_1 = search_word(SEARCHED_WORDS[0]);
		vector_2 = search_word(SEARCHED_WORDS[2]);
		numbered_results = intersection(vector_1, vector_2);
		sorted_results.clear();
		sorted_results = sort_webpages(numbered_results);
		display_results(sorted_results);

	}
	case 2:
	{
		numbered_results = search_word(SEARCHED_WORDS[0]);

		for (int i = 1; i < SEARCHED_WORDS.size(); i++) {
			numbered_results = Union(numbered_results, search_word(SEARCHED_WORDS[i]));
		}
		/*for (int i = 0; i < numbered_results.size(); i++) {
			cout << numbered_results[i] << endl;
		}*/
		sorted_results = sort_webpages(numbered_results);
		display_results(sorted_results);

	}
	case 3: {
		for (int i = 0; i < SEARCHED_WORDS.size(); i++)
		{
			for (int j = 0; j < SEARCHED_WORDS[i].length(); j++)
			{
				if (SEARCHED_WORDS[i][j] == '\"')
				{
					SEARCHED_WORDS[i].erase(j, 1);
					j--;
				}
			}
		}




		string st = SEARCHED_WORDS[0];

		for (int i = 1; i < SEARCHED_WORDS.size(); i++) {
			st += " " + SEARCHED_WORDS[i];
		}

		numbered_results.clear();
		numbered_results = search_word(st);
		/*for (int i = 0; i < numbered_results.size(); i++) {
			cout << numbered_results[i] << endl;
		}*/
		sorted_results = sort_webpages(numbered_results);
		display_results(sorted_results);

	}

	}
}





void search() {
	cout << "\nSearch for:";
	string key;
	
	cin.ignore();
	getline(cin, key);

	string word;
	stringstream s(key);
	int Case = 2;

	vector <string> searched_Words;
	while (getline(s, word, ' '))
	{
		searched_Words.push_back(word);
	}

	string word2;
	bool lastcase = false;
	stringstream s2(key);
	while (getline(s2, word2, ' '))
	{

		if (word2 == "AND")
		{
			Case = 1;
			lastcase = true;
			search_steps(Case, searched_Words);
			break;
		}
		else if (word2 == "OR")
		{
			Case = 2;
			lastcase = true;
			search_steps(Case, searched_Words);
			break;
		}
		else if (word2[0] == '\"')
		{
			Case = 3;
			lastcase = true;
			search_steps(Case, searched_Words);

			break;
		}


	}

	// this was just to validate


	/*for (int i = 0; i < searched_Words.size(); i++) {

		cout << searched_Words[i]<< "  "<< endl;
	}*/

	if (lastcase == false) {
		search_steps(Case, searched_Words);
	}
	//cout << Case << endl;
}

void rewrite_ctr()
{
	ofstream myfile;



	myfile.open("impressions.csv");
	if (myfile.fail()) {
		cout << "errorrr" << "," << endl;
		exit(-1);
	}

	for (int i = 0; i < websites.size(); i++) {
		myfile << websites[i].get_name() << "," << websites[i].get_impressions() << "," << websites[i].get_clicks() << endl;
	}


	myfile.close();
}

void welcome_menu() {

	int choice1;
	cout << "Welcome!\n What would you like to do?\n 1. New Search.\n2. Exit." << endl;
	cout << "Enter your choice:__";
	do {
		cin >> choice1;
		switch (choice1)
		{
		case 1:
		{
			search();

			break;
		}
		case 2:
		{
			rewrite_ctr();
			exit(0);
			break;
		}
		default:
		{
			cout << "Invalid input!!" << endl << "Enter yout chice:--" << endl;
			break;
		}
		}
	} while (choice1 != 1 && choice1 != 2);
}


//vector <webpage> results;

void print_vector(vector <string> file_content) {
	for (int i = 0; i < file_content.size(); i++)
	{

		cout << file_content[i] << " ";

		cout << "\n";
	}

}


void print_websites(vector <webpage> websites) {// this is just to validate that what we add to the objects is correct

	for (int i = 0; i < websites.size(); i++) {
		cout << "website " << i + 1 << "  name is " << websites[i].get_name() << endl;
		cout << "website " << i + 1 << "  impressions is " << websites[i].get_impressions() << endl;

		cout << "website " << i + 1 << "  clicks is " << websites[i].get_clicks() << endl;
		cout << "website " << i + 1 << "  out pages are : " << endl;
		for (int j = 0; j < websites[i].pages_out.size(); j++) {
			cout << websites[i].pages_out[j].get_name() << "   ";
		}

		cout << "website " << i + 1 << "  in pages are : " << endl;
		for (int j = 0; j < websites[i].pages_in.size(); j++) {
			cout << websites[i].pages_in[j].get_name() << "   ";
		}
		cout << endl << endl;

	}
	cout << endl << endl;
	for (int i = 0; i < websites.size(); i++) {
		cout << "website " << i + 1 << "  key words are  " << endl;
		for (int j = 0; j < websites[i].keywords.size(); j++) {
			cout << websites[i].keywords[j] << ",";
		}
		cout << endl << endl;
	}
}

void read_links(string file_name) {

	vector<string> file_content;
	//vector<string> row;
	string line, word;

	fstream csv_file(file_name, ios::in);
	if (csv_file.is_open())
	{
		while (getline(csv_file, line))
		{
			//row.clear();

			stringstream str(line);

			while (getline(str, word, ','))
				file_content.push_back(word);

		}
	}
	else
		cout << "Error opening file\n";
	int src_ind = 0, dest_ind = 0;
	//print_vector(file_content);
	for (int i = 0; i < file_content.size(); i += 2) {
		for (int j = 0; j < websites.size(); j++) {
			if (file_content[i] == websites[j].get_name()) {
				src_ind = j;

			}

			if (file_content[i + 1] == websites[j].get_name()) {
				dest_ind = j;

			}

		}
		websites[src_ind].pages_out.push_back(websites[dest_ind]);
		websites[dest_ind].pages_in.push_back(websites[src_ind]);

	}
	//print_websites(websites);

};
void read_keywords(string file_name) {
	vector<vector<string>> file_content;
	vector<string> row;
	string line, word;

	fstream csv_file(file_name, ios::in);
	if (csv_file.is_open())
	{
		while (getline(csv_file, line))
		{

			row.clear();

			stringstream str(line);


			while (getline(str, word, ','))
				row.push_back(word);
			int pind = 0;
			for (int k = 0; k < websites.size(); k++) {
				if (*row.begin() == websites[k].get_name()) {
					pind = k;

				}
			}
			row.erase(row.begin());
			for (int j = 0; j < row.size(); j++) {
				websites[pind].keywords.push_back(row[j]);

			}
			file_content.push_back(row);
		}
	}
	else
		cout << "Error opening file\n";



}
void open_webpage() {
	int page_num=0;
	cout << "type in the number of page you want to open" << endl;
	cin >> page_num;
	while (page_num > numbered_results.size() && page_num < 0) {
		cout << "invalid input , enter choice again :" << endl;
		cin >> page_num;
	}
	cout << "you are now viewing   " << sorted_results[page_num - 1].get_name() << endl;
	
	
	websites[sorted_results[page_num - 1].get_number() - 1].pclicks++;
	cout << "  num of clicks " <<websites[(sorted_results[page_num-1].get_number())-1].get_clicks();
	
	websites[sorted_results[page_num - 1].get_number() - 1].set_pctr();
	websites[sorted_results[page_num - 1].get_number() - 1].set_pscore();
	cout << "Would you like to \n 1.back to search results \n 2. New search\n 3.Exit " << endl;
	cout << "Type in your choice:__";
	int choice1;
	do {
		cin >> choice1;
		switch (choice1)
		{
		case 1:
		{
			display_results(sorted_results);
			break;
		}
		case 2:
		{
			rewrite_ctr();
			search();

			break;

		}
		case 3: {
			rewrite_ctr();
			exit(0);
			break;
		}
		default:
		{
			cout << "Invalid input!!" << endl << "Enter yout chice:--" << endl;
			break;
		}
		}
	} while (choice1 != 1 && choice1 != 2 && choice1 != 3);





}
void before_opening() {
	cout << "Would you like to: \n 1.Choose a webpage to open \n 2. New search\n 3.Exit " << endl;
	cout << "Type in your choice:__";
	int choice1;
	do {
		cin >> choice1;
		switch (choice1)
		{
		case 1:
		{
			open_webpage();
			break;
		}
		case 2:
		{	
		search();

		break;
			
		}
		case 3: {
			rewrite_ctr();
			exit(0);
			break;
		}
		default:
		{
			cout << "Invalid input!!" << endl << "Enter yout chice:--" << endl;
			break;
		}
		}
	} while (choice1 != 1 && choice1 != 2&& choice1 !=3);
}

void display_results(vector <webpage> &sorted_results) {

	cout << "Search results :" << endl;
	for (int i = 0; i < sorted_results.size(); i++) {
		cout << i+1 << ")"<< " "<< sorted_results[i].get_name() << endl;
		websites[numbered_results[i]-1].set_pimpressions((websites[numbered_results[i] - 1].get_impressions()) + 1);
		websites[numbered_results[i] - 1].set_pctr();
		websites[numbered_results[i] - 1].set_pscore();
	
	}
	before_opening();
}



int main()
{
	read_websites("impressions.csv");

	read_links("websites.csv");
	
	read_keywords("keywords.csv");
	
	welcome_menu();
	//print_websites(websites);
	//search();
	//cout << mapped_websites[2].get_name() << endl;
	///cout << websites[2].get_number() << endl;



	


	


	
	





	return 0;

}
