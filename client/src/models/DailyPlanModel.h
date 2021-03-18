#ifndef DAILYPLANMODEL_H
#define DAILYPLANMODEL_H

#include <QAbstractListModel>

struct DailyTask {
    int id;
    QString title = "";
    bool status = false;
};

class DailyPlanModel : public QAbstractListModel
{
Q_OBJECT

public:
    enum {
        DescriptionRole = Qt::UserRole,
        StatusRole,
        IdRole,
    };

    explicit DailyPlanModel(QObject *parent = nullptr);

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
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    QHash<int, QByteArray> roleNames() const override;

    void push_back(const DailyTask &task);
    void update(const int &taskId, const QString &desc, const bool &status);
    void remove(const int &taskId);
    void reset();

private:
    QList<DailyTask> m_data;
};


#endif // DAILYPLANMODEL_H
