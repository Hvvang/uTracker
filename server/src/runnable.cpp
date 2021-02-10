#include "runnable.h"
#include "database.h"

Runnable::Runnable(Connection *socket) {
    m_ptr = socket;

    m_signIn = std::make_shared<ToSignIn>(socket);
    m_signUp = std::make_shared<ToSignUp>(socket);
    m_autoSignIn = std::make_shared<ToAutoSignIn>(socket);
    m_googleSignIn = std::make_shared<ToSignInWithGoogle>(socket);
    m_logOut = std::make_shared<ToLogOut>(socket);
    m_createWorkFlow = std::make_shared<ToCreatedWorkflow>(socket);
    m_updateWorkFlow = std::make_shared<ToUpdateWorkflow>(socket);
    m_inviteToWorkFlow = std::make_shared<ToInvitedToWorkflow>(socket);
    m_sendAllWorkFlows = std::make_shared<SendAllWorkflows>(socket);
    m_sendSingleWorkFlow = std::make_shared<SendSingleWorkflowData>(socket);
    m_sendStatistics = std::make_shared<SendStatistics>(socket);
    m_sendProfile = std::make_shared<SendProfile>(socket);
    m_updateProfile = std::make_shared<ToUpdateProfile>(socket);

}

void Runnable::parseJSON(QJsonDocument itemDoc) {
    if (true) {
        m_mutex->lock();
        //qDebug() << "mutex locked";
        m_mutex->unlock();
    }
    //else
    //    qDebug() << "mutex unlocked";

    QJsonObject itemObject = itemDoc.object();

    QVector<std::shared_ptr<AbstractRequestHandler>> funcList;
    funcList.append({m_signUp, m_signIn, m_autoSignIn, m_googleSignIn, m_logOut, m_createWorkFlow});
    funcList.append({m_updateWorkFlow, m_inviteToWorkFlow, m_sendAllWorkFlows, m_sendSingleWorkFlow});
    funcList.append({m_sendStatistics, m_sendProfile, m_updateProfile});
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
            emit funcList[types.indexOf(i)]->responseInited(itemObject);
}

Runnable::~Runnable() {}

void Runnable::setMutex(QMutex *mutex) {
    m_mutex = mutex;
}

void Runnable::setTask(QByteArray task) {
    m_task = task;
}

void Runnable::run() {
    QJsonDocument itemDoc = QJsonDocument::fromJson(m_task);
    if (!itemDoc.isNull())
        parseJSON(itemDoc);
}
