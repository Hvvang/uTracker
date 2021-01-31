#ifndef GOOGLEAUTH_H
#define GOOGLEAUTH_H

#include <QObject>
#include <QOAuth2AuthorizationCodeFlow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>
#include <QOAuthHttpServerReplyHandler>
#include <QDesktopServices>

class GoogleAuth : public QObject
{
    Q_OBJECT
public:
    explicit GoogleAuth(QObject *parent = nullptr);
    virtual ~GoogleAuth();
    Q_INVOKABLE void click();

    void refreshToken(const QString &);

signals:
    void gotToken(const QString &, const QString &, const QString &);

private:
    QOAuth2AuthorizationCodeFlow * google;
};


#endif // GOOGLEAUTH_H
