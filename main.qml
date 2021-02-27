import Qt3D 2.0
import Qt3D.Renderer 2.0
import QtQuick 2.1 as QQ2
import QtQuick.Window 2.0

//Window {
//    visible: true;
//    title: qsTr("3D姿态展示")
//}
Entity
{
    components: FrameGraph {
        activeFrameGraph: ForwardRenderer {
            clearColor: Qt.rgba(0, 0.5, 1, 1)
            camera: camera
        }
    }

    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        aspectRatio: 16/9
        nearPlane : 0.1
        farPlane : 1000.0
        position: Qt.vector3d( 0.0, 0.0, 40.0 )    //Qt.vector3d( _data.getanX(), _data.getanY(), _data.getanZ() )
        upVector: Qt.vector3d( 0.0, 100.0, 0.0 )
        viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
    }

    Configuration  {
        controlledCamera: camera
    }

    Entity {
        id: robot
        components : [
            Transform {
                Scale { scale: 5 }
                Translate { dy: -10 }
                Rotate {
                    id: rotateX
                    angle : _data.agx
                    axis: Qt.vector3d(1, 0, 0)
                }
                Rotate {
                    id: rotateY
                    angle: _data.agy
                    axis: Qt.vector3d(0, 1, 0)
                }
                Rotate {
                    id: rotateZ
                    angle: _data.agz
                    axis: Qt.vector3d(0, 0, 1)
                }


//                Rotate {
//                    id: rotateX
//                    angle: 0
//                    axis: Qt.vector3d(1, 0, 0)
//                }
//                Rotate {
//                    id: rotateY
//                    angle: 0
//                    axis: Qt.vector3d(0, 1, 0)
//                }
//                Rotate {
//                    id: rotateZ
//                    angle: 0
//                    axis: Qt.vector3d(0, 0, 1)
//                }
            },
            SceneLoader
            {
                source: "qrc:/new/prefix1/robot.obj"
            }
        ]

//        QQ2.ParallelAnimation {
//            loops: QQ2.Animation.Infinite
//            running: true
//            QQ2.NumberAnimation {
//                target: rotateX
//                property: "angle"
//                from: 0; to: _data.getanX();
//                duration: 4000
//            }
//            QQ2.NumberAnimation {
//                target: rotateY
//                property: "angle"
//                from: 0; to: _data.getanY();
//                duration: 4000
//            }
//            QQ2.NumberAnimation {
//                target: rotateZ
//                property: "angle"
//                from: 0; to: _data.getanZ();
//                duration: 4000
//            }
//        }
    }
}

