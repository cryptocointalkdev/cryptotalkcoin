// Copyright (c) 2011-2014 The Cryptotalkcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CRYPTOTALKCOIN_QT_CRYPTOTALKCOINADDRESSVALIDATOR_H
#define CRYPTOTALKCOIN_QT_CRYPTOTALKCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class CryptotalkcoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit CryptotalkcoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Cryptotalkcoin address widget validator, checks for a valid cryptotalkcoin address.
 */
class CryptotalkcoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit CryptotalkcoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // CRYPTOTALKCOIN_QT_CRYPTOTALKCOINADDRESSVALIDATOR_H
