struct WeatherForecast {
  int date;
  String weather;
  float min;
  float max;
};

struct TwoDaysWeatherForecasts {
  WeatherForecast today;
  WeatherForecast tomorrow;
};
