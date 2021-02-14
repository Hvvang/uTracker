//
// Created by Artem Shemidko on 03.02.2021.
//

#include "Client.h"
#include <QHostAddress>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>

#include "googleauth.h"
#include "models/KanbanModel.h"

Client* Client::m_instance = nullptr;

Client::Client(QQmlApplicationEngine *engine, const QHostAddress &host, const quint16 port, QObject *parent)
    : QObject(parent)
    , m_engine(engine) {

    m_socket.connectToHost(host, port);
    connect(&m_socket, &QTcpSocket::connected, this, [=]{
        qDebug() << "Client successfully connected to server.";

        initResponseHandlers();
        connect(this, &Client::request, this, &Client::send);
//        autoSignIn();

        connect(&m_socket, &QTcpSocket::bytesWritten, this, &Client::bytesWritten);
        connect(&m_socket, &QTcpSocket::readyRead, this, &Client::readyRead);
        connect(&m_socket, &QTcpSocket::disconnected, this, [=] {
            reject();
            deinitResponseHandlers();
            qDebug() << "disconnected...";
        });

    });
    m_instance = this;
}


void Client::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}

void Client::readyRead() {
    while (!m_socket.atEnd()) {

        QByteArray size = m_socket.readLine();
        auto data = m_socket.read(size.toInt());
        qDebug() << "response is " << data;
        QJsonDocument itemDoc = QJsonDocument::fromJson(data);


        if (!itemDoc.isNull()) {
            QJsonObject rootObject = itemDoc.object();

            int responseType;
            if (rootObject.contains("type")) {
                emit handled(data);
            } else {
                return;
            }
        }
    }
}

void Client::deinitResponseHandlers() {
    delete m_authHandler;
    delete m_profileHandler;
    delete m_createWorkflowHandler;
    delete m_archiveWorkflowHandler;
    delete m_inviteContactResponseHandler;
    delete m_getWorkflowsResponseHandler;
    delete m_editWorkflowResponseHandler;
    delete m_getWorkflowColaborantsResponseHandler;
}

void Client::initResponseHandlers() {
    m_authHandler = new AuthorisationResponseHandler(this);
    m_profileHandler = new ProfileDataResponseHandler(this);
    m_createWorkflowHandler = new CreateWorkflowResponseHandler(this);
    m_archiveWorkflowHandler = new ArchiveWorkflowResponseHandler(this);
    m_inviteContactResponseHandler = new InviteContactResponseHandler(this);
    m_getWorkflowsResponseHandler = new GetWorkflowsResponseHandler(this);
    m_editWorkflowResponseHandler = new EditWorkflowResponseHandler(this);
    m_getWorkflowColaborantsResponseHandler = new GetWorkflowColaborantsResponseHandler(this);
}

void Client::send(const QString &data) {
    QByteArray json = data.toUtf8();

    QByteArray buffer;
    m_socket.write(buffer.setNum(json.size()));
    m_socket.write("\n" + json);
}


Client *Client::singleton() {
    if (!m_instance) {
        m_instance = new Client();
    }
    return m_instance;
}

void Client::getProfileData() {
    QJsonObject json;

    json["type"] = static_cast<int>(Client::RequestType::GET_PROFILE);
    json["token"] = m_accessesToken;
    json["userId"] = m_id;

    QJsonDocument document;
    document.setObject(json);
    emit request(document.toJson(QJsonDocument::Compact));
}

void Client::setProfile(const QString &login, const QString &name, const QString &surname) {
    m_profile.login = login;
    m_profile.name = name;
    m_profile.surname = surname;
    emit profileNameChanged();
}

void Client::setId(quint64 id) {
    m_id = id;
}

void Client::saveToken(const QString &type, const QString &value) {
    QFile file(AUTH_CONFIGURE_FILE);
    m_accessesToken = value;

    if (!file.open(QIODevice::ReadWrite)) {
        return;
    }

    QJsonObject json = QJsonDocument().fromJson(file.readAll()).object();
    json[type] = value;

    QJsonDocument document;
    document.setObject(json);
    file.write(document.toJson(QJsonDocument::Indented));
}

QString Client::getToken(const QString &type) {
    QFile file(AUTH_CONFIGURE_FILE);

    if (!file.open(QIODevice::ReadWrite)) {
        return QString();
    }

    auto json = QJsonDocument().fromJson(file.readAll()).object();
    return json.value(type).toString();
}

void Client::googleAuthorize() {
    if (!m_googleInstance)
        m_googleInstance = new GoogleAuth(this);
}

void Client::autoSignIn() {
    QString token;
    QJsonObject json;

    if (token = m_client->getToken("auth_token"); !token.isEmpty()) {
        json["type"] = static_cast<int>(Client::RequestType::AUTO_AUTH);
        json["token"] = token;
    } else if (token = m_client->getToken("accesses_token"); !token.isEmpty()) {
        json["type"] = static_cast<int>(Client::RequestType::AUTO_OAUTH);
        json["token"] = token;
    } else {
        return;
    }
    QJsonDocument document;
    document.setObject(json);
    emit request(document.toJson(QJsonDocument::Compact));
}

