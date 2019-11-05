// File parser for protobuf objects

#include <iostream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>

#include <curl/curl.h>
#include <google/protobuf/util/json_util.h>

#include "protobufs/nyct-subway.pb.h"
#include "protobufs/gtfs-realtime.pb.h"
#include "utils/utils.cc"

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

