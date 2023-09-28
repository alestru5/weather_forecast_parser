#include <iostream>
#include <fstream>
#include "./WeatherForecast/WeatherForecast.h"
#include "./DailyForecast/DailyForecast.h"
#include "./Parsing/Parsing.h"
#include <fstream>

int main()
{

	std::string res = request();
	std::vector<std::string> ans = scrape(res);
	for (size_t i = 0; i < ans.size(); i++){
		std::cout<<ans[i]<<std::endl;
	}
	return 0;
}