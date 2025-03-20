#include "notemodel.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkReply>

using namespace Qt::StringLiterals;

namespace {
const auto url = u"http://127.0.0.1:8080"_s;
enum Roles {
    Note = Qt::UserRole,
    Date
};
} //namespace

NoteModel::NoteModel()
{
    retreiveNotes();
}

void NoteModel::erase(int row)
{
    QNetworkRequest request;
    request.setUrl(url + "/api/v1/notes/" + QString::number(m_notes[row].id));
    QNetworkReply *reply = m_qnam.deleteResource(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply] {
        if (reply->error() == QNetworkReply::NoError) {
            retreiveNotes();
        } else {
            qDebug() << reply->errorString();
        }
    });
}

void NoteModel::add(const QString &note)
{
    QNetworkRequest request;
    QJsonObject obj;
    obj.insert("note", note);
    request.setUrl(url + "/api/v1/notes");
    QNetworkReply *reply = m_qnam.post(request, QJsonDocument{obj}.toJson());
    connect(reply, &QNetworkReply::finished, this, [this, reply] {
        if (reply->error() == QNetworkReply::NoError) {
            retreiveNotes();
        } else {
            qDebug() << reply->errorString();
        }
    });
}

void NoteModel::edit(int row, const QString &note)
{
    QNetworkRequest request;
    QJsonObject obj;
    obj.insert("note", note);
    request.setUrl(url + "/api/v1/notes/" + QString::number(m_notes[row].id));
    QNetworkReply *reply = m_qnam.put(request, QJsonDocument{obj}.toJson());
    connect(reply, &QNetworkReply::finished, this, [this, reply] {
        if (reply->error() == QNetworkReply::NoError) {
            retreiveNotes();
        } else {
            qDebug() << reply->errorString();
        }
    });
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
        return m_notes[index.row()].note;
    case Date:
        return m_notes[index.row()].date;
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
    m_notes.clear();
    QNetworkRequest request;
    request.setUrl(url + "/api/v1/notes");
    QNetworkReply *reply = m_qnam.get(request);
    connect(reply, &QNetworkReply::readyRead, this, [this, reply] {
        m_data += reply->readAll();
    });
    connect(reply, &QNetworkReply::finished, this, [this, reply] {
        if (reply->error() == QNetworkReply::NoError) {
            QJsonParseError err;
            const auto doc = QJsonDocument::fromJson(m_data, &err);
            if (err.error == QJsonParseError::NoError) {
                const auto data = doc.array();
                beginResetModel();
                for (const auto &o : data) {
                    const auto obj = o.toObject();
                    m_notes.emplace_back(obj["id"].toInt(), obj["note"].toString(), QDateTime::fromString(obj["date"].toString(), Qt::ISODate));
                }
                endResetModel();
            }
            m_data.clear();
        } else {
            qDebug() << reply->errorString();
        }
    });
}
