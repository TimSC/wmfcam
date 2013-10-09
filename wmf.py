
import wmfbase, time

class wmfsource(object):
    def __init__(self, mf, deviceId):
        self.friendlyName = "Video source"
        self._deviceId = deviceId
        self._mf = mf
        self._mf.StartCamera(self._deviceId)
        
    def GetFrame(self):
        frame = self._mf.ProcessSamples(self._deviceId)
        return frame

class wmf(object):
    def __init__(self):
        self._mf = wmfbase.MediaFoundation()
        self._mf.Init()

    def __len__(self):
        deviceList = self._mf.ListDevices()
        return len(deviceList)

    def __getitem__(self, key):
        deviceList = self._mf.ListDevices()
        selectedDeviceInfo = deviceList[key]
        
        vidsrc = wmfsource(self._mf, selectedDeviceInfo[1])
        vidsrc.friendlyName = selectedDeviceInfo[0]
        return vidsrc

if __name__ == "__main__":
    wmfobj = wmf()
    print "Number of video sources", len(wmfobj)

    cam0 = wmfobj[0]

    print cam0.friendlyName    

    for i in range(100):
        frame = cam0.GetFrame()
        print frame.keys()
