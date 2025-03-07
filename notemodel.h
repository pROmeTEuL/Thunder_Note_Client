#ifndef NOTEMODEL_H
#define NOTEMODEL_H

#include <QAbstractListModel>
#include <QDateTime>
#include <QNetworkAccessManager>
// #include <QNetworkRequestFactory>
// #include <QRestAccessManager>

#include <vector>

class NoteModel : public QAbstractListModel
{
    Q_OBJECT
public:
    NoteModel();

public slots:
    void erase(int row);
    void add(const QString &note);
    void edit(int row, const QString &note);
    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    void retreiveNotes();
private:
    std::vector<std::pair<QString, QDateTime>> m_notes;
    QNetworkAccessManager m_qnam;
    // std::shared_ptr<QNetworkRequestFactory> m_serviceApi;
    // std::shared_ptr<QRestAccessManager> m_manager;
};

#endif // NOTEMODEL_H
