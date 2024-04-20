/*
=============================================================================
Title : api.cpp
Description : This file performs GET and PUT API methods to a localhost. It then prints the response.
Author : Carson Spaniel (R#11712895)
Date : 04/18/2024
Version : 1.1
Usage : Compile and run this program using the GNU C++ compiler
Notes : Run chmod +x * in order to apply permissions.
C++ Version : Version 11
=============================================================================
*/

#include <iostream>
#include <curl/curl.h>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  ((std::string*)userp)->append((char*)contents, size * nmemb);
  return size * nmemb;
}

void send_put(std::string endpoint) {
  /*
	description: Function to perform PUT requests.
	Params:
	  - endpoint(string): contains a string for the endpoint that I want to hit
	  - apiData(string): contains the data to be sent
	returns: None
  */

  // Initialize libcurl
  curl_global_init(CURL_GLOBAL_ALL);

  // Create a curl handle
  CURL* curl = curl_easy_init();

  if (curl) {
    struct curl_slist *headers = NULL;

    // Initialize the headers for PUT request
    headers = curl_slist_append(headers, "Content-Type: application/json");

    // Concatenate the full endpoint
    std::string fullEndpoint = "http://localhost:5432/"+endpoint;

    // Set everything up for the curl
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL, fullEndpoint.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");

    // Perform the PUT request
    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
      std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
    }

    // Cleanup the curl handle
    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();
}

std::string send_get(std::string endpoint) {
  /*
        description: Function to perform GET requests.
        Params:
          - endpoint(string): contains a string for the endpoint that I want to hit
        returns: string of the integer from the response
  */
  

  // Initialize libcurl
  curl_global_init(CURL_GLOBAL_ALL);

  // Create a new curl handle for the GET request
  // Create a curl handle
  CURL* curl = curl_easy_init();
  
  // Create a string buffer to hold response data
  std::string buffer;

  if (curl) {
    // Concatenate the full endpoint
    std::string fullEndpoint = "http://localhost:5432/"+endpoint;

    // Set everything for the curl
    curl_easy_setopt(curl, CURLOPT_URL, fullEndpoint.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

    // Perform the GET request
    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
      std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
    }

    // Cleanup the curl handle
    curl_easy_cleanup(curl);
  }

  // Cleanup libcurl
  curl_global_cleanup();

  return buffer;
}