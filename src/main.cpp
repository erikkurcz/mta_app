// Main for running this application 

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>

struct cli_args {
	std::string station;
	std::string direction;
	std::string route;	
};

static void show_usage(void)
{
	std::cerr << "Usage:\nmta -s|--station []\n"
		  << "-d|--direction [north|south]\n"
		  << "-r|--route [1|2|3|4|5|6|7|S|A|C|E|B|D|F|M|J|Z|G ... \n"
		  << std::endl; 
}

int main(int argc, char* argv[])
{
	cli_args args;
	
	// sanity check	
	if (argc <= 1)
	{
		show_usage();
		return 1; 
	}
	
	// parse out	
	int c;	
	while( (c = getopt(argc, argv, "s:d:r:")) != -1 )
	{
		switch (c)
		{
			case 's':
				args.station = optarg;
				break;
			case 'd':
				args.direction = optarg;
				break;
			case 'r':
				args.route = optarg;
				break;
		}
	}

	std::cout << "Arguments given:"
		  << "\nStation: " << args.station
		  << "\nDirection: " << args.direction
		  << "\nRoute: " << args.route
		  << std::endl;

	// parse file here
	return 0;
}

