import QtQuick 2.15
import QtQuick.Controls 2.15
//import QtQuick.VirtualKeyboard 2.15
import QtQuick.Layouts 1.12
import PjSuaCtx 1.0

ApplicationWindow {
    id: window
    width: 600
    height: 440
    visible: true
    title: qsTr("Qsua")

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }
    }

    footer: ToolBar {
        RowLayout {
            anchors.fill: parent
            Label {
                text: qsTr("Client state:")
            }
            Label {
                id: regStateLabel
                text: "Unregistered"
            }
            Label {
                Layout.fillWidth: true
                id: regReasonLabel
            }
        }
    }

    Drawer {
        id: drawer
        width: window.width * 0.66
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Account configuration")
                width: parent.width
                onClicked: {
                    stackView.push("Page1.qml")
                    drawer.close()
                }
            }
            /*ItemDelegate {
                text: qsTr("Page 2")
                width: parent.width
                onClicked: {
                    stackView.push("Page2Form.ui.qml")
                    drawer.close()
                }
            }*/
        }
    }

    PjSuaContext {
        id: pjSuaCtx

        onRegStateChanged: {
            if(regIsActive) {
                regStateLabel.text = "Registered"
            } else {
                regStateLabel.text = "Unregistered"
            }

            regReasonLabel.text = statusTxt
        }
    }

    StackView {
        id: stackView
        initialItem: "Home.qml"
        anchors.fill: parent
    }

    /* qtvirtualkeyboard */
 /*   InputPanel {
        id: inputPanel
        z: 99
        x: 0
        y: window.height
        width: window.width

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: window.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }*/

    Component.onCompleted: {
        pjSuaCtx.start();
        pjSuaCtx.onCreateAccount();
    }
}
