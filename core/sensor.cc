/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "chre/core/sensor.h"

namespace chre {

Sensor::Sensor() {}

Sensor::Sensor(const PlatformSensor& platformSensor)
    : mPlatformSensor(platformSensor) {}

SensorType Sensor::getSensorType() const {
  return isValid() ? mPlatformSensor->getSensorType() : SensorType::Unknown;
}

bool Sensor::isValid() const {
  return mPlatformSensor.has_value();
}

bool Sensor::setRequest(const SensorRequest& request) {
  bool requestWasSet = false;
  if (isValid() && !request.isEquivalentTo(mSensorRequest)
      && mPlatformSensor->setRequest(request)) {
    mSensorRequest = request;
    requestWasSet = true;
  }

  return requestWasSet;
}

Sensor& Sensor::operator=(Sensor&& other) {
  mSensorRequest = other.mSensorRequest;
  mPlatformSensor = other.mPlatformSensor;
  return *this;
}

bool Sensor::isOneShot() const {
  return isValid() ? mPlatformSensor->isOneShot() : false;
}

bool Sensor::isOnChange() const {
  return isValid() ? mPlatformSensor->isOnChange() : false;
}

uint64_t Sensor::getMinInterval() const {
  return isValid() ? mPlatformSensor->getMinInterval() :
      CHRE_SENSOR_INTERVAL_DEFAULT;
}

}  // namespace chre
