
import hello_ext

if __name__ == "__main__":
    mf = hello_ext.MediaFoundation()

    print "Init"
    mf.Init()

    print "Deinit"
    mf.DeInit()
    