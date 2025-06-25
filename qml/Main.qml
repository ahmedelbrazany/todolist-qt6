import QtQuick 6.5
import QtQuick.Controls 6.5
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 400
    height: 600
    title: qsTr("ToDo List")

    ColumnLayout {
        anchors.fill: parent
        spacing: 10  // ضبط المسافة بين العناصر

        TextField {
            id: taskName
            placeholderText: "Task Name"
            Layout.fillWidth: true  // اجعل العنصر يشغل كامل العرض
        }

        TextField {
            id: startTime
            placeholderText: "Start Time (HH:MM)"
            Layout.fillWidth: true  // اجعل العنصر يشغل كامل العرض
            inputMethodHints: Qt.ImhFormattedNumbersOnly
        }

        TextField {
            id: endTime
            placeholderText: "End Time (HH:MM)"
            Layout.fillWidth: true  // اجعل العنصر يشغل كامل العرض
            inputMethodHints: Qt.ImhFormattedNumbersOnly
        }

        Button {
            text: "Add Task"
            onClicked: {
                if (startTime.text !== "" && endTime.text !== "") {
                    taskManager.addTask(taskName.text, startTime.text, endTime.text)
                    taskName.text = ""
                    startTime.text = ""
                    endTime.text = ""
                } else {
                    console.log("Please enter valid start and end times.")
                }
            }
        }

        ListView {
            id: taskList
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: taskManager.tasks
            interactive: true
            delegate: Rectangle {
                width: parent.width
                height: 60
                color: "#ffffff"
                radius: 10
                border.color: "#ccc"

                // MouseArea with drag functionality
                MouseArea {
                    id: dragArea
                    anchors.fill: parent
                    drag.target: parent  // Dragging target is the parent Rectangle

                    // Define drag properties within MouseArea
                    Drag.active: dragArea.drag.active
                    Drag.hotSpot.x: mouse.x
                    Drag.hotSpot.y: mouse.y
                    Drag.source: parent  // The source is the parent Rectangle

                    onReleased: {
                        console.log("Item released")
                    }
                }

                Row {
                    spacing: 10
                    anchors.centerIn: parent
                    Text { text: model.name }
                    Text { text: model.startTime + " - " + model.endTime }
                }
            }
            onMovementEnded: {
                console.log("Tasks visually reordered")
            }
        }
    }

    Connections {
        target: taskManager
        function onTaskStartingSoon(taskName) {
            toast.text = "⏰ " + taskName + " is starting soon!"
            toast.open()
        }
    }

    Popup {
        id: toast
        width: parent.width
        height: 50
        anchors.centerIn: parent  // وضع الـ Popup في المنتصف
        background: Rectangle {
            color: "#333"
            radius: 10
            border.color: "#ccc"
        }
        Text {
            anchors.centerIn: parent
            color: "white"
            font.pixelSize: 16
            text: toast.text
        }

        property string text: ""

        // Display the Popup when triggered
        onTextChanged: {
            if (text.length > 0) {
                visible = true
                // Hide the Popup after 4 seconds
                Qt.callLater(function() {
                    visible = false
                })
            }
        }
    }
}
