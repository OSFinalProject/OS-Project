/*
=============================================================================
Title : client.cpp
Description : This file performs GET and PUT API methods to a localhost. It then prints the response.
Author : Carson Spaniel (R#11712895)
Date : 02/29/2024
Version : 1.0
Usage : Compile and run this program using the GNU C++ compiler
Notes : Run chmod +x * in order to apply permissions.
C++ Version : Unknown
=============================================================================
*/

#include <iostream>
#include <curl/curl.h>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  ((std::string*)userp)->append((char*)contents, size * nmemb);
  return size * nmemb;
}

void send_put(std::string endpoint, std::string apiData) {
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

    // Set the request data to the integer value
    // std::string data = apiData;

    // Initalize the headers for PUT request
    headers = curl_slist_append(headers, "Content-Type: application/json");

    // Concatenate the full endpoint
    std::string fullEndpoint = "http://localhost:5432/"+endpoint;

    // Set everything up for the curl
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL, fullEndpoint.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
    // curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

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

    // Print the response body
    std::cout <<  buffer << std::endl;
  }

  // Cleanup libcurl
  curl_global_cleanup();

  return buffer;
}

int main() {
  // Print Name and R#
  std::cout << "Carson Spaniel\n";
  std::cout << "R11712895\n";

  // Perform PUT requests
  send_put("initialize","3360");
  send_put("modify","4");

  // Perform GET requests and store the output
  std::string initInt = send_get("initialize");
  std::string modInt = send_get("modify");

  // Perform PUT requests with new values
  send_put("initialize",modInt);
  send_put("modify",initInt);

  // Perform new GET requests
  std::string newInit = send_get("initialize");
  std::string newMod = send_get("modify");
  
  return 0;
}
