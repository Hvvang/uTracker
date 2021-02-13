#include "client.h"
#include "requests.h"

AbstractRequest::AbstractRequest(std::shared_ptr<QSslSocket> socket) {
    m_socket = socket;
}

void AbstractRequest::createJSON(QMap<QString, QVariant> map) {

    QJsonObject jsonObject =  QJsonObject::fromVariantMap(map);
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();
    qDebug() << json;

    QByteArray buffer;
    m_socket->write(buffer.setNum(json.size()));
    m_socket->write("\n" + json);
}

void AbstractRequest::signUp(QString login, QString pass, QString name, QString surname, QString email) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::SIGN_UP);
    mapa["login"] = login;
    mapa["password"] = pass;
    mapa["email"] = email;
    mapa["name"] = name;
    mapa["surname"] = surname;
    createJSON(mapa);
}
void AbstractRequest::signIn(QString email, QString  login, QString pass) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::SIGN_IN);
    mapa["login"] = login;
    mapa["password"] = pass;
    mapa["email"] = email;
    createJSON(mapa);
}
void AbstractRequest::autoSignInWithGoogle(QString token) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::AUTO_OAUTH);
    mapa["token"] = token;
    createJSON(mapa);
}
void AbstractRequest::autoSignIn(QString token) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::AUTO_AUTH);
    mapa["token"] = token;
    createJSON(mapa);
}
void AbstractRequest::logOut(int userId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::LOG_OUT);
    mapa["userId"] = userId;
    createJSON(mapa);
}

void AbstractRequest::createWorkflow(QString title, QString description, int ownerId) {
//    Q_UNUSED(ownerId);
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::CREATE_WORKFLOW);
    mapa["ownerId"] = ownerId;
    mapa["title"] = title;
    mapa["description"] = description;
    createJSON(mapa);
}

void AbstractRequest::updateWorkflow(QString title, QString description,int workflowId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::UPDATE_WORKFLOW);
    mapa["title"] = title;
    mapa["description"] = description;
    mapa["workflowId"] = workflowId;
    createJSON(mapa);
}
void AbstractRequest::inviteToWorkflow(int userId, int workflowId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::INVITE_TO_WORKFLOW);
    mapa["userId"] = userId;
    mapa["workflowId"] = workflowId;
    createJSON(mapa);
}

void AbstractRequest::getAllWorkflows(int userId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::GET_ALL_WORKFLOWS);
    mapa["userId"] = userId;
    createJSON(mapa);
}

void AbstractRequest::getSingleWorkflowData(int workflowId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::GET_SINGLE_WORKFLOW_DATA);
    mapa["workflowId"] = workflowId;
    createJSON(mapa);
}

void AbstractRequest::getStatistics() {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::GET_STATISTICS);
    createJSON(mapa);
}

void AbstractRequest::getProfile(int userId) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::GET_PROFILE);
    mapa["userId"] = userId;
    createJSON(mapa);
}
void AbstractRequest::updateProfile(int userId, QString name, QString surname) {
    QMap<QString, QVariant> mapa;
    mapa["type"] = static_cast<int>(RequestType::UPDATE_PROFILE);
    mapa["userId"] = userId;
    mapa["name"] = name;
    mapa["surname"] = surname;
    createJSON(mapa);
}


// //EXAMPLE
// //creating json
// //QString login = "ND";
// //QString pass = "12345678";
// //QJsonArray npcArray;
// //QVector<int> vitya = {1, 2, 3, 4, 5};
// //for (auto item : vitya) {
// //QJsonObject npcObject {
// //        {"num", item}
// //};
// //npcArray.append(npcObject);
// //}
// //QJsonObject jsonObject {
// //        {"type", "signup"},
// //        {"login", login},
// //        {"password", pass},
// //        {"array", npcArray}
// //};
// //QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
// //QByteArray json = jsonDoc->toJson();
// //qDebug() << "WANNA SIGNUP !";
// //m_socket->write(json);
