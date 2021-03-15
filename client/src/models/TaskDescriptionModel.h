#ifndef TASKDESCRIPTIONMODEL_H
#define TASKDESCRIPTIONMODEL_H

#include <QAbstractListModel>
#include <QJsonObject>

struct Description {
    int type = 0; // 0: string; 1: date; 2: checkboxes, 3: tags, 4: workers
    bool isMainType = false;
    QString propertyName;
    QVariant value;
};


class TaskDescriptionModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit TaskDescriptionModel(const int &taskId, QObject *parent = nullptr);

    int Id() const;
    void reset(const int &id);
    void pushBack(const QString &description);
    void pushBack(const QString &name, const QVariant &value, const int &typeId = 0, const bool &isMain = true);

    enum {
        PropertyNameRole = Qt::UserRole,
        PropertyValueRole,
        PropertyTypeRole,
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void addProperty();
    Q_INVOKABLE void removeProperty(const int &index);

    QJsonObject convertToJson();

private:
    int taskId;
    int mainTypeCount = 0;
    QVector<Description> m_model;
};

#endif // TASKDESCRIPTIONMODEL_H
