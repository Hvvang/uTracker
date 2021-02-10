#include "responses.h"
#include "database.h"

AbstractRequestHandler::AbstractRequestHandler(Connection *connection) : m_connection(connection) {
    connect(this, &AbstractRequestHandler::responseInited, &AbstractRequestHandler::responseSend);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
ToSignUp::ToSignUp(Connection *socket) :  AbstractRequestHandler(socket){}

void ToSignUp::responseSend(QJsonObject itemObject) {
    if (isValid(itemObject))
        emit DataBase::getInstance()->getData(m_connection, itemObject["type"].toInt(), itemObject.toVariantMap());
}

bool ToSignUp::isValid(QJsonObject itemObject) {
    qDebug() << "login :" << itemObject["login"].toString() << "\n";
    qDebug() << "email :" << itemObject["email"].toString() << "\n";
    qDebug() << "password :" << itemObject["password"].toString() << "\n";
    qDebug() << "name :" << itemObject["name"].toString() << "\n";
    qDebug() << "surname :" << itemObject["surname"].toString() << "\n";
    // DASHA TUT
    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
ToSignIn::ToSignIn(Connection *socket) : AbstractRequestHandler(socket){}

void ToSignIn::responseSend(QJsonObject itemObject) {
    if (isValid(itemObject))
        emit DataBase::getInstance()->getData(m_connection, itemObject["type"].toInt(), itemObject.toVariantMap());
}

bool ToSignIn::isValid(QJsonObject itemObject) {
    qDebug() << "login :" << itemObject["login"].toString() << "\n";
    qDebug() << "email :" << itemObject["email"].toString() << "\n";
    qDebug() << "password :" << itemObject["password"].toString() << "\n";
    //DASHA TUT
    return 1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToSignInWithGoogle::ToSignInWithGoogle(Connection *socket) : AbstractRequestHandler(socket){}

void ToSignInWithGoogle::responseSend(QJsonObject itemObject) {
    if (isValid(itemObject))
        emit DataBase::getInstance()->getData(m_connection, itemObject["type"].toInt(), itemObject.toVariantMap());
}

bool ToSignInWithGoogle::isValid(QJsonObject itemObject) {
    qDebug() << "token :" << itemObject["token"].toString() << "\n";
    //DASHA TUT
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToAutoSignIn::ToAutoSignIn(Connection *socket) : AbstractRequestHandler(socket){}

void ToAutoSignIn::responseSend(QJsonObject itemObject) {
    if (isValid(itemObject))
        emit DataBase::getInstance()->getData(m_connection, itemObject["type"].toInt(), itemObject.toVariantMap());
}

bool ToAutoSignIn::isValid(QJsonObject itemObject) {
    qDebug() << "token :" << itemObject["token"].toString() << "\n";
    //DASHA TUT
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToLogOut::ToLogOut(Connection *socket) : AbstractRequestHandler(socket){}

void ToLogOut::responseSend(QJsonObject itemObject) {
    if (isValid(itemObject))
        emit DataBase::getInstance()->getData(m_connection, itemObject["type"].toInt(), itemObject.toVariantMap());
}

bool ToLogOut::isValid(QJsonObject itemObject) {
    qDebug() << "userId :" << itemObject["userId"].toInt() << "\n";
    //DASHA TUT
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToCreatedWorkflow::ToCreatedWorkflow(Connection *socket) : AbstractRequestHandler(socket){}

void ToCreatedWorkflow::responseSend(QJsonObject itemObject) {
    if (isValid(itemObject))
        emit DataBase::getInstance()->getData(m_connection, itemObject["type"].toInt(), itemObject.toVariantMap());
}

bool ToCreatedWorkflow::isValid(QJsonObject itemObject) {
    qDebug() << "title :" << itemObject["title"].toString() << "\n";
    qDebug() << "description :" << itemObject["description"].toString() << "\n";
    //DASHA TUT
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToUpdateWorkflow::ToUpdateWorkflow(Connection *socket) : AbstractRequestHandler(socket){}

void ToUpdateWorkflow::responseSend(QJsonObject itemObject) {
    if (isValid(itemObject))
        emit DataBase::getInstance()->getData(m_connection, itemObject["type"].toInt(), itemObject.toVariantMap());
}

bool ToUpdateWorkflow::isValid(QJsonObject itemObject) {
    qDebug() << "workflowId :" << itemObject["workflowId"].toInt() << "\n";
    qDebug() << "title :" << itemObject["title"].toString() << "\n";
    qDebug() << "description :" << itemObject["description"].toString() << "\n";
    //DASHA TUT
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToInvitedToWorkflow::ToInvitedToWorkflow(Connection *socket) : AbstractRequestHandler(socket){}

void ToInvitedToWorkflow::responseSend(QJsonObject itemObject) {
    if (isValid(itemObject))
        emit DataBase::getInstance()->getData(m_connection, itemObject["type"].toInt(), itemObject.toVariantMap());
}

bool ToInvitedToWorkflow::isValid(QJsonObject itemObject) {
    qDebug() << "userID :" << itemObject["userId"].toInt() << "\n";
    qDebug() << "workflowID :" << itemObject["workflowId"].toInt() << "\n";
    //DASHA TUT
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
SendAllWorkflows::SendAllWorkflows(Connection *socket) : AbstractRequestHandler(socket){}

void SendAllWorkflows::responseSend(QJsonObject itemObject) {
    if (isValid(itemObject))
        emit DataBase::getInstance()->getData(m_connection, itemObject["type"].toInt(), itemObject.toVariantMap());
}

bool SendAllWorkflows::isValid(QJsonObject itemObject) {
    Q_UNUSED(itemObject);
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
SendSingleWorkflowData::SendSingleWorkflowData(Connection *socket) : AbstractRequestHandler(socket){}

void SendSingleWorkflowData::responseSend(QJsonObject itemObject) {
    if (isValid(itemObject))
        emit DataBase::getInstance()->getData(m_connection, itemObject["type"].toInt(), itemObject.toVariantMap());
}

bool SendSingleWorkflowData::isValid(QJsonObject itemObject) {
    qDebug() << "workflowID :" << itemObject["workflowId"].toInt() << "\n";
    //DASHA TUT
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
SendStatistics::SendStatistics(Connection *socket) : AbstractRequestHandler(socket){}

void SendStatistics::responseSend(QJsonObject itemObject) {
    if (isValid(itemObject))
            emit DataBase::getInstance()->getData(m_connection, itemObject["type"].toInt(), itemObject.toVariantMap());
}

bool SendStatistics::isValid(QJsonObject itemObject) {
    Q_UNUSED(itemObject);
    //qDebug() << "userID :" << itemObject["userId"].toString() << "\n";
    //DASHA TUT
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
SendProfile::SendProfile(Connection *socket) : AbstractRequestHandler(socket){}

void SendProfile::responseSend(QJsonObject itemObject) {
    if (isValid(itemObject))
        emit DataBase::getInstance()->getData(m_connection, itemObject["type"].toInt(), itemObject.toVariantMap());
}

bool SendProfile::isValid(QJsonObject itemObject) {
    qDebug() << "userID :" << itemObject["userId"].toInt() << "\n";
    //DASHA TUT
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToUpdateProfile::ToUpdateProfile(Connection *socket) : AbstractRequestHandler(socket){}

void ToUpdateProfile::responseSend(QJsonObject itemObject) {
    if (isValid(itemObject))
        emit DataBase::getInstance()->getData(m_connection, itemObject["type"].toInt(), itemObject.toVariantMap());
}

bool ToUpdateProfile::isValid(QJsonObject itemObject) {
    qDebug() << "userID :" << itemObject["userId"].toInt() << "\n";
    qDebug() << "name :" << itemObject["name"].toString() << "\n";
    qDebug() << "surname :" << itemObject["surname"].toString() << "\n";

    return true;
}
