// Copyright (c) 2011-2018 The Cryptotalkcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CRYPTOTALKCOIN_QT_MACDOCKICONHANDLER_H
#define CRYPTOTALKCOIN_QT_MACDOCKICONHANDLER_H

#include <QObject>

/** macOS-specific Dock icon handler.
 */
class MacDockIconHandler : public QObject
{
    Q_OBJECT

public:
    static MacDockIconHandler *instance();
    static void cleanup();

Q_SIGNALS:
    void dockIconClicked();

private:
    MacDockIconHandler();
};

#endif // CRYPTOTALKCOIN_QT_MACDOCKICONHANDLER_H
