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

////auth sector//////////////////////////////////////////
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
    if (!itemObject["email"].toString().isEmpty()
        && !itemObject["password"].toString().isEmpty()) {
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
////workflow (desk) sector//////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToCreatedWorkflow::ToCreatedWorkflow(Connection *socket) : AbstractRequestHandler(socket){}

bool ToCreatedWorkflow::isValid(QJsonObject itemObject) {
    if (itemObject.contains("title")
        && itemObject.contains("deadline")
        && itemObject.contains("userId")) {
            return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToUpdateWorkflow::ToUpdateWorkflow(Connection *socket) : AbstractRequestHandler(socket){}

bool ToUpdateWorkflow::isValid(QJsonObject itemObject) {
    if (itemObject.contains("title")
     && itemObject.contains("deadline")
     && itemObject.contains("workflowId"))
        return true;
    return false;
}
ArchiveWorkflow::ArchiveWorkflow(Connection *socket) : AbstractRequestHandler(socket){}

bool ArchiveWorkflow::isValid(QJsonObject itemObject) {
    if (itemObject.contains("token")
     && itemObject.contains("workflowId"))
        return true;
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToInvitedToWorkflow::ToInvitedToWorkflow(Connection *socket) : AbstractRequestHandler(socket){}

bool ToInvitedToWorkflow::isValid(QJsonObject itemObject) {
    if (itemObject.contains("email")
        && itemObject.contains("workflowId"))
        return true;
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToRemoveFromWorkflow::ToRemoveFromWorkflow(Connection *socket) : AbstractRequestHandler(socket){}

bool ToRemoveFromWorkflow::isValid(QJsonObject itemObject) {
    if (itemObject.contains("workflowId")
        && itemObject.contains("userId"))
        return true;
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToGetUsersFromWorkflow::ToGetUsersFromWorkflow(Connection *socket) : AbstractRequestHandler(socket){}

bool ToGetUsersFromWorkflow::isValid(QJsonObject itemObject) {
    if (itemObject.contains("workflowId"))
        return true;
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
SendAllWorkflows::SendAllWorkflows(Connection *socket) : AbstractRequestHandler(socket){}

bool SendAllWorkflows::isValid(QJsonObject itemObject) {
    if (itemObject.contains("userId"))
        return true;
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
SendSingleWorkflowData::SendSingleWorkflowData(Connection *socket) : AbstractRequestHandler(socket){}

bool SendSingleWorkflowData::isValid(QJsonObject itemObject) {
    if (itemObject.contains("workflowId"))
        return true;
    return false;
}
////statistic sector//////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
SendStatistics::SendStatistics(Connection *socket) : AbstractRequestHandler(socket){}

bool SendStatistics::isValid(QJsonObject itemObject) {
    Q_UNUSED(itemObject);
    return true;
}
////profile sector//////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
SendProfile::SendProfile(Connection *socket) : AbstractRequestHandler(socket){}

bool SendProfile::isValid(QJsonObject itemObject) {
    if (itemObject.contains("userId"))
        return true;
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
ToUpdateProfile::ToUpdateProfile(Connection *socket) : AbstractRequestHandler(socket){}

bool ToUpdateProfile::isValid(QJsonObject itemObject) {
    if (itemObject.contains("name")
        && itemObject.contains("surname")
        && itemObject.contains("userId"))
        return true;
    return false;
}
////list sector//////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToCreateList::ToCreateList(Connection *socket) : AbstractRequestHandler(socket){}

bool ToCreateList::isValid(QJsonObject itemObject) {
    if (itemObject.contains("title")
        && itemObject.contains("creatorId")
        && itemObject.contains("listIndex")
        && itemObject.contains("workflowId"))
        return true;
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToRenameList::ToRenameList(Connection *socket) : AbstractRequestHandler(socket){}

bool ToRenameList::isValid(QJsonObject itemObject) {
    if (itemObject.contains("title")
        && itemObject.contains("listId"))
        return true;
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToGetLists::ToGetLists(Connection *socket) : AbstractRequestHandler(socket){}

bool ToGetLists::isValid(QJsonObject itemObject) {
    if (itemObject.contains("workflowId"))
        return true;
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToRemoveList::ToRemoveList(Connection *socket) : AbstractRequestHandler(socket){}

bool ToRemoveList::isValid(QJsonObject itemObject) {
    if (itemObject.contains("listId"))
        return true;
    return false;
}
////task sector//////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToCreateTask::ToCreateTask(Connection *socket) : AbstractRequestHandler(socket){}

bool ToCreateTask::isValid(QJsonObject itemObject) {
    if (itemObject.contains("title")
        && itemObject.contains("listId")
        && itemObject.contains("creatorId")
        && itemObject.contains("taskIndex"))
        return true;
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToGetTasks::ToGetTasks(Connection *socket) : AbstractRequestHandler(socket){}

bool ToGetTasks::isValid(QJsonObject itemObject) {
    if (itemObject.contains("listId"))
        return true;
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
UpdateTaskTitleRequestHandler::UpdateTaskTitleRequestHandler(Connection *socket)
    : AbstractRequestHandler(socket) {}

bool UpdateTaskTitleRequestHandler::isValid(QJsonObject itemObject) {
    if (itemObject.contains("taskId") && itemObject.contains("title")) {
        return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToUpdateTask::ToUpdateTask(Connection *socket) : AbstractRequestHandler(socket){}

bool ToUpdateTask::isValid(QJsonObject itemObject) {
    if (itemObject.contains("taskId")
        && itemObject.contains("title")
        && itemObject.contains("deadline_time")
        && itemObject.contains("creation_time")
        && itemObject.contains("tags")
        && itemObject.contains("description")) {
        return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToMoveTask::ToMoveTask(Connection *socket) : AbstractRequestHandler(socket){}

bool ToMoveTask::isValid(QJsonObject itemObject) {
    if (itemObject.contains("listId")
        && itemObject.contains("taskId")
        && itemObject.contains("taskIndex"))
        return true;
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
ToRemoveTask::ToRemoveTask(Connection *socket) : AbstractRequestHandler(socket){}

bool ToRemoveTask::isValid(QJsonObject itemObject) {
    if (itemObject.contains("taskId"))
        return true;
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
SendTaskData::SendTaskData(Connection *socket) : AbstractRequestHandler(socket){}

bool SendTaskData::isValid(QJsonObject itemObject) {
    if (itemObject.contains("taskId"))
        return true;
    return false;
}

GetTaskWorkers::GetTaskWorkers(Connection *socket) : AbstractRequestHandler(socket){}

bool GetTaskWorkers::isValid(QJsonObject itemObject) {
    if (itemObject.contains("taskId"))
        return true;
    return false;
}

ChangeTaskWorkStatus::ChangeTaskWorkStatus(Connection *socket) : AbstractRequestHandler(socket){}

bool ChangeTaskWorkStatus::isValid(QJsonObject itemObject) {
    if (itemObject.contains("taskId")
        && itemObject.contains("userId")
        && itemObject.contains("status"))
        return true;
    return false;
}

ChangeTaskDoneStatus::ChangeTaskDoneStatus(Connection *socket) : AbstractRequestHandler(socket){}

bool ChangeTaskDoneStatus::isValid(QJsonObject itemObject) {
    if (itemObject.contains("taskId")
        && itemObject.contains("userId")
        && itemObject.contains("status"))
        return true;
    return false;
}

bool GetDailyPlan::isValid(QJsonObject itemObject) {
    if (itemObject.contains("userId"))
        return true;
    return false;
}
bool CreateDailyTask::isValid(QJsonObject itemObject) {
    Q_UNUSED(itemObject)
    return true;
}
bool RemoveDailyTask::isValid(QJsonObject itemObject) {
    if (itemObject.contains("taskId"))
        return true;
    return false;
}
bool UpdateDailyTask::isValid(QJsonObject itemObject) {
    if (itemObject.contains("taskId")
        && itemObject.contains("title")
        && itemObject.contains("status"))
        return true;
    return false;
}