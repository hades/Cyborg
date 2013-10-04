#include "CyborgCoder.h"
#include <QtCrypto>

#include <QDebug>

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
        qWarning() << "PassKey numHashes is invalid, assuming (1)";
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
    QCA::Hash hashObj("md5");
    hashObj.update(this->key);
    QByteArray iv = hashObj.final().toByteArray();

    QCA::Cipher cipher("aes128", QCA::Cipher::CBC, 
            QCA::Cipher::DefaultPadding, QCA::Decode,
            QCA::SymmetricKey(key), QCA::InitializationVector(iv));

    QByteArray out = QCA::SecureArray(cipher.process(data)).toByteArray();
    if (!cipher.ok()) {
        return QString();
    }

    return QString::fromUtf8(out);
}

