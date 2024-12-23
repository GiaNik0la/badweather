#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
	char *str;
	size_t size;
} Response;

size_t write_chunk(void *data, size_t size, size_t nmemb, void *usrdata);

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
	CURLcode code;

	if (!curl) {
		fprintf(stderr, "curl could not be initialized\n");
		return 1;
	}

	Response res;
	res.str = malloc(1);
	res.size = 0;

	code = curl_easy_setopt(curl, CURLOPT_URL, url);

	if (code != CURLE_OK) {
		fprintf(stderr, "%s\n", curl_easy_strerror(code));
		return 1;
	}

	code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_chunk);

	if (code != CURLE_OK) {
		fprintf(stderr, "%s\n", curl_easy_strerror(code));
		return 1;
	}

	code = curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*) &res);

	if (code != CURLE_OK) {
		fprintf(stderr, "%s\n", curl_easy_strerror(code));
		return 1;
	}

	code = curl_easy_perform(curl);
	
	if (code != CURLE_OK) {
		fprintf(stderr, "%s\n", curl_easy_strerror(code));
		return 1;
	}

	printf("%s\n", res.str);

	free(res.str);

	curl_easy_cleanup(curl);
	return 0;
}

size_t write_chunk(void *data, size_t size, size_t nmemb, void *usrdata) {
	size_t realsize = nmemb * size;
	Response *res = (Response *)usrdata;

	char *ptr = realloc(res->str, res->size + realsize + 1);

	if (ptr == NULL) {
		return CURL_WRITEFUNC_ERROR;
	}

	res->str = ptr;
	memcpy(&(res->str[res->size]), data, realsize);
	res->size += realsize;
	res->str[res->size] = 0;

	return realsize;
}

