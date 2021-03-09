#include "TaskDescriptionModel.h"

#include <QJsonArray>

TaskDescriptionModel::TaskDescriptionModel(const QJsonObject &json, QObject *parent)
    : QAbstractListModel(parent) {
    m_data.resize(json.count());
    foreach(const QString& key, json.keys()) {
        const auto &value = json.value(key);

        Description d;
        d.property = key;
        d.type = value["type"].toInt();
        switch (d.type) {
            case 0:
                d.str = value["str"].toString(); break;
            case 1:
                d.str = value["date"].toString(); break;
            case 2:
                foreach(const auto& item, value["checkboxes"].toArray()) {
                    d.checkboxesText.push_back(item["value"].toString());
                    d.checkboxesText.push_back(item["status"].toString());
                }
                break;
            case 3:
                d.tags = value["tags"].toString().split('&');
                break;
        }
        m_data.insert(value["index"].toInt(), d);
    }
}

int TaskDescriptionModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;
    return m_data.size();
    // FIXME: Implement me!
}

QVariant TaskDescriptionModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    switch(role) {
        case PropertyRole: return m_data[index.row()].property;
        case TypeRole: return m_data[index.row()].type;
        case StrRole: return m_data[index.row()].str;
        case DateRole: return m_data[index.row()].date;
        case CheckBoxRole: return m_data[index.row()].checkboxesText;
        case CheckBoxStatus: return m_data[index.row()].checkboxesValue;
        case TagsRole: return m_data[index.row()].tags;
    }
    return QVariant();
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
    roles[PropertyRole] = "propertyValue";
    roles[TypeRole] = "typeValue";
    roles[StrRole] = "strValue";
    roles[DateRole] = "dateValue";
    roles[CheckBoxRole] = "checkboxText";
    roles[CheckBoxStatus] = "checkboxStatus";
    roles[CheckBoxesCountRole] = "checkboxSize";
    roles[TagsRole] = "tagsValue";
    return roles;
}
