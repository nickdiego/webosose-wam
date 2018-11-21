// Copyright (c) 2014-2018 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <map>
#include <string>

class DeviceInfo {
public:
    virtual ~DeviceInfo() {}

    virtual bool getDisplayWidth(int& value);
    virtual void setDisplayWidth(int value);

    virtual bool getDisplayHeight(int& value);
    virtual void setDisplayHeight(int value);

    virtual bool getSystemLanguage(std::string& value);
    virtual void setSystemLanguage(const std::string& value);

    virtual bool getDeviceInfo(const std::string& name, std::string& value);
    virtual void setDeviceInfo(const std::string& name, const std::string& value);

private:
    std::map<std::string, std::string> m_deviceInfo;
};

#endif /* DEVICEINFO_H */
