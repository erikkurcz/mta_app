// General utilities

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>


std::string SITE_BASE("http://datamine.mta.info/mta_esi.php?key=");

std::string get_api_key(void)
{
	// Open file and read key
	std::string api_key;
	std::string line;
	std::ifstream infile("data/api_key.data");

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		iss >> api_key;
	}
	return api_key;	
}

std::string form_site_link(std::string line, std::string feed_id)
{
	std::stringstream ss;
	ss << SITE_BASE << get_api_key() << line << "&feed_id=" << feed_id;
	return ss.str();
}

std::map<std::string, std::string>* get_line_site_map(void)
{
	// create the map of url:filename
	std::map<std::string, std::string>* map = new std::map<std::string, std::string>;
	typedef std::pair<std::string, std::string> mappair;
	
	std::string subwayline;
	std::string feed_id;
	std::string line;
	std::string site;

	// open and read file
	std::ifstream infile("data/lines_and_feeds.data");

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		iss >> subwayline >> feed_id;
		site = form_site_link(subwayline, feed_id);
	       	map->insert(mappair(subwayline, site));
	}

	return map;
}
