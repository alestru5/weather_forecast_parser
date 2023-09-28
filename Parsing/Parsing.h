#ifndef PARSING_H
#define PARSING_H

#include <iostream>
#include <string>
#include <limits>
#include <compare>
#include "cstring"
#include <curl/curl.h>
#include <gumbo.h>
#include <vector>
#include "algorithm"
std::string request();
std::vector<std::string> scrape(std::string markup);
void find_definitions(GumboNode *node);
std::string extract_text(GumboNode *node);
std::string str_replace(std::string search, std::string replace, std::string &subject);
#endif