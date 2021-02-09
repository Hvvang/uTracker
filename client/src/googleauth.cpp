#include "googleauth.h"

#include <QString>
#include <QDir>
#include <QUrl>
#include <QOAuthHttpServerReplyHandler>
#include <QDesktopServices>
#include <QNetworkRequest>
#include <QProcess>


// Get these from https://console.developers.google.com/apis/credentials
#define CLIENT_ID "202759414279-loo1r8qem042oda0rv27or0r4sljg2j4.apps.googleusercontent.com"
#define CLIENT_SECRET "NPfzAD0K44ZLrlYGXxLTvii_"
#define AUTH_URI "https://accounts.google.com/o/oauth2/auth"
#define TOKEN_URI "https://oauth2.googleapis.com/token"
//#define REDIRECT_URI "urn:ietf:wg:oauth:2.0:oob"
//#define REDIRECT_URI "http://localhost"
//#define REDIRECT_URI "http://localhost:1234/"
#define REDIRECT_URI "http://127.0.0.1:5000/"

GoogleAuth::GoogleAuth(QObject *parent) : QObject(parent) {
    this->google = new QOAuth2AuthorizationCodeFlow(this);

    this->google->setScope("email profile https://www.googleapis.com/auth/calendar");

    connect(this->google, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, [=](QUrl url) {
        QUrlQuery query(url);

        query.addQueryItem("prompt", "consent");      // Param required to get data everytime
        query.addQueryItem("access_type", "offline"); // Needed for Refresh Token (as AccessToken expires shortly)
        url.setQuery(query);
        QDesktopServices::openUrl(url);
    });

    const QUrl authUri(AUTH_URI);
    const auto clientId = CLIENT_ID;
    const QUrl tokenUri(TOKEN_URI);
    const auto clientSecret(CLIENT_SECRET);
    const QUrl redirectUri(REDIRECT_URI);
    const auto port = static_cast<quint16>(redirectUri.port());
    this->google->setAuthorizationUrl(authUri);
    this->google->setClientIdentifier(clientId);
    this->google->setAccessTokenUrl(tokenUri);

    this->google->setClientIdentifierSharedKey(clientSecret);

    this->google->setModifyParametersFunction([](QAbstractOAuth::Stage stage, QVariantMap* parameters) {
        // Percent-decode the "code" parameter so Google can match it
        if (stage == QAbstractOAuth::Stage::RequestingAccessToken) {
            QByteArray code = parameters->value("code").toByteArray();
            (*parameters)["code"] = QUrl::fromPercentEncoding(code);
        }
    });


    QOAuthHttpServerReplyHandler* replyHandler = new QOAuthHttpServerReplyHandler(port, this);
    this->google->setReplyHandler(replyHandler);

    connect(this->google, &QOAuth2AuthorizationCodeFlow::granted, [=](){
        const QString token = this->google->token();

        emit gotToken("accesses_token", google->token());
        emit gotToken("refresh_token", google->refreshToken());

//        auto reply = this->google->post(getRefreshUrl());

//        connect(reply, &QNetworkReply::finished, [reply]() {
//            qDebug() << "REQUEST FINISHED. Error? " << (reply->error() != QNetworkReply::NoError);
//            qDebug() << reply->readAll();
//        });
        // TODO: send gotted shrared key to server for getting tokens on server side of application

    });
}

GoogleAuth::~GoogleAuth() {
    delete this->google;
}

// Invoked externally to initiate
void GoogleAuth::click() {
    this->google->grant();
}

void GoogleAuth::refreshToken(const QString &token) {
    QUrl url(QString("%1?alt=json&grant_type=refresh_token&refresh_token=%2&client_id=%3&client_secret=%4")
              .arg("https://www.googleapis.com/oauth2/v4/token/")
              .arg(token)
              .arg(CLIENT_ID)
              .arg(CLIENT_SECRET));

    auto reply = this->google->post(url);

    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() != QNetworkReply::NoError) {
            emit gotToken("accesses_token", google->token());
            emit gotToken("refresh_token", google->refreshToken());
        }
        qDebug() << "REQUEST FINISHED. Error? " << (reply->error() != QNetworkReply::NoError);
        qDebug() << reply->readAll();
    });
}

