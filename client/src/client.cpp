#include "client.h"

class AES;

Client::Client(QObject *parent) : QObject(parent) {
    m_socket = new QTcpSocket(this);
    m_request = new AbstractRequest(m_socket);
    m_signUp = new SignUpResponse(m_socket);
    m_signIn = new SignInResponse(m_socket);
    m_autoSignIn = new AutoSignInResponse(m_socket);
    m_googleSignIn = new SignInWithGoogleResponse(m_socket);
    m_logOut = new LogOutResponse(m_socket);
    m_createdWorkflow = new CreatedWorkflowResponse(m_socket);
    m_updateWorkflow = new UpdateWorkflowResponse(m_socket);
    m_inviteToWorkflow = new InvitedToWorkflowResponse(m_socket);
    m_allWorkflow = new AllWorkflowsResponse(m_socket);
    m_singleWorkflow = new SingleWorkflowDataResponse(m_socket);
    m_sendStat = new SendStatistics(m_socket);
    m_sendProfile = new SendProfileResponse(m_socket);
    m_updateProfile = new ToUpdateProfileResponse(m_socket);
}

Client::~Client() {
    m_socket->abort();
    delete m_socket;
    delete m_request;
    delete m_signUp;
    delete m_signIn;
    delete m_autoSignIn;
    delete m_googleSignIn;
    delete m_logOut;
    delete m_createdWorkflow;
    delete m_updateWorkflow;
    delete m_inviteToWorkflow;
    delete m_allWorkflow;
    delete m_singleWorkflow;
    delete m_sendStat;
    delete m_sendProfile;
    delete m_updateProfile;
}

void Client::doConnect(char *ip, int port) {
    connect(m_socket, &QTcpSocket::disconnected, this, &Client::disconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &Client::readyRead);
    m_socket->connectToHost(ip, port);
    if (!m_socket->waitForConnected(5000))
        qDebug() << "Error: " << m_socket->errorString();
}

void Client::testRequestLoop() {
    m_request->signUp("NazarDykyy@gmail.com", "ndykyy", "21453#gs8kFSdfD1F244iuSn", "Nazar", "Dykyy");
    m_request->signIn("NazarDykyy@gmail.com", "ndykyy", "21453#gs8kFSdfD1F244iuSn");
    m_request->autoSignIn("token");
    m_request->autoSignInWithGoogle("token");
    m_request->logOut(1);
    m_request->createWorkflow("EL TITLE", "EL DESCRIPTION");
    m_request->updateWorkflow("QString title", "QString description", 1);
    m_request->inviteToWorkflow(1, 1);
    m_request->getAllWorkflows();
    m_request->getSingleWorkflowData(1);
    m_request->getStatistics();
    m_request->getProfile(1);
    m_request->updateProfile(1, "Nazar", "Dykyy");
}

void Client::parseJSON(QJsonDocument itemDoc) {
    QJsonObject itemObject = itemDoc.object();

    QVector<AbstractResponseHandler *> funcList;

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

void Client::disconnected() {
    // do something when disconnection happens
}

void Client::readyRead() {
    while (!m_socket->atEnd()) {
        QByteArray size = m_socket->readLine();
//        qDebug() << m_socket->read(size.toInt());
        QJsonDocument itemDoc = QJsonDocument::fromJson(m_socket->read(size.toInt()));
        if (!itemDoc.isNull())
            parseJSON(itemDoc);
    }
}