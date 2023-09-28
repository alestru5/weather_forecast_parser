#include "Parsing.h"
typedef size_t( * curl_write)(char * , size_t, size_t, std::string * );


std::string request(const std::string &word) {
	CURLcode res_code = CURLE_FAILED_INIT;
	CURL * curl = curl_easy_init();
	std::string result;
	std::string url = "https://world-weather.ru/pogoda/russia/" + word + "/14days/";

	curl_global_init(CURL_GLOBAL_ALL);

	if (curl) {
		curl_easy_setopt(curl,
		CURLOPT_WRITEFUNCTION,
		static_cast < curl_write > ([](char * contents, size_t size,
			size_t nmemb, std::string * data) -> size_t {
			size_t new_size = size * nmemb;
			if (data == NULL) {
			return 0;
			}
			data -> append(contents, new_size);
			return new_size;
		}));
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, & result);
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "simple scraper");

		res_code = curl_easy_perform(curl);

		if (res_code != CURLE_OK) {
		return curl_easy_strerror(res_code);
		}

		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();

	return result;
}

std::string str_replace(std::string search, std::string replace, std::string &subject){
	size_t count;
	for (std::string::size_type pos{};
		subject.npos != (pos = subject.find(search.data(), pos, search.length()));
		pos += replace.length(), ++count){
		subject.replace(pos, search.length(), replace.data(), replace.length());
	}

	return subject;
}

std::string strtolower(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

std::string extract_text(GumboNode *node)
{
	if (node->type == GUMBO_NODE_TEXT){
		return std::string(node->v.text.text);
	}
	else if (node->type == GUMBO_NODE_ELEMENT &&
			node->v.element.tag != GUMBO_TAG_SCRIPT &&
			node->v.element.tag != GUMBO_TAG_STYLE){
		std::string contents = "";
		GumboVector *children = &node->v.element.children;
		for (unsigned int i = 0; i < children->length; ++i){
			std::string text = extract_text((GumboNode *)children->data[i]);
			if (i != 0 && !text.empty()){
				contents.append("");
			}
			contents.append(str_replace(":", ">", text));
		}
		return contents;
	}
	else{
		return "";
	}
}

void split(GumboNode *node, std::vector<std::string> &res){
	GumboAttribute *attr;
	GumboVector *children = &node->v.element.children;
	if (node->type != GUMBO_NODE_ELEMENT){
		return;
	} else{
		attr = gumbo_get_attribute(&node->v.element.attributes, "class");
		if (attr != NULL && strstr(attr->value, "weather-temperature") != NULL){
			std::string tmp = extract_text(node);
			if (tmp.substr(1, tmp.size() - 3).size() == 0){
				res.push_back("0");
			} else{
				res.push_back(tmp.substr(1, tmp.size() - 3));
			}
		} 
		if (attr != NULL && strstr(attr->value, "weather-probability") != NULL ){
			std::string tmp = extract_text(node);
			res.push_back(tmp.substr(0, size(tmp) - 1));
		}
	}
	for (size_t i = 0; i < children->length; ++i){
		split(static_cast<GumboNode *>(children->data[i]), res);
	}
}

void find_definitions(GumboNode *node, std::vector<std::string> &res)
{
	GumboAttribute *attr;
	if (node->type != GUMBO_NODE_ELEMENT){
		return;
	}
	GumboVector *children = &node->v.element.children;
	if ((attr = gumbo_get_attribute(&node->v.element.attributes, "class")) && strstr(attr->value, "weather-short") != NULL){
		std::string tmp = gumbo_get_attribute(&node->v.element.attributes, "id")->value;
		res.push_back(tmp.substr(5, 2));
		res.push_back(tmp.substr(8, 2));
		split(node, res);
	}
	for (size_t i = 0; i < children->length; ++i){
		find_definitions(static_cast<GumboNode *>(children->data[i]), res);
	}
}

std::vector<std::string> scrape(std::string markup)
{
	std::vector<std::string> res;
	GumboOutput *output = gumbo_parse_with_options(&kGumboDefaultOptions,
													markup.data(), markup.length());
	find_definitions(output->root, res);
	gumbo_destroy_output(&kGumboDefaultOptions, output);
	return res;
}
