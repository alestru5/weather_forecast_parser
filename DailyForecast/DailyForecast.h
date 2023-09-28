#ifndef DAILYFORECAST_H
#define DAILYFORECAST_H

#include <iostream>
#include <string>
#include <limits>
#include <compare>

/**
* @brief struct Date
*/

struct Date
{
	int day;
	int mount;
};

/**
* @brief enum for weather 
*/

enum class weather_type
{
	sunny,
	cloudy,
	rain,
	snow
};

/**
* @brief Class DailyForecast
* @param maxPrecipitation - const max precipitation = 1500
* @param maxPrecipitation - const min Temperature = -100
* @param maxPrecipitation - const max Temperature = 60
* @param Date
* @param morningT
* @param dayT
* @param eveningT
*/

class DailyForecast
{
private:
	static constexpr double maxPrecipitation = 1500;
	static constexpr double minTemperature = -100;
	static constexpr double maxTemperature = 60;
	Date date;
	double morningT;
	double dayT;
	double eveningT;
	weather_type weather;
	double precipitation;
public:
	/**
	* @brief costructor default
	*/
	DailyForecast();
	/**
	* @brief costructor with all parametr
	*/
	DailyForecast(Date, double, double, double, weather_type, double);
	/**
	* @brief costructor with three paramet
	* @param Date - date
	* @param double - temperature
	* @param double - precepitation
	*/
	DailyForecast(Date, double, double);
	/**
	* @brief check temperature
	*/
	void check_temperature_snow(double);
	/**
	* @brief check precepitation
	*/
	void check_precipitation(double);
	/**
	* @brief Setter by dayT
	*/
	DailyForecast& SetDayT(double);
	/**
	* @brief Setter by morningT
	*/
	DailyForecast& SetMorningT(double);
	/**
	* @brief Setter by eveningT
	*/
	DailyForecast& SetEveningT(double);
	/**
	* @brief Setter by date
	*/
	DailyForecast& SetDate(Date);
	/**
	* @brief Setter by precepitation
	*/
	DailyForecast& SetPrecipitation(double);
	/**
	* @brief Setter by weather
	*/
	DailyForecast& SetWeather(weather_type);
	/**
	* @brief Getter by Date
	* @return date(Date)
	*/
	Date GetDate() const;
	/**
	* @brief Getter by weather
	* @return weather(weather_type)
	*/
	weather_type GetWeather()const;
	/**
	* @brief Getter by temperature
	* @return eveningT(double)
	*/
	double GetEveningT() const;
	/**
	* @brief Getter by temperature
	* @return dayT(double)
	*/
	double GetDayT() const;
	/**
	* @brief Getter by temperature
	* @return morningT(double)
	*/
	double GetMorningT() const;
	/**
	* @brief Getter by precepitation
	* @return precepitation(double)
	*/
	double GetPr() const;
	/**
	* @brief average_temperature
	* @return temperature(double)
	*/
	double average_temperature();
	/**
	* @brief friend operator >>
	* @param DailyForecast & - parametr by this class
	* @return std::istream& 
	*/
	friend std::istream& operator>>(std::istream&, DailyForecast&);
	/**
	* @brief this metod return average temperature and average  precepitation and the bad weather
	* @return *this
	*/
	DailyForecast& operator += (const DailyForecast&);
	DailyForecast& operator = (const DailyForecast&);
	/**
	* @brief metod comparison 
	* return std::strong_oredering(less, equal, greater)
	*/
	std::strong_ordering operator <=>(const DailyForecast&) const;
	bool operator ==(const DailyForecast& other) const {
		return ((*this) <=> other) == std::strong_ordering::equal;
	}
	/**
	* @brief friend operator <<
	* @param DailyForecast & - parametr by this class
	* @return std::ostream&
	*/
	friend std::ostream& operator<<(std::ostream&, const DailyForecast&);
};

template <class T>
T getNum(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max())
{
	T number;
	while (true)
	{
		std::cin >> number;
		if (std::cin.eof())
		{
			throw std::runtime_error("It is EOF, sorry\n");
		}
		else if (std::cin.bad())
		{
			throw std::runtime_error("WTF?!\n");
		}
		else if (std::cin.fail() || number < min || number > max)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "You are wrong; repeat please!" << std::endl;
		}
		else return number;
	}
}

#endif 