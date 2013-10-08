
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
		time.sleep(1.)
		mf.ProcessSamples()
    
    print "Deinit"
    mf.DeInit()
    
