#include <DataTables.hpp>
#include <Car.hpp>

// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;

std::vector<CarData> initializeCarData()
{
	std::vector<CarData> data(Car::TypeCount);

	data[Car::FastCar].speed = 80.f;
	data[Car::FastCar].texture = Textures::FastCar;
	data[Car::FastCar].directions.push_back(Direction(+45.f, 80.f));
	data[Car::FastCar].directions.push_back(Direction(-45.f, 160.f));
	data[Car::FastCar].directions.push_back(Direction(+45.f, 80.f));

	data[Car::SlowCar].speed = 50.f;
	data[Car::SlowCar].texture = Textures::SlowCar;
	data[Car::SlowCar].directions.push_back(Direction(+45.f,  50.f));
	data[Car::SlowCar].directions.push_back(Direction(  0.f,  50.f));
	data[Car::SlowCar].directions.push_back(Direction(-45.f, 100.f));
	data[Car::SlowCar].directions.push_back(Direction(  0.f,  50.f));
	data[Car::SlowCar].directions.push_back(Direction(+45.f,  50.f));

	return data;
}