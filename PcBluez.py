#coding:utf-8

from PySide import QtGui,QtCore
import sys
import serial
import time

keyMap={
    QtCore.Qt.Key_Up:u"w",
    QtCore.Qt.Key_Right:u"d",
    QtCore.Qt.Key_Left:u"a",
    QtCore.Qt.Key_Down:u"s",
    QtCore.Qt.Key_Space:u"p",}
class PySerial():
    def __init__(self,port):
        self.port=port
        self.initSerial(port)
    def initSerial(self,port):
        self.pySerial=serial.Serial(
            port,
            9600,
            serial.EIGHTBITS,
            serial.PARITY_NONE,
            serial.STOPBITS_ONE)
        time.sleep(2)

class TestWidget(QtGui.QWidget):
    def __init__(self,port="com8",parent=None):
        super(TestWidget,self).__init__(parent)
        self.resize(400,300)
        self.move(100,100)
        self.setWindowTitle(u"Test")
        self.label=QtGui.QLabel(self)
        self.label.setGeometry(QtCore.QRect(100,100,131,71))
        self.label.setText(u"This is a test.")
        self.thisidx=0;
        self.lastHeldKey=None;
        self.adruino=PySerial(port)

    def keyPressEvent(self,event):
        if event.key() not in keyMap.keys():
            QtGui.QWidget.keyPressEvent(self,event)
            return

        for key,cmd in keyMap.items():
            if key==event.key() and self.lastHeldKey!=event.key():
                self.send(cmd)
                self.label.setText(u"Direction:%s"%cmd)
                self.lastHeldKey=key
                break
    def keyReleaseEvent(self,event):
        if event.isAutoRepeat():
            QtGui.QWidget.keyReleaseEvent(self,event)
        else:
            self.send("p")
            self.label.setText(u"Direction:Stopped.")
            self.lastHeldKey=QtCore.Qt.Key_Space

    def send(self,cmd):
        #print cmd
        self.adruino.pySerial.write(cmd)

    def event_(self,event):
        print event.type(),event.isAutoRepeat()
if __name__=="__main__":
    app=QtGui.QApplication(sys.argv)
    port=sys.argv[1]
    t=TestWidget(port)
    t.show()
    sys.exit(app.exec_())