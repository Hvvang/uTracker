#include "TaskDescriptionModel.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "CheckboxPropertyModel.h"
#include "Client.h"

TaskDescriptionModel::TaskDescriptionModel(const int &taskId, QObject *parent)
    : QAbstractListModel(parent)
    , taskId(taskId) { }

int TaskDescriptionModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;
    return m_model.size();
}

QVariant TaskDescriptionModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    switch(role) {
        case PropertyNameRole:
            return m_model.at(index.row()).propertyName;
        case PropertyValueRole:
            return m_model.at(index.row()).value;
        case PropertyTypeRole:
            return m_model.at(index.row()).type;
    }
    return QVariant();
}

bool TaskDescriptionModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    qDebug() << mainTypeCount;
    if (!index.isValid() || (index.row() < mainTypeCount && role != PropertyValueRole))
        return false;

    qDebug() << "VALUE is " << value;
    auto &property = m_model[index.row()];
    switch(role) {
        case PropertyNameRole:
            property.propertyName = value.toString();
            break;
        case PropertyValueRole:
            property.value = value;
            break;
        case PropertyTypeRole:
            if (value.toInt() == 2) {
                auto *checkboxes = new CheckboxPropertyModel(this);
                m_engine->rootContext()->setContextProperty("CheckboxModel", checkboxes);
                property.value = QVariant::fromValue<CheckboxPropertyModel *>(checkboxes);
            }
            property.type = value.toInt();
            break;
    }
    emit dataChanged(index, index, QVector<int>() << role);
    return true;
}

Qt::ItemFlags TaskDescriptionModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEditable;
}

bool TaskDescriptionModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
}

bool TaskDescriptionModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
}

QHash<int, QByteArray> TaskDescriptionModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PropertyNameRole] = "propertyName";
    roles[PropertyValueRole] = "propertyValue";
    roles[PropertyTypeRole] = "propertyType";
    return roles;
}

void TaskDescriptionModel::reset(const int &id) {
    beginResetModel();
    m_model.clear();
    taskId = id;
    mainTypeCount = 0;
    endResetModel();
}

QVariant tagsFromJsonArray(const QJsonArray &jsonValue) {
    QStringList tags;
    foreach(const auto& item, jsonValue) {
        tags.push_back(item.toString());
    }
    return tags;
}

void TaskDescriptionModel::pushBack(const QString &description) {
    QJsonDocument doc = QJsonDocument::fromJson(description.toUtf8());
    QJsonArray json = doc.array();

    foreach(const auto &jsonValue, json) {
        qDebug() << jsonValue;
        QVariant value;
        switch (jsonValue["type"].toInt()) {
            case 0:
            case 1:
                value = jsonValue["value"].toString(); break;
            case 2:
                value = CheckboxPropertyModel::QVariantFromJson(
                        QJsonDocument::fromJson(jsonValue["value"].toString().toUtf8()).array());
                break;
            case 3:
                value = tagsFromJsonArray(jsonValue["value"].toArray());
                break;
            case 4:
//                value = CheckboxPropertyModel::QVariantFromJson(QJsonDocument::fromJson(description.toUtf8()).array());
                break;
        }
        pushBack(jsonValue["name"].toString(), value, jsonValue["type"].toInt(),false);
    }
}

void TaskDescriptionModel::pushBack(const QString &name, const QVariant &value, const int &typeId, const bool &isMain) {
    Description t;
    t.isMainType = isMain;
    t.type = typeId;
    t.propertyName = name;
    t.value = value;

    if (isMain) {
        ++mainTypeCount;
    }
    beginInsertRows(QModelIndex(), m_model.size(), m_model.size());
    m_model.push_back(t);
    endInsertRows();
}

void TaskDescriptionModel::removeProperty(const int &index) {
    if (m_model.at(index).isMainType) {
        --mainTypeCount;
    }
    beginRemoveRows(QModelIndex(), index, index);
    m_model.remove(index);
    endRemoveRows();
}

void TaskDescriptionModel::addProperty() {
    Description d;
    beginInsertRows(QModelIndex(), m_model.size(), m_model.size());
    m_model.push_back(d);
    endInsertRows();
}

int TaskDescriptionModel::Id() const {
    return taskId;
}

QString deserialize(const QJsonArray &json) {
    QJsonDocument doc(json);
    return doc.toJson();
}

QJsonObject TaskDescriptionModel::convertToJson() {
    QJsonObject json;
    QJsonArray description;

    foreach(const auto &property, m_model) {
        if (property.isMainType) {
            QString key;
            if (property.propertyName == "Title") {
                key = "title";
            } else if (property.propertyName == "Deadline time") {
                key = "deadline_time";
            } else {
                key = "creation_time";
            }
            json[key] = property.value.toString();
        } else {
            QJsonObject wrap;
            wrap["name"] = property.propertyName;
            wrap["type"] = property.type;
            switch (property.type) {
                case 0:
                case 1:
                    wrap["value"] = property.value.toString();
                    break;
                case 2:
                    wrap["value"] = deserialize(
                            qobject_cast<CheckboxPropertyModel *>(qvariant_cast<QObject*>(property.value))->toJsonArray());
                    break;
                case 3:
                    wrap["value"] = QJsonArray::fromStringList(property.value.toStringList());
                    break;
                case 4:

                    break;

            }
            description.push_back(wrap);
        }
    }
    QJsonDocument doc(description);
    QString desc = doc.toJson();
    json["description"] = deserialize(description);
//    qDebug() << "QWEEQWEQWEWEQWEQWE: " << json.value("description").toVariant().toString();
    return json;
}

