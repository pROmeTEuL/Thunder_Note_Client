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

private:
    void retreiveNotes();

private:
    struct NoteData {
        NoteData(int id, const QString &note, const QDateTime &date)
            : id(id)
            , note(note)
            , date(date)
        { }
        QString shortNote() const
        {
            auto idx = note.indexOf("\n");
            if (idx == -1)
                idx = note.length();
            idx = std::min<int>(idx, 25);
            return note.left(idx);
        }
        int id;
        QString note;
        QDateTime date;
    };
    std::vector<NoteData> m_notes;
    QNetworkAccessManager m_qnam;
    QByteArray m_data;
    // std::shared_ptr<QNetworkRequestFactory> m_serviceApi;
    // std::shared_ptr<QRestAccessManager> m_manager;
};

#endif // NOTEMODEL_H
