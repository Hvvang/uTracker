#include <QSslConfiguration>
#include <QFile>
#include <QSslKey>
#include "client.h"
#include "loggingcategories.h"

Client::Client(QObject* parent) :QObject(parent)
{
    m_ssl_socket = std::make_shared<QSslSocket>();
    m_request = std::make_unique<AbstractRequest>(m_ssl_socket);
    m_signUp = std::make_shared<SignUpResponse>(m_ssl_socket);
    m_signIn = std::make_shared<SignInResponse>(m_ssl_socket);
    m_autoSignIn = std::make_shared<AutoSignInResponse>(m_ssl_socket);
    m_googleSignIn = std::make_shared<SignInWithGoogleResponse>(m_ssl_socket);
    m_logOut = std::make_shared<LogOutResponse>(m_ssl_socket);
    m_createdWorkflow = std::make_shared<CreatedWorkflowResponse>(m_ssl_socket);
    m_updateWorkflow = std::make_shared<UpdateWorkflowResponse>(m_ssl_socket);
    m_inviteToWorkflow = std::make_shared<InvitedToWorkflowResponse>(m_ssl_socket);
    m_allWorkflow = std::make_shared<AllWorkflowsResponse>(m_ssl_socket);
    m_singleWorkflow = std::make_shared<SingleWorkflowDataResponse>(m_ssl_socket);
    m_sendStat = std::make_shared<SendStatistics>(m_ssl_socket);
    m_sendProfile = std::make_shared<SendProfileResponse>(m_ssl_socket);
    m_updateProfile = std::make_shared<ToUpdateProfileResponse>(m_ssl_socket);

    connect(m_ssl_socket.get(), &QSslSocket::encrypted, this, &Client::connectSuccess);
    connect(m_ssl_socket.get(), &QSslSocket::readyRead, this, &Client::readyRead);
    connect(m_ssl_socket.get(), &QSslSocket::disconnected, this, &Client::disconnected);
    connect(m_ssl_socket.get(), SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(sslErrors(QList<QSslError>)));
    configSSL();
}

Client::~Client()
{
    qDebug(logDebug) << "Client destructor";
    m_ssl_socket->abort();
}

void Client::doConnect(char* host, int port)
{
    qDebug(logDebug()) << "doConnect to host " << host;
    m_ssl_socket->connectToHostEncrypted(host, port);  // start a secure connection, starts an immediate SSL handshake
    // once the connection has been established.

    if (m_ssl_socket->waitForEncrypted(50000)) {
        m_ssl_socket->write("new client Suceeded");
        qDebug() << " connected to server ";
    }
    else {
        qDebug(logDebug()) << "error connection to server :" << m_ssl_socket->errorString();
        exit(1);
    }
//    m_ssl_socket->startClientEncryption();
}

bool Client::configSSL()
{
    QSslConfiguration config;
    QByteArray key;
    QByteArray cert;

    QFile file_key("./CA/client2.key");
    if (file_key.open(QIODevice::ReadOnly)) {
        key = file_key.readAll();
        file_key.close();
    }
    else {
        qDebug() << "error key " << file_key.errorString();
        return false;
    }

    QFile file_cert("./CA/client2.pem");
    if (file_cert.open(QIODevice::ReadOnly)) {
        cert = file_cert.readAll();
        file_cert.close();
    }
    else {
        qDebug() << "error cert " << file_cert.errorString();
        return false;
    }
    QSslKey ssl_key(key, QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey);
    QSslCertificate ssl_cert(cert, QSsl::Pem);
    config.setLocalCertificate(ssl_cert);
    config.setPrivateKey(ssl_key);
//    config.setProtocol(QSsl::TlsV1_2);
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    m_ssl_socket->setSslConfiguration(config);
    return true;
}

void Client::testConnect() const
{
    m_ssl_socket->write("hello");
    qDebug(logDebug()) << "testConnect, socket mode =" << m_ssl_socket->mode();
}

void Client::testRequestLoop()
{
    m_request->signUp("ndykyy1", "21453#gs8kFSdfD1F244iuSn1", "Nazar1", "Dykyy1", "NazarDykyy1@gmail.com");
    m_request->signIn("NazarDykyy1@gmail.com", "ndykyy", "21453#gs8kFSdfD1F244iuSn1");
//     m_request->autoSignIn("token");//-
//     m_request->autoSignInWithGoogle("token");//-
//     m_request->logOut(1);//+
    m_request->createWorkflow("EL TITLE", "EL DESCRIPTION", 1);
    m_request->updateWorkflow("QString title", "QString description", 1);
    m_request->inviteToWorkflow(1, 1);
    m_request->getAllWorkflows(1);
    m_request->getSingleWorkflowData(1);
//     m_request->getStatistics();//-
    m_request->getProfile(1);
    m_request->updateProfile(1, "Nazar", "Dykyy");
}

void Client::parseJSON(QJsonDocument itemDoc)
{
    QJsonObject itemObject = itemDoc.object();

    QVector<std::shared_ptr<AbstractResponseHandler>> funcList;

    funcList.append({m_signIn, m_signUp, m_autoSignIn, m_googleSignIn, m_logOut, m_createdWorkflow});
    funcList.append({m_updateWorkflow, m_inviteToWorkflow, m_allWorkflow, m_singleWorkflow});
    funcList.append({m_sendStat, m_sendProfile, m_updateProfile});
    QVector<RequestType> types;
    types.append(RequestType::SIGN_UP);
    types.append(RequestType::SIGN_IN);
    types.append(RequestType::AUTO_AUTH);
    types.append(RequestType::AUTO_OAUTH);
    types.append(RequestType::LOG_OUT);
    types.append(RequestType::CREATE_WORKFLOW);
    types.append(RequestType::UPDATE_WORKFLOW);
    types.append(RequestType::INVITE_TO_WORKFLOW);
    types.append(RequestType::GET_ALL_WORKFLOWS);
    types.append(RequestType::GET_SINGLE_WORKFLOW_DATA);
    types.append(RequestType::GET_STATISTICS);
    types.append(RequestType::GET_PROFILE);
    types.append(RequestType::UPDATE_PROFILE);
    for (auto i : types)
        if (static_cast<int>(i) == itemObject["type"].toInt())
                emit funcList[types.indexOf(i)]->handleInited(itemObject);
}

void Client::disconnected()
{
    qDebug(logDebug()) << "server::disconnected";
//    reconnect();
//    this->deleteLater();
}

void Client::readyRead()
{
    while (!m_ssl_socket->atEnd()) {
        QByteArray size = m_ssl_socket->readLine();
        QJsonDocument itemDoc = QJsonDocument::fromJson(m_ssl_socket->read(size.toInt()));
        if (!itemDoc.isNull())
            parseJSON(itemDoc);
    }
}

void Client::connectSuccess()
{
    qInfo(logInfo()) << "handshake success, state = " << m_ssl_socket->state();
    m_ssl_socket->write("send from client !!!");
}

void Client::sslErrors(const QList<QSslError>& errors)
{
            foreach (const QSslError& error, errors)
            qDebug() << error.errorString();
}
