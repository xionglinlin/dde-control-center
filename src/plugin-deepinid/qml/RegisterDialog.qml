// SPDX-FileCopyrightText: 2024 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import org.deepin.dcc 1.0
import org.deepin.dtk 1.0 as D

D.DialogWindow {
    id: dialog
    icon: "dcc_union_id"
    width: 400

    ColumnLayout {
        width: parent.width
        Label {
            Layout.fillWidth: true
            font: D.DTK.fontManager.t5
            text: qsTr("Set a Password")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Item {
            Layout.fillWidth: true
            height: 10
        }        

        D.PasswordEdit {
            Layout.fillWidth: true
            text: "123456"
        }

        D.PasswordEdit {
            Layout.fillWidth: true
            text: "123456"
        }

        RowLayout {
            Layout.alignment: Qt.AlignBottom | Qt.AlignHCenter
            Layout.bottomMargin: 10
            Layout.fillWidth: true
            Button {
                text: qsTr("Cancel")
                Layout.fillWidth: true
                onClicked: {
                    close()
                }
            }
            D.WarningButton {
                text: qsTr("Confirm")
                Layout.fillWidth: true
                onClicked: {
                    close()
                }
            }
        }
    }
}
