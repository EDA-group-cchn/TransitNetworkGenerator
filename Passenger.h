#ifndef TRANSIT_PASSENGER_H
#define TRANSIT_PASSENGER_H


class Passenger {
private:
  int busStopStartId, busStopEndId;
  float busStopStartDistance, busStopEndDistance;
public:
  int getBusStopStartId() const {
    return busStopStartId;
  }
  int getBusStopEndId() const {
    return busStopEndId;
  }
  float getBusStopStartDistance() const {
    return busStopStartDistance;
  }
  float getBusStopEndDistance() const {
    return busStopEndDistance;
  }
public:
  Passenger(int busStopStartId=-1, int busStopEndId=-1,
            float busStopStartDistance=0, float busStopEndDistance=0) :
      busStopStartId(busStopStartId), busStopEndId(busStopEndId),
      busStopStartDistance(busStopStartDistance),
      busStopEndDistance(busStopEndDistance) { }
};


#endif //TRANSIT_PASSENGER_H
