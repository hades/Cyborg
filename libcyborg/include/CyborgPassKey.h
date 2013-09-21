
#ifndef CYBORGPASSKEY_H
#define CYBORGPASSKEY_H

#include <QString>

class CyborgPassKey
{
public:
	CyborgPassKey(const QString& passPhrase, int numHashes=10);
	CyborgPassKey(const QByteArray&);
	QString decode(const QByteArray &data);

	static bool isSupported();

private:
	QByteArray key;
};

#endif
