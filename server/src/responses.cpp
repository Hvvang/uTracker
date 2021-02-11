#include "database.h"
#include "responses.h"

AbstractRequestHandler::AbstractRequestHandler(Connection *connection) : m_connection(connection) {
    connect(this, &AbstractRequestHandler::responseInited, &AbstractRequestHandler::responseSend);
}

void AbstractRequestHandler::responseSend(QJsonObject itemObject) {
    qDebug() << " =========================== TYPE "<< itemObject["type"].toInt() << "=========================\n";
    if (isValid(itemObject))
        emit DataBase::getInstance()->getData(m_connection, itemObject["type"].toInt(), itemObject.toVariantMap());
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
ToSignUp::ToSignUp(Connection *socket) :  AbstractRequestHandler(socket){}

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

bool ToSignIn::isValid(QJsonObject itemObject) {
    qDebug() << "login :" << itemObject["login"].toString() << "\n";
    qDebug() << "email :" << itemObject["email"].toString() << "\n";
    qDebug() << "password :" << itemObject["password"].toString() << "\n";
    //DASHA TUT
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToSignInWithGoogle::ToSignInWithGoogle(Connection *socket) : AbstractRequestHandler(socket){}

bool ToSignInWithGoogle::isValid(QJsonObject itemObject) {
    qDebug() << "token :" << itemObject["token"].toString() << "\n";
    //DASHA TUT
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToAutoSignIn::ToAutoSignIn(Connection *socket) : AbstractRequestHandler(socket){}

bool ToAutoSignIn::isValid(QJsonObject itemObject) {
    qDebug() << "token :" << itemObject["token"].toString() << "\n";
    //DASHA TUT
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToLogOut::ToLogOut(Connection *socket) : AbstractRequestHandler(socket){}

bool ToLogOut::isValid(QJsonObject itemObject) {
    qDebug() << "userId :" << itemObject["userId"].toInt() << "\n";
    //DASHA TUT
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToCreatedWorkflow::ToCreatedWorkflow(Connection *socket) : AbstractRequestHandler(socket){}

bool ToCreatedWorkflow::isValid(QJsonObject itemObject) {
    qDebug() << "title :" << itemObject["title"].toString() << "\n";
    qDebug() << "description :" << itemObject["description"].toString() << "\n";
    qDebug() << "ownerId :" << itemObject["ownerId"].toInt() << "\n";
    //DASHA TUT
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToUpdateWorkflow::ToUpdateWorkflow(Connection *socket) : AbstractRequestHandler(socket){}

bool ToUpdateWorkflow::isValid(QJsonObject itemObject) {
    qDebug() << "workflowId :" << itemObject["workflowId"].toInt() << "\n";
    qDebug() << "title :" << itemObject["title"].toString() << "\n";
    qDebug() << "description :" << itemObject["description"].toString() << "\n";
    //DASHA TUT
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToInvitedToWorkflow::ToInvitedToWorkflow(Connection *socket) : AbstractRequestHandler(socket){}

bool ToInvitedToWorkflow::isValid(QJsonObject itemObject) {
    qDebug() << "userID :" << itemObject["userId"].toInt() << "\n";
    qDebug() << "workflowID :" << itemObject["workflowId"].toInt() << "\n";
    //DASHA TUT
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
SendAllWorkflows::SendAllWorkflows(Connection *socket) : AbstractRequestHandler(socket){}

bool SendAllWorkflows::isValid(QJsonObject itemObject) {
    qDebug() << "userID :" << itemObject["userId"].toInt() << "\n";
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
SendSingleWorkflowData::SendSingleWorkflowData(Connection *socket) : AbstractRequestHandler(socket){}

bool SendSingleWorkflowData::isValid(QJsonObject itemObject) {
    qDebug() << "workflowID :" << itemObject["workflowId"].toInt() << "\n";
    //DASHA TUT
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
SendStatistics::SendStatistics(Connection *socket) : AbstractRequestHandler(socket){}

bool SendStatistics::isValid(QJsonObject itemObject) {
    Q_UNUSED(itemObject);
    //qDebug() << "userID :" << itemObject["userId"].toString() << "\n";
    //DASHA TUT
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
SendProfile::SendProfile(Connection *socket) : AbstractRequestHandler(socket){}

bool SendProfile::isValid(QJsonObject itemObject) {
    qDebug() << "userID :" << itemObject["userId"].toInt() << "\n";
    //DASHA TUT
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
ToUpdateProfile::ToUpdateProfile(Connection *socket) : AbstractRequestHandler(socket){}

bool ToUpdateProfile::isValid(QJsonObject itemObject) {
    qDebug() << "userID :" << itemObject["userId"].toInt() << "\n";
    qDebug() << "name :" << itemObject["name"].toString() << "\n";
    qDebug() << "surname :" << itemObject["surname"].toString() << "\n";

    return true;
}
