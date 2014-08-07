import QtQuick 2.1
import Deepin.Widgets 1.0

GridView {
    id: avatar_icon_view
    clip: true
    width: 290
    height: Math.min(cellHeight * Math.ceil(count /3), maxHeight)

    cellWidth: 96
    cellHeight: 93

    property bool withAddButton: false
    property int maxHeight: 10
    
    signal initialize
    signal deleteButtonClicked (string path)
    signal avatarSet (url path)
    signal checkPrivate (int idx)
    
    function doCheck(iconFile) {
        for (var i = 0; i < model.count; i++) {
            if (model.get(i).avatarPath == iconFile) {
                currentIndex = i
            }
        }
    }

    //AvatarPickDialog {
        //id: avatar_pick_dialog
        //folder: mainObject.getHomeDir()
        //onAccepted: {
            //avatarSet(fileUrl)
        //}
    //}

    DFileChooseDialog {
        id: avatar_pick_dialog
        currentFolder: mainObject.getHomeDir()
        onSelectAction: {
            avatarSet(fileUrl)
        }
    }

    MouseArea {
        z: -1
        anchors.fill: parent
        onClicked: { parent.forceActiveFocus() }
    }

    Keys.onUpPressed: { avatar_icon_view.moveCurrentIndexUp() }
    Keys.onDownPressed: { avatar_icon_view.moveCurrentIndexDown() }
    Keys.onLeftPressed: { avatar_icon_view.moveCurrentIndexLeft() }
    Keys.onRightPressed: { avatar_icon_view.moveCurrentIndexRight() }

    Component {
        id: avatar_icon_view_delegate


        Item {
            width: GridView.view.cellWidth
            height: GridView.view.cellHeight

            function checkSelect() {
                if (index == avatar_icon_view.currentIndex && round_image.checkSupport) {
                    round_image.state = "checked"
                } else {
                    round_image.state = "normal"
                }
            }

            Connections {
                target: avatar_icon_view

                onCurrentIndexChanged: { checkSelect() }
            }

            Component.onCompleted: {
                if (avatarPath == this_user.iconFile) {
                    round_image.state = "checked"
                }
            }

            DRoundImage {
                id: round_image

                roundRadius: 30
                borderWidth: 2
                glowRadius: 2
                imageSource: {
                    if(avatarPath.indexOf("image") != 0)
                        return "file://" + avatarPath
                    return avatarPath
                }
                checkSupport: !(withAddButton && index == (count - 1))

                onClicked: {
                    if (checkSupport) {
                        state = "checked"
                        avatar_icon_view.currentIndex = index
                        avatar_icon_view.forceActiveFocus()
                        avatar_icon_view.avatarSet(round_image.imageSource)
                    } else {
                        avatar_pick_dialog.showWindow()
                    }
                }

                onEntered: { delete_icon_button.visible = this_user.IsIconDeletable(avatarPath) }
                onExited: { delete_icon_button.visible = false}

                anchors.centerIn: parent
            }

            Image {
                id: delete_icon_button

                visible: false
                source: "images/delete_icon.png"
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.topMargin: 8
                anchors.rightMargin: 10

                MouseArea {
                    anchors.fill: parent

                    onClicked: avatar_icon_view.deleteButtonClicked(avatarPath)
                }
            }
        }
    }

    delegate: avatar_icon_view_delegate
    model: ListModel { id: avatar_icon_view_model }

    Component.onCompleted: {
        avatar_icon_view.initialize()
    }
}
