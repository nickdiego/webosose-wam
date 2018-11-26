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

#include "WebAppFactoryLuna.h"

#include "ApplicationDescription.h"
#include "WebAppWaylandWebOS.h"
#include "WebPageBase.h"
#include "WebAppBase.h"
#include "WebAppWayland.h"
#include "WebPageBlink.h"
#include "WindowTypes.h"
#include "LogManager.h"

WebAppBase* WebAppFactoryLuna::createWebApp(const std::string& winType, std::shared_ptr<ApplicationDescription> desc)
{
    WebAppBase* app = nullptr;

    if(winType == WT_CARD || winType == WT_POPUP || winType == WT_MINIMAL || winType == WT_FLOATING) {
        app = new WebAppWaylandWebOS(winType, desc);
    } else if(winType == WT_OVERLAY) {
        app = new WebAppWayland(winType, desc->surfaceId());
    } else if(winType == WT_SYSTEM_UI) {
        app = new WebAppWayland(winType, desc->surfaceId());
    } else if(winType == WT_NONE) {
        app = new WebAppWayland(winType, desc->surfaceId());
    } else {
        LOG_WARNING(MSGID_BAD_WINDOW_TYPE, 1,
                    PMLOGKS("WINDOW_TYPE", qPrintable(winType)), "");
    }
    return app;
}

WebAppBase* WebAppFactoryLuna::createWebApp(const std::string& winType, WebPageBase* page, std::shared_ptr<ApplicationDescription> desc)
{
    return createWebApp(winType, desc);
}

WebPageBase* WebAppFactoryLuna::createWebPage(const Url& url, std::shared_ptr<ApplicationDescription> desc, const std::string& launchParams)
{
    return new WebPageBlink(url, desc, launchParams);
}

