#ifndef TASKPANELMODEL_H
#define TASKPANELMODEL_H

#include <QAbstractListModel>
#include <QList>

struct Task {
    QString m_title = "";
    QStringList m_tags = {""};
    QStringList m_colaborants = {""};
    bool blank = false;
};

class TaskPanelModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit TaskPanelModel(QObject *parent = nullptr);

    enum {
        TitleRole = Qt::UserRole,
        TagsRole,
        ColabsRole,
        IconRole,
        BlankRole,
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    Q_INVOKABLE bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void move(int from, int to, int n);
    Q_INVOKABLE void test(int index);
    Q_INVOKABLE void removeBlank();

    Task getTask(int index);
    void setTask(int index, Task &task);

    Q_INVOKABLE void reset();

private:
    QList<Task> m_model;

private:
    int blank_index = -1;
};

#endif // TASKPANELMODEL_H
