// Web access via libcurl for pinging NYC MTA site for data

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <map>

#include <curl/curl.h>
#include "protobufs/nyct-subway.pb.h"
#include "protobufs/gtfs-realtime.pb.h"
#include "utils/utils.cc"
#include <google/protobuf/util/json_util.h>

std::string GTFS_PATH = "data/gtfs";

// Parse file into protobuf objects
bool parse_file(void)
{
	NyctTripDescriptor subway_data;

	// Parse file of gtfs data in order to work with protobuf 
	std::fstream gtfs(GTFS_PATH, std::ios::in | std::ios::binary);

	if (!gtfs)
	{
		std::cerr << "Error opening GTFS data: " << strerror(errno) << std::endl;
		return false;
	}
	else if (!subway_data.ParseFromIstream(&gtfs))
	{
		std::cerr << "Error parsing GTFS data" << std::endl;
		return false;
	}
	
	// good to go from here
	std::string json;
	google::protobuf::util::MessageToJsonString(subway_data, &json);
	std::cout << json << std::endl;
	return true;	

}

int main(void)
{
	bool status = parse_file();	
	std::string strstatus = status ? "YAY!" : "NAWWWWWWW";
	std::cout << "Parsing status: " << strstatus << std::endl;
	return 0;
}

