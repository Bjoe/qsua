import QtQuick 2.0

Page1Form {
    id: page1Form

    Component.onDestruction: {
        pjSuaCtx.onCreateAccount()
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
