#include "notemodel.h"

namespace {
enum Roles {
    Note = Qt::UserRole,
    Date
};
} //namespace

NoteModel::NoteModel()
{
    for (int i = 1; i <= 50; ++i) {
        m_notes.emplace_back(QString("Note %1").arg(i), QDateTime::currentDateTime());
    }
}

void NoteModel::erase(int row)
{
    beginRemoveRows({}, row, row);
    m_notes.erase(m_notes.begin() + row);
    endRemoveRows();
}

void NoteModel::add(const QString &note)
{
    beginInsertRows({}, m_notes.size(), m_notes.size());
    m_notes.emplace_back(note, QDateTime::currentDateTime());
    endInsertRows();
}

void NoteModel::edit(int row, const QString &note)
{
    m_notes[row].first = note;
    m_notes[row].second = QDateTime::currentDateTime();
    emit dataChanged(createIndex(row, 0), createIndex(row, 0));
}

int NoteModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return -1;
    return m_notes.size();
}

QVariant NoteModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return {};
    switch (role) {
    case Note:
        return m_notes[index.row()].first;
    case Date:
        return m_notes[index.row()].second;
    }
    return {};
}

QHash<int, QByteArray> NoteModel::roleNames() const
{
    static const QHash<int, QByteArray> roles {
        {Note, "_note"},
        {Date, "_date"}
    };
    return roles;
}

void NoteModel::retreiveNotes()
{
    QNetworkRequest request;
    request.setUrl(QUrl("127.0.0.1:8080/api/v1/notes"));
    QNetworkReply *reply = m_qnam.get(request);
}
