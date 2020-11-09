import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

Item {
    id: rootDelegate
    height: hangupButton.implicitHeight
    width: listView.width

    signal clicked(string remoteUri)

    RowLayout {
        anchors.fill: rootDelegate
        Text {
            Layout.fillWidth: true

            id: uriTxt
            text: model.display
            font.bold: true

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("Click on " + model.display)
                    rootDelegate.clicked(model.display)
                }
            }
        }
        Text {
            id: txtState
            text: model.state
            font.bold: true
        }
        Button {
            id: acceptButton
            visible: false
            text: qsTr("Accept")
            onClicked: {
                model.callObj.accept();
            }
        }
        Button {
            id: declineButton
            visible: false
            text: qsTr("Decline")
            onClicked: {
                model.callObj.decline();
            }
        }
        Button {
            id: hangupButton
            visible: false
            text: qsTr("Hangup")
            onClicked: {
                model.callObj.hangup();
            }
        }
    }

    states: [
        State {
            when: model.state === "INCOMING"
            PropertyChanges { target: acceptButton; visible: true }
            PropertyChanges { target: declineButton; visible: true }
        },
        State {
            when: model.state === "CALLING"
            PropertyChanges { target: hangupButton; visible: true }
        },
        State {
            when: model.state === "CONNECTING"
            PropertyChanges { target: hangupButton; visible: true }
        },
        State {
            when: model.state === "EARLY"
            PropertyChanges { target: hangupButton; visible: true }
        },
        State {
            when: model.state === "CONFIRMED"
            PropertyChanges { target: hangupButton; visible: true }
        },
        State {
            when: model.state === "DISCONNCTD"
            PropertyChanges { target: acceptButton; visible: false }
            PropertyChanges { target: declineButton; visible: false }
            PropertyChanges { target: hangupButton; visible: false }
        }

    ]
}
