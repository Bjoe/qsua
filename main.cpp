#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "calllistmodel.h"
#include "pjsuacontext.h"

#if defined (Q_OS_ANDROID)
#include <QtAndroid>
const QVector<QString> permissions({"android.permission.INTERNET",
                                    "android.permission.RECORD_AUDIO",
                                    "android.permission.MODIFY_AUDIO_SETTINGS",
                                    "android.permission.ACCESS_NETWORK_STATE",
                                    "android.permission.ACCESS_WIFI_STATE"
                                    });
#endif

int main(int argc, char *argv[])
{
    //qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    if (qEnvironmentVariableIsEmpty("QTGLESSTREAM_DISPLAY")) {
        qputenv("QT_QPA_EGLFS_PHYSICAL_WIDTH", QByteArray("213"));
        qputenv("QT_QPA_EGLFS_PHYSICAL_HEIGHT", QByteArray("120"));

        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    }

    QGuiApplication app(argc, argv);
    app.setOrganizationName("Devolab");
    app.setOrganizationDomain("devolab.de");
    app.setApplicationName("Qsua");

    qmlRegisterType<qsua::CallListModel>("CallList", 1, 0, "CallListModel");
    qmlRegisterType<qsua::PjSuaContext>("PjSuaCtx", 1, 0, "PjSuaContext");

#if defined (Q_OS_ANDROID)
    //Request requiered permissions at runtime
    for(const QString &permission : permissions){
       auto result = QtAndroid::checkPermission(permission);
        if(result == QtAndroid::PermissionResult::Denied){
            auto resultHash = QtAndroid::requestPermissionsSync(QStringList({permission}));
            if(resultHash[permission] == QtAndroid::PermissionResult::Denied)
                return 0;
        }
    }
#endif

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
