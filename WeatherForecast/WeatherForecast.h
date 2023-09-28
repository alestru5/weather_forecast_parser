#ifndef WEATHERFORECAST_H
#define WEATHERFORECAST_H

#include <iostream>
#include <cstdlib>
#include "../DailyForecast/DailyForecast.h"
#include <algorithm>
#include <stack>


namespace Prog3 {
	/**
	* @brief Class WeatherForecast
	* @param msize - max size by data
	* @param csize - current size
	* @param data - array with DailyForecast(use dynamic)
	*/
	
	class WeatherForecast
	{
	private:
		static constexpr size_t max_size = 14;
		size_t csize{ 0 };
		DailyForecast* data;
	public:
		/**
		* @brief costructor init data, use new
		*/
		WeatherForecast() : data(new DailyForecast[max_size]()) {};
		/**
		* @brief costructor with one DailyForecast
		* @param  - const &
		*/
		WeatherForecast(const DailyForecast&);
		/**
		* @brief costructor with one DailyForecast
		* @param - size by type size_t
		* @param  - const array*
		*/
		WeatherForecast(size_t, const DailyForecast*);
		/**
		* @brief costructor copy
		* @param  - const WeatherForecst&
		*/
		WeatherForecast(const WeatherForecast&);
		/**
		* @brief costructor peremech(I am pusy, bacause i do not know English)
		* @param  - const WeatherForecst&
		*/
		WeatherForecast(WeatherForecast&&) noexcept;
		/**
		* @brief distructor delete data
		*/
		~WeatherForecast() { delete[] data; }
		/**
		* @brief operator = (for per construct )
		* @param rvalue &
		*/
		WeatherForecast& operator = (WeatherForecast&&) noexcept;
		/**
		* @brief operator = (for copy construct )
		* @param value &
		*/
		WeatherForecast& operator =(const WeatherForecast&);
		size_t GetCsize() const { return csize; };
		/**
		* @brief function - return elem by this index
		* @param - index
		* @return param about this index
		*/
		DailyForecast& operator[](int);
		/**
		* @brief function sort
		*/
		void sortirovka();
		/**
		* @brief function - delete element by this index
		* @param - index
		*/
		void delete_ind(int);
		/**
		* @brief friend operator >>
		* @param - std::istream& - input
		* @param  -  & on my type
		*/
		friend std::istream& operator>>(std::istream&, WeatherForecast&);
		/**
		* @brief friend operator <<
		* @param - std::istream& - otput
		* @param  -  const & on my type
		*/
		friend std::ostream& operator<<(std::ostream&, const WeatherForecast&);
		/**
		* @brief WeatherForecast& operator += add new param in data
		* @param - new param
		* @return *this
		*/
		WeatherForecast& operator += (const DailyForecast&);
		/**
		* @brief set - setting
		* @param - mount
		*/
		void SET(WeatherForecast&, int);
		void unification();
	};
}
#endif