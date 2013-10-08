
import hello_ext, time

if __name__ == "__main__":
    mf = hello_ext.MediaFoundation()

    print "Init"
    mf.Init()

    print "ListDevices"
    deviceList = mf.ListDevices()
    print deviceList

    for devNum in range(len(deviceList)):
        print "Activate", devNum
        mf.ActivateDevice(devNum)

	while 1:
		time.sleep(0.01)
		ret = mf.ProcessSamples()
                print ret.keys(), len(ret['buff'])
    
    print "Deinit"
    mf.DeInit()
    
