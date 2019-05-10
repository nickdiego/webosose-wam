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

#include "ApplicationDescription.h"
#include "JsonHelper.h"
#include "LogManager.h"
#include "PalmSystemBlink.h"
#include "WebAppBase.h"
#include "WebAppWayland.h"
#include "WebPageBlink.h"

#include <QtCore/QDataStream>
PalmSystemBlink::PalmSystemBlink(WebAppBase* app)
    : PalmSystemWebOS(app)
    , m_initialized(false)
{
}

QString PalmSystemBlink::handleBrowserControlMessage(const QString& message, const QStringList& params)
{
    if (message == "initialize") {
        std::string json;
        dumpJsonToString(initialize(), json);
        return QString::fromStdString(json);
    } else if (message == "country") {
        return country();
    } else if (message == "locale") {
        return QString::fromStdString(locale()); // FIXME: PalmSystem: qstr2stdstr
    } else if (message == "localeRegion") {
        return localeRegion();
    } else if (message == "isMinimal") {
        if(isMinimal())
            return QString("true");
        else
            return QString("false");
    } else if (message == "identifier") {
        return identifier();
    } else if (message == "screenOrientation") {
        return screenOrientation();
    } else if (message == "currentCountryGroup") {
        return QString::fromStdString(getDeviceInfo("CountryGroup")); // FIXME: PalmSystem: qstr2stdstr
    } else if (message == "stageReady") {
        stageReady();
    } else if (message == "containerReady") {
        setContainerAppReady(QString::fromStdString(m_app->appId())); // FIXME: PalmSystem: qstr2stdstr
    } else if (message == "activate") {
        LOG_INFO(MSGID_PALMSYSTEM, 2, PMLOGKS("APP_ID", m_app->appId().c_str()), PMLOGKFV("PID", "%d", m_app->page()->getWebProcessPID()), "webOSSystem.activate()");
        activate();
    } else if (message == "deactivate") {
        LOG_INFO(MSGID_PALMSYSTEM, 2, PMLOGKS("APP_ID", m_app->appId().c_str()), PMLOGKFV("PID", "%d", m_app->page()->getWebProcessPID()), "webOSSystem.deactivate()");
        deactivate();
    } else if (message == "isActivated") {
        if(isActivated())
            return QString("true");
        else
            return QString("false");
    } else if (message == "isKeyboardVisible") {
        if(isKeyboardVisible())
            return QString("true");
        else
            return QString("false");
    } else if (message == "getIdentifier" || message == "identifier") {
        return QString(identifier().toUtf8());
    } else if (message == "launchParams") {
        LOG_INFO(MSGID_PALMSYSTEM, 2, PMLOGKS("APP_ID", m_app->appId().c_str()), PMLOGKFV("PID", "%d", m_app->page()->getWebProcessPID()), "webOSSystem.launchParams Updated by app; %s", qPrintable(params[0]));
        updateLaunchParams(params[0]);
    } else if (message == "screenOrientation") {
        QByteArray res;
        QDataStream out(res);
        out << QVariant(screenOrientation());
        return QString(res);
    } else if (message == "keepAlive") {
        if (params.size() > 0)
            setKeepAlive(params[0] == "true");
    } else if (message == "PmLogInfoWithClock") {
#ifdef HAS_PMLOG
        if (params.size() == 3)
            pmLogInfoWithClock(params[0], params[1], params[2]);
#endif
    } else if (message == "PmLogString") {
#ifdef HAS_PMLOG
        if (params.size() > 3)
            pmLogString(static_cast<PmLogLevel>(params[0].toInt()), params[1], params[2], params[3]);
#endif
    } else if (message == "setWindowProperty") {
        if (params.size() > 1) {
            LOG_INFO(MSGID_PALMSYSTEM, 2, PMLOGKS("APP_ID", m_app->appId().c_str()), PMLOGKFV("PID", "%d", m_app->page()->getWebProcessPID()),
                "webOSSystem.window.setProperty('%s', '%s')", qPrintable(params[0]), qPrintable(params[1]));
            m_app->setWindowProperty(params[0].toStdString(), params[1].toStdString());
        }
    } else if (message == "platformBack") {
        LOG_INFO(MSGID_PALMSYSTEM, 2, PMLOGKS("APP_ID", m_app->appId().c_str()), PMLOGKFV("PID", "%d", m_app->page()->getWebProcessPID()), "webOSSystem.platformBack()");
        m_app->platformBack();
    } else if (message == "setCursor") {
        QVariant v1, v2, v3;
        v1 = params.at(0);
        v2 = params.at(1);
        v3 = params.at(2);
        m_app->setCursor(v1.toString().toStdString(), v2.toInt(), v3.toInt());
    } else if (message == "setInputRegion") {
        QByteArray data;
        for (int i = 0; i < params.count(); i++) {
            data.append(params.at(i));
        }
        setInputRegion(data);
    } else if (message == "setKeyMask") {
        QByteArray data;
        for (int i = 0; i < params.count(); i++) {
            data.append(params.at(i));
        }
        setGroupClientEnvironment(KeyMask, data);
    } else if (message == "focusOwner") {
        setGroupClientEnvironment(FocusOwner, NULL);
    } else if (message == "focusLayer") {
        setGroupClientEnvironment(FocusLayer, NULL);
    } else if (message == "hide") {
        hide();
    } else if (message == "setLoadErrorPolicy") {
        if (params.size() > 0) {
            LOG_INFO(MSGID_PALMSYSTEM, 2, PMLOGKS("APP_ID", m_app->appId().c_str()), PMLOGKFV("PID", "%d", m_app->page()->getWebProcessPID()), "webOSSystem.setLoadErrorPolicy(%s)", qPrintable(params[0]));
            setLoadErrorPolicy(params[0]);
        }
    } else if (message == "onCloseNotify") {
        if (params.size() > 0) {
            LOG_INFO(MSGID_PALMSYSTEM, 2, PMLOGKS("APP_ID", m_app->appId().c_str()), PMLOGKFV("PID", "%d", m_app->page()->getWebProcessPID()), "webOSSystem.onCloseNotify(%s)", qPrintable(params[0]));
            onCloseNotify(params[0]);
        }
    } else if (message == "cursorVisibility") {
        return cursorVisibility() ? "true" : "false";
    } else if (message == "serviceCall") {
        if (m_app->page()->isClosing()) {
          LOG_INFO(MSGID_PALMSYSTEM, 2, PMLOGKS("APP_ID", m_app->appId().c_str()), PMLOGKFV("PID", "%d", m_app->page()->getWebProcessPID()), "webOSSystem.serviceCall(%s, %s)", qPrintable(params[0]), qPrintable(params[1]));
          m_app->serviceCall(params[0].toStdString(), params[1].toStdString(), m_app->appId()); // FIXME: PalmSystem: qstr2stdstr
        } else {
            LOG_WARNING(MSGID_SERVICE_CALL_FAIL, 2, PMLOGKS("APP_ID", m_app->appId().c_str()),
              PMLOGKS("URL", qPrintable(params[0])), "Page is NOT in closing");
        }
    }

    return QString();
}

