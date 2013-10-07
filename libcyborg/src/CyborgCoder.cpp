#include "CyborgCoder.h"

#include <QDebug>
#include <QtCrypto>

static inline QCA::Cipher getCipher(const QByteArray& key, QCA::Direction dir)
{
    QCA::Hash hashObj("md5");
    hashObj.update(key);
    QByteArray iv = hashObj.final().toByteArray();
    return QCA::Cipher("aes128", QCA::Cipher::CBC, 
            QCA::Cipher::DefaultPadding, dir,
            QCA::SymmetricKey(key), QCA::InitializationVector(iv));
}

bool CyborgCoder::isSupported() 
{
    QCA::init();
    if (!QCA::isSupported("md5")) {
        return false;
    }
    if (!QCA::isSupported("aes128-cbc-pkcs7")) {
        return false;
    }
    return true;
}

CyborgCoder::CyborgCoder(const QString& passPhrase, int numHashes)
{
    if ( numHashes < 1) {
        qWarning() << "Pass phrase numHashes is invalid, assuming (1)";
        numHashes = 1;
    }

    QByteArray bytes = passPhrase.toUtf8();
    for(int i=0; i<numHashes; i++) {
        QCA::Hash hashObj("md5");
        hashObj.update(bytes);
        bytes = hashObj.final().toByteArray();
    }
    this->key = bytes;
}

CyborgCoder::CyborgCoder(const QByteArray& bytes)
{
    this->key = bytes;
}

QString CyborgCoder::decode(const QByteArray &data)
{
    QCA::Cipher cipher = getCipher(this->key, QCA::Decode);
    QByteArray out = QCA::SecureArray(cipher.process(data)).toByteArray();
    if (!cipher.ok()) {
        return QString();
    }
    return QString::fromUtf8(out);
}

QByteArray CyborgCoder::encode(const QString& msg )
{
    QByteArray data = msg.toUtf8();
    QCA::Cipher cipher = getCipher(this->key, QCA::Encode);
    QByteArray out = QCA::SecureArray(cipher.process(data)).toByteArray();
    if (!cipher.ok()) {
        return QByteArray();
    }
    return out;
}

