
import hello_ext, time

if __name__ == "__main__":
    mf = hello_ext.MediaFoundation()

    print "Init"
    mf.Init()

    print "ListDevices"
    deviceList = mf.ListDevices()
    print deviceList

    for devNum in range(len(deviceList)):
        print "Enumerate Types", devNum
        mediaTypes = mf.EnumerateMediaTypes(deviceList[devNum][1])
        for tyCount, ty in enumerate(mediaTypes):
            print tyCount, ty

    for devNum in range(len(deviceList)):
        print "Set Media Type", devNum
        mediaIndex = 0
        mf.SetMediaType(deviceList[devNum][1], mediaIndex)

    for devNum in range(len(deviceList)):
        print "Starting", devNum
        mf.StartCamera(deviceList[devNum][1])

    startTime = time.time()
    while time.time() < startTime + 10.:
        for devNum in range(len(deviceList)):
            time.sleep(0.01)
	    ret = mf.ProcessSamples(deviceList[devNum][1])
	    if 'buff' in ret:
                print ret.keys(), len(ret['buff'])
                del ret['buff']
            else:
                print ret.keys()
            print ret
            
    print "Deinit"
    mf.DeInit()
    
