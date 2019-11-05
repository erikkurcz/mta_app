// Testing out accessing the web via cpp

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <map>

#include <curl/curl.h>

static size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream)
{
	size_t written = fwrite(ptr, size, nmemb, (FILE*)stream);
	return written;
}

bool iter_sites(std::map<const char*, const char*>* map_ptr, CURL*& handle)
{
	// basic setup 
	FILE* output_file; 
	CURLcode rc;

	// create iterator to beginning of map
	std::map<const char*, const char*>::iterator iter;
	iter = map_ptr->begin();

	// iter and make calls
	while (iter != map_ptr->end())
	{
		// open output file
		output_file = fopen(iter->second, "wb");
		if (!output_file)
		{
			curl_easy_cleanup(handle);
			std::cerr << "Error opening file: " << iter->second << std::endl;
			return -1;
		}
		
		// set up the call and perform
		curl_easy_setopt(handle, CURLOPT_WRITEDATA, output_file);
		curl_easy_setopt(handle, CURLOPT_URL, iter->first);
		rc = curl_easy_perform(handle);

		// some light logging
		std::cout << "Status code for site: " << iter->first << ": " << curl_easy_strerror(rc) << std::endl;

		// close out and flush
		fclose(output_file);

		// error handline
		if (rc == CURLE_OK)
		{
			std::cout << "Data successfully retrieved for: " << iter->first << std::endl;
		}
		else
		{
			std::cerr << "Something went wrong for: " << iter->first << " : " << curl_easy_strerror(rc) << std::endl;
		}
	
		iter++;
	}
	
}

int main(void)
{
	// instantiation
	CURL* handle;
	curl_global_init(CURL_GLOBAL_ALL);
	handle = curl_easy_init();
	
	// some option setting
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);

	// create the map of url:filename
	std::map<const char*, const char*> url_to_site;
	typedef std::pair<const char*, const char*> mappair;
	
	// fill the map
	url_to_site.insert(mappair("https://google.com", "google.out"));
	url_to_site.insert(mappair("https://twitter.com", "twitter.out"));
	url_to_site.insert(mappair("https://foursquare.com", "foursquare.out"));
	
	// do the thing	
	iter_sites(&url_to_site, handle);

	// clean up
	curl_easy_cleanup(handle);

	return 0;
}

