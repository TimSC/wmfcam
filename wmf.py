
import wmfbase

class wmf:
    def __init__(self):
        self.mf = wmfbase.MediaFoundation()
        self.mf.Init()

    def __len__(self):
        deviceList = self.mf.ListDevices()
        return len(deviceList)

    

if __name__ == "__main__":
    wmfobj = wmf()
    print len(wmfobj)
