#include "CheckboxPropertyModel.h"
#include <QJsonArray>
#include "Client.h"

CheckboxPropertyModel::CheckboxPropertyModel(QObject *parent)
    : QAbstractListModel(parent) {
}

int CheckboxPropertyModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;
    return m_data.size();
}

QVariant CheckboxPropertyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    switch (role) {
        case IsDoneRole:
            return m_data.at(index.row()).done;
        case DescriptionRole:
            return m_data.at(index.row()).description;
    }
    return QVariant();
}

bool CheckboxPropertyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    switch (role) {
        case IsDoneRole:
            m_data[index.row()].done = value.toBool();
        case DescriptionRole:
            m_data[index.row()].description = value.toString();
    }
    emit dataChanged(index, index, QVector<int>() << role);
    return true;
}

Qt::ItemFlags CheckboxPropertyModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

bool CheckboxPropertyModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return true;
}

bool CheckboxPropertyModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
    return true;
}

QHash<int, QByteArray> CheckboxPropertyModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IsDoneRole] = "isDone";
    roles[DescriptionRole] = "description";
    return roles;
}

QVariant CheckboxPropertyModel::QVariantFromJson(const QJsonArray &json) {
    auto *data = new CheckboxPropertyModel();

    foreach(const auto &item, json) {
        Checkbox c;
        c.done = item.toObject().value("done").toBool();
        c.description = item.toObject().value("description").toString();
        data->model().push_back(c);
    }
    m_engine->rootContext()->setContextProperty("CheckboxModel", data);
    return QVariant::fromValue<CheckboxPropertyModel *>(data);
}

QJsonArray CheckboxPropertyModel::toJsonArray() {
    QJsonArray array;

    foreach(const auto &item, m_data) {
        QJsonObject wrap;
        wrap["done"] = item.done;
        wrap["description"] = item.description;
        array.push_back(wrap);
    }
    return array;
}

QVector<Checkbox> &CheckboxPropertyModel::model() {
    return m_data;
}

void CheckboxPropertyModel::removeItem(const int &index) {
    beginRemoveRows(QModelIndex(), index, index);
    m_data.remove(index);
    endRemoveRows();
}

void CheckboxPropertyModel::addItem() {
    Checkbox c;
    beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
    m_data.push_back(c);
    endInsertRows();
}