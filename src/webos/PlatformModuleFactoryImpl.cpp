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

#include "PlatformModuleFactory.h"

#include "PlatformModuleFactoryImpl.h"
#ifdef HAS_LUNA_SERVICE
#include "ServiceSenderLuna.h"
#endif
#include "ContainerAppManager.h"
#include "DeviceInfoImpl.h"
#include "WebAppManagerConfig.h"
#include "BlinkWebProcessManager.h"
#include "WebAppManagerUtils.h"

PlatformModuleFactoryImpl::PlatformModuleFactoryImpl()
{
    prepareRenderingContext();
}

std::unique_ptr<ServiceSender> PlatformModuleFactoryImpl::createServiceSender()
{
#ifdef HAS_LUNA_SERVICE
    return std::unique_ptr<ServiceSenderLuna>(new ServiceSenderLuna());
#else
    return nullptr;
#endif
}

std::unique_ptr<WebProcessManager> PlatformModuleFactoryImpl::createWebProcessManager()
{
    return std::unique_ptr<BlinkWebProcessManager>(new BlinkWebProcessManager());
}

std::unique_ptr<ContainerAppManager> PlatformModuleFactoryImpl::createContainerAppManager()
{
    if(useContainerApp()) {
        return std::unique_ptr<ContainerAppManager>(new ContainerAppManager());
    }

    return nullptr;

}

std::unique_ptr<DeviceInfo> PlatformModuleFactoryImpl::createDeviceInfo()
{
    return std::unique_ptr<DeviceInfoImpl>(new DeviceInfoImpl());
}

std::unique_ptr<WebAppManagerConfig> PlatformModuleFactoryImpl::createWebAppManagerConfig()
{
    return std::unique_ptr<WebAppManagerConfig>(new WebAppManagerConfig());
}

bool PlatformModuleFactoryImpl::useContainerApp()
{
    if (WebAppManagerUtils::getEnv("DISABLE_CONTAINER") == "1")
        return false;

    return true;
}

void PlatformModuleFactoryImpl::prepareRenderingContext()
{
}
