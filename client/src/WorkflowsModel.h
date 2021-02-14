#ifndef WORKFLOWSMODEL_H
#define WORKFLOWSMODEL_H

#include <QAbstractListModel>

#include "ColaborantsModel.h"


struct Workflow {
    quint64 id = -1;
    QString title = "Untitled";
    QString deadline = "Inf";
    unsigned progress = 100;
    ColaborantsModel *colaborants = new ColaborantsModel;
};

class WorkflowsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum {
        DeadlineRole = Qt::UserRole,
        TitleRole,
        ProgressRole,
        ColaborantsRole,
    };

    explicit WorkflowsModel(QObject *parent = nullptr);

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

    Q_INVOKABLE void archive(int index);

    void add(const Workflow &flow);
    void addColaborant(quint64 index, const Colaborant &contact);

private:
    QList<Workflow> m_data;

};

#endif // WORKFLOWSMODEL_H
