/*
 * observer_pattern.cpp
 *
 *  Created on: 26 May 2017
 *      Author: yogeshb2
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class IWeatherChanger
{
	public :
	virtual ~IWeatherChanger(){}
	virtual void OnTemperatureChange(int temperature) = 0;
};

class ITemperature
{
	public :
	virtual ~ITemperature(){}
	virtual void AddSubscriber(IWeatherChanger* w) = 0;
	virtual void RemoveSubscriber(IWeatherChanger* w) = 0;
	virtual void NotifyAllSubscriber() = 0;
};

class Weather : public ITemperature
{
	public :
		Weather():temperature(0)
		{

		}
		void AddSubscriber(IWeatherChanger* w)
		{
			if(w)
			{
				subscriberlist.push_back(w);
			}
		}
		void RemoveSubscriber(IWeatherChanger* w)
		{
			//TODO
			if(w)
			{
				vector<IWeatherChanger*>::iterator it = find(subscriberlist.begin(),subscriberlist.end(),w);
				if(it != subscriberlist.end())
				{
					subscriberlist.erase(it);
				}
				else
				{
					cout << "Not a registered subscriber"<<endl;
				}
			}
		}
		void NotifyAllSubscriber()
		{
			if(!subscriberlist.empty())
			{
				vector<IWeatherChanger*>::iterator it;
				for (it = subscriberlist.begin(); it != subscriberlist.end(); ++it)
				{
					(*it)->OnTemperatureChange(temperature);
				}
			}
		}
		void ChangeTemperature(int temp)
		{
			temperature = temp;
			NotifyAllSubscriber();
		}
	private :
		int temperature;
		vector<IWeatherChanger*> subscriberlist;

};


class NewsChannel : public IWeatherChanger
{
	public :
	NewsChannel()
	{

	}
	NewsChannel(string name)
	{
		this->name = name;
	}
	void OnTemperatureChange(int temperature)
	{
		cout << "Channel name : "<< name << " Temperature : " << temperature;
		cout << "\n";
	}
	private :
	string name;

};

int main(int argc, char **argv)
{
	Weather weather;
	NewsChannel fox("Fox News");
	NewsChannel times("Times News");
	weather.AddSubscriber(&fox);
	weather.AddSubscriber(&times);

	weather.ChangeTemperature(25);

	weather.ChangeTemperature(20);

	weather.RemoveSubscriber(&fox);

	weather.ChangeTemperature(10);

	return 0;
}
