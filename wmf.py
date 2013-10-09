
import wmfbase, time, mjpeg, cStringIO
from PIL import Image

class wmfsource(object):
    def __init__(self, mf, deviceId):
        self.friendlyName = "Video source"
        self._deviceId = deviceId
        self._mf = mf
        
    def GetFrame(self):
        if not self._mf.IsCameraRunning(self._deviceId):
            self._mf.StartCamera(self._deviceId)
        frame = self._mf.ProcessSamples(self._deviceId)
        frame['pix'] = None

        #Decode pixels into RGB
        if 'subtype' in frame and frame['subtype'] == "MFVideoFormat_MJPG":
            jpg = cStringIO.StringIO()
            parseJpeg = mjpeg.ParseJpeg()
            parseJpeg.InsertHuffmanTable(cStringIO.StringIO(frame['buff']), jpg)
            jpg.seek(0)
            im = Image.open(jpg)
            frame['pix'] = im
        
        return frame

    def GetMediaTypes(self):
        mediaTypes = self._mf.EnumerateMediaTypes(self._deviceId)
        return mediaTypes

    def SetMediaType(self, typeIndex):
        self._mf.SetMediaType(self._deviceId, typeIndex)

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
    print "Number of video sources:", len(wmfobj)

    cam0 = wmfobj[0]

    print cam0.friendlyName
    print "Media types available:", len(cam0.GetMediaTypes())
    cam0.SetMediaType(31)

    for i in range(100):
        frame = cam0.GetFrame()
        print frame.keys(),
        if 'subtype' in frame: print frame['subtype'],
        if 'width' in frame: print frame['width'],
        if 'height' in frame: print frame['height'],
        print ""
        
