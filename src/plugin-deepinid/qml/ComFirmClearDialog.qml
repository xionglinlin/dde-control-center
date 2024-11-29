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
    icon: "qrc:/icons/deepin/builtin/icons/dcc_union_id_32px.svg"
    width: 420

    signal requestClear()

    ColumnLayout {
        width: parent.width
        Label {
            Layout.fillWidth: true
            font: D.DTK.fontManager.t5
            text: qsTr("Are you sure you want to clear your system settings and personal data saved in the cloud?")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
        }

        Label {
            Layout.fillWidth: true
            font: D.DTK.fontManager.t7
            text: qsTr("Once the data is cleared, it cannot be recovered!")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter            
        }

        Item {
            Layout.fillWidth: true
            height: 10
        }        

        RowLayout {
            Layout.fillWidth: true
            Layout.bottomMargin: 10
            Button {
                text: qsTr("Cancel")
                Layout.fillWidth: true
                onClicked: {
                    close()
                }
            }
            D.WarningButton {
                text: qsTr("Clear")
                Layout.fillWidth: true
                onClicked: {
                    requestClear()
                }
            }
        }
    }
}
