// Copyright (c) 2017-2018 The PIVX developers
// Copyright (c) 2019-2020 The LEVIATHAN developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZLVTCONTROLDIALOG_H
#define ZLVTCONTROLDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "zlvt/zerocoin.h"
#include "privacydialog.h"

class CZerocoinMint;
class WalletModel;

namespace Ui {
class ZLvtControlDialog;
}

class CZLvtControlWidgetItem : public QTreeWidgetItem
{
public:
    explicit CZLvtControlWidgetItem(QTreeWidget *parent, int type = Type) : QTreeWidgetItem(parent, type) {}
    explicit CZLvtControlWidgetItem(int type = Type) : QTreeWidgetItem(type) {}
    explicit CZLvtControlWidgetItem(QTreeWidgetItem *parent, int type = Type) : QTreeWidgetItem(parent, type) {}

    bool operator<(const QTreeWidgetItem &other) const;
};

class ZLvtControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZLvtControlDialog(QWidget *parent);
    ~ZLvtControlDialog();

    void setModel(WalletModel* model);

    static std::set<std::string> setSelectedMints;
    static std::set<CMintMeta> setMints;
    static std::vector<CMintMeta> GetSelectedMints();

private:
    Ui::ZLvtControlDialog *ui;
    WalletModel* model;
    PrivacyDialog* privacyDialog;

    void updateList();
    void updateLabels();

    enum {
        COLUMN_CHECKBOX,
        COLUMN_DENOMINATION,
        COLUMN_PUBCOIN,
        COLUMN_VERSION,
        COLUMN_PRECOMPUTE,
        COLUMN_CONFIRMATIONS,
        COLUMN_ISSPENDABLE
    };
    friend class CZLvtControlWidgetItem;

private slots:
    void updateSelection(QTreeWidgetItem* item, int column);
    void ButtonAllClicked();
};

#endif // ZLVTCONTROLDIALOG_H
