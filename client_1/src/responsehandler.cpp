#include <QSslSocket>
#include "responsehandler.h"

AbstractResponseHandler::AbstractResponseHandler(std::shared_ptr<QSslSocket>  socket) : m_socket(socket)
{
    connect(this, &AbstractResponseHandler::handleInited, &AbstractResponseHandler::responseHandle);
}
///////////////////////////////////////////////////////////////////////////////////////
SignUpResponse::SignUpResponse(std::shared_ptr<QSslSocket> socket) :AbstractResponseHandler(socket) { }

void SignUpResponse::responseHandle(QJsonObject itemObject)
{
    qDebug() << "message :" << itemObject["message"].toString() << "\n";
}
////////////////////////////////////////////////////////////////////////////////////////
SignInResponse::SignInResponse(std::shared_ptr<QSslSocket> socket) :AbstractResponseHandler(socket) { }

void SignInResponse::responseHandle(QJsonObject itemObject)
{
    qDebug() << "message :" << itemObject["message"].toString() << "\n";
}
////////////////////////////////////////////////////////////////////////////////////////
SignInWithGoogleResponse::SignInWithGoogleResponse(std::shared_ptr<QSslSocket> socket) :AbstractResponseHandler(socket) { }

void SignInWithGoogleResponse::responseHandle(QJsonObject itemObject)
{
    qDebug() << "message :" << itemObject["message"].toString() << "\n";
}
////////////////////////////////////////////////////////////////////////////////////////
AutoSignInResponse::AutoSignInResponse(std::shared_ptr<QSslSocket> socket) :AbstractResponseHandler(socket) { }

void AutoSignInResponse::responseHandle(QJsonObject itemObject)
{
    qDebug() << "message :" << itemObject["message"].toString() << "\n";
}
////////////////////////////////////////////////////////////////////////////////////////
LogOutResponse::LogOutResponse(std::shared_ptr<QSslSocket> socket) :AbstractResponseHandler(socket) { }

void LogOutResponse::responseHandle(QJsonObject itemObject)
{
    qDebug() << "Message :" << itemObject["message"].toString() << "\n";
}
////////////////////////////////////////////////////////////////////////////////////////
CreatedWorkflowResponse::CreatedWorkflowResponse(std::shared_ptr<QSslSocket> socket) :AbstractResponseHandler(socket) { }

void CreatedWorkflowResponse::responseHandle(QJsonObject itemObject)
{
    qDebug() << "Message :" << itemObject["message"].toString() << "\n";
}
////////////////////////////////////////////////////////////////////////////////////////
UpdateWorkflowResponse::UpdateWorkflowResponse(std::shared_ptr<QSslSocket> socket) :AbstractResponseHandler(socket) { }

void UpdateWorkflowResponse::responseHandle(QJsonObject itemObject)
{
    qDebug() << "Message :" << itemObject["message"].toString() << "\n";
}
////////////////////////////////////////////////////////////////////////////////////////
InvitedToWorkflowResponse::InvitedToWorkflowResponse(std::shared_ptr<QSslSocket> socket) :AbstractResponseHandler(socket) { }

void InvitedToWorkflowResponse::responseHandle(QJsonObject itemObject)
{
    qDebug() << "Message :" << itemObject["message"].toString() << "\n";
}
////////////////////////////////////////////////////////////////////////////////////////
AllWorkflowsResponse::AllWorkflowsResponse(std::shared_ptr<QSslSocket> socket) :AbstractResponseHandler(socket) { }

void AllWorkflowsResponse::responseHandle(QJsonObject itemObject)
{
    qDebug() << "Message :" << itemObject["message"].toString() << "\n";
}
////////////////////////////////////////////////////////////////////////////////////////
SingleWorkflowDataResponse::SingleWorkflowDataResponse(std::shared_ptr<QSslSocket> socket) :AbstractResponseHandler(socket) { }

void SingleWorkflowDataResponse::responseHandle(QJsonObject itemObject)
{
    qDebug() << "Message :" << itemObject["message"].toString() << "\n";
}
////////////////////////////////////////////////////////////////////////////////////////
SendStatistics::SendStatistics(std::shared_ptr<QSslSocket> socket) :AbstractResponseHandler(socket) { }

void SendStatistics::responseHandle(QJsonObject itemObject)
{
    qDebug() << "Message :" << itemObject["message"].toString() << "\n";
}
////////////////////////////////////////////////////////////////////////////////////////
SendProfileResponse::SendProfileResponse(std::shared_ptr<QSslSocket> socket) :AbstractResponseHandler(socket) { }

void SendProfileResponse::responseHandle(QJsonObject itemObject)
{
    qDebug() << "Message :" << itemObject["message"].toString() << "\n";
}
////////////////////////////////////////////////////////////////////////////////////////
ToUpdateProfileResponse::ToUpdateProfileResponse(std::shared_ptr<QSslSocket> socket) :AbstractResponseHandler(socket) { }

void ToUpdateProfileResponse::responseHandle(QJsonObject itemObject)
{
    qDebug() << "Message :" << itemObject["message"].toString() << "\n";
}
////////////////////////////////////////////////////////////////////////////////////////