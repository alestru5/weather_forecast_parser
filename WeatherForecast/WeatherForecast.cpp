#include "WeatherForecast.h"


namespace Prog3 {

	WeatherForecast::WeatherForecast(const DailyForecast& one) : data(new DailyForecast[max_size]()), csize(1)
	{
		data[0] = one;
	}

	WeatherForecast::WeatherForecast(size_t count, const DailyForecast* array) : data(new DailyForecast[max_size]()), csize(count)
	{
		std::copy(array, array + count, data);
	}

	WeatherForecast::WeatherForecast(const WeatherForecast& w) : WeatherForecast(w.csize, w.data) {}

	WeatherForecast::WeatherForecast(WeatherForecast&& w) noexcept : csize(w.csize), data(w.data)
	{
		w.data = nullptr;
		w.csize = 0;
	}

	WeatherForecast& WeatherForecast::operator = (WeatherForecast&& w) noexcept
	{
		if (this != &w)
		{
			csize = 0;
			delete[] data;
			data = w.data;
			csize = w.csize;
			w.data = nullptr;
			w.csize = 0;
		}
		return *this;
	}

	WeatherForecast& WeatherForecast::operator = (const WeatherForecast& w)
	{
		if (this != &w)
		{
			DailyForecast* d = new DailyForecast[max_size]();
			csize = w.csize;
			delete[] data;
			data = d;
			std::copy(w.data, w.data + w.csize, data);
		}
		return *this;
	}

	std::ostream& operator<<(std::ostream& s, const WeatherForecast& w)
	{
		for (int i = 0; i < w.csize; i++)
		{
			s << w.data[i] << "\n";
		}
		return s;
	}

	std::istream& operator>>(std::istream& s, WeatherForecast& w)
	{
		int x;
		s >> x;
		if (s.good())
		{
			if (x < w.max_size)
			{
				w.csize = 0;
				for (int i = 0; i < x; i++)
				{
					s >> w.data[i];
				}
				w.csize += x;
			}
			else
			{
				s.setstate(std::ios::failbit);
			}
		}
		return s;
	}

	DailyForecast& WeatherForecast::operator[](int index)
	{
		if (index < 0 || index >= max_size || index >= csize)
		{
			throw std::invalid_argument("Invalid\n");
		}
		return data[index];
	}

	WeatherForecast& WeatherForecast::operator+=(const DailyForecast& one)
	{
		if (csize >= max_size)
		{
			throw std::runtime_error("Error\n");
		}
		data[csize] = one;
		csize++;
		return *this;
	}

	bool comp(const DailyForecast& a, const DailyForecast& b)
	{
		return a.GetDate().day < b.GetDate().day;
	}

	void WeatherForecast::sortirovka()
	{
		std::sort(data, data + csize, comp);
	}

	void WeatherForecast::delete_ind(int index)
	{
		for (int i = index; i < csize - 1; i++)
		{
			data[i] = data[i + 1];
		}
		csize--;
	}

	void WeatherForecast::SET(WeatherForecast& w, int mount)
	{
		if (this->csize != 0)
		{
			throw std::invalid_argument("This WeatherForecast is not emty\n");
		}
		for (int i = 0; i < w.csize; i++)
		{
			if (w.data[i].GetDate().mount == mount)
			{
				this->data[csize] = w.data[i];
				this->csize++;
			}
		}
		if (this->csize != 0)
		{
			sortirovka();
		}
	}

	void WeatherForecast::unification()
	{
		std::stack <int> st;
		for (int i = 0; i < csize - 1; i++)
		{
			for (int j = i + 1; j < csize; j++)
			{
				if ((data[i] < data[j]))
				{
					st.push(j);
				}
			}		
		}
		while (!st.empty())
		{
			delete_ind(st.top());
			st.pop();
		}
	}
}