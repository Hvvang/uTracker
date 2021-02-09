#include "runnable.h"
#include "database.h"

Runnable::Runnable(Connection *socket) {
    m_ptr = socket;

    m_signIn = new ToSignIn(socket);
    m_signUp = new ToSignUp(socket);
    m_autoSignIn = new ToAutoSignIn(socket);
    m_googleSignIn = new ToSignInWithGoogle(socket);
    m_logOut = new ToLogOut(socket);
    m_createWorkFlow = new ToCreatedWorkflow(socket);
    m_updateWorkFlow = new ToUpdateWorkflow(socket);
    m_inviteToWorkFlow = new ToInvitedToWorkflow(socket);
    m_sendAllWorkFlows = new SendAllWorkflows(socket);
    m_sendSingleWorkFlow = new SendSingleWorkflowData(socket);
    m_sendStatistics = new SendStatistics(socket);
    m_sendProfile = new SendProfile(socket);
    m_updateProfile = new ToUpdateProfile(socket);
    m_sendresp = new SendResp(socket);
    Q_UNUSED(m_sendresp);
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

    QVector<AbstractRequestHandler *> funcList;
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

Runnable::~Runnable() {
    delete m_signIn;
    delete m_signUp;
    delete m_autoSignIn;
    delete m_googleSignIn;
    delete m_logOut;
    delete m_createWorkFlow;
    
    delete m_sendresp;
}

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
