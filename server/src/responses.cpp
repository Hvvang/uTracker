#include <sys/socket.h>
#include "responses.h"

AbstractRequestHandler::AbstractRequestHandler(Connection *connection) : m_connection(connection) {
    connect(this, &AbstractRequestHandler::responseInited, &AbstractRequestHandler::responseSend);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
ToSignUp::ToSignUp(Connection *socket) :  AbstractRequestHandler(socket){}

void ToSignUp::responseSend(QJsonObject itemObject) {
    parseJSON(itemObject);
    QJsonObject jsonObject {
            {"type", static_cast<int>(RequestType::SIGN_UP)},
            {"message", "ebu sho pisat"}
    };
    if(true) {
        QString token = "sdfhFdvY#YF28Dd4Nqj64";
        jsonObject["token"] = token;// SHA-256 hash,
    }
    else
        jsonObject["error"] = 1;
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();
    m_connection->sendResponse(json);
}

void ToSignUp::parseJSON(QJsonObject itemObject){
    qDebug() << "login :" << itemObject["login"].toString() << "\n";
    qDebug() << "email :" << itemObject["email"].toString() << "\n";
    qDebug() << "password :" << itemObject["password"].toString() << "\n";
    qDebug() << "name :" << itemObject["name"].toString() << "\n";
    qDebug() << "surname :" << itemObject["surname"].toString() << "\n";
    // DASHA TUT
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
ToSignIn::ToSignIn(Connection *socket) : AbstractRequestHandler(socket){}

void ToSignIn::responseSend(QJsonObject itemObject) {
    parseJSON(itemObject);
    QJsonObject jsonObject {
            {"type", static_cast<int>(RequestType::SIGN_IN)},
            {"message", "ebu sho pisat"}
    };
    if (true) {
        QString token = "sdfhFdvY#YF28Dd4Nqj64";
        jsonObject["token"] = token;// SHA-256 hash,
    }
    else
        jsonObject["error"] = 1;
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();
    m_connection->sendResponse(json);
}

void ToSignIn::parseJSON(QJsonObject itemObject) {
    qDebug() << "login :" << itemObject["login"].toString() << "\n";
    qDebug() << "email :" << itemObject["email"].toString() << "\n";
    qDebug() << "password :" << itemObject["password"].toString() << "\n";
    //DASHA TUT
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToSignInWithGoogle::ToSignInWithGoogle(Connection *socket) : AbstractRequestHandler(socket){}

void ToSignInWithGoogle::responseSend(QJsonObject itemObject) {
    parseJSON(itemObject);
    QJsonObject jsonObject {
            {"type", static_cast<int>(RequestType::AUTO_OAUTH)},
            {"message", "ebu sho pisat"}
    };
    if(true) {
        QString token = "sdfhFdvY#YF28Dd4Nqj64";
        jsonObject["token"] = token;// SHA-256 hash,
    }
    else
        jsonObject["error"] = 1;
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();

    m_connection->sendResponse(json);
}

void ToSignInWithGoogle::parseJSON(QJsonObject itemObject) {
        qDebug() << "token :" << itemObject["token"].toString() << "\n";
        //DASHA TUT
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToAutoSignIn::ToAutoSignIn(Connection *socket) : AbstractRequestHandler(socket){}

void ToAutoSignIn::responseSend(QJsonObject itemObject) {
    parseJSON(itemObject);
    QJsonObject jsonObject {
            {"type", static_cast<int>(RequestType::AUTO_AUTH)},
            {"message", "ebu sho pisat"}
    };
    if(true) {
        QString token = "sdfhFdvY#YF28Dd4Nqj64";
        jsonObject["token"] = token;// SHA-256 hash,
    }
    else
        jsonObject["error"] = 1;
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();
    m_connection->sendResponse(json);
}

void ToAutoSignIn::parseJSON(QJsonObject itemObject) {
    qDebug() << "token :" << itemObject["token"].toString() << "\n";
    //DASHA TUT
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToLogOut::ToLogOut(Connection *socket) : AbstractRequestHandler(socket){}

void ToLogOut::responseSend(QJsonObject itemObject) {
    parseJSON(itemObject);
    QJsonObject jsonObject {
            {"type", static_cast<int>(RequestType::LOG_OUT)}
    };
    if(true)
        jsonObject["message"] = "User succesfully logged out";
    else
        jsonObject["error"] = 1;
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();
    m_connection->sendResponse(json);
}

void ToLogOut::parseJSON(QJsonObject itemObject) {
    qDebug() << "userId :" << itemObject["userId"].toInt() << "\n";
    //DASHA TUT
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToCreatedWorkflow::ToCreatedWorkflow(Connection *socket) : AbstractRequestHandler(socket){}

void ToCreatedWorkflow::responseSend(QJsonObject itemObject) {
    parseJSON(itemObject);
    QJsonObject jsonObject {
            {"type", static_cast<int>(RequestType::CREATE_WORKFLOW)}
    };
    if(true)
        jsonObject["message"] = "Workflow created succesfully";
    else
        jsonObject["error"] = 1;
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();
    m_connection->sendResponse(json);
}

void ToCreatedWorkflow::parseJSON(QJsonObject itemObject) {
    qDebug() << "title :" << itemObject["title"].toString() << "\n";
    qDebug() << "description :" << itemObject["description"].toString() << "\n";
    //DASHA TUT
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToUpdateWorkflow::ToUpdateWorkflow(Connection *socket) : AbstractRequestHandler(socket){}

void ToUpdateWorkflow::responseSend(QJsonObject itemObject) {
    parseJSON(itemObject);
    QJsonObject jsonObject {
            {"type", static_cast<int>(RequestType::UPDATE_WORKFLOW)}
    };
    if(true)
        jsonObject["message"] = "Workflow updated succesfully";
    else
        jsonObject["error"] = 1;
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();
    m_connection->sendResponse(json);
}

void ToUpdateWorkflow::parseJSON(QJsonObject itemObject) {
    qDebug() << "workflowId :" << itemObject["workflowId"].toInt() << "\n";
    qDebug() << "title :" << itemObject["title"].toString() << "\n";
    qDebug() << "description :" << itemObject["description"].toString() << "\n";
    //DASHA TUT
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToInvitedToWorkflow::ToInvitedToWorkflow(Connection *socket) : AbstractRequestHandler(socket){}

void ToInvitedToWorkflow::responseSend(QJsonObject itemObject) {
    parseJSON(itemObject);
    QJsonObject jsonObject {
            {"type", static_cast<int>(RequestType::INVITE_TO_WORKFLOW)}
    };
    if(true)
        jsonObject["message"] = "Invited to Workflow succesfully";
    else
        jsonObject["error"] = 1;
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();
    m_connection->sendResponse(json);
}

void ToInvitedToWorkflow::parseJSON(QJsonObject itemObject) {
    qDebug() << "userID :" << itemObject["userId"].toInt() << "\n";
    qDebug() << "workflowID :" << itemObject["workflowId"].toInt() << "\n";
    //DASHA TUT
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
SendAllWorkflows::SendAllWorkflows(Connection *socket) : AbstractRequestHandler(socket){}

void SendAllWorkflows::responseSend(QJsonObject itemObject) {
    parseJSON(itemObject);
    QJsonObject jsonObject {
            {"type", static_cast<int>(RequestType::GET_ALL_WORKFLOWS)}
    };
    if(true)
        jsonObject["message"] = "All Workflows sended succesfully";
    else
        jsonObject["error"] = 1;
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();
    m_connection->sendResponse(json);
}

void SendAllWorkflows::parseJSON(QJsonObject itemObject) {
    Q_UNUSED(itemObject);
    //qDebug() << "userID :" << itemObject["userId"].toString() << "\n";
    //DASHA TUT
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
SendSingleWorkflowData::SendSingleWorkflowData(Connection *socket) : AbstractRequestHandler(socket){}

void SendSingleWorkflowData::responseSend(QJsonObject itemObject) {
    parseJSON(itemObject);
    QJsonObject jsonObject {
            {"type", static_cast<int>(RequestType::GET_SINGLE_WORKFLOW_DATA)}
    };
    if(true)
        jsonObject["message"] = "single Workflow sended succesfully";
    else
        jsonObject["error"] = 1;
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();
    m_connection->sendResponse(json);
}

void SendSingleWorkflowData::parseJSON(QJsonObject itemObject) {
    qDebug() << "workflowID :" << itemObject["workflowId"].toInt() << "\n";
    //DASHA TUT
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
SendStatistics::SendStatistics(Connection *socket) : AbstractRequestHandler(socket){}

void SendStatistics::responseSend(QJsonObject itemObject) {
    parseJSON(itemObject);
    QJsonObject jsonObject {
            {"type", static_cast<int>(RequestType::GET_STATISTICS)}
    };
    if(true)

        jsonObject["message"] = "Statistics sended succesfully";
    else
        jsonObject["error"] = 1;
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();
    m_connection->sendResponse(json);
}

void SendStatistics::parseJSON(QJsonObject itemObject) {
    Q_UNUSED(itemObject);
    //qDebug() << "userID :" << itemObject["userId"].toString() << "\n";
    //DASHA TUT
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
SendProfile::SendProfile(Connection *socket) : AbstractRequestHandler(socket){}

void SendProfile::responseSend(QJsonObject itemObject) {
    parseJSON(itemObject);
    QJsonObject jsonObject {
            {"type", static_cast<int>(RequestType::GET_PROFILE)}
    };
    if(true)
        jsonObject["message"] = "Profile sended succesfully";
    else
        jsonObject["error"] = 1;
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();
    m_connection->sendResponse(json);
}

void SendProfile::parseJSON(QJsonObject itemObject) {
    qDebug() << "userID :" << itemObject["userId"].toInt() << "\n";
    //DASHA TUT
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToUpdateProfile::ToUpdateProfile(Connection *socket) : AbstractRequestHandler(socket){}

void ToUpdateProfile::responseSend(QJsonObject itemObject) {
    parseJSON(itemObject);
    QJsonObject jsonObject {
            {"type", static_cast<int>(RequestType::UPDATE_PROFILE)}
    };
    if(true)
        jsonObject["message"] = "Profile updated succesfully";
    else
        jsonObject["error"] = 1;
    QJsonDocument *jsonDoc = new QJsonDocument(jsonObject);
    QByteArray json = jsonDoc->toJson();
    m_connection->sendResponse(json);
}

void ToUpdateProfile::parseJSON(QJsonObject itemObject) {
    qDebug() << "userID :" << itemObject["userId"].toInt() << "\n";
    qDebug() << "name :" << itemObject["name"].toString() << "\n";
    qDebug() << "surname :" << itemObject["surname"].toString() << "\n";
    //DASHA TUT
}