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

#ifndef WEBAPPFACTORYAGL_H
#define WEBAPPFACTORYAGL_H

#include <string>

#include "WebAppFactoryInterface.h"

class WebAppFactoryAGL : public WebAppFactoryInterface {
public:
    virtual WebAppBase* createWebApp(const std::string& winType, std::shared_ptr<ApplicationDescription> desc = 0);
    virtual WebAppBase* createWebApp(const std::string& winType, WebPageBase* page, std::shared_ptr<ApplicationDescription> desc = 0);
    virtual WebPageBase* createWebPage(const Url& url, std::shared_ptr<ApplicationDescription> desc, const std::string& launchParams = "");
};

#endif /* WEBAPPFACTORYAGL_H */
