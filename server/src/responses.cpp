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
    if (!itemObject["email"].toString().isEmpty()
      && !itemObject["password"].toString().isEmpty()
      && !itemObject["name"].toString().isEmpty()
      && !itemObject["surname"].toString().isEmpty())
        return true;
    return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
ToSignIn::ToSignIn(Connection *socket) : AbstractRequestHandler(socket){}

bool ToSignIn::isValid(QJsonObject itemObject) {
    if (!itemObject["password"].toString().isEmpty()) {
        if (!itemObject["login"].toString().isEmpty()
            || !itemObject["email"].toString().isEmpty())
            return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToSignInWithGoogle::ToSignInWithGoogle(Connection *socket) : AbstractRequestHandler(socket){}

bool ToSignInWithGoogle::isValid(QJsonObject itemObject) {
    if (!itemObject["token"].toString().isEmpty())
        return true;
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToAutoSignIn::ToAutoSignIn(Connection *socket) : AbstractRequestHandler(socket){}

bool ToAutoSignIn::isValid(QJsonObject itemObject) {
    if (!itemObject["token"].toString().isEmpty())
        return true;
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToLogOut::ToLogOut(Connection *socket) : AbstractRequestHandler(socket){}

bool ToLogOut::isValid(QJsonObject itemObject) {
    if (!itemObject["userId"].toInt())
        return true;
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToCreatedWorkflow::ToCreatedWorkflow(Connection *socket) : AbstractRequestHandler(socket){}

bool ToCreatedWorkflow::isValid(QJsonObject itemObject) {
    if (itemObject.contains("title")
        && itemObject.contains("deadline")
        && itemObject.contains("userId")) {
        if (!itemObject["title"].toString().isEmpty()
            && !itemObject["deadline"].toString().isEmpty()
            && itemObject["userId"].toInt())
            return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToUpdateWorkflow::ToUpdateWorkflow(Connection *socket) : AbstractRequestHandler(socket){}

bool ToUpdateWorkflow::isValid(QJsonObject itemObject) {
    if (!itemObject["title"].toString().isEmpty()
        && !itemObject["description"].toString().isEmpty()
        && itemObject["workflowId"].toInt())
        return true;
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToInvitedToWorkflow::ToInvitedToWorkflow(Connection *socket) : AbstractRequestHandler(socket){}

bool ToInvitedToWorkflow::isValid(QJsonObject itemObject) {
    if (itemObject["userId"].toInt()
        && itemObject["workflowId"].toInt())
        return true;
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
SendAllWorkflows::SendAllWorkflows(Connection *socket) : AbstractRequestHandler(socket){}

bool SendAllWorkflows::isValid(QJsonObject itemObject) {
    if (itemObject["userId"].toInt())
        return true;
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
SendSingleWorkflowData::SendSingleWorkflowData(Connection *socket) : AbstractRequestHandler(socket){}

bool SendSingleWorkflowData::isValid(QJsonObject itemObject) {
    if (itemObject["workflowId"].toInt())
        return true;
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
SendStatistics::SendStatistics(Connection *socket) : AbstractRequestHandler(socket){}

bool SendStatistics::isValid(QJsonObject itemObject) {
    Q_UNUSED(itemObject);
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
SendProfile::SendProfile(Connection *socket) : AbstractRequestHandler(socket){}

bool SendProfile::isValid(QJsonObject itemObject) {
    qDebug() << itemObject["userId"].toInt();
    if (itemObject["userId"].toInt())
        return true;
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
ToUpdateProfile::ToUpdateProfile(Connection *socket) : AbstractRequestHandler(socket){}

bool ToUpdateProfile::isValid(QJsonObject itemObject) {
    if (!itemObject["name"].toString().isEmpty()
        && !itemObject["surname"].toString().isEmpty()
        && itemObject["userId"].toInt())
        return true;
    return false;
}
