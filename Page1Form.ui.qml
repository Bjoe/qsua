import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11
import Qt.labs.settings 1.1

Page {
    title: qsTr("Account configuration")

    Settings {
        property alias pjsuaAccConfigId: pjsuaAccConfigId.text
        property alias pjsuaAccConfigRegUri: pjsuaAccConfigRegUri.text
        property alias pjsipCredInfoScheme: pjsipCredInfoScheme.text
        property alias pjsipCredInfoRealm: pjsipCredInfoRealm.text
        property alias pjsipCredInfoUsername: pjsipCredInfoUsername.text
        property alias pjsipCredInfoData: pjsipCredInfoData.text
    }

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.bottomMargin: 20
        anchors.topMargin: 20

        GroupBox {
            id: groupBox
            width: 200
            height: 200
            Layout.fillWidth: true
            title: qsTr("Account configuration")

            GridLayout {
                id: gridLayout
                anchors.fill: parent
                columns: 2

                Label {
                    id: label
                    text: qsTr("The full SIP URL for the account")
                }

                TextField {
                    id: pjsuaAccConfigId
                    width: 80
                    height: 20
                    text: qsTr("")
                    font.pixelSize: 12
                    Layout.fillWidth: true
                    placeholderText: "\"Display Name\" <sip:account@provider>"
                }

                Label {
                    id: label1
                    text: qsTr("URL to be put in the request URI for the registration")
                }

                TextField {
                    id: pjsuaAccConfigRegUri
                    width: 80
                    height: 20
                    text: qsTr("")
                    font.pixelSize: 12
                    Layout.fillWidth: true
                    placeholderText: "sip:serviceprovider"
                }
            }
        }

        GroupBox {
            id: groupBox1
            width: 200
            height: 200
            Layout.fillWidth: true
            title: qsTr("Account credentials")

            GridLayout {
                id: gridLayout1
                anchors.fill: parent
                columns: 2

                Label {
                    id: label2
                    text: qsTr("Credential Scheme")
                }

                TextField {
                    id: pjsipCredInfoScheme
                    width: 80
                    height: 20
                    text: qsTr("")
                    font.pixelSize: 12
                    Layout.fillWidth: true
                    placeholderText: "Digest"
                }

                Label {
                    id: label3
                    text: qsTr("Realm")
                }

                TextField {
                    id: pjsipCredInfoRealm
                    width: 80
                    height: 20
                    text: qsTr("")
                    font.pixelSize: 12
                    Layout.fillWidth: true
                    placeholderText: "*"
                }

                Label {
                    id: label4
                    text: qsTr("User name")
                }

                TextField {
                    id: pjsipCredInfoUsername
                    width: 80
                    height: 20
                    text: qsTr("")
                    font.pixelSize: 12
                    Layout.fillWidth: true
                    placeholderText: "user name"
                }

                Label {
                    id: label5
                    text: qsTr("Password")
                }

                TextField {
                    id: pjsipCredInfoData
                    Layout.fillWidth: true
                    placeholderText: qsTr("password")
                }
            }
        }
    }

    Component.onDestruction: {
        pjSuaCtx.onCreateAccount()
    }
}
