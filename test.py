
import hello_ext

if __name__ == "__main__":
    mf = hello_ext.MediaFoundation()

    print "Init"
    mf.Init()

    print "ListDevices"
    deviceList = mf.ListDevices()
    #print type(deviceList)
    #print dir(deviceList)
    #print type(deviceList[0])
    #print dir(deviceList[0])
    print deviceList[0]
    
    print "Deinit"
    mf.DeInit()
    
