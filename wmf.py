
import wmfbase, time, mjpeg, cStringIO
from PIL import Image

def DecodeYuy2ToPilImage(buff, height, width, stride):
    print len(buff), height, width, stride
    out = Image.new("RGB", (width, height))
    outl = out.load()
    
    for lineNum in range(height):
        lineOffset = lineNum * stride
        for pxPairNum in range(width / 2):
            Y1 = buff[pxPairNum * 4 + lineOffset]
            Cb = buff[pxPairNum * 4 + lineOffset + 1]
            Y2 = buff[pxPairNum * 4 + lineOffset + 2]
            Cr = buff[pxPairNum * 4 + lineOffset + 3]

            #ITU-R BT.601 colour conversion
            R1 = (Y1 + 1.402 * (Cr - 128))
            G1 = (Y1 - 0.344 * (Cb - 128) - 0.714 * (Cr - 128))
            B1 = (Y1 + 1.772 * (Cb - 128))
            R2 = (Y2 + 1.402 * (Cr - 128))
            G2 = (Y2 - 0.344 * (Cb - 128) - 0.714 * (Cr - 128))
            B2 = (Y2 + 1.772 * (Cb - 128))

            outl[pxPairNum*2, lineNum] = tuple(map(int, (R1, G1, B1)))
            outl[pxPairNum*2+1, lineNum] = tuple(map(int, (R2, G2, B2)))
   
    return out

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

        #Decode MJPEG pixels into RGB
        if 'subtype' in frame and frame['subtype'] == "MFVideoFormat_MJPG":
            jpg = cStringIO.StringIO()
            parseJpeg = mjpeg.ParseJpeg()
            parseJpeg.InsertHuffmanTable(cStringIO.StringIO(frame['buff']), jpg)
            jpg.seek(0)
            im = Image.open(jpg)
            frame['pix'] = im

        if 'subtype' in frame and frame['subtype'] == "MFVideoFormat_YUY2":
            frame['pix'] = DecodeYuy2ToPilImage(frame['buff'], frame['height'], frame['width'], frame['stride'])
        
        return frame

    def GetMediaTypes(self):
        mediaTypes = self._mf.EnumerateMediaTypes(self._deviceId)
        return mediaTypes

    def SetMediaType(self, typeIndex):
        self._mf.SetMediaType(self._deviceId, typeIndex)

    def Stop(self):
        self._mf.StopCamera(self._deviceId)

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
    #cam0.SetMediaType(31)

    for j in range(2):
        for i in range(100):
            frame = cam0.GetFrame()
            print frame.keys(),
            if 'subtype' in frame: print frame['subtype'],
            if 'width' in frame: print frame['width'],
            if 'height' in frame: print frame['height'],
            print ""

            if 'pix' in frame and frame['pix'] is not None:
                frame['pix'].save("img{0}.jpg".format(i))

        print "Stop camera"
        cam0.Stop()

        time.sleep(5)

    
