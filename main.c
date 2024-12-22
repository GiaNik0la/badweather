#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>

int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "not enough arguments\n");
		return 1;
	}

	const char* API_KEY = "PUT YOUR API KEY HERE";
	char* url = malloc(sizeof(char) * 100);

	snprintf(url, 100, "http://api.weatherapi.com/v1/current.json?key=%s&q=%s,%s&aqi=no",
			API_KEY,
			argv[1], argv[2]);

	CURL* curl = curl_easy_init();
	CURLcode res;

	if (!curl) {
		fprintf(stderr, "curl could not be initialized\n");
		return 1;
	}

	res = curl_easy_setopt(curl, CURLOPT_URL, url);

	if (res != CURLE_OK) {
		fprintf(stderr, "%s\n", curl_easy_strerror(res));
		return 1;
	}

	res = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	if (res != CURLE_OK) {
		fprintf(stderr, "%s\n", curl_easy_strerror(res));
		return 1;
	}

	res = curl_easy_perform(curl);
	
	if (res != CURLE_OK) {
		fprintf(stderr, "%s\n", curl_easy_strerror(res));
		return 1;
	}

	printf("\n");

	curl_easy_cleanup(curl);
	return 0;
}
