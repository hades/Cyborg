
#ifndef CYBORGCODER_H
#define CYBORGCODER_H

#include <QString>

class CyborgCoder
{
public:
    CyborgCoder(const QString& passPhrase, int numHashes=10);
    CyborgCoder(const QByteArray&);
    QString decode(const QByteArray &data);
    QByteArray encode(const QString &msg);

    static bool isSupported();

private:
    QByteArray key;
};

#endif
