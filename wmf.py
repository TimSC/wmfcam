
import wmfbase, time, mjpeg, cStringIO
from PIL import Image
import numpy as np

def FastDecodeYuy2ToPilImage(buff, height, width, stride):
    out = bytearray(height * width * 3)
    wmfbase.DecodeYuy2ToPilImage(buff, height, width, stride, out)
    return out

class wmfsource(object):
    def __init__(self, mf, deviceId):
        self.friendlyName = "Video source"
        self._deviceId = deviceId
        self._mf = mf
        
    def GetFrame(self):
        if not self._mf.IsCameraRunning(self._deviceId):
            self._mf.StartCamera(self._deviceId, 0)
        frame = self._mf.ProcessSamples(self._deviceId)
        frame['pix'] = None

        if 'subtype' in frame and frame['subtype'] == "MFVideoFormat_MJPG" and 'buff' in frame:
            #Decode MJPEG pixels to RGB
            jpg = cStringIO.StringIO()
            parseJpeg = mjpeg.ParseJpeg()
            parseJpeg.InsertHuffmanTable(cStringIO.StringIO(frame['buff']), jpg)
            jpg.seek(0)
            im = Image.open(jpg)
            im = im.convert("RGB")
            frame['pix'] = im.tostring()

        if 'subtype' in frame and frame['subtype'] == "MFVideoFormat_YUY2" and 'buff' in frame:
            #Decode YUY2 to RGB
            frame['pix'] = FastDecodeYuy2ToPilImage(frame['buff'], frame['height'], frame['width'], frame['stride'])
        
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

    cams = []
    cams.append(wmfobj[0])
    cams.append(wmfobj[1])
    li = [[] for cam in cams]
    statTime = 0.
    count = 0

    for cam in cams:
        print "Friendly name:", cam.friendlyName
        print "Device name:", cam._deviceId
        print "Media types available:", len(cam.GetMediaTypes())
        #cam.SetMediaType(31)

    for j in range(1):
        while 1:
            tiNow = time.time()
            for frameTimes, cam in zip(li, cams):
                frame = cam.GetFrame()
                if 'pix' not in frame: continue
                if frame['pix'] is None: continue

                #Estimate frame rate
                frameTimes.append(tiNow)
                while len(frameTimes) > 10:
                    frameTimes.pop(0)
                
                if 0:
                    print frame.keys(),
                    if 'subtype' in frame: print frame['subtype'],
                    if 'width' in frame: print frame['width'],
                    if 'height' in frame: print frame['height'],
                    print ""

                if 'pix' in frame and frame['pix'] is not None:
                    #print len(str(frame['pix']))
                    pilImg = Image.fromstring("RGB", (frame['width'], frame['height']), str(frame['pix']))
                    pilImg.save("img{0}.jpg".format(count))
                    count += 1

            if tiNow > statTime + 1.:
                for camNum, (frameTimes, cam) in enumerate(zip(li, cams)):
                    if len(frameTimes) > 2:
                        print "FR", camNum, len(frameTimes) / (frameTimes[-1] - frameTimes[0])
                statTime = tiNow

            time.sleep(0.01)

        for cam in cams:
            print "Stop camera"
            cam.Stop()

        time.sleep(5)

    
