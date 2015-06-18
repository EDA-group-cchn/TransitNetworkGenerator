#ifndef TRANSIT_PASSENGER_H
#define TRANSIT_PASSENGER_H


class passenger {
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
  Passenger(int busStopStartId, int busStopEndId, float busStopStartDistance,
            float busStopEndDistance) : busStopStartId(busStopStartId),
                                        busStopEndId(busStopEndId),
                                        busStopStartDistance(
                                            busStopStartDistance),
                                        busStopEndDistance(
                                            busStopEndDistance) { }
};


#endif //TRANSIT_PASSENGER_H