void PalmSystemBlink::setCountry()
{
    static_cast<WebPageBlink*>(m_app->page())->updateExtensionData(QStringLiteral("country"), country());
}

void PalmSystemBlink::setLaunchParams(const QString& params)
{
    PalmSystemWebOS::setLaunchParams(params);
    static_cast<WebPageBlink*>(m_app->page())->updateExtensionData(QStringLiteral("launchParams"), launchParams());
}

void PalmSystemBlink::setLocale(const std::string& params)
{
    QString l = QString::fromStdString(params); // FIXME: WebPage: qstr2stdstr
    static_cast<WebPageBlink*>(m_app->page())->updateExtensionData(QStringLiteral("locale"), l);
}

QString PalmSystemBlink::identifier() const
{
    if (!m_app->page())
        return QStringLiteral("");

    return static_cast<WebPageBlink*>(m_app->page())->getIdentifier();
}

void PalmSystemBlink::setLoadErrorPolicy(const QString& params)
{
    static_cast<WebPageBlink*>(m_app->page())->setLoadErrorPolicy(params);
}

QString PalmSystemBlink::trustLevel() const
{
    return static_cast<WebPageBlink*>(m_app->page())->trustLevel();
}

void PalmSystemBlink::onCloseNotify(const QString& params)
{
    if (params == "didSetOnCloseCallback")
        static_cast<WebPageBlink*>(m_app->page())->setHasOnCloseCallback(true);
    else if (params == "didClearOnCloseCallback")
        static_cast<WebPageBlink*>(m_app->page())->setHasOnCloseCallback(false);
    else if (params == "didRunOnCloseCallback")
        static_cast<WebPageBlink*>(m_app->page())->didRunCloseCallback();
}

double PalmSystemBlink::devicePixelRatio()
{
    return static_cast<WebPageBlink*>(m_app->page())->devicePixelRatio();
}

Json::Value PalmSystemBlink::initialize()
{
    m_initialized = true;

    // Setup initial data set
    Json::Value data;

    data["launchParams"] = launchParams().toStdString();
    data["country"] = country().toStdString();
    data["currentCountryGroup"] = getDeviceInfo("CountryGroup").toStdString();
    data["locale"] = locale().toStdString();
    data["localeRegion"] = localeRegion().toStdString();
    data["isMinimal"] = isMinimal();
    data["identifier"] = identifier().toStdString();
    data["screenOrientation"] = screenOrientation().toStdString();
    data["activityId"] = (double)activityId();
    data["phoneRegion"] = phoneRegion().toStdString();
    data["folderPath"] = m_app->getAppDescription()->folderPath();
    data["devicePixelRatio"] = devicePixelRatio();
    data["trustLevel"] = trustLevel().toStdString();
    return std::move(data);
}