void Client::authorize(const QString &email, const QString &password) {
    QJsonObject json;

    json["type"] = static_cast<int>(Client::RequestType::SIGN_IN);
    json["email"] = email;
    json["password"] = password;

    QJsonDocument document;
    document.setObject(json);
    emit request(document.toJson(QJsonDocument::Compact));
}

void Client::registrate(const QString &email, const QString &password,
                    const QString &name, const QString &surname) {
    QJsonObject json;

    json["type"] = static_cast<int>(Client::RequestType::SIGN_UP);;
    json["email"] = email;
    json["password"] = password;
    json["name"] = name;
    json["surname"] = surname;

    QJsonDocument document;
    document.setObject(json);
    emit request(document.toJson(QJsonDocument::Compact));
}

void Client::openWorkflow(int index) {
//    KanbanModel kanban(this);
//
//    m_engine->rootContext()->setContextProperty("KanbanModel", &kanban);
    emit switchMenu("qrc:/qml/workflowswindow/Kanbanview.qml");
}

QChar Client::nameFirstLetter() {
    if (!m_profile.name.isEmpty()) {
        return m_profile.name.front();
    }
    return QChar();
}

void Client::createWorkflow(const QString &title, const QString &date) {
    QJsonObject json;

    json["type"] = static_cast<int>(Client::RequestType::CREATE_WORKFLOW);
    json["token"] = m_accessesToken;
    json["title"] = title;
    json["deadline"] = date;
    json["userId"] = m_id;

    QJsonDocument document;
    document.setObject(json);
    emit request(document.toJson(QJsonDocument::Compact));
}

void Client::archiveWorkflow(int index) {
    QJsonObject json;

    json["type"] = static_cast<int>(Client::RequestType::ARCHIVE_WORKFLOW);
    json["token"] = m_accessesToken;
    json["workflowId"] = index;

    QJsonDocument document;
    document.setObject(json);
    emit request(document.toJson(QJsonDocument::Compact));
}

void Client::inviteContact(const QString &contact, int index) {
    QJsonObject json;

    json["type"] = static_cast<int>(Client::RequestType::INVITE_CONTACT);
    json["token"] = m_accessesToken;
    json["workflowId"] = index;
    json["contact"] = contact;

    QJsonDocument document;
    document.setObject(json);
    emit request(document.toJson(QJsonDocument::Compact));
}

void Client::getWorkflows() {
    QJsonObject json;

    json["type"] = static_cast<int>(Client::RequestType::GET_WORKFLOWS);
    json["token"] = m_accessesToken;
    json["userId"] = m_id;

    QJsonDocument document;
    document.setObject(json);
    emit request(document.toJson(QJsonDocument::Compact));
}

void Client::editWorkflow(int id, const QString &title, const QString &date) {
    QJsonObject json;

    json["type"] = static_cast<int>(Client::RequestType::UPDATE_WORKFLOW);
    json["token"] = m_accessesToken;
    json["userId"] = m_id;
    json["workflowId"] = id;
    json["title"] = title;
    json["deadline"] = date;

    QJsonDocument document;
    document.setObject(json);
    emit request(document.toJson(QJsonDocument::Compact));
}

void Client::getWorkflowColaborants(int workflowId) {
    QJsonObject json;

    json["type"] = static_cast<int>(Client::RequestType::GET_WORKFLOW_COLABORANT);
    json["token"] = m_accessesToken;
    json["userId"] = m_id;
    json["workflowId"] = workflowId;

    QJsonDocument document;
    document.setObject(json);
    emit request(document.toJson(QJsonDocument::Compact));
}

void Client::logout() {
    QJsonObject json;

    json["type"] = static_cast<int>(Client::RequestType::LOGOUT);
    json["token"] = m_accessesToken;
    json["userId"] = m_id;

    QJsonDocument document;
    document.setObject(json);
    emit request(document.toJson(QJsonDocument::Compact));
}

void Client::newWorkflow(const Workflow &flow) {
    m_workflows->add(flow);
}

void Client::removeWorkflow(int id) {
    m_workflows->archive(id);
}

void Client::addColaborant(quint64 flowIndex, const Colaborant &contact) {
    m_workflows->addColaborant(flowIndex, contact);
}

void Client::updateWorkflow(const Workflow &flow) {
    m_workflows->updateWorkflow(flow);
}

void Client::reject() {
    if (m_workflows) {
        delete m_workflows;
        m_workflows = nullptr;
    }
    if (m_kanban) {
        delete m_kanban;
        m_kanban = nullptr;
    }

//    deinitResponseHandlers();
}

void Client::initWorkflowsModel() {
    if (!m_workflows) {
        m_workflows = new WorkflowsModel(this);
        m_engine->rootContext()->setContextProperty("WorkflowsModel", m_workflows);
    }
}









