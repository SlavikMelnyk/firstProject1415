#include "HTMLService.h"
#include <fstream>
#include <string>

using namespace std;

void HTMLService::write(int id, const Date& start, const Date& end)
{
	//Change the direction if you want
	ofstream file("History.html");
	file << "<!DOCTYPE html>\n";
	file << "<html>\n";

	string head = "<head>\n"
				  "<title>Purchase history</title>\n"
				  "<meta charset=\"UTF-8\"/>\n"
				  "<style type=\"text/css\">\n"
				  "* { font-family: Verdana; }"
				  "h1 { font-size: 2em; font-weight: normal; text-align: center; }"
				  "p { font-size: 1.25em; }"
				  "</style>\n"
				  "</head>";

	file << head;

	string body = "<body>\n";

	ifstream history(to_string(id) + ".txt");

	//Someone please write the loop

	body += "</body>\n";

	file << body;

	file << "</html>";
	file.close();
}